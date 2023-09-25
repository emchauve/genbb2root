
void energy_spectrum (const char *root_filename, const int energy_nbins=3000, const float energy_min=0, const float energy_max=3)
{
  TFile *root_file = new TFile (root_filename, "READ");
  if (!root_file->IsOpen()) return;

  TTree *genbb_tree = (TTree*)(root_file->Get("genbb_tree"));
  if (genbb_tree == nullptr)
    {
      printf("*** missing 'genbb_tree' is '%s\n'", root_filename);
      return;
    }

  TH1F *gamma_histo = new TH1F ("gamma_histo", ";Energy (MeV);Intensity", energy_nbins, energy_min, energy_max);
  genbb_tree->Project("gamma_histo", "energy", "type==1");

  TH1F *electron_histo = new TH1F ("electron_histo", ";Energy (MeV);Intensity", energy_nbins, energy_min, energy_max);
  genbb_tree->Project("electron_histo", "energy", "type==3");

  for (int bin=1; bin<=energy_nbins; bin++)
    {
      gamma_histo->SetBinError(bin, 0);
      electron_histo->SetBinError(bin, 0);
    }

  const double norm_factor = genbb_tree->GetEntries();
  gamma_histo->SetLineColor(kGreen+1);
  gamma_histo->Scale(1.0/norm_factor);
  electron_histo->SetLineColor(kRed);
  electron_histo->Scale(1.0/norm_factor);

  (new TCanvas)->SetLogy();
  gamma_histo->Draw();
  electron_histo->Draw("same");
}
