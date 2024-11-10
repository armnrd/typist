/**
 * @file symbol_data.cpp
 * @brief Functions to generate collections of symbols from various Unicode ranges.
 *
 * @author Arindam Biswas
 * @date 10/11/2024
 */

#include "symbol_data.hpp"
#include <utility>
#include <QApplication>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <QMap>
#include <unicode/unistr.h>
#include <unicode/uchar.h>
#include <QClipboard>
#include <QGuiApplication>

std::tuple<UChar32, UChar32> unicode_ranges[] {
        {0x1F600, 0x1F64F}, // emojis
        {0x2200, 0x22FF},   // mathematical operators
        {0x27C0, 0x27EF},   // miscellaneous mathematical symbols A
        {0x2A00, 0x2AFF},   // supplemental mathematical operators
        {0x2980, 0x29FF},   // miscellaneous mathematical symbols B
        {0x2B00, 0x2BFF},   // miscellaneous symbols and arrows
        {0x1D400, 0x1D7FF}  // mathematical alphanumeric symbols
};

/**
 * @brief Creates a collection of Unicode symbols inside ranges specified in *unicode_ranges*.
 *
 * The pairs are stored as (*std::string*, *UChar32*).
 *
 * @return symbol_data - An *unordered_map* containing (description, symbol) pairs.
 */
std::unordered_map<std::string, UChar32> get_symbol_data()
{
    std::unordered_map<std::string, UChar32> symbol_data;

    for (auto range : unicode_ranges) {
        auto [start, end] = range;
        for (UChar32 codepoint = start; codepoint <= end; ++codepoint) {
            if (u_isdefined(codepoint)) {
                UErrorCode status = U_ZERO_ERROR;
                char buffer[100];
                u_charName(codepoint, U_CHAR_NAME_ALIAS, buffer, sizeof(buffer), &status);
                if (U_SUCCESS(status)) {
                    std::string description = std::string(buffer);
                    symbol_data[description] = codepoint;
                }
            }
        }
    }
    return symbol_data;
}

/**
 * @brief Creates a collection of Unicode symbols inside ranges specified in *unicode_ranges*.
 *
 * The pairs are stored as (*std::string*, *QString*).
 *
 * @return symbol_data - An *unordered_map* containing (description, symbol) pairs.
 */
std::unordered_map<std::string, QString> get_symbol_data_qt()
{
    std::unordered_map<std::string, QString> symbol_data;

    for (auto range : unicode_ranges) {
        auto [start, end] = range;
        for (UChar32 codepoint = start; codepoint <= end; ++codepoint) {
            if (u_isdefined(codepoint)) {
                UErrorCode status = U_ZERO_ERROR;
                char buffer[100];
                u_charName(codepoint, U_CHAR_NAME_ALIAS, buffer, sizeof(buffer), &status);
                if (U_SUCCESS(status)) {
                    std::string description = std::string(buffer);
                    symbol_data[description] = QString::fromUcs4(reinterpret_cast<const char32_t *>(&codepoint), 1);
                }
            }
        }
    }
    return symbol_data;
}
