void interactions(unsigned int resbinNo, bool logscale = false, double maxE = 20.) {
	TFile* infile = new TFile(Form("Data/ND_MC_summAll_wBWeight_Interactions_resBin%d.root", resbinNo), "READ");
	TH1D* QEComp = (TH1D*) infile->Get("TrueEnergyQEMode_ND");
	TH1D* RESComp = (TH1D*) infile->Get("TrueEnergyRESMode_ND");
	TH1D* DISComp = (TH1D*) infile->Get("TrueEnergyDISMode_ND");
	TH1D* CPPComp = (TH1D*) infile->Get("TrueEnergyCPPMode_ND");
	TH1D* AllComp = (TH1D*) infile->Get("TrueEnergyTrueCCFidEventsAll_ND");

	QEComp->Sumw2();
	RESComp->Sumw2();
	DISComp->Sumw2();
	CPPComp->Sumw2();

	QEComp->Divide(AllComp);
	RESComp->Divide(AllComp);
	DISComp->Divide(AllComp);
	CPPComp->Divide(AllComp);

	QEComp ->SetLineColor(kRed);
	RESComp->SetLineColor(kOrange);
	DISComp->SetLineColor(kGreen);
	CPPComp->SetLineColor(kBlue);

	gStyle->SetOptStat(0);
	TCanvas* c = new TCanvas("c", "c", 1000, 1000);
	//TPad* pL = new TPad("pL", "pL", 0, 0, 0.8, 1);
	//TPad* pR = new TPad("pR", "pR", 0.8, 0, 1, 1);
	//pL->Draw();
	//pR->Draw();

	//pL->cd();

	double ymin = 0;
	std::string logStr = "";
	if (logscale) {
		c->SetLogy();
		ymin = 1E-3;
		logStr = "_log";
	}

	QEComp->GetYaxis()->SetRangeUser(ymin, 1.2);
	QEComp->GetXaxis()->SetRangeUser(0, maxE);
	QEComp->SetTitle(Form("Resolution Bin %d", resbinNo));
	QEComp->GetXaxis()->SetTitle("True Energy (GeV)");
	QEComp->GetYaxis()->SetTitle("Fraction");
	QEComp->GetYaxis()->CenterTitle();
	QEComp->GetXaxis()->CenterTitle();
	
	QEComp ->Draw("");
	RESComp->Draw("SAME");
	DISComp->Draw("SAME");
	CPPComp->Draw("SAME");
	
	/*
	QEComp->Draw("HIST");
	RESComp->Draw("HIST SAME");
	DISComp->Draw("HIST SAME");
	CPPComp->Draw("HIST SAME");
	*/
	
	TLine* line = new TLine(0, 1, maxE, 1);
	line->SetLineWidth(2);
	line->SetLineStyle(kDashed);
	line->Draw();

	//pR->cd();
	TLegend* leg = new TLegend(0.7, 0.68, 0.85, 0.82);
	leg->SetTextSize(0.03);
	leg->AddEntry(QEComp, "QE", "L");
	leg->AddEntry(RESComp, "RES", "L");
	leg->AddEntry(DISComp, "DIS", "L");
	leg->AddEntry(CPPComp, "CPP", "L");
	leg->SetBorderSize(0);
	leg->Draw();

	c->SaveAs(Form("interactions_resBin%d%s.pdf", resbinNo, logStr.c_str()));
}
