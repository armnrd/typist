//
// Created by Arindam on 08/11/2024.
//

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

// Function to initialize the symbol descriptions using ICU
QMap<QString, QString> initialize_symbol_data() {
    QMap<QString, QString> symbol_data;

    // Unicode range for emojis and mathematical symbols
    UChar32 start = 0x1F600; // Start of common emoji range
    UChar32 end = 0x1F64F;   // End of common emoji range

    for (UChar32 codepoint = start; codepoint <= end; ++codepoint) {
        if (u_isdefined(codepoint)) {
            UErrorCode status = U_ZERO_ERROR;
            char name[100];
            u_charName(codepoint, U_UNICODE_CHAR_NAME, name, sizeof(name), &status);
            if (U_SUCCESS(status)) {
                QString description = QString::fromStdString(std::string(name)).toLower();
                QString symbol = QString::fromUcs4(reinterpret_cast<const char32_t *>(&codepoint), 1);
                symbol_data[description] = symbol;
            }
        }
    }

    // Add mathematical operators range (U+2200 to U+22FF)
    for (UChar32 codepoint = 0x2200; codepoint <= 0x22FF; ++codepoint) {
        if (u_isdefined(codepoint)) {
            UErrorCode status = U_ZERO_ERROR;
            char name[100];
            u_charName(codepoint, U_UNICODE_CHAR_NAME, name, sizeof(name), &status);
            if (U_SUCCESS(status)) {
                QString description = QString::fromStdString(std::string(name)).toLower();
                QString symbol = QString::fromUcs4(reinterpret_cast<const char32_t *>(&codepoint), 1);
                symbol_data[description] = symbol;
            }
        }
    }

    // Add miscellaneous mathematical symbols A range (U+27C0 to U+27EF)
    for (UChar32 codepoint = 0x27C0; codepoint <= 0x27EF; ++codepoint) {
        if (u_isdefined(codepoint)) {
            UErrorCode status = U_ZERO_ERROR;
            char name[100];
            u_charName(codepoint, U_UNICODE_CHAR_NAME, name, sizeof(name), &status);
            if (U_SUCCESS(status)) {
                QString description = QString::fromStdString(std::string(name)).toLower();
                QString symbol = QString::fromUcs4(reinterpret_cast<const char32_t *>(&codepoint), 1);
                symbol_data[description] = symbol;
            }
        }
    }

    // Add supplemental mathematical operators range (U+2A00 to U+2AFF)
    for (UChar32 codepoint = 0x2A00; codepoint <= 0x2AFF; ++codepoint) {
        if (u_isdefined(codepoint)) {
            UErrorCode status = U_ZERO_ERROR;
            char name[100];
            u_charName(codepoint, U_UNICODE_CHAR_NAME, name, sizeof(name), &status);
            if (U_SUCCESS(status)) {
                QString description = QString::fromStdString(std::string(name)).toLower();
                QString symbol = QString::fromUcs4(reinterpret_cast<const char32_t *>(&codepoint), 1);
                symbol_data[description] = symbol;
            }
        }
    }

    // Add miscellaneous mathematical symbols B range (U+2980 to U+29FF)
    for (UChar32 codepoint = 0x2980; codepoint <= 0x29FF; ++codepoint) {
        if (u_isdefined(codepoint)) {
            UErrorCode status = U_ZERO_ERROR;
            char name[100];
            u_charName(codepoint, U_UNICODE_CHAR_NAME, name, sizeof(name), &status);
            if (U_SUCCESS(status)) {
                QString description = QString::fromStdString(std::string(name)).toLower();
                QString symbol = QString::fromUcs4(reinterpret_cast<const char32_t *>(&codepoint), 1);
                symbol_data[description] = symbol;
            }
        }
    }

    // Add miscellaneous symbols and arrows range (U+2B00 to U+2BFF)
    for (UChar32 codepoint = 0x2B00; codepoint <= 0x2BFF; ++codepoint) {
        if (u_isdefined(codepoint)) {
            UErrorCode status = U_ZERO_ERROR;
            char name[100];
            u_charName(codepoint, U_UNICODE_CHAR_NAME, name, sizeof(name), &status);
            if (U_SUCCESS(status)) {
                QString description = QString::fromStdString(std::string(name)).toLower();
                QString symbol = QString::fromUcs4(reinterpret_cast<const char32_t *>(&codepoint), 1);
                symbol_data[description] = symbol;
            }
        }
    }

    // Add mathematical alphanumeric symbols range (U+1D400 to U+1D7FF)
    for (UChar32 codepoint = 0x1D400; codepoint <= 0x1D7FF; ++codepoint) {
        if (u_isdefined(codepoint)) {
            UErrorCode status = U_ZERO_ERROR;
            char name[100];
            u_charName(codepoint, U_UNICODE_CHAR_NAME, name, sizeof(name), &status);
            if (U_SUCCESS(status)) {
                QString description = QString::fromStdString(std::string(name)).toLower();
                QString symbol = QString::fromUcs4(reinterpret_cast<const char32_t *>(&codepoint), 1);
                symbol_data[description] = symbol;
            }
        }
    }

    return symbol_data;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Main widget
    QWidget window;
    window.setWindowTitle("Symbol Searcher");

    // Layout for main widget
    QVBoxLayout *layout = new QVBoxLayout;

    // Input text field for search
    QLineEdit *search_field = new QLineEdit;
    search_field->setPlaceholderText("Type to search for symbols...");

    // List widget to display matching emojis
    QListWidget *symbol_list = new QListWidget;

    // Emoji data
    QMap<QString, QString> symbol_data = initialize_symbol_data();

    // Connect the text changed signal to filter the emojis
    QObject::connect(search_field, &QLineEdit::textChanged, [&symbol_data, symbol_list](const QString &text) {
        symbol_list->clear();
        for (auto it = symbol_data.constBegin(); it != symbol_data.constEnd(); ++it) {
            if (it.key().contains(text, Qt::CaseInsensitive)) {
                QListWidgetItem *symbol_item = new QListWidgetItem(it.key() + " " + it.value());
                symbol_list->addItem(symbol_item);
            }
        }
    });

    // Connect the emoji list item click to copy the emoji
    QObject::connect(symbol_list, &QListWidget::itemClicked, [](QListWidgetItem *item) {
        QString symbol = item->text().split(" ").last();
        QGuiApplication::clipboard()->setText(symbol);
    });

    // Add widgets to layout
    layout->addWidget(search_field);
    layout->addWidget(symbol_list);

    // Set layout to main window
    window.setLayout(layout);
    window.resize(400, 300);
    window.show();

    return app.exec();
}
