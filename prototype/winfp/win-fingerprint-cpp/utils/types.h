#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>
#include <iostream>


///
/// \brief The RegItem struct
///
struct RegItem {
    std::vector<uint8_t> bin_key_value_;
    std::string key_path_;
    std::string value_name_;
    std::string key_value_;
    std::string file_name_;

    unsigned long type_;

    RegItem() = default;
    ~RegItem() = default;

    RegItem(const std::string& key_path, const std::string& value_name, const std::string& key_value, const std::string& file_name, const unsigned long type)
        : key_path_     (key_path)
        , value_name_   (value_name)
        , key_value_    (key_value)
        , file_name_    (file_name)
        , type_         (type)
    { }

    RegItem(std::string&& key_path, std::string&& value_name, std::string&& key_value, std::string&& file_name, const unsigned long type)
        : key_path_     (std::move(key_path))
        , value_name_   (std::move(value_name))
        , key_value_    (std::move(key_value))
        , file_name_    (std::move(file_name))
        , type_         (type)
    { }

    RegItem(const RegItem& item)
        : bin_key_value_(item.bin_key_value_)
        , key_path_     (item.key_path_)
        , value_name_   (item.value_name_)
        , key_value_    (item.key_value_)
        , file_name_    (item.file_name_)
        , type_         (item.type_)
    { }

    RegItem& operator=(const RegItem& item) {
        bin_key_value_ = item.bin_key_value_;
        key_path_    = item.key_path_;
        value_name_  = item.value_name_;
        key_value_   = item.file_name_;
        file_name_   = item.file_name_;
        type_        = item.type_;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const RegItem& item) {
        os << "[KeyPath]: '"     << item.key_path_
           << "' [ValueName]: '" << item.value_name_
           << "' [KeyValue]: '"  << item.key_value_
           << "' [FileName]: '"  << item.file_name_
           << "' [Type]: '"      << item.type_
           << "' [BINARY]: '";
        for (auto &it : item.bin_key_value_) os << (unsigned char)it;
        return os;
    }
};

#endif // TYPES_H
