#include <iostream>
#include <list>
#include <memory>
#include <sys/stat.h>
#include "json.hpp"
#include "tarball.h"

using json = nlohmann::json;

static int make_directory (const std::string& path) {
  return mkdir(path.c_str(), 0755) && errno != EEXIST;
};

static bool ends_with (const std::string& full_string, const std::string& suffix) {
  if (full_string.length() < suffix.length()) {
    return false;
  } else {
    return full_string.compare(full_string.length() - suffix.length(), suffix.length(), suffix) == 0;
  }
}

std::list<std::shared_ptr<Dependency>> parse_manifest (std::istream& manifest) {
  json j;
  j << manifest;

  json deps = j["dependencies"];
  if (deps.is_null()) {
    throw "no key dependencies";
  }

  if(make_directory("deps") != 0) {
    perror("deps");
    throw "error making deps dir";
  };

  std::list<std::shared_ptr<Dependency>> dependencies;
  for (auto it = deps.cbegin(); it != deps.cend(); ++it) {
    std::cout << it.key() << " | " << it.value() << std::endl;

    if (!it.value().is_string()) {
      std::cerr << "skipping non string value" << std::endl;
      continue;
    }

    auto value = it.value().get<std::string>();
    if (ends_with(value, ".tar.gz")) {
      dependencies.push_back(std::make_shared<Tarball>(value));
    }
  }
  return dependencies;
}

