#include "taxdb.h"
#include "quickfile.hpp"
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

int main(int argc, char **argv) {
  if (argc != 4) {
    std::cerr << "Usage: dump_taxdb taxDB names.dmp nodes.dmp\n";
    return 1;
  }
  TaxonomyDB<uint32_t, uint32_t> taxdb {(string)argv[1]};
  ofstream names_file(argv[2]);
  names_file.exceptions(ifstream::failbit | ifstream::badbit);
  ofstream nodes_file(argv[3]);
  nodes_file.exceptions(ifstream::failbit | ifstream::badbit);

  for (const auto &taxon : taxdb.taxIDsAndEntries) {
    std::string scientificName;
    nodes_file << taxon.second.taxonomyID 
      << "\t|\t" << taxon.second.parentTaxonomyID
      << "\t|\t" << taxon.second.rank
      << "\t|\n"; // there are further columns, but Kraken does not care about them
    
    names_file << taxon.second.taxonomyID 
      << "\t|\t" << taxon.second.scientificName
      << "\t|\t" 
      << "\t|\t" << "scientific name" << "\t|\n";
  }
  names_file.close();
  nodes_file.close();
}
