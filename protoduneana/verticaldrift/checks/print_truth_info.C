void print_truth_info() {
  const char* filename = "example_ana_output.root";

  TFile* f = TFile::Open(filename);
  if (!f || f->IsZombie()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return;
  }

  // Navigate into the subdirectory "exampleana"
  TDirectory* dir = (TDirectory*)f->Get("exampleana");
  if (!dir) {
    std::cerr << "Error: Could not find subdirectory 'exampleana'" << std::endl;
    return;
  }
  dir->cd();

  // Load the truth tree from inside the directory
  TTree* tree = (TTree*)dir->Get("TruthTree");
  if (!tree) {
    std::cerr << "Error: Could not find TruthTree in exampleana" << std::endl;
    return;
  }

  // Variables
  int run, subrun, event;
  int pdg;
  float vx, vy, vz;
  float endx, endy, endz;
  float energy;
  std::string* endproc = nullptr;

  // Set branches
  tree->SetBranchAddress("run", &run);
  tree->SetBranchAddress("subrun", &subrun);
  tree->SetBranchAddress("event", &event);
  tree->SetBranchAddress("pdg", &pdg);
  tree->SetBranchAddress("vx", &vx);
  tree->SetBranchAddress("vy", &vy);
  tree->SetBranchAddress("vz", &vz);
  tree->SetBranchAddress("endx", &endx);
  tree->SetBranchAddress("endy", &endy);
  tree->SetBranchAddress("endz", &endz);
  tree->SetBranchAddress("e", &energy);
  tree->SetBranchAddress("endprocess", &endproc);

  Long64_t nentries = tree->GetEntries();
  int last_event = -1;

  for (Long64_t i = 0; i < nentries; ++i) {
    tree->GetEntry(i);

    if (event != last_event) {
      std::cout << "\n========================================" << std::endl;
      std::cout << "Event: " << event << " | Run: " << run << " | Subrun: " << subrun << std::endl;
      std::cout << "----------------------------------------" << std::endl;
      last_event = event;
    }

    std::cout << "  PDG: " << pdg
              << " | Start: (" << vx << ", " << vy << ", " << vz << ")"
              << " | End: (" << endx << ", " << endy << ", " << endz << ")"
              << " | Energy: " << energy << " MeV"
              << " | EndProc: " << (endproc ? *endproc : "n/a")
              << std::endl;
  }

  std::cout << "\nDone!" << std::endl;
}

