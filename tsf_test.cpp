//
// Created by Arindam on 08/11/2024.
//

#include <windows.h>
#include <msctf.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>

// Structure to hold emoji descriptions
struct EmojiEntry {
    std::wstring description;
    wchar_t symbol;
};

// Function to initialize emoji data
std::vector<EmojiEntry> initialize_emoji_data() {
    return {
            {L"smiling face", L'\U0001F600'},  // 😀
            {L"rolling on the floor laughing", L'\U0001F923'},  // 🤣
            {L"rocket", L'\U0001F680'},  // 🚀
            {L"summation", L'∑'},  // ∑
            {L"integral", L'∫'},  // ∫
            {L"pi", L'π'},  // π
            {L"approximately equal", L'≈'},  // ≈
            {L"square root", L'√'}  // √
    };
}

// Function to search emojis by description
std::vector<wchar_t> search_emojis(const std::wstring& query, const std::vector<EmojiEntry>& emoji_data) {
    std::vector<wchar_t> results;
    for (const auto& entry : emoji_data) {
        if (entry.description.find(query) != std::wstring::npos) {
            results.push_back(entry.symbol);
        }
    }
    return results;
}

// Function to simulate sending a Unicode input
void send_unicode_input(wchar_t unicode_char) {
    INPUT input_event;
    input_event.type = INPUT_KEYBOARD;
    input_event.ki.wVk = 0;
    input_event.ki.wScan = unicode_char;
    input_event.ki.dwFlags = KEYEVENTF_UNICODE;
    input_event.ki.time = 0;
    input_event.ki.dwExtraInfo = 0;

    SendInput(1, &input_event, sizeof(INPUT));

    // Release the key
    input_event.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
    SendInput(1, &input_event, sizeof(INPUT));
}

// Function to display popup and let user select
wchar_t display_popup_and_select(const std::vector<wchar_t>& options) {
    if (options.empty()) {
        return 0;
    }

    std::wcout << L"Matching Emojis: " << std::endl;
    for (size_t i = 0; i < options.size(); ++i) {
        std::wcout << i + 1 << L": " << options[i] << std::endl;
    }

    std::wcout << L"Select an option (1-" << options.size() << L"): ";
    int choice;
    std::wcin >> choice;

    if (choice > 0 && choice <= options.size()) {
        return options[choice - 1];
    }

    return 0;
}

int main() {
    // Initialize emoji data
    std::vector<EmojiEntry> emoji_data = initialize_emoji_data();

    // Wait 3 seconds to give time to focus on the target input field
    Sleep(3000);

    // Ask user for input to search emojis
    std::wcout << L"Enter a description to search for an emoji: ";
    std::wstring query;
    std::getline(std::wcin, query);

    // Search for matching emojis
    std::vector<wchar_t> matching_emojis = search_emojis(query, emoji_data);

    // Display matching emojis and let user select
    wchar_t selected_emoji = display_popup_and_select(matching_emojis);
    if (selected_emoji != 0) {
        send_unicode_input(selected_emoji);
        std::wcout << L"Emoji sent: " << selected_emoji << std::endl;
    } else {
        std::wcout << L"No valid selection made." << std::endl;
    }

    return 0;
}
