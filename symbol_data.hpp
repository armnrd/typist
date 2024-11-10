/**
 * @file symbol_data.hpp
 * @brief Functions to generate collections of symbols from various Unicode ranges.
 *
 * @author Arindam Biswas
 * @date 10/11/2024
 */

#ifndef TYPIST_SYMBOL_DATA_HPP
#define TYPIST_SYMBOL_DATA_HPP

#include <unordered_map>
#include <string>
#include <QString>
#include <unicode/utf.h>

std::unordered_map<std::string, QString> get_symbol_data_qt();
std::unordered_map<std::string, UChar32> get_symbol_data();

#endif //TYPIST_SYMBOL_DATA_HPP
