#ifndef _LIBSTRING_H_
#define _LIBSTRING_H_

#include <vector>
#include <string>

using namespace std;

class libstring
{
private:
    /* data */
public:
    libstring(/* args */);
    ~libstring();

    static string trim(const string &str);
    static void split(const string &str, vector<string> &ret_, string sep);
    static string replace(const string &str, const string &src, const string &dest);
    static int startsWith(string s, string sub);
    static int endsWith(string s, string sub);
};

#endif
