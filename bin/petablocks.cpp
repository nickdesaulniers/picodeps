#include <iostream>
#include <fstream>
#include "petablocks.h"
#include "curl/curl.h"

int main (int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "usage: ./petablocks <inputfile>" << std::endl;
    exit(1);
  }

  std::ifstream f { argv[1] };
  if (!f.is_open()) {
    std::cerr << "failed to open file: " << argv[1] << std::endl;
    exit(1);
  }

  parse_manifest(f);
}

