#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

/// @brief The RegItem struct
struct RegItem {
    std::vector<uint8_t> bin_value_;
    std::string key_path_;
    std::string value_name_;
    std::string value_;
    std::string file_name_;
    unsigned long type_;

    RegItem() = default;
    ~RegItem() = default;

    RegItem(const std::string& key_path, const std::string& value_name, const std::string& value, const std::string& file_name, const unsigned long type)
        : key_path_     (key_path)
        , value_name_   (value_name)
        , value_        (value)
        , file_name_    (file_name)
        , type_         (type)
    { }

    RegItem(std::string&& key_path, std::string&& value_name, std::string&& value, std::string&& file_name, const unsigned long type)
        : key_path_     (std::move(key_path))
        , value_name_   (std::move(value_name))
        , value_        (std::move(value))
        , file_name_    (std::move(file_name))
        , type_         (type)
    { }

    RegItem(const RegItem& item)
        : bin_value_    (item.bin_value_)
        , key_path_     (item.key_path_)
        , value_name_   (item.value_name_)
        , value_        (item.value_)
        , file_name_    (item.file_name_)
        , type_         (item.type_)
    { }

    RegItem& operator=(const RegItem& item) {
        bin_value_   = item.bin_value_;
        key_path_    = item.key_path_;
        value_name_  = item.value_name_;
        value_       = item.file_name_;
        file_name_   = item.file_name_;
        type_        = item.type_;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const RegItem& item) {
        LOG_DEBUG << "Try to write item: " << item.key_path_;
        os  << item.key_path_       << '\r' << '\n'
            << item.type_           << '\r' << '\n'
            << item.value_name_     << '\r' << '\n'
            << item.value_          << '\r' << '\n';

        switch (item.type_) {
            case REG_SZ:
                os << item.value_;
                break;
            case REG_DWORD:
                os << item.value_;
                break;
            case REG_BINARY:
            os << item.bin_value_.data();
                break;
            default: break;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, RegItem& item) {
        is >> item.key_path_;
        is >> item.type_;
        is >> item.value_name_;
        switch (item.type_) {
            case REG_SZ:
                is >> item.value_;
                break;
            case REG_DWORD:
                is >> item.value_;
                break;
            case REG_BINARY:
                is >> item.bin_value_.data();
                break;
            default: break;
        }
        return is;
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "[KeyPath]: '"     << key_path_
           << "' [ValueName]: '" << value_name_
           << "' [KeyValue]: '"  << value_
           << "' [FileName]: '"  << file_name_
           << "' [Type]: '"      << type_
           << "' [BINARY]: '";
        for (auto &it : bin_value_) ss << (unsigned char)it;
        return ss.str();

    }

    operator bool() const {
        return key_path_.empty() || value_name_.empty();
    }
};

#endif // TYPES_H
