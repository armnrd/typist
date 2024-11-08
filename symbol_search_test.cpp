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
#include <QListWidgetItem>
#include <unicode/unistr.h>
#include <unicode/uchar.h>
#include <unicode/uname.h>
#include <QClipboard>
#include <QGuiApplication>
#include <iostream>

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
                QString symbol = QString::fromUcs4(&codepoint, 1);
                symbol_data[description] = symbol;
            }
        }
    }

    // Add more symbols (mathematical symbols, etc.)
    UChar32 math_symbols[] = {0x2211, 0x222B, 0x03C0, 0x2248, 0x221A}; // ∑, ∫, π, ≈, √
    for (UChar32 codepoint : math_symbols) {
        if (u_isdefined(codepoint)) {
            UErrorCode status = U_ZERO_ERROR;
            char name[100];
            u_charName(codepoint, U_UNICODE_CHAR_NAME, name, sizeof(name), &status);
            if (U_SUCCESS(status)) {
                QString description = QString::fromStdString(std::string(name)).toLower();
                QString symbol = QString::fromUcs4(&codepoint, 1);
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
