#include <iostream>
#include <unordered_map>
#include <ctime>
#include <chrono>
#include <string>
#include <sstream>
using namespace std;
using namespace std::chrono;

//пример для контр. вопросов
//struct TrieNode {
//    unordered_map<char, TrieNode*> children;
//    bool isEndOfWord;
//};
//
//class Trie {
//public:
//    Trie() {
//        root = new TrieNode();
//    }
//
//    void insert(string word) {
//        TrieNode* current = root;
//        for (char c : word) {
//            if (current->children.find(c) == current->children.end()) {
//                current->children[c] = new TrieNode();
//            }
//            current = current->children[c];
//        }
//        current->isEndOfWord = true;
//    }
//
//    bool search(string word) {
//        TrieNode* current = root;
//        for (char c : word) {
//            if (current->children.find(c) == current->children.end()) {
//                return false;
//            }
//            current = current->children[c];
//        }
//        return current->isEndOfWord;
//    }
//
//private:
//    TrieNode* root;
//};
//
//int main() {
//    Trie trie;
//    trie.insert("apple");
//    trie.insert("banana");
//    trie.insert("orange");
//
//    cout << trie.search("apple") << endl;   // Output: 1
//    cout << trie.search("banana") << endl;  // Output: 1
//    cout << trie.search("orange") << endl;  // Output: 1
//    cout << trie.search("kiwi") << endl;    // Output: 0
//
//    return 0;
//}

//задание 1 линейный поиск...
//int linearSearch(const string& text, const string& pattern) {
//    stringstream ss(text);
//    string word;
//    int wordCount = 0;
//
//    while (ss >> word) {
//        wordCount++;
//        if (word == pattern) {
//            return wordCount;
//        }
//    }
//
//    return -1; // Слово не найдено
//}
//
//
//int main() {
//    string text;
//    string pattern;
//
//    getline(cin, text);
//    cout << "write down pattern: ";
//    cin >> pattern;
//
//    auto start = high_resolution_clock::now();
//    int index = linearSearch(text, pattern);
//    auto stop = high_resolution_clock::now();
//
//    if (index != -1) {
//        cout << "The first occurrence of the word \"" << pattern << "\" is at position " << index << endl;
//        auto duration = duration_cast<nanoseconds>(stop - start);
//        cout << "Linear Search Time: " << duration.count() << " nanosec" << endl << endl;
//    }
//    else {
//        cout << "The word \"" << pattern << "\" was not found." << endl;
//    }
//
//    return 0;
//}


//задание 2 Бойер-Мур...
//vector<int> calculateShifts(const string& pattern) {
//    int m = pattern.size();
//    vector<int> shifts(256, m);
//
//    for (int i = 0; i < m; i++) {
//        shifts[static_cast<int>(pattern[i])] = m - i - 1;
//    }
//
//    return shifts;
//}
//
//int boyerMoore(const string& text, const string& pattern) {
//    int n = text.size();
//    int m = pattern.size();
//    vector<int> shifts = calculateShifts(pattern);
//
//    int i = m - 1;
//    while (i < n) {
//        int j = m - 1;
//        while (text[i] == pattern[j]) {
//            if (j == 0) {
//                return i;
//            }
//            i--;
//            j--;
//        }
//        i += shifts[static_cast<int>(text[i])];
//    }
//
//    return -1;
//}
//
//int main() {
//    string text;
//    string pattern;
//
//    getline(cin, text);
//    cout << "write down pattern: ";
//    cin >> pattern;
//
//    auto start = high_resolution_clock::now();
//    int index = boyerMoore(text, pattern);
//    auto stop = high_resolution_clock::now();
//
//    if (index != -1) {
//        cout << "The first occurrence of the word \"" << pattern << "\" is at position " << index + 1 << endl;
//        auto duration = duration_cast<nanoseconds>(stop - start);
//        cout << "Linear Search Time: " << duration.count() << " nanosec" << endl << endl;
//    }
//    else {
//        cout << "The word \"" << pattern << "\" was not found." << endl;
//    }
//
//    return 0;
//}


//задание 3 поиск по бору

// Определение узла бора
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
};

// Создание узла бора
TrieNode* createNode() {
    TrieNode* node = new TrieNode;
    node->isEndOfWord = false;
    return node;
}

// Добавление слова в бор
void insertWord(TrieNode* root, string word) {
    TrieNode* current = root;

    // Для каждого символа слова
    for (int i = 0; i < word.length(); i++) {
        char c = word[i];

        // Если узел для символа не существует, создаем новый узел
        if (current->children.find(c) == current->children.end()) {
            current->children[c] = createNode();
        }

        // Переходим к следующему узлу
        current = current->children[c];
    }

    // Отмечаем, что слово закончилось в данном узле
    current->isEndOfWord = true;
}

// Поиск слова в боре
bool searchWord(TrieNode* root, string word, bool addIfNotFound = true) {
    TrieNode* current = root;

    // Для каждого символа слова
    for (int i = 0; i < word.length(); i++) {
        char c = word[i];

        // Если узел для символа не существует и флаг добавления нового слова включен, создаем новый узел
        if (current->children.find(c) == current->children.end() && addIfNotFound) {
            current->children[c] = createNode();
        }
        // Если узел для символа не существует и флаг добавления нового слова выключен, слово не найдено
        else if (current->children.find(c) == current->children.end() && !addIfNotFound) {
            return false;
        }

        // Переходим к следующему узлу
        current = current->children[c];
    }

    // Если слово закончилось в узле, слово найдено
    return current->isEndOfWord;
}

int main() {
    TrieNode* root = createNode();

    string text;

    getline(cin, text);
    stringstream ss(text);

    string word;
    string aim;
    cout << "write down a word: ";
    cin >> word;

    int wordCount = 0;
    while (ss >> aim) {
        wordCount++;

        // Добавление слова в бор
        insertWord(root, aim);
    }

    // Поиск слова в боре
    if (searchWord(root, word)) {
        cout << "The word " << word << " was found in the dictionary.\n";
    }
    else {
        cout << "The word " << word << " was not found in the dictionary.\n";

        // Добавление нового слова в бор, если оно не было найдено
        insertWord(root, word);
        cout << "The word " << word << " was added to the dictionary.\n";
        text = text + " " + word;
        wordCount++;
    }
    cout << endl << text << endl;
    return 0;
    }