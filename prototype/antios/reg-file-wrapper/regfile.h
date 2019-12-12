#pragma once

#include <cerrno>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <codecvt>
#include <exception>

#include "utils/utils.h"
#include "utils/types.h"
#include "utils/keys.h"


class RegFile {
public:
    RegFile();
    RegFile(const std::string& path, const RegItem& item);

    ~RegFile();

public:
    void set_path(const std::string& path);
    std::string get_path() const;

    RegItem read();
    bool write();

    void set_reg_item(const RegItem& item);
    void set_reg_item(RegItem&& item);
    const RegItem& get_reg_item() const;

    bool is_valid() const;

protected:
    void handle_exceptionptr(std::exception_ptr ptr);
	std::string get_error_string(const int err);
protected:
    RegItem item_;
    std::string path_;
    bool is_valid_;
};
