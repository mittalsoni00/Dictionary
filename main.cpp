//Here is the code for running this dictionary while connecting to database.
#include <iostream>
#include <string>
#include <unordered_map>
#include <windows.h>
#include <mysql.h>
#include <cctype>
#include <algorithm>

using namespace std;
void displayCenteredText(const std::string& text, int totalWidth) {
    int padding = (totalWidth - text.length()) / 2;
    std::cout << std::string(padding, ' ') << text << std::endl;
}
void toLowerCase(string& str) {
    transform(str.begin(), str.end(), str.begin(),
              [](unsigned char c) { return std::tolower(c); });
}

void displayMenu() {
      int consoleWidth = 80;
    displayCenteredText("Welcome to Dictionary", consoleWidth);
    cout << "1. Dictionary" << endl;
    cout << "2. Exit" << endl;
}

int main() {
    system("Color 5F");
    MYSQL* conn;
    conn = mysql_init(NULL);

    if (conn == NULL) {
        cerr << "mysql_init() failed" << endl;
        return 1;
    }

    if (mysql_real_connect(conn, "localhost", "root", "", "dict", 0, NULL, 0) == NULL) {
        cerr << "mysql_real_connect() failed" << endl;
        mysql_close(conn);
        return 1;
    }

    unordered_map<string, pair<string, pair<string, string>>> dictionaryMap;

    string query = "SELECT english_word, hindi_translation, antonyms, synonyms FROM bilingual_dictionary";
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                string englishWord = row[0] ? row[0] : "";
                string hindiTranslation = row[1] ? row[1] : "";
                string antonyms = row[2] ? row[2] : "";
                string synonyms = row[3] ? row[3] : "";
                dictionaryMap[englishWord] = make_pair(hindiTranslation, make_pair(antonyms, synonyms));
            }
            mysql_free_result(result);
        } else {
            cerr << "mysql_store_result() failed" << endl;
        }
    } else {
        cerr << "mysql_query() failed" << endl;
    }

    int choice;
    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string englishWord;
                cout << "Enter an English word: ";
                cin >> englishWord;

                // Convert the input word to lowercase
                toLowerCase(englishWord);

                // Search for the lowercase version of the word in the unordered_map
                if (dictionaryMap.find(englishWord) != dictionaryMap.end()) {
                    cout << "Hindi translation: " << dictionaryMap[englishWord].first << endl;
                    cout << "Antonyms: " << dictionaryMap[englishWord].second.first << endl;
                    cout << "Synonyms: " << dictionaryMap[englishWord].second.second << endl;
                } else {
                    cout << "Translation not found." << endl;

                    char addChoice;
                    cout << "Do you want to add this word to the dictionary? (Y/N): ";
                    cin >> addChoice;

                    if (addChoice == 'Y' || addChoice == 'y') {
                        string newHindiTranslation, newAntonyms, newSynonyms;
                        cout << "Enter the Hindi translation for " << englishWord << ": ";
                        cin.ignore();
                        getline(cin, newHindiTranslation);
                        cout << "Enter the Antonyms for " << englishWord << ": ";
                        getline(cin, newAntonyms);
                        cout << "Enter the Synonyms for " << englishWord << ": ";
                        getline(cin, newSynonyms);

                        dictionaryMap[englishWord] = make_pair(newHindiTranslation, make_pair(newAntonyms, newSynonyms));

                        query = "INSERT INTO bilingual_dictionary (english_word, hindi_translation, antonyms, synonyms) VALUES ('" + englishWord + "', '" + newHindiTranslation + "', '" + newAntonyms + "', '" + newSynonyms + "')";
                        if (mysql_query(conn, query.c_str()) != 0) {
                            cerr << "Failed to update the database" << endl;
                        }
                    }
                }
                break;
            }



            case 2: {
                cout << "Exiting the program." << endl;
                mysql_close(conn);
                return 0;
            }

            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }

    mysql_close(conn);
    return 0;
}
