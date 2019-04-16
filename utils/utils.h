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
#include <ShlObj_core.h>
#include <memory>
#include <codecvt>
#include "plog/Log.h"

/// example export: REG EXPORT "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Fonts" C:\fonts.reg

class RegUtil {
public:
    static std::pair<bool, std::string> export_key(const std::string& full_key_name, const std::string& file_name, const std::string& reg_mode) {
        STARTUPINFO info;
        PROCESS_INFORMATION proc_info;
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstringstream cmd;

        /// LOG_WARNING << "EXPORT KEY: " << full_key_name << "   FILE_NAME: " << file_name;

        ZeroMemory(&info, sizeof(info));
        ZeroMemory(&proc_info, sizeof(proc_info));
        info.cb = sizeof(info);

        cmd << L" EXPORT \"" << converter.from_bytes(full_key_name.data())
            << "\" \"" << converter.from_bytes(file_name.data())
            << L"\" /y " << converter.from_bytes(reg_mode.data());

        /// LOG_WARNING << "COMMAND TO EXPORT: " << cmd.str();

        bool res = CreateProcess( L"C:\\Windows\\System32\\reg.exe", (LPWSTR)cmd.str().data(), NULL, NULL, FALSE, 0, NULL, NULL, &info, &proc_info);
        if (!res) {
            return std::make_pair(res, std::string(strerror(GetLastError())));
        }

        WaitForSingleObject(proc_info.hProcess, INFINITE);
        CloseHandle(proc_info.hProcess);
        CloseHandle(proc_info.hThread);
        return std::make_pair(res, std::string());
    }

    //// There is a bug with "reg import" command, success message is written to stderr!
    //// https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/reg-import
    static std::pair<bool, std::string> import_key(const std::string& file_name/*, const std::string& reg_mode*/) {
        STARTUPINFO info;
        PROCESS_INFORMATION proc_info;
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstringstream cmd;

        ZeroMemory(&info, sizeof(info));
        ZeroMemory(&proc_info, sizeof(proc_info));
        info.cb = sizeof(info);

        cmd << L" IMPORT \""
            << ".\\" << converter.from_bytes(file_name.data());
//            << "\""<< converter.from_bytes(reg_mode.data());

        LOG_WARNING << "Command to restore: " << cmd.str();

        bool res = CreateProcess( L"C:\\Windows\\System32\\reg.exe", (LPWSTR)cmd.str().data(), NULL, NULL, FALSE, 0, NULL, NULL, &info, &proc_info);
        if (!res) {
            return std::make_pair(res, std::string(strerror(GetLastError())));
        }

        WaitForSingleObject(proc_info.hProcess, INFINITE);
        CloseHandle(proc_info.hProcess);
        CloseHandle(proc_info.hThread);
        return std::make_pair(res, std::string());
    }
};


///
/// \brief The CMDParser class
///
class CMDParser {
public:
    ///
    /// \brief CMDParser::option_exists
    /// \param begin
    /// \param end
    /// \param option
    /// \return
    ///
    static bool CMDParser::option_exists(char **begin, char **end, const std::string &option) {
        return (std::find(begin, end, option) != end);
    }

    ///
    /// \brief CMDParser::get_option
    /// \param argc
    /// \param argv
    /// \param option
    /// \return
    ///
    static std::string CMDParser::get_option(int argc, char *argv[], const std::string &option) {
        std::string command;
        for( int i(0); i < argc; ++i) {
            std::string arg = argv[i];
            if(0 == arg.find(option)) {
                std::size_t found = arg.find_last_of(option);
                command = arg.substr(found + 1);
                return command;
            }
        }
        return command;
    }
};

///
/// \brief The SimpleUUID class
///
class SimpleUUID {
public:
    static std::string get_uuid() {
        UUID uuid;
        UuidCreate(&uuid);
        unsigned char* str;
        /*RPC_STATUS res = */UuidToStringA(&uuid, &str);
        return std::string((char*)str);
    }
};

///
/// \brief The File class
///
class File {
public:
    ///
    /// \brief file_exist
    /// \param file_name
    /// \return
    ///
    static bool file_exist(const std::string& file_name) {
        std::ifstream f(file_name.data());
        return f.good();
    }

    ///
    /// \brief remove_file
    /// \param file_name
    /// \return
    ///
    static bool remove_file(const std::string& file_name) {
        if (remove(file_name.data()) != 0) {
            return false;
        }
        return true;
    }

    ///
    /// \brief wchar_t2string
    /// \param wchar
    /// \return
    ///
    static std::string wchar_t2string(const wchar_t *wchar) {
        std::string str = "";
        int index = 0;
        while(wchar[index] != 0) {
            str += (char)wchar[index];
            ++index;
        }
        return str;
    }

