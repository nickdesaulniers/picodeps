#include <iostream>
#include <unistd.h>
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

// TOCTOU ?
bool Dependency::downloaded (const std::string& filename) {
  return access(filename.c_str(), F_OK) != -1;
}

int Dependency::download() {
  std::string save_as = "deps/" + basename(this->location);

  if (downloaded(save_as)) {
    std::cout << "Already have " << save_as << " downloaded" << std::endl;
    return 0;
  }

  FILE* file = save_file(save_as.c_str());
  std::cout << "Downloading " << this->location << std::endl;

  CURL* curl = curl_easy_init();
  if (curl && file) {
    curl_easy_setopt(curl, CURLOPT_URL, this->location.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_perform(curl);
    fclose(file);
    long response_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    std::cout << "response code: " << response_code << std::endl;
    curl_easy_cleanup(curl);
    // on a non 200, we should rm the file, but could be used for malice
    return response_code == 200 ? 0 : -1;
  } else {
    std::cerr << "error downloading: " << this->location << std::endl;
    return -1;
  }
}

Dependency::~Dependency () {};

