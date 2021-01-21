#ifndef _LIBSTRING_H_
#define _LIBSTRING_H_

#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

class Libstring
{
private:
    Libstring(/* args */);
    Libstring(const Libstring &);
    Libstring &operator=(const Libstring &);
    ~Libstring();

public:
    static string &ltrim(string &str);
    static string &rtrim(string &str);
    static string &trim(string &str);
    static void split(const string &str, vector<string> &ret_, const string &sep);
    static string replace(const string &str, const string &src, const string &dest);
    static int startsWith(const string &s, const string &sub);
    static int endsWith(const string &s, const string &sub);
};

inline string &Libstring::ltrim(string &str)
{
    string::iterator p = find_if(str.begin(), str.end(), not1(ptr_fun<int, int>(isspace)));
    str.erase(str.begin(), p);
    return str;
}

inline string &Libstring::rtrim(string &str)
{
    string::reverse_iterator p = find_if(str.rbegin(), str.rend(), not1(ptr_fun<int, int>(isspace)));
    str.erase(p.base(), str.end());
    return str;
}

inline string &Libstring::trim(string &str)
{
    ltrim(rtrim(str));
    return str;
}

inline int Libstring::startsWith(const string &s, const string &sub)
{
    if (&s == &sub)
        return true;
    const typename basic_string<char>::size_type big_size = s.size();
    const typename basic_string<char>::size_type small_size = sub.size();
    const bool valid_ = (big_size >= small_size);
    const bool starts_with_ = (s.compare(0, small_size, sub) == 0);
    return valid_ and starts_with_;
    // return s.find(sub) == 0 ? 1 : 0;
}

inline int Libstring::endsWith(const string &s, const string &sub)
{
    if (&s == &sub)
        return true;
    const typename basic_string<char>::size_type big_size = s.size();
    const typename basic_string<char>::size_type small_size = sub.size();
    const bool valid_ = (big_size >= small_size);
    const bool ends_with_ = (s.compare(big_size - small_size, small_size, sub) == 0);
    return valid_ and ends_with_;
    // return s.rfind(sub) == (s.length() - sub.length()) ? 1 : 0;
}

#endif
