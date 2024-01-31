#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

bool isIgnoredSymbol(char symbol) {
    string ignoredSymbols = ",.!?:;\"'";
    return ignoredSymbols.find(symbol) != string::npos;
}

string toLowerCase(string word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    return word;
}

class FrequencyDictionary {
private:
    map<string, int> dict;

public:
    FrequencyDictionary(string filename) {
        ifstream input(filename);
        if (input.is_open()) {
            string word;
            while (input >> word) {
                bool ignoreWord = false;
                for (char c : word) {
                    if (isIgnoredSymbol(c)) {
                        ignoreWord = true;
                        break;
                    }
                }

                if (!ignoreWord) {
                    dict[toLowerCase(word)]++;
                }
            }
            input.close();
        }
        else {
            cout << "Failed to open the file " << filename << endl;
        }
    }

    void printAllWords() {
        cout << "Words and their count:" << endl;
        for (auto pair : dict) {
            cout << pair.first << " - " << pair.second << endl;
        }
    }

    void printMostFrequentWord() {
        string mostFrequentWord;
        int maxCount = 0;
        for (auto pair : dict) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                mostFrequentWord = pair.first;
            }
        }
        cout << "Most frequent word: " << mostFrequentWord << " - " << maxCount << endl;
    }

    void writeResultToFile(string filename) {
        ofstream output(filename);
        if (output.is_open()) {
            output << "Words and their count:" << endl;
            for (auto pair : dict) {
                output << pair.first << " - " << pair.second << endl;
            }
            output.close();
        }
        else {
            cout << "Failed to open the file " << filename << endl;
        }
    }
};

int main() {
    string inputFilename;
    string outputFilename;
    cout << "Enter the input file name: ";
    cin >> inputFilename;
    cout << "Enter the output file name: ";
    cin >> outputFilename;
    FrequencyDictionary fd(inputFilename);
    fd.printAllWords();
    fd.printMostFrequentWord();
    fd.writeResultToFile(outputFilename);
    return 0;
}
