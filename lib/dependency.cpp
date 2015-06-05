#include <iostream>
#include "curl/curl.h"
#include "dependency.h"

FILE* Dependency::save_file (const std::string& filename) {
  return fopen(filename.c_str(), "w");
}

std::string Dependency::basename (const std::string& path) {
  return std::string(std::find_if(path.crbegin(), path.crend(), [](char c) {
    return c == '/';
  }).base(), path.end());
}

int Dependency::download() {
  CURL* curl = curl_easy_init();
  std::string base_name = basename(this->location);
  FILE* file = save_file(("deps/" + base_name).c_str());
  if (curl && file) {
    curl_easy_setopt(curl, CURLOPT_URL, this->location.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_perform(curl);
    long response_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    std::cout << "response code: " << response_code << std::endl;
    fclose(file);
    curl_easy_cleanup(curl);
  } else {
    std::cerr << "error downloading: " << this->location << std::endl;
  }
  return 0;
}
