//////////////////////////////////////////////////////////
//                ZDC tree class                        //
// Class for analyzing ZDC tree                         //
//                                                      //
// maintainer Miroslav Simko (msimko@bnl.gov)           //
//////////////////////////////////////////////////////////
//

#ifndef zdcTree_h
#define zdcTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <climits>
#include <limits>
#include <iostream>

using namespace std;
//#include "zdcTree_Self_Define.h"


class zdcTree {
  public :
    TTree          *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t           fCurrent; //!current Tree number in a TChain

    int mTofCut;              // TOF cut // msimko

    // Declaration of leaf types
    UShort_t        zdc_ADC_EastSum_Attenuated;
    UShort_t        zdc_ADC_EastSum;
    UShort_t        zdc_ADC_EastTow1;
    UShort_t        zdc_ADC_EastTow2;
    UShort_t        zdc_ADC_EastTow3;
    UShort_t        zdc_ADC_WestSum_Attenuated;
    UShort_t        zdc_ADC_WestSum;
    UShort_t        zdc_ADC_WestTow1;
    UShort_t        zdc_ADC_WestTow2;
    UShort_t        zdc_ADC_WestTow3;
    UShort_t        zdc_TDC_EastSum;
    UShort_t        zdc_TDC_EastTow1;
    UShort_t        zdc_TDC_EastTow2;
    UShort_t        zdc_TDC_EastTow3;
    UShort_t        zdc_TDC_WestSum;
    UShort_t        zdc_TDC_WestTow1;
    UShort_t        zdc_TDC_WestTow2;
    UShort_t        zdc_TDC_WestTow3;
    UShort_t        zdc_ADC_EWSum;
    UShort_t        tof_multiplicity;
    UShort_t        bbc_ADC_EastSum_SmallTile;
    UShort_t        bbc_ADC_EastSum_LargeTile;
    UShort_t        bbc_ADC_WestSum_SmallTile;
    UShort_t        bbc_ADC_WestSum_LargeTile;

    // List of branches
    TBranch        *b_zdc_ADC_EastSum_Attenuated;   //!
    TBranch        *b_zdc_ADC_EastSum;   //!
    TBranch        *b_zdc_ADC_EastTow1;   //!
    TBranch        *b_zdc_ADC_EastTow2;   //!
    TBranch        *b_zdc_ADC_EastTow3;   //!
    TBranch        *b_zdc_ADC_WestSum_Attenuated;   //!
    TBranch        *b_zdc_ADC_WestSum;   //!
    TBranch        *b_zdc_ADC_WestTow1;   //!
    TBranch        *b_zdc_ADC_WestTow2;   //!
    TBranch        *b_zdc_ADC_WestTow3;   //!
    TBranch        *b_zdc_TDC_EastSum;   //!
    TBranch        *b_zdc_TDC_EastTow1;   //!
    TBranch        *b_zdc_TDC_EastTow2;   //!
    TBranch        *b_zdc_TDC_EastTow3;   //!
    TBranch        *b_zdc_TDC_WestSum;   //!
    TBranch        *b_zdc_TDC_WestTow1;   //!
    TBranch        *b_zdc_TDC_WestTow2;   //!
    TBranch        *b_zdc_TDC_WestTow3;   //!
    TBranch        *b_zdc_ADC_EWSum;   //!
    TBranch        *b_tof_multiplicity;   //!
    TBranch        *b_bbc_ADC_EastSum_SmallTile;   //!
    TBranch        *b_bbc_ADC_EastSum_LargeTile;   //!
    TBranch        *b_bbc_ADC_WestSum_SmallTile;   //!
    TBranch        *b_bbc_ADC_WestSum_LargeTile;   //!
    int mRunNumber;

    zdcTree(int RunNumber = 0, TTree *tree=0, int tofCut = std::numeric_limits<int>::max());
    virtual ~zdcTree();
    virtual Int_t    Cut(Long64_t entry);
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Loop();
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef zdcTree_cxx
zdcTree::zdcTree(int runNumber, TTree *tree, int tofCut):
  mTofCut(tofCut), mRunNumber(runNumber)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.

