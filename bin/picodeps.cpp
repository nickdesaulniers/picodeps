#include <iostream>
#include <fstream>
#include <list>
#include "dependency.h"
#include "picodeps.h"

int main (int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "usage: ./picodeps <inputfile>" << std::endl;
    exit(1);
  }

  std::ifstream f { argv[1] };
  if (!f.is_open()) {
    std::cerr << "failed to open file: " << argv[1] << std::endl;
    exit(1);
  }

  auto dependencies = parse_manifest(f);
  for (auto dependency : dependencies) {
    dependency->download();
    dependency->install();
  }
}

