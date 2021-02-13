void checkNumberOfEvts(bool isMC = 0) {
  std::string mcOrDataStr;
  if (isMC) {
    mcOrDataStr = "MC";
  } else {
    mcOrDataStr = "Data";
  }

  std::vector<int> noEvents;
  for (unsigned int i = 0; i < 5; ++i) {
    TFile* infile = new TFile(Form("Data/ND_%s_summAll_resBin%d.root", mcOrDataStr.c_str(), i), "READ");
    TH1D* hAll = (TH1D*) infile->Get("RecoEnergyAll_ND");
    noEvents.push_back(hAll->Integral());
    //std::cout << hAll->Integral() << std::endl;
    infile->Close();
  }

  int sumEvts = 0.;
  for (auto no : noEvents) {
    sumEvts += no;
  }

  for (unsigned int i = 0; i < noEvents.size(); ++i) {
    std::cout << Form("\\item %s resBin%d: %d (%2.1f\\%%).", mcOrDataStr.c_str(), i, noEvents.at(i), (float)noEvents.at(i)*100./(float)sumEvts) << std::endl;
  }
}
