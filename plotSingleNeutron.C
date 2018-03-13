#include <string>
// NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
// 1  Constant     7.11954e+01   1.92490e+01   6.98087e-03  -1.45442e-05
// 2  BgConstant   1.91250e+03   3.33039e+02   8.66676e-02   1.43172e-06
// 3  BgSlope      2.24099e-02   2.98008e-03   4.67199e-07  -3.43983e-02
// 4  Yield        1.09016e+02   1.45410e+01   2.37760e-02   2.10045e-06
// 5  Mean         9.44266e+01   1.32988e+00   2.91330e-03   9.60399e-06
// 6  sigma        9.80875e+00   1.28593e+00   2.11360e-03   1.01395e-04


void plotSingleNeutron()
{
  std::string runNumber = "19071065";
  TFile *inf1 = new TFile( ("analysis/" + runNumber + "/" + runNumber + "_my_zdc_result_file.root").data() );

  TCanvas *C1 = new TCanvas("C1", "east", 600, 400);
  TCanvas *C2 = new TCanvas("C2", "west", 600, 400);

  TH1D *hEast = (TH1D*)inf1->Get("ZDC_ADC_east_sum");
  TH1D *hWest = (TH1D*)inf1->Get("ZDC_ADC_west_sum");

  TF1 *eastF = new TF1("eastF", "[0] + ([1])*(TMath::Exp(-[2]*x)) + ([3])*(TMath::Gaus(x,[4],[5],1)) + [6]*TMath::Gaus(x,2.*[4],[7],1)",50,400);
  TF1 *westF = new TF1("westF", "[0] + ([1])*(TMath::Exp(-[2]*x)) + ([3])*(TMath::Gaus(x,[4],[5],1)) + [6]*TMath::Gaus(x,2.*[4],[7],1)",50,400);

  //eastF->SetParameters( 7.11954e+01, 1.91250e+03 , 2.24099e-02, 14,  9.44266e+01 , 9.80875e+00 );
  eastF->SetParameters(  -3500, 3500, 0.00044, 15000, 80, 9.80875e+00, 5000, 10 );
  eastF->SetParName(0,"Constant");
  eastF->SetParName(1,"BgConstant");
  eastF->SetParName(2,"BgSlope");
  eastF->SetParName(3,"Yield Single");
  eastF->SetParName(4,"Mean");
  eastF->SetParName(5,"sigma Single");
  eastF->SetParName(6,"Yield Double");
  eastF->SetParName(7,"sigma Double");

  westF->SetParameters( -3300, 3600, 0.00001, 9000, 90 , 9.80875e+00 ,2200, 10);
  //westF->SetParameters( 7.11954e+01, 1.91250e+03 , 2.24099e-02, 14,  110 , 9.80875e+00 );
  westF->SetParName(0,"Constant");
  westF->SetParName(1,"BgConstant");
  westF->SetParName(2,"BgSlope");
  westF->SetParName(3,"Yield");
  westF->SetParName(4,"Mean");
  westF->SetParName(5,"sigma");
  westF->SetParName(6,"Yield Double");
  westF->SetParName(7,"sigma Double");

  hEast->Fit("eastF", "","", 50, 330);
  hWest->Fit("westF", "","", 60, 330);
  // hEast->SetAxisRange(50,180,"X");
  // hWest->SetAxisRange(50,180,"X");

  hEast->GetXaxis()->SetTitle("ADC sum east [-]");
  hWest->GetXaxis()->SetTitle("ADC sum west [-]");

  hEast->GetYaxis()->SetTitle("N [-]");
  hEast->GetYaxis()->SetTitleOffset(1.1);
  hWest->GetYaxis()->SetTitle("N [-]");
  hWest->GetYaxis()->SetTitleOffset(1.1);

  C1->cd();
  gStyle->SetOptFit(1111);
  hEast->Draw();

  C2->cd();
  gStyle->SetOptFit(1111);
  hWest->Draw();

  std::string eastFileName = "analysis/" + runNumber + "/snp" + runNumber + "east";
  C1->SaveAs( (eastFileName + ".pdf" ).data() );
  C1->SaveAs( (eastFileName + ".png" ).data() );
  C1->SaveAs( (eastFileName + ".root").data() );

  std::string westFileName = "analysis/" + runNumber + "/snp" + runNumber + "west";
  C2->SaveAs( (westFileName + ".pdf" ).data() );
  C2->SaveAs( (westFileName + ".png" ).data() );
  C2->SaveAs( (westFileName + ".root").data() );
}
