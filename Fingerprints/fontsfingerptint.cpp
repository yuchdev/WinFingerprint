#include "fontsfingerptint.h"

FontsFingerptint::FontsFingerptint(const std::string &backup_dir)
    : backup_dir_path_(backup_dir + std::string("fonts_fp\\"))
    , size_ ( 0 )
{

}

FontsFingerptint::~FontsFingerptint()
{

}

void FontsFingerptint::generate() {
    try {

    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

void FontsFingerptint::save_state() {
    try {
        if (!File::directory_exists(backup_dir_path_)) {
            File::create_directory_recursively(backup_dir_path_);
        }

        if (helpers::RegistryKey::is_key_exist(Fonts)) {
            helpers::RegistryKey key(Fonts);
            export_to_file(Fonts, std::string("Fonts"), std::string(WOW64_64));

            std::string hidden_key("Hidden");
            auto values_list  = key.enumerate_values();
            for (auto &item : values_list) {
                all_fonts_.emplace_back(std::make_pair(item, key.get_string_value(item)));
            }

            key.create_key(hidden_key);

            if (helpers::RegistryKey::is_key_exist(FontsHidden)) {
                helpers::RegistryKey hiddenKey(FontsHidden);
                export_to_file(FontsHidden, std::string("FontsHidden"), std::string(WOW64_64));
            }
            else {
                std::stringstream ss;
                ss << "Hidden Fonts key: " << FontsHidden << " not exist, skip...";
                throw std::runtime_error(ss.str().data());
            }
        }
        else { LOG_ERROR << "Registry key: '" << Fonts << "' not found, skip..."; }
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

void FontsFingerptint::restore_state() {
    try {
        recover_fonts();
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

void FontsFingerptint::generate_random_state() {
    try {
        move_fonst_to_hidden(3);
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

void FontsFingerptint::write_state() {
    try {
        ///generate_random_state();
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

bool FontsFingerptint::is_customizable() {
    return true;
}

void FontsFingerptint::move_fonst_to_hidden(size_t size) {
    try {

        if (all_fonts_.empty()) {
            LOG_DEBUG << "FONTS epty, do nothing!";
            return;
        }

        if (size == 0) {
            std::uniform_int_distribution<std::size_t> uid1_(1, 3);
            size = uid1_(rd_);
        }

        std::size_t index = 0;
        std::uniform_int_distribution<std::size_t> uid_(0, all_fonts_.size() - 1);
        for (std::size_t i(0); i < size; ++i) {
            index = uid_(rd_);
            random_fonts_.emplace_back(all_fonts_[index]);
        }

        if (helpers::RegistryKey::is_key_exist(FontsHidden) && helpers::RegistryKey::is_key_exist(Fonts)) {
            helpers::RegistryKey fonts_key(Fonts);
            helpers::RegistryKey hidden_key(FontsHidden);
            for (auto &item : random_fonts_) {
                hidden_key.set_string_value(item.first, item.second);
                fonts_key.delete_value(item.first);
            }
        }
        else { LOG_ERROR << "Hidden Fonts key not foun!"; }
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

void FontsFingerptint::recover_fonts() {
    try {
        if (helpers::RegistryKey::is_key_exist(FontsHidden) && helpers::RegistryKey::is_key_exist(Fonts)) {
            helpers::RegistryKey fonts_key(Fonts);
            helpers::RegistryKey hidden_key(FontsHidden);
            for (auto &item : random_fonts_) {
                fonts_key.set_string_value(item.first, item.second);
                hidden_key.delete_value(item.first);
            }
        }
        else {
            LOG_ERROR << "'HiddenFonts' (or 'Fonts') keys not found! Try to restore from files...";
            import_from_files();
        }
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

void FontsFingerptint::set_random_size(const size_t size) {
    size_ = size;
}

size_t FontsFingerptint::get_random_size() const {
    return size_;
}

void FontsFingerptint::export_to_file(const std::string &key, const std::string &file, const std::string& reg_mode) {
    auto result = RegUtil::export_key(key, (backup_dir_path_ + file + ".reg"), reg_mode);
    if (!result.first) {
        LOG_ERROR << "Can't export key: '" << key << "' Reason: '" << result.second << "'";
    }
    else {
        LOG_INFO << "Success save to file key: '" << key << "'";
    }
}

void FontsFingerptint::import_from_files() {
    auto list_files = File::list_files_in_directory(backup_dir_path_);
    for (auto &item : list_files) {
        std::pair<bool, std::string> result;
        std::size_t max_count = 1000;
        std::size_t current_ = 0;
        do {
            if (current_ > max_count) break;
            result = RegUtil::import_key(item);
            current_++;
        }
        while (!result.first);
        if (!result.first) {
            LOG_ERROR << "Error import from file: '" << item << "' Reason: '" << result.second << "'";
        }
        else {
            LOG_INFO << "Success import from file: " << item << "'";
        }
    }
}
