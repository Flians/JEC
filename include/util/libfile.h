#ifndef _LIBFILE_H_
#define _LIBFILE_H_

#ifdef WIN32
    #include <io.h>
#else
    #include <string.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <sys/types.h>
#endif

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class libfile
{
private:
    /* data */
public:
    libfile();
    ~libfile();

    bool getAllFiles(const string &path, vector<string>& files);
};

#endif
