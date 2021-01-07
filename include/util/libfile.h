#ifndef _LIBFILE_H_
#define _LIBFILE_H_

#ifdef WIN32
    #include <io.h>
    #include <direct.h>
#else
    #include <unistd.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <sys/types.h>
#endif

#include <string>
#include <cstring>
#include <vector>
#include <fstream>

#define MAX_PATH_LEN 256

#ifdef WIN32
    #define ACCESS(fileName, accessMode) _access(fileName, accessMode)
    #define MKDIR(path) _mkdir(path)
#else
    #define ACCESS(fileName, accessMode) access(fileName, accessMode)
    #define MKDIR(path) mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif

using namespace std;

class Libfile
{
private:
    Libfile();
    Libfile(const Libfile &);
    Libfile &operator=(const Libfile &);
    ~Libfile();

public:
    static bool getAllFiles(const string &path, vector<string> &files);
    static int createDirectory(const std::string &directoryPath);
};

#endif
