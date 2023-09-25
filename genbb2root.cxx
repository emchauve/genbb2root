// -*- mode: c++; -*-
// g2b.cxx

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <datatools/ioutils.h>
#include <datatools/io_factory.h>                                                                                                                                                                
#include <datatools/properties.h>                                                                                                                                                                 
#include <genbb_help/primary_event.h>

#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"

void usage (std::ostream & a_out = std::clog)
{
  using namespace std;
  a_out << " -- convert GENBB data into ROOT's TTree" << endl;
  a_out << "Usage: genbb2root -i [INPUT_GENBB_FILE] -o [OUTPUT_ROOT_FILE]" << endl;
  // a_out << " Options: " << endl;
  // a_out << "   -d|--debug  : print debug info" << endl;
  // a_out << "   -h|--help   : print help" << endl;
  return;
}

int main (int argc, char **argv)
{
  bool debug = false;

  std::string input_file;
  std::string output_file;

  for (int iarg = 1; iarg < argc; ++iarg) {

    std::string arg = argv[iarg];

    if (arg[0] == '-') {
      
      if (arg == "-d" || arg == "--debug") debug = true;
      // if (arg == "-h" || arg == "--help") usage();

      else if (arg == "-i" || arg == "--input")
	input_file = std::string(argv[++iarg]);
      
      else if (arg == "-o" || arg == "--output")
	output_file = std::string(argv[++iarg]);

      else if (input_file.empty())
	input_file = arg;

      else if (output_file.empty())
	output_file = arg;

    } // if -d

  } // for iarg



  datatools::data_reader reader;
  reader.init(input_file, datatools::using_multi_archives);

  // ROOT stuff //

  gROOT->ProcessLine("#include <vector>");

  TFile *root_file = new TFile (output_file.data(), "RECREATE");
  TTree *root_tree = new TTree ("genbb_tree", "");

  float event_weight;
  root_tree->Branch("weight",  &event_weight);

  std::vector<unsigned short> *particle_type  = new std::vector<unsigned short>;
  root_tree->Branch("type",   &particle_type);

  std::vector<unsigned short> *particle_time  = new std::vector<unsigned short>;
  root_tree->Branch("time",   &particle_time);

  std::vector<float>          *particle_px    = new std::vector<float>;
  std::vector<float>          *particle_py    = new std::vector<float>;
  std::vector<float>          *particle_pz    = new std::vector<float>;
  root_tree->Branch("px"    , &particle_px);
  root_tree->Branch("py"    , &particle_py);
  root_tree->Branch("pz"    , &particle_pz);

  std::vector<float>          *particle_energy = new std::vector<float>;
  root_tree->Branch("energy", &particle_energy);

  ////////////////

  genbb::primary_event event;

  while ( reader.has_record_tag() ) {

    reader.load(event);
    
    event_weight = event.get_genbb_weight();

    const genbb::primary_event::particles_col_type particles = event.get_particles();

    genbb::primary_event::particles_col_type::const_iterator particle_it = particles.begin();

    for ( ; particle_it != particles.end() ; ++particle_it)
      {
	particle_type->push_back   ( particle_it->get_type() );
	particle_time->push_back   ( particle_it->get_time() );
	particle_px->push_back     ( particle_it->get_momentum()[0] );
	particle_py->push_back     ( particle_it->get_momentum()[1] );
	particle_pz->push_back     ( particle_it->get_momentum()[2] );
	particle_energy->push_back ( particle_it->get_kinetic_energy() );
      }
    
    root_tree->Fill();

    particle_type->clear();
    particle_time->clear();
    particle_px->clear();
    particle_py->clear();
    particle_pz->clear();
    particle_energy->clear();
  }
  
  root_tree->Write();
  root_file->Close();

  return 0;
}

  // end of genbb2root.cxx
