class Dependency {
  FILE* save_file (const std::string& filename);
protected:
  std::string location;
  std::string basename (const std::string& path);
public:
  virtual int install () = 0;
  int download ();
  bool downloaded (const std::string& path);
  virtual ~Dependency ();
};

