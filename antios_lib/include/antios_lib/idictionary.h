#ifndef IDICTIONARY_H
#define IDICTIONARY_H

#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <codecvt>
#include <exception>

/// @brief The Dictionary class for reading and storing the dictionary
class IDictionary {
public:
    /// @brief @brief get a random value from the dictionary in the format of a string
    /// @return random word from the dictionary
    virtual std::string get_random_value() = 0;

    /// @brief get a random value from the dictionary in the format of a wide string
    /// @return random word from the dictionary in wide string
    virtual std::wstring get_random_value_w() = 0;

    /// @brief get the number of entries in the dictionary
    /// @return count of words in dictionary
    virtual std::size_t size() const = 0;

protected:

    /// @brief read file line by line
    virtual void read_lines() = 0;

    /// @brief lines_ - holds lines from file
    std::vector<std::string> lines_;

    /// @brief file stream object
    std::ifstream stream_;

    /// @brief string converter (std::string <--> std::wstring)
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter_;

    /// @brief Device for generating pseudo-random numbers
    std::random_device rd_;

    /// @brief file path (must not be empty!)
    std::string path_;
};


#endif // IDICTIONARY_H