    ///
    /// \brief string2wchar_t
    /// \param str
    /// \return unique ptr of wchar_t array
    ///
    static std::unique_ptr<wchar_t[]> string2wchar_t(const std::string &str) {
        std::unique_ptr<wchar_t[]> wchar(new wchar_t[260]);
        std::size_t index = 0;
        while(index < str.size()) {
            wchar.get()[index] = (wchar_t)str[index];
            ++index;
        }
        wchar.get()[index] = 0;
        return wchar;
    }

    ///
    /// \brief list_files_in_directory
    /// \param directoryName
    /// \return
    ///
    static std::vector<std::string> list_files_in_directory(const std::string& directoryName) {
        WIN32_FIND_DATA FindFileData;
        std::unique_ptr<wchar_t[]> FileName = string2wchar_t(directoryName + "\\*");
        HANDLE hFind = FindFirstFile(FileName.get(), &FindFileData);

        std::vector<std::string> listFileNames;
        ///listFileNames.push_back(directoryName + "\\" + wchar_t2string(FindFileData.cFileName));
        while (FindNextFile(hFind, &FindFileData)) {
            std::string tmp(wchar_t2string(FindFileData.cFileName));
            if (tmp != ".."){
                listFileNames.push_back(directoryName + "\\" + tmp);
            }
        }
        return listFileNames;
    }

    ///
    /// \brief remove_all_files
    /// \param dir_path
    /// \return
    ///
    static bool remove_all_files(const std::string& dir_path) {
        if (dir_path.empty()) return false;
        return true;
    }

    ///
    /// \brief ends_with
    /// \param value
    /// \param ending
    /// \return
    ///
    static bool ends_with(const std::string& value, const std::string& ending) {
        if (ending.size() > value.size()) {
            return false;
        }

        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    ///
    /// \brief get_current_dirrectory
    /// \return
    ///
    static std::string get_current_dirrectory() {
        std::unique_ptr<char[]> buffer(new char[MAX_PATH]);
        GetCurrentDirectoryA(MAX_PATH, buffer.get());
        auto res = GetLastError();
        printf_s("LASTError: '%s'\n", strerror(res));
        return std::string(buffer.get(), MAX_PATH);
    }

    ///
    /// \brief directory_exists
    /// \param path
    /// \return
    ///
    static bool directory_exists(const std::string& path) {
        DWORD dwAttrib = GetFileAttributesA(path.data());
        return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
    }

    ///
    /// \brief create_directory_recursively
    /// \param path
    ///
    static void create_directory_recursively(const std::string& path) {
        std::size_t pos = 0;
        do {
            pos = path.find_first_of("\\/", pos + 1);
            CreateDirectoryA(path.substr(0, pos).data(), NULL);
        }
        while (pos != std::string::npos);
    }


};


///
/// \brief The String class
///
class String {
public:

    ///
    /// \brief Split
    /// \param str
    /// \param delim
    /// \return
    ///
    static std::vector<std::string> Split(const std::string& str, const char delim) {
        std::vector<std::string> tokens;
        std::istringstream stream(str);
        std::string token;
        while(std::getline(stream, token, delim)) tokens.push_back(token);
        return tokens;
    }

    ///
    /// \brief disperse_string
    /// \param string
    /// \return
    ///
    static std::string disperse_string(const std::string& string) {
        if (string.empty()) return string;
        std::string result(string);
        for (std::size_t i(0); i < result.size(); ++i) {
            if (i % 2 != 0)
            result.insert(i, 1, '\0');
        }
        return result;
    }
};


class Volume {
  public:
    static std::pair<bool, std::string> get_volume_serial() {
        DWORD serial = 0;
        if (!GetVolumeInformationA((LPCSTR)L"C:\\", NULL, NULL, &serial, NULL, NULL, NULL, NULL)) {
            return std::make_pair(false, std::string(strerror(GetLastError())));
        }
        std::ostringstream os;
        os << std::to_string(HIWORD(serial)) << "-" << std::to_string(LOWORD(serial));
//        std::string f = std::to_string(HIWORD(serial));
//        std::string s = std::to_string(LOWORD(serial));
        return std::make_pair(true, os.str());
    }

    static std::string get_random_id() {
        std::string ascii_string{"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};
        std::random_device rd;
        std::uniform_int_distribution<std::size_t> uid(0, ascii_string.size() - 1);
        std::ostringstream os;
        os << std::hex << ascii_string[uid(rd)];
        os << std::hex << ascii_string[uid(rd)];
        os << std::hex << ascii_string[uid(rd)];
        os << std::hex << ascii_string[uid(rd)];
        os << "-";
        os << std::hex << ascii_string[uid(rd)];
        os << std::hex << ascii_string[uid(rd)];
        os << std::hex << ascii_string[uid(rd)];
        os << std::hex << ascii_string[uid(rd)];
        return os.str();
    }
};

#endif // UUID_H
