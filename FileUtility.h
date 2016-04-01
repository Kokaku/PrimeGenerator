#ifndef FILEUTILITY_H
#define FILEUTILITY_H

#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

bool fexists(const std::string filename);
bool createDir(std::string sPath);

#endif // FILEUTILITY_H