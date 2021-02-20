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
    static void ltrim(string &str);
    static void rtrim(string &str);
    static void trim(string &str);
    static string ltrim_copy(string str);
    static string rtrim_copy(string str);
    static string trim_copy(string str);
    static void split(const string &str, vector<string> &ret_, const string &sep);
    static string replace(const string &str, const string &src, const string &dest);
    static int startsWith(const string &s, const string &sub);
    static int endsWith(const string &s, const string &sub);
};

// trim from start (in place)
inline void Libstring::ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
}

// trim from end (in place)
inline void Libstring::rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base(),
            s.end());
}

// trim from both ends (in place)
inline void Libstring::trim(std::string &s)
{
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
inline std::string Libstring::ltrim_copy(std::string s)
{
    ltrim(s);
    return s;
}

// trim from end (copying)
inline std::string Libstring::rtrim_copy(std::string s)
{
    rtrim(s);
    return s;
}

// trim from both ends (copying)
inline std::string Libstring::trim_copy(std::string s)
{
    trim(s);
    return s;
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
