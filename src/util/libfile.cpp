#include "libfile.h"

bool Libfile::getAllFiles(const string &path, vector<string> &files)
{
    if (path.empty()) {
        return false;
    }

#ifdef WIN32
	long   hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
#else
    DIR *dir;
	struct dirent *ptr;
	if ((dir = opendir(path.c_str())) == nullptr)
	{
		return false;
	}
	while ((ptr = readdir(dir)) != nullptr)
	{
		if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
			continue;
		else if (ptr->d_type == 8)
		{
			std::string strFile;
			strFile = path;
			strFile += "/";
			strFile += ptr->d_name;
			files.push_back(strFile);
		}
		else
		{
			continue;
		}
	}
	closedir(dir);
#endif
    return true;
}

int Libfile::createDirectory(const std::string &directoryPath)
{
    size_t dirPathLen = directoryPath.length();
    if (dirPathLen > MAX_PATH_LEN)
    {
        return -1;
    }
    char tmpDirPath[MAX_PATH_LEN] = { 0 };
    for (size_t i = 0; i < dirPathLen; ++i)
    {
        tmpDirPath[i] = directoryPath[i];
        if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/')
        {
            if (ACCESS(tmpDirPath, 0) != 0)
            {
                int32_t ret = MKDIR(tmpDirPath);
                if (ret != 0)
                {
                    return ret;
                }
            }
        }
    }
    return 0;
}