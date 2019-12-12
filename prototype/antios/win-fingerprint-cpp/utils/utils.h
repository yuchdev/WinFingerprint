#ifndef UUID_H
#define UUID_H

#include <Windows.h>
#include <sstream>
#include <random>
#include <cstdio>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <rpcdce.h>
#include <ShlObj.h>
#include <memory>
#include <codecvt>
#include "plog/Log.h"

class RegUtil {
public:
    static std::pair<bool, std::string> export_key(const std::string& full_key_name, const std::string& file_name, const std::string& reg_mode);

    //// There is a bug with "reg import" command, success message is written to stderr!
    //// https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/reg-import
    static std::pair<bool, std::string> RegUtil::import_key(const std::string& file_name);
};


/// \brief The CMDParser class
class CMDParser {
public:
    /// \brief CMDParser::option_exists
    /// \param begin
    /// \param end
    /// \param option
    /// \return
    static bool CMDParser::option_exists(char **begin, char **end, const std::string &option);

    /// \brief CMDParser::get_option
    /// \param argc
    /// \param argv
    /// \param option
    /// \return
    static std::string CMDParser::get_option(int argc, char *argv[], const std::string &option);
};


/// \brief The SimpleUUID class
class SimpleUUID {
public:
    static std::string get_uuid();
};


/// \brief The File class
class File {
public:
    /// \brief file_exist
    /// \param file_name
    /// \return
    static bool file_exist(const std::string& file_name);

    /// \brief remove_file
    /// \param file_name
    /// \return
    static bool remove_file(const std::string& file_name);

    /// \brief wchar_t2string
    /// \param wchar
    /// \return
    static std::string wchar_t2string(const wchar_t *wchar);

    /// \brief string2wchar_t
    /// \param str
    /// \return unique ptr of wchar_t array
    static std::unique_ptr<wchar_t[]> string2wchar_t(const std::string &str);

    /// \brief list_files_in_directory
    /// \param directoryName
    /// \return
    static std::vector<std::string> list_files_in_directory(const std::string& directoryName);

    /// \brief remove_all_files
    /// \param dir_path
    /// \return
    static bool remove_all_files(const std::string& dir_path);

    /// \brief ends_with
    /// \param value
    /// \param ending
    /// \return
    static bool ends_with(const std::string& value, const std::string& ending);

    /// \brief get_current_dirrectory
    /// \return
    static std::string get_current_dirrectory();

    /// \brief directory_exists
    /// \param path
    /// \return
    static bool directory_exists(const std::string& path);

    /// \brief create_directory_recursively
    /// \param path
    static void create_directory_recursively(const std::string& path);
};


/// \brief The String class
class String {
public:
    /// \brief Split
    /// \param str
    /// \param delim
    /// \return
    static std::vector<std::string> Split(const std::string& str, const char delim);

    /// \brief disperse_string
    /// \param string
    /// \return
    static std::string disperse_string(const std::string& string);

    static std::vector<uint8_t> disperse_array(const std::vector<uint8_t>& array);
};


class Volume {
  public:
    static std::pair<bool, std::string> get_volume_serial();
    static std::string get_random_id();
};

#endif // UUID_H
