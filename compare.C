TH1D* compare(unsigned int resbinNo, double maxElimit = 200) {
  TFile* mcfile = new TFile(Form("Data/ND_MC_summAll_resBin%d.root", resbinNo), "READ");
  TFile* datafile = new TFile(Form("Data/ND_Data_summAll_resBin%d.root", resbinNo), "READ");

  TH1D* recoE_CC_NuMu_MC = (TH1D*) mcfile->Get("RecoEnergyAll_ND");
  TH1D* recoE_CC_NuMu_Data = (TH1D*) datafile->Get("RecoEnergyAll_ND");

  TH1D* h_pot_mc = (TH1D*) mcfile->Get("hTotalPot");
  TH1D* h_pot_data = (TH1D*) datafile->Get("hTotalPot");

  double pot_mc = h_pot_mc->Integral();
  double pot_data = h_pot_data->Integral();

  gStyle->SetOptStat(0);
  TCanvas* cnumu = new TCanvas("c", "c", 1200, 1000);
  auto *p2= new TPad("p2", "p3", 0., 0., 1., 0.2); 
  p2->Draw();
  p2->SetTopMargin(0.04);
  p2->SetBottomMargin(0.2);
  //p2->SetLogx();
  p2->SetGrid();


  auto *p1 = new TPad("p1", "p1", 0., 0.2, 1., 1.);
  p1->SetBottomMargin(0.1);
  p1->Draw();
  p1->cd();
  //p1->SetGrid();
  //p1->SetLogx();
  //p1->SetLogy();


  recoE_CC_NuMu_MC->Scale(1./pot_mc);
  recoE_CC_NuMu_Data->Scale(1./pot_data);

  recoE_CC_NuMu_MC->SetLineColor(kRed);
  recoE_CC_NuMu_Data->SetLineColor(kBlue);
  recoE_CC_NuMu_MC->SetTitle(Form("Run 11 - ND RecoE Data/MC (resBin%d)", resbinNo));
  recoE_CC_NuMu_MC->GetXaxis()->SetTitle("RecoE (GeV)");
  recoE_CC_NuMu_MC->GetXaxis()->CenterTitle();
  recoE_CC_NuMu_MC->Draw();
  double maxY = recoE_CC_NuMu_MC->GetMaximum() * 1.2;
  recoE_CC_NuMu_MC->GetYaxis()->SetRangeUser(0, maxY);
  recoE_CC_NuMu_MC->GetXaxis()->SetRangeUser(0, maxElimit);
  recoE_CC_NuMu_Data->Draw("SAME");
  TLegend* leg = new TLegend(0.55, 0.55, 0.7, 0.7);
  leg->AddEntry(recoE_CC_NuMu_MC, "MC", "L");
  leg->AddEntry(recoE_CC_NuMu_Data, "Data", "L");
  leg->SetBorderSize(0);
  leg->Draw();
  
  auto recoE_CC_NuMu_Ratio = (TH1D*) recoE_CC_NuMu_Data->Clone("ratio");
  recoE_CC_NuMu_Ratio->Sumw2();
  recoE_CC_NuMu_Ratio->Divide(recoE_CC_NuMu_MC);
  p2->cd();
  //p2->SetLogy();
  recoE_CC_NuMu_Ratio->SetTitle("");
  recoE_CC_NuMu_Ratio->Draw();
  TLine* line = new TLine(0, 1, maxElimit, 1);
  line->SetLineColor(kRed);
  line->Draw();
  recoE_CC_NuMu_Ratio->GetXaxis()->SetLabelSize(0.13);
  recoE_CC_NuMu_Ratio->GetYaxis()->SetLabelSize(0.13);
  recoE_CC_NuMu_Ratio->GetYaxis()->SetNdivisions(503);
  recoE_CC_NuMu_Ratio->GetXaxis()->SetRangeUser(0, maxElimit);
  recoE_CC_NuMu_Ratio->GetYaxis()->SetRangeUser(0.8, 1.2);
  std::string isZoom;
  if (maxElimit == 20) {
    isZoom = "zoomed";
  } else {
    isZoom = "unzoomed";
  }
  cnumu->SaveAs(Form("Plots/compare_resbin%d.%s.pdf", resbinNo, isZoom.c_str()));

  return recoE_CC_NuMu_Ratio;
}

void OverlayRatio() {
  auto hRatioResBin0 = compare(0, 20);
  auto hRatioResBin1 = compare(1, 20);
  auto hRatioResBin2 = compare(2, 20);
  auto hRatioResBin3 = compare(3, 20);
  auto hRatioResBin4 = compare(4, 20);

  TCanvas* c = new TCanvas
}
