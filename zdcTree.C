#define zdcTree_cxx
#include "zdcTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

void zdcTree::Loop()
{
  if (fChain == 0) return;
  //	Setup code goes here ***************************************************
  bool Output_rootfile = true;
  bool Output_datafile = true;
  bool Output_gif_file = true;
  bool Create_folder = true;
  //*******************************************************
  //*******************************************************
  int RunNumber = 17035115;
  //	char trgSetup[50] = {"production_15GeV_2014"};
  //	char trgSetup[20] = {"pedestal_rhicclock"};
  char trgSetup[20] = {"ZdcCalibration"};
  char typeEnergy[10]={"msimko"};
  //*******************************************************
  int RunYear=int(RunNumber/1000000)-1;
  //*******************************************************
  char root_file_path[200]={"/direct/star+u/msimko/ZDC/ZDC_Calibration"};

  char work_dir[200];
  sprintf(work_dir,"%s/run%d.%s.%s",root_file_path,RunYear,trgSetup,typeEnergy);

  char processFile[200];
  sprintf(processFile,"%s/histo/run_%d.histo.root",work_dir,RunNumber);

  //Create A Folder Under analysis/, specify folder name
  char folder_name[200];
  sprintf(folder_name,"%s/analysis/%d",work_dir,RunNumber);

  cout<<"******************************************************************************"<<endl;
  cout<<"work_dir    : "<<work_dir<<endl;
  cout<<"processFile : "<<processFile<<endl;
  cout<<"folder_name : "<<folder_name<<endl;
  cout<<"******************************************************************************"<<endl;
  //*******************************************************
  //*******************************************************
  char command_mkdir[200];
  sprintf(command_mkdir,"mkdir -p %s",folder_name);

  ofstream ofile;
  if(Output_datafile)
  {
    if(Create_folder) {cout<<"Will Create folder   : "<<folder_name<<endl;Create_folder=false;}
    system(command_mkdir); 
    char dfilename[200];
    sprintf(dfilename,"%s/analysis/%d/%d_gain_ratio.dat",work_dir,RunNumber,RunNumber);
    cout<<"Will Create datafile : "<<dfilename<<endl;
    ofile.open(dfilename,ios::out);
    if(!ofile) {cerr<<"Create data file failed !"<<endl; return;}
  }
  if(Output_rootfile)
  {
    if(Create_folder) {cout<<"Will Create folder   : "<<folder_name<<endl;Create_folder=false;}
    system(command_mkdir); 
    char tfilename[200];
    sprintf(tfilename,"%s/analysis/%d/%d_my_zdc_result_file.root",work_dir,RunNumber,RunNumber);
    cout<<"Will Create rootfile : "<<tfilename<<endl;
    TFile *f = new TFile(tfilename,"RECREATE");
  }

  TCanvas *c;
  if(Output_gif_file)
  {
    if(Create_folder) {cout<<"Will Create folder   : "<<folder_name<<endl;Create_folder=false;}
    cout<<"Will Create giffile  : "<<endl;
    system(command_mkdir); 
    gStyle->SetPalette(1,0);
    gStyle->SetOptLogz(1);
    gStyle->SetOptDate(0);
    c = new TCanvas("c","c",800,600);
  }

  char savename_east_att[200];
  char savename_east_sum[200];
  char savename_east_1[200];
  char savename_east_2[200];
  char savename_east_3[200];

  char savename_west_att[200];
  char savename_west_sum[200];
  char savename_west_1[200];
  char savename_west_2[200];
  char savename_west_3[200];

  char savename_gain_east[200];
  char savename_gain_west[200];

  char savename_east_sum_diff[200];
  char savename_west_sum_diff[200];

  TH1D *east_att = new TH1D("ZDC_ADC_east_att","ZDC_ADC_east_att",400,0,4000);// attenuated
  TH1D *east_sum = new TH1D("ZDC_ADC_east_sum","ZDC_ADC_east_sum",100,0,400); // close view of the single neutron peak
  TH1D *east_1 = new TH1D("ZDC_ADC_east_1","ZDC_ADC_east_1",400,0,4000);
  TH1D *east_2 = new TH1D("ZDC_ADC_east_2","ZDC_ADC_east_2",400,0,4000);
  TH1D *east_3 = new TH1D("ZDC_ADC_east_3","ZDC_ADC_east_3",400,0,4000);

  TH1D *west_att = new TH1D("ZDC_ADC_west_att","ZDC_ADC_west_att",400,0,4000);
  TH1D *west_sum = new TH1D("ZDC_ADC_west_sum","ZDC_ADC_west_sum",100,0,400); // close view of the single neutron peak
  TH1D *west_1 = new TH1D("ZDC_ADC_west_1","ZDC_ADC_west_1",400,0,4000);
  TH1D *west_2 = new TH1D("ZDC_ADC_west_2","ZDC_ADC_west_2",400,0,4000);
  TH1D *west_3 = new TH1D("ZDC_ADC_west_3","ZDC_ADC_west_3",400,0,4000);

  TH1D *gain_east = new TH1D("ratio_east","ratio_east",3,0,3);
  TH1D *gain_west = new TH1D("ratio_west","ratio_east",3,0,3);

  TH2D *east_sum_diff = new TH2D("east_sum_diff","east_sum_diff",4000,0,4000,4000,0,4000);
  east_sum_diff->GetXaxis()->SetTitle("ZDC_ADC_Sum:Tower1+Tower2+Tower3");
  east_sum_diff->GetYaxis()->SetTitle("ZDC_Sum_ADC");
  TH2D *west_sum_diff = new TH2D("west_sum_diff","west_sum_diff",4000,0,4000,4000,0,4000);
  west_sum_diff->GetXaxis()->SetTitle("ZDC_ADC_Sum:Tower1+Tower2+Tower3");
  west_sum_diff->GetYaxis()->SetTitle("ZDC_Sum_ADC");

  int east_count_att=0;
  int east_count_sum=0;
  int east_count_1=0;
  int east_count_2=0;
  int east_count_3=0;

  int west_count_att=0;
  int west_count_sum=0;
  int west_count_1=0;
  int west_count_2=0;
  int west_count_3=0;

  //	Setup code ends here ***************************************************
  printf("\033[?25l");
  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for(Long64_t jentry=0; jentry<nentries;jentry++)
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    //if(Cut(ientry) < 0) continue;
    //Analysis code goes here ***************************************************
    if(ientry%1000==0)
    {
      cout<<"Processing ... ";
      cout<<setiosflags(ios::fixed)<<setprecision(2);
      cout<<double(ientry)/double(nentries)*100<<"%"<<"\r";
      cout<<resetiosflags(ios::fixed);
    }

    // TOF multiplicity cut
    if(tof_multiplicity >= mTofCut)
      continue;

    east_att->Fill(zdc_ADC_EastSum_Attenuated);
    east_sum->Fill(zdc_ADC_EastSum);
    east_1->Fill(zdc_ADC_EastTow1);
    east_2->Fill(zdc_ADC_EastTow2);
    east_3->Fill(zdc_ADC_EastTow3);

    west_att->Fill(zdc_ADC_WestSum_Attenuated);
    west_sum->Fill(zdc_ADC_WestSum);
    west_1->Fill(zdc_ADC_WestTow1);
    west_2->Fill(zdc_ADC_WestTow2);
    west_3->Fill(zdc_ADC_WestTow3);

    east_count_att += zdc_ADC_EastSum_Attenuated;
    east_count_sum += zdc_ADC_EastSum;
    east_count_1 += zdc_ADC_EastTow1;
    east_count_2 += zdc_ADC_EastTow2;
    east_count_3 += zdc_ADC_EastTow3;

    west_count_att += zdc_ADC_WestSum_Attenuated;
    west_count_sum += zdc_ADC_WestSum;
    west_count_1 += zdc_ADC_WestTow1;
    west_count_2 += zdc_ADC_WestTow2;
    west_count_3 += zdc_ADC_WestTow3;

    east_sum_diff->Fill(zdc_ADC_EastTow1+zdc_ADC_EastTow2+zdc_ADC_EastTow3,zdc_ADC_EastSum);
    west_sum_diff->Fill(zdc_ADC_WestTow1+zdc_ADC_WestTow2+zdc_ADC_WestTow3,zdc_ADC_WestSum);
    //Analysis code ends here ***************************************************
  }
  printf("\033[?25h");
  // Wrap-up code goes here ****************************************************
  gain_east->SetFillColor(38);
  gain_west->SetFillColor(38);

  gain_east->SetBinContent(1,east_count_1);
  gain_east->SetBinContent(2,east_count_2);
  gain_east->SetBinContent(3,east_count_3);
  gain_west->SetBinContent(1,west_count_1);
  gain_west->SetBinContent(2,west_count_2);
  gain_west->SetBinContent(3,west_count_3);

  if(Output_rootfile)
  {
    east_att->Write();
    east_sum->Write();
    east_1->Write();
    east_2->Write();
    east_3->Write();
    west_att->Write();
    west_sum->Write();
    west_1->Write();
    west_2->Write();
    west_3->Write();
    gain_east->Write();
    gain_west->Write();
    east_sum_diff->Write();
    west_sum_diff->Write();
  }
  if(Output_gif_file)
  {
    sprintf(savename_east_att,"%s/analysis/%d/%d_east_att.gif",work_dir,RunNumber,RunNumber);
    sprintf(savename_east_sum,"%s/analysis/%d/%d_east_sum.gif",work_dir,RunNumber,RunNumber);
    sprintf(savename_east_1,  "%s/analysis/%d/%d_east_1.gif",work_dir,RunNumber,RunNumber);
    sprintf(savename_east_2,  "%s/analysis/%d/%d_east_2.gif",work_dir,RunNumber,RunNumber);
    sprintf(savename_east_3,  "%s/analysis/%d/%d_east_3.gif",work_dir,RunNumber,RunNumber);

    sprintf(savename_west_att,"%s/analysis/%d/%d_west_att.gif",work_dir,RunNumber,RunNumber);
    sprintf(savename_west_sum,"%s/analysis/%d/%d_west_sum.gif",work_dir,RunNumber,RunNumber);
    sprintf(savename_west_1,  "%s/analysis/%d/%d_west_1.gif",work_dir,RunNumber,RunNumber);
    sprintf(savename_west_2,  "%s/analysis/%d/%d_west_2.gif",work_dir,RunNumber,RunNumber);
    sprintf(savename_west_3,  "%s/analysis/%d/%d_west_3.gif",work_dir,RunNumber,RunNumber);

    sprintf(savename_gain_east,"%s/analysis/%d/%d_gain_east.gif",work_dir,RunNumber,RunNumber);
    sprintf(savename_gain_west,"%s/analysis/%d/%d_gain_west.gif",work_dir,RunNumber,RunNumber);

    sprintf(savename_east_sum_diff,"%s/analysis/%d/%d_east_sum_diff.gif",work_dir,RunNumber,RunNumber);
    sprintf(savename_west_sum_diff,"%s/analysis/%d/%d_west_sum_diff.gif",work_dir,RunNumber,RunNumber);

    c->SetLogy(1);
    east_att->Draw();	c->SaveAs(savename_east_att);
    east_sum->Draw();	c->SaveAs(savename_east_sum);
    east_1->Draw();		c->SaveAs(savename_east_1);
    east_2->Draw();		c->SaveAs(savename_east_2);
    east_3->Draw();		c->SaveAs(savename_east_3);

    west_att->Draw();	c->SaveAs(savename_west_att);
    west_sum->Draw();	c->SaveAs(savename_west_sum);
    west_1->Draw();		c->SaveAs(savename_west_1);
    west_2->Draw();		c->SaveAs(savename_west_2);
    west_3->Draw();		c->SaveAs(savename_west_3);

    c->SetLogy(0);
    gain_east->Draw();	c->SaveAs(savename_gain_east);
    gain_west->Draw();	c->SaveAs(savename_gain_west);

    east_sum_diff->Draw("col");	c->SaveAs(savename_east_sum_diff);
    west_sum_diff->Draw("col");	c->SaveAs(savename_west_sum_diff);
  }

  if(Output_datafile)
  {
    ofile<<east_count_1<<'\t'<<east_count_2<<'\t'<<east_count_3<<'\t'<<east_count_sum<<'\t'<<east_count_att<<endl;
    ofile<<west_count_1<<'\t'<<west_count_2<<'\t'<<west_count_3<<'\t'<<west_count_sum<<'\t'<<west_count_att<<endl;
    ofile<<endl;
    ofile<<"east_1 : east_2 : east_3 : east_sum : east_att"<<endl;
    ofile<<"west_1 : west_2 : west_3 : west_sum : west_att"<<endl;
    ofile<<endl;
    ofile<<endl;
    ofile<<"**************************************************"<<endl;
    ofile<<"east_count_1  ="<<east_count_1<<"\tratio="<<double(east_count_1)/double(east_count_sum)<<endl;
    ofile<<"east_count_2  ="<<east_count_2<<"\tratio="<<double(east_count_2)/double(east_count_sum)<<endl;
    ofile<<"east_count_3  ="<<east_count_3<<"\tratio="<<double(east_count_3)/double(east_count_sum)<<endl;
    ofile<<"east_count_sum="<<east_count_sum<<endl;
    ofile<<"east_count_att="<<east_count_att<<endl;

    ofile<<"**************************************************"<<endl;
    ofile<<"west_count_1  ="<<west_count_1<<"\tratio="<<double(west_count_1)/double(west_count_sum)<<endl;
    ofile<<"west_count_2  ="<<west_count_2<<"\tratio="<<double(west_count_2)/double(west_count_sum)<<endl;
    ofile<<"west_count_3  ="<<west_count_3<<"\tratio="<<double(west_count_3)/double(west_count_sum)<<endl;
    ofile<<"west_count_sum="<<west_count_sum<<endl;
    ofile<<"west_count_att="<<west_count_att<<endl;
    ofile<<"**************************************************"<<endl;
    double ratio_east_1 = double(east_count_1)/double(east_count_3);
    double ratio_east_2 = double(east_count_2)/double(east_count_3);
    double ratio_west_1 = double(west_count_1)/double(west_count_3);
    double ratio_west_2 = double(west_count_2)/double(west_count_3);
    ofile<<setiosflags(ios::fixed)<<setprecision(2)<<endl;
    ofile<<"East:"<<endl;
    ofile<<"\tRatio 1:2:3 =  "<<ratio_east_1<<" : "<<ratio_east_2<<" : 1.00"<<endl;
    ofile<<"West:"<<endl;
    ofile<<"\tRatio 1:2:3 =  "<<ratio_west_1<<" : "<<ratio_west_2<<" : 1.00"<<endl;
    ofile<<resetiosflags(ios::fixed)<<endl;
  }

  cout<<"**************************************************"<<endl;
  cout<<"east_count_1  ="<<east_count_1<<"\tratio="<<double(east_count_1)/double(east_count_sum)<<endl;
  cout<<"east_count_2  ="<<east_count_2<<"\tratio="<<double(east_count_2)/double(east_count_sum)<<endl;
  cout<<"east_count_3  ="<<east_count_3<<"\tratio="<<double(east_count_3)/double(east_count_sum)<<endl;
  cout<<"east_count_sum="<<east_count_sum<<endl;
  cout<<"east_count_att="<<east_count_att<<endl;

  cout<<"**************************************************"<<endl;
  cout<<"west_count_1  ="<<west_count_1<<"\tratio="<<double(west_count_1)/double(west_count_sum)<<endl;
  cout<<"west_count_2  ="<<west_count_2<<"\tratio="<<double(west_count_2)/double(west_count_sum)<<endl;
  cout<<"west_count_3  ="<<west_count_3<<"\tratio="<<double(west_count_3)/double(west_count_sum)<<endl;
  cout<<"west_count_sum="<<west_count_sum<<endl;
  cout<<"west_count_att="<<west_count_att<<endl;
  cout<<"**************************************************"<<endl;
  double ratio_east_1 = double(east_count_1)/double(east_count_3);
  double ratio_east_2 = double(east_count_2)/double(east_count_3);
  double ratio_west_1 = double(west_count_1)/double(west_count_3);
  double ratio_west_2 = double(west_count_2)/double(west_count_3);
  cout<<setiosflags(ios::fixed)<<setprecision(2)<<endl;
  cout<<"East:"<<endl;
  cout<<"\tRatio 1:2:3 =  "<<ratio_east_1<<" : "<<ratio_east_2<<" : 1.00"<<endl;
  cout<<"West:"<<endl;
  cout<<"\tRatio 1:2:3 =  "<<ratio_west_1<<" : "<<ratio_west_2<<" : 1.00"<<endl;
  cout<<resetiosflags(ios::fixed)<<endl;
  // Wrap-up code ends here ****************************************************
}
