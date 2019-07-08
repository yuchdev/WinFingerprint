#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <antios_lib/idictionary.h>

#include "plog/Log.h"
#include "plog/Logger.h"

///
/// \brief The Dictionary class
///
class Dictionary : public IDictionary {
public:

    ///
    /// \brief Dictionary
    /// \param file_path
    ///
    explicit Dictionary(const std::string& file_path);

    ///
    /// \brief ~Dictionary
    ///
    virtual ~Dictionary();

    std::string get_random_value() override;
    std::wstring get_random_value_w() override;
    std::size_t size() const override;
    bool is_valid() const override;

private:
    void read_lines() override;
};

#endif // DICTIONARY_HPP
