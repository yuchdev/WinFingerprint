#include "utils.h"

std::pair<bool, std::string> RegUtil::export_key(const std::string &full_key_name, const std::string &file_name, const std::string &reg_mode) {
    STARTUPINFOA info;
    PROCESS_INFORMATION proc_info;
    std::stringstream cmd;

    /// LOG_WARNING << "EXPORT KEY: " << full_key_name << "   FILE_NAME: " << file_name;

    ZeroMemory(&info, sizeof(info));
    ZeroMemory(&proc_info, sizeof(proc_info));
    info.cb = sizeof(info);

    cmd << " EXPORT \"" << full_key_name.data()
        << "\" \""       << file_name.data()
        << "\" /y "      << reg_mode.data();

    LOG_DEBUG << "COMMAND TO EXPORT: " << cmd.str();

    bool res = CreateProcessA("C:\\Windows\\System32\\reg.exe", (LPSTR)cmd.str().data(), NULL, NULL, FALSE, 0, NULL, NULL, &info, &proc_info);
    if (!res) {
        return std::make_pair(res, std::string(strerror(GetLastError())));
    }

    WaitForSingleObject(proc_info.hProcess, INFINITE);
    CloseHandle(proc_info.hProcess);
    CloseHandle(proc_info.hThread);
    return std::make_pair(res, std::string());
}

std::pair<bool, std::string> RegUtil::import_key(const std::string& file_name) {
    STARTUPINFOA info;
    PROCESS_INFORMATION proc_info;
    std::stringstream cmd;

    ZeroMemory(&info, sizeof(info));
    ZeroMemory(&proc_info, sizeof(proc_info));
    info.cb = sizeof(info);

    cmd << " IMPORT \"" << ".\\" << file_name.data();

    LOG_DEBUG << "Command to restore: " << cmd.str();

    bool res = CreateProcessA("C:\\Windows\\System32\\reg.exe", (LPSTR)cmd.str().data(), NULL, NULL, FALSE, 0, NULL, NULL, &info, &proc_info);
    if (!res) return std::make_pair(res, std::string(strerror(GetLastError())));

    WaitForSingleObject(proc_info.hProcess, INFINITE);
    CloseHandle(proc_info.hProcess);
    CloseHandle(proc_info.hThread);
    return std::make_pair(res, std::string());
}

bool CMDParser::CMDParser::option_exists(char **begin, char **end, const std::string &option) {
    return (std::find(begin, end, option) != end);
}

std::string CMDParser::CMDParser::get_option(int argc, char *argv[], const std::string &option) {
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

std::string SimpleUUID::get_uuid() {
    UUID uuid;
    UuidCreate(&uuid);
    unsigned char* str;
    UuidToStringA(&uuid, &str);
    std::string result = std::string((char*)str);
    return result;
}

bool File::file_exist(const std::string &file_name) {
    std::ifstream f(file_name.data());
    return f.good();
}

bool File::remove_file(const std::string &file_name) {
    if (remove(file_name.data()) != 0) {
        return false;
    }
    return true;
}

std::string File::wchar_t2string(const wchar_t *wchar) {
    std::string str = "";
    int index = 0;
    while(wchar[index] != 0) {
        str += (char)wchar[index];
        ++index;
    }
    return str;
}

std::unique_ptr<wchar_t[]> File::string2wchar_t(const std::string &str) {
    std::unique_ptr<wchar_t[]> wchar(new wchar_t[260]);
    std::size_t index = 0;
    while(index < str.size()) {
        wchar.get()[index] = (wchar_t)str[index];
        ++index;
    }
    wchar.get()[index] = 0;
    return wchar;
}

std::vector<std::string> File::list_files_in_directory(const std::string &directoryName) {
    WIN32_FIND_DATAA FindFileData;
    HANDLE hFind = FindFirstFileA((directoryName + "\\*").data(), &FindFileData);
    std::vector<std::string> listFileNames;
    while (FindNextFileA(hFind, &FindFileData)) {
        std::string tmp(FindFileData.cFileName);
        if (tmp != ".."){
            listFileNames.push_back(directoryName + "\\" + tmp);
        }
    }
    return listFileNames;
}

bool File::remove_all_files(const std::string &dir_path) {
    if (dir_path.empty()) return false;
    return true;
}

bool File::ends_with(const std::string &value, const std::string &ending) {
    if (ending.size() > value.size()) {
        return false;
    }

    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

std::string File::get_current_dirrectory() {
    std::unique_ptr<char[]> buffer(new char[MAX_PATH]);
    GetCurrentDirectoryA(MAX_PATH, buffer.get());
    printf_s("LastError: '%s'\n", strerror(GetLastError()));
    return std::string(buffer.get(), MAX_PATH);
}

bool File::directory_exists(const std::string &path) {
    DWORD dwAttrib = GetFileAttributesA(path.data());
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void File::create_directory_recursively(const std::string &path) {
    std::size_t pos = 0;
    do {
        pos = path.find_first_of("\\/", pos + 1);
        CreateDirectoryA(path.substr(0, pos).data(), NULL);
    }
    while (pos != std::string::npos);
}

std::vector<std::string> String::Split(const std::string &str, const char delim) {
    std::vector<std::string> tokens;
    std::istringstream stream(str);
    std::string token;
    while(std::getline(stream, token, delim)) tokens.push_back(token);
    return tokens;
}

std::string String::disperse_string(const std::string &string) {
    if (string.empty()) return string;
    std::string result(string);
    for (std::size_t i(0); i < result.size(); ++i) {
        if (i % 2 != 0) result.insert(i, 1, 0x00);
    }
    return result;
}

std::vector<uint8_t> String::disperse_array(const std::vector<uint8_t> &array) {
    if (array.empty()) return std::vector<uint8_t>();
    std::vector<uint8_t> result(array);
    for (std::size_t i(0); i < result.size(); ++i) {
        if (i % 2 != 0) {
            result.insert(result.begin() + i + 1, 1, static_cast<uint8_t>(0x00));
        }
    }
    return result;
}

std::pair<bool, std::string> Volume::get_volume_serial() {
    DWORD serial = 0;
    if (!GetVolumeInformationA((LPCSTR)"C:\\", NULL, NULL, &serial, NULL, NULL, NULL, NULL)) {
        return std::make_pair(false, std::string(strerror(GetLastError())));
    }
    std::ostringstream os;
    os << std::to_string(HIWORD(serial)) << "-" << std::to_string(LOWORD(serial));
    return std::make_pair(true, os.str());
}

std::string Volume::get_random_id() {
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
