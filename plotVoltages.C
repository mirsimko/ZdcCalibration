
void plotVoltages()
{
  TFile *inf1 = new TFile("analysis/17037043/17037043_my_zdc_result_file.root");
  TFile *inf2 = new TFile("analysis/17037044/17037044_my_zdc_result_file.root");
  TFile *inf3 = new TFile("analysis/17037045/17037045_my_zdc_result_file.root");

  TCanvas *C1 = new TCanvas("C1", "east", 600, 400);

  TH1D *hEast1 = (TH1D*)inf1->Get("ZDC_ADC_east_sum");
  TH1D *hEast2 = (TH1D*)inf2->Get("ZDC_ADC_east_sum");
  TH1D *hEast3 = (TH1D*)inf3->Get("ZDC_ADC_east_sum");

  hEast2->SetLineColor(kRed);
  hEast3->SetLineColor(kBlue);

  hEast1->GetXaxis()->SetTitle("ADC sum east [-]");

  hEast1->GetYaxis()->SetTitle("N [-]");
  hEast1->GetYaxis()->SetTitleOffset(1.1);

  C1->cd();
  hEast1->Draw();
  hEast2->Draw("same");
  hEast3->Draw("same");

}
