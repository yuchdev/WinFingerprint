#include "dictionary.h"

Dictionary::Dictionary(const std::string &file_path) {
    try {
        path_ = file_path;
        if (path_.empty()) {
            is_valid_ = false;
        }
        else {
            stream_.open(path_, std::ios_base::in);
            if (stream_.is_open()) {
                is_valid_ = true;
                read_lines();
            }
            else { is_valid_ = false; }
        }
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception in ctor";
    }
}


Dictionary::~Dictionary() {
    stream_.close();
}


std::string Dictionary::get_random_value() {
    try {
        std::uniform_int_distribution<std::size_t> uid_(0, lines_.size() - 1);
        std::size_t index = uid_(rd_);
        if (index > lines_.size()) {
            std::stringstream ss;
            ss << "Index in '" << __FUNCTION__ << " [" << __LINE__ << "] is out of range!";
            throw std::out_of_range(ss.str().data());
        }
        return lines_[index];
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::string();

    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::string();
    }
}


std::wstring Dictionary::get_random_value_w() {
    try {
        return converter_.from_bytes(get_random_value().data());
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::wstring();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::wstring();
    }
}


std::size_t Dictionary::size() const {
    return lines_.size();
}

bool Dictionary::is_valid() const {
    return is_valid_;
}


void Dictionary::read_lines() {
    try {
        if (!stream_.is_open()) {
            LOG_ERROR << "Can't open stream: '" << path_ << "'";
        }
        else {
            std::string tmp;
            while(std::getline(stream_, tmp)) { lines_.push_back(tmp); }
        }
    }
    catch (const std::exception& e) { LOG_ERROR << e.what(); }
    catch ( ... ) { LOG_ERROR << "Unknown exception"; }
}
