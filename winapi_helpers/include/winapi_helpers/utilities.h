#pragma once
#include <string>

// Small utility functions without belonging to any group

// handler for Ctrl-C type
#ifdef __GNUC__
typedef int(*posix_ctrl_handler_t)(unsigned long);
#elif _MSC_VER
typedef int(__stdcall *ctrl_handler_t)(unsigned long);
#endif

namespace helpers{

/// @brief Initialize memory debug options
void set_memory_profiling();


#if defined(_WIN32) || defined(_WIN64)

/// @brief Set custom action for the console application pressing Ctrl-C
void set_console_ctrl_handler(ctrl_handler_t ctrl_handler);

#elif defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))

/// @brief Set custom action for the console application pressing Ctrl-C
void set_console_ctrl_handler(posix_ctrl_handler_t ctrl_handler);

#endif

/// @brief Converts wstring to UTF-8 string
std::string wstring_to_utf8(const std::wstring &var);

/// @brief Converts UTF-8 string to wstring
std::wstring utf8_to_wstring(const std::string &var);

/// @brief Converts wstring to string using locale dependent codecvt facet
std::string wstring_to_string(const std::wstring &var);

/// @brief Converts string to wstring using locale dependent codecvt facet
std::wstring string_to_wstring(const std::string &var);

} // namespace helpers
