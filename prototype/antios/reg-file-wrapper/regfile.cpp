#include "regfile.h"

RegFile::RegFile()
    : is_valid_ ( false )
{
}

RegFile::RegFile(const std::string &path, const RegItem &item)
    : item_     (item)
    ,  path_    (path)
    , is_valid_ (false) {

    if (!File::ends_with(path_, "/")) {
        path_ += "/";
    }

    if (!File::directory_exists(path_)) {
        File::create_directory_recursively(path_);
    }
    LOG_DEBUG << "RegFile()";
}


RegFile::~RegFile()
{
}


void RegFile::set_path(const std::string &path) {
    if (path != path_ && !path.empty()) {
        path_ = path;

        if (!File::ends_with(path_, "/")) {
            path_ += "/";
        }

        if (!File::directory_exists(path_)) {
            File::create_directory_recursively(path_);
        }
    }
}


std::string RegFile::get_path() const {
    return path_;
}


RegItem RegFile::read() {
    try {
        if (item_.file_name_.empty()) {
            throw std::runtime_error("File name is empty!");
        }

        if (path_.empty()) {
            throw std::runtime_error("Path is empty!");
        }

        std::ifstream stream_(path_ + item_.file_name_, std::ios_base::in);

        if (!stream_.is_open() || stream_.fail()) {
            throw std::runtime_error(get_error_string(errno));
        }

        RegItem item;
        stream_ >> item;
        stream_.close();
        return item;
    }
    catch ( const std::system_error& e ) {
        LOG_ERROR << "Read file: '" << item_.file_name_
                  << "' filed. Reason: '" << e.code().message() << "'";
        return RegItem();
    }
    catch ( const std::exception& e ) {
        LOG_ERROR << "Read file: '" << item_.file_name_
                  << "' filed. Reason: '" << e.what() << "'";
        return RegItem();
    }
    catch ( ... ) {
        handle_exceptionptr(std::current_exception());
        return RegItem();
    }
}

bool RegFile::write() {
    try {
        if (item_.file_name_.empty()) {
            throw std::runtime_error("File name is empty!");
        }

        if (path_.empty()) {
            throw std::runtime_error("Path is empty!");
        }

        std::ofstream stream_(path_ + item_.file_name_, std::ios_base::out);

        stream_ << item_;

        if (!stream_.is_open() || stream_.fail()) {
            throw std::runtime_error(get_error_string(errno));
        }
        stream_.close();
        return true;
    }
    catch ( const std::system_error& e ) {
        LOG_ERROR << "Write file: '" << item_.file_name_
                  << "' filed. Reason: '" << e.code().message() << "'";
        return false;
    }
    catch ( const std::exception& e ) {
        LOG_ERROR << "Write file: '" << item_.file_name_
                  << "' filed. Reason: '" << e.what() << "'";
        return false;
    }
    catch ( ... ) {
        handle_exceptionptr(std::current_exception());
        return false;
    }
}

void RegFile::set_reg_item(const RegItem &item) {
    item_ = item;
}

void RegFile::set_reg_item(RegItem &&item) {
    item_ = std::move(item);
}

const RegItem &RegFile::get_reg_item() const {
    return item_;
}

bool RegFile::is_valid() const {
    return is_valid_;
}

void RegFile::handle_exceptionptr(std::exception_ptr ptr) {
    try { std::rethrow_exception(ptr); }
    catch (const std::exception& e) {
       LOG_ERROR << "Unknown exception, file: '" << item_.file_name_
                 << "'. Reason: '" << e.what()
                 << "'";
    }
}

std::string RegFile::get_error_string(const int err) {
    char buff[1024]{ 0 };
    strerror_s(buff, 1024, errno);
    return std::string(buff);
}
