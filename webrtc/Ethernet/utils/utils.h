#ifndef UTILS_H
#define UTILS_H

#include <iomanip>
#include <sstream>

template <class T, class T2 = typename std::enable_if<std::is_integral<T>::value>::type>
static std::string ToHex(const T & data, bool addPrefix = true);

template<class T, class>
inline std::string ToHex(const T & data, bool addPrefix) {
    std::stringstream sstream;
    sstream << std::hex;
    std::string ret;

    if (typeid(T) == typeid(char) || typeid(T) == typeid(unsigned char) || sizeof(T)==1) {
        sstream << static_cast<int>(data);
        ret = sstream.str();
        if (ret.length() > 2) {
            ret = ret.substr(ret.length() - 2, 2);
        }
    }
    else {
        sstream << data;
        ret = sstream.str();
    }
    return (addPrefix ? u8"0x" : u8"") + ret;
}

#endif // UTILS_H
