#include <iostream>
#include <regex>
#include <sys/stat.h>
#include "json.hpp"
#include "tarball.h"

using json = nlohmann::json;

void parse_dependency (const std::string& dependency) {
  if (std::regex_search(dependency, std::regex { "\\.tar\\.gz$" })) {
    std::cout << "^ tar file" << std::endl;
    Tarball t { dependency };
    t.download();
    t.install();
  }
}

int make_directory (const std::string& path) {
  return mkdir(path.c_str(), 0755) && errno != EEXIST;
};

void parse_manifest (std::istream& manifest) {
  json j;
  j << manifest;
  //std::cout << manifest.dump(2) << std::endl;

  json deps = j["dependencies"];
  if (deps.is_null()) {
    std::cerr << "no key dependencies" << std::endl;
    return;
  }

  std::cout << "making deps dir" << std::endl;
  if(make_directory("deps") != 0) {
    std::cerr << "error making deps" << std::endl;
    perror("deps");
    return;
  };

  std::cout << "iterating dependencies" << std::endl;
  for (auto it = deps.cbegin(); it != deps.cend(); ++it) {
    std::cout << it.key() << " | " << it.value() << std::endl;

    if (!it.value().is_string()) {
      std::cerr << "skipping non string value" << std::endl;
      continue;
    }

    parse_dependency(it.value().get<std::string>());
  }
}

