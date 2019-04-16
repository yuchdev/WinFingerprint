#include "dictionary.h"

Dictionary::Dictionary(const std::string &file_path) {
    try {
        path_ = file_path;
        if (path_.empty()) {
            throw std::exception("Path is empty!");
        }

        stream_.open(path_, std::ios_base::in);
        if (!stream_.is_open()) {
            std::stringstream ss;
            ss << "Can't Open file by name: '" << path_
               << "' Error: '" << strerror(errno)  /// Pusibly need to use strerror_s for safety
               << "'";
            throw std::runtime_error(ss.str().data());
        }
        read_lines();
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception in ctor"; }
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
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception"; }
}


std::wstring Dictionary::get_random_value_w() {
    try {
        return converter_.from_bytes(get_random_value().data());
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception"; }
}


size_t Dictionary::size() const {
    return lines_.size();
}


void Dictionary::read_lines() {
    if (!stream_.is_open()) {
        std::stringstream ss;
        ss << "Can't Open file by name: '" << path_
           << "' Error: '" << strerror(errno)
           << "'";
        throw std::runtime_error(ss.str().data());
    }

    try {
        std::string tmp;
        while(std::getline(stream_, tmp)){
            lines_.push_back(tmp);
        }
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception"; }
}
