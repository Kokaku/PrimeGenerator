#include "FileUtility.h"

bool fexists(const std::string filename) {
  std::ifstream ifile(filename.c_str());
    if (ifile.good()) {
        ifile.close();
        return true;
    } else {
        ifile.close();
        return false;
    } 
}

bool createDir(std::string sPath) {
    if(!fexists(sPath)) {
        mode_t nMode = 0733;
        int nError = 0;
        #if defined(_WIN32)
          nError = _mkdir(sPath.c_str());
        #else 
          nError = mkdir(sPath.c_str(),nMode);
        #endif
        return nError == 0;
    }

    return true;
}
