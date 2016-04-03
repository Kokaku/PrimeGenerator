#ifndef FILEUTILITY_H
#define FILEUTILITY_H

#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

/*
    @author Kokaku
*/
    
// Return true if the given file exists on the disk
bool fexists(const std::string filename);
// Create a directory at this given location and return true if the task succeed
bool createDir(std::string sPath);

#endif // FILEUTILITY_H