  if (tree == 0) {
    //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/star/u/xyf/protected_lfspectra/ZDC_Calibration/run13.ZdcPolarimetry.pp500/histo/run_14142119.histo.root");//xuyifei
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(Form("/direct/star+u/msimko/ZDC/ZDC_Calibration/run18.ZdcCalibration.msimko/histo/run_%d.histo.root", mRunNumber));
    if (!f) {
      //f = new TFile("/star/u/xyf/protected_lfspectra/ZDC_Calibration/run13.ZdcPolarimetry.pp500/histo/run_14142119.histo.root");// xuyifei
      f = new TFile(Form("/direct/star+u/msimko/ZDC/ZDC_Calibration/run18.ZdcCalibration.msimko/histo/run_%d.histo.root", mRunNumber));
    }
    tree = (TTree*)gDirectory->Get("zdcTree");

  } // if (tree == 0)
  Init(tree);
}

zdcTree::~zdcTree()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t zdcTree::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t zdcTree::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void zdcTree::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("zdc_ADC_EastSum_Attenuated", &zdc_ADC_EastSum_Attenuated, &b_zdc_ADC_EastSum_Attenuated);
  fChain->SetBranchAddress("zdc_ADC_EastSum", &zdc_ADC_EastSum, &b_zdc_ADC_EastSum);
  fChain->SetBranchAddress("zdc_ADC_EastTow1", &zdc_ADC_EastTow1, &b_zdc_ADC_EastTow1);
  fChain->SetBranchAddress("zdc_ADC_EastTow2", &zdc_ADC_EastTow2, &b_zdc_ADC_EastTow2);
  fChain->SetBranchAddress("zdc_ADC_EastTow3", &zdc_ADC_EastTow3, &b_zdc_ADC_EastTow3);
  fChain->SetBranchAddress("zdc_ADC_WestSum_Attenuated", &zdc_ADC_WestSum_Attenuated, &b_zdc_ADC_WestSum_Attenuated);
  fChain->SetBranchAddress("zdc_ADC_WestSum", &zdc_ADC_WestSum, &b_zdc_ADC_WestSum);
  fChain->SetBranchAddress("zdc_ADC_WestTow1", &zdc_ADC_WestTow1, &b_zdc_ADC_WestTow1);
  fChain->SetBranchAddress("zdc_ADC_WestTow2", &zdc_ADC_WestTow2, &b_zdc_ADC_WestTow2);
  fChain->SetBranchAddress("zdc_ADC_WestTow3", &zdc_ADC_WestTow3, &b_zdc_ADC_WestTow3);
  fChain->SetBranchAddress("zdc_TDC_EastSum", &zdc_TDC_EastSum, &b_zdc_TDC_EastSum);
  fChain->SetBranchAddress("zdc_TDC_EastTow1", &zdc_TDC_EastTow1, &b_zdc_TDC_EastTow1);
  fChain->SetBranchAddress("zdc_TDC_EastTow2", &zdc_TDC_EastTow2, &b_zdc_TDC_EastTow2);
  fChain->SetBranchAddress("zdc_TDC_EastTow3", &zdc_TDC_EastTow3, &b_zdc_TDC_EastTow3);
  fChain->SetBranchAddress("zdc_TDC_WestSum", &zdc_TDC_WestSum, &b_zdc_TDC_WestSum);
  fChain->SetBranchAddress("zdc_TDC_WestTow1", &zdc_TDC_WestTow1, &b_zdc_TDC_WestTow1);
  fChain->SetBranchAddress("zdc_TDC_WestTow2", &zdc_TDC_WestTow2, &b_zdc_TDC_WestTow2);
  fChain->SetBranchAddress("zdc_TDC_WestTow3", &zdc_TDC_WestTow3, &b_zdc_TDC_WestTow3);
  fChain->SetBranchAddress("zdc_ADC_EWSum", &zdc_ADC_EWSum, &b_zdc_ADC_EWSum);
  fChain->SetBranchAddress("tof_multiplicity", &tof_multiplicity, &b_tof_multiplicity);
  fChain->SetBranchAddress("bbc_ADC_EastSum_SmallTile", &bbc_ADC_EastSum_SmallTile, &b_bbc_ADC_EastSum_SmallTile);
  fChain->SetBranchAddress("bbc_ADC_EastSum_LargeTile", &bbc_ADC_EastSum_LargeTile, &b_bbc_ADC_EastSum_LargeTile);
  fChain->SetBranchAddress("bbc_ADC_WestSum_SmallTile", &bbc_ADC_WestSum_SmallTile, &b_bbc_ADC_WestSum_SmallTile);
  fChain->SetBranchAddress("bbc_ADC_WestSum_LargeTile", &bbc_ADC_WestSum_LargeTile, &b_bbc_ADC_WestSum_LargeTile);
  Notify();
}

Bool_t zdcTree::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void zdcTree::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t zdcTree::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef zdcTree_cxx
