#include "dependency.h"
class Tarball: public Dependency {
public:
    int install ();
    Tarball (const std::string& url);
};

