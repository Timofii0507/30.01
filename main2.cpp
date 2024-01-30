#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <map>

using namespace std;

class Dictionary 
{
public:
    Dictionary() {}

    void Add(const string& word, const string& definition) 
    {
        dictionary_[word] = definition;
    }

    void Remove(const string& word) 
    {
        dictionary_.erase(word);
    }

    void Edit(const string& word, const string& new_definition) 
    {
        dictionary_[word] = new_definition;
    }

    bool Search(const string& word) const 
    {
        return dictionary_.find(word) != dictionary_.end();
    }

    string GetDefinition(const string& word) const 
    {
        auto it = dictionary_.find(word);
        if (it != dictionary_.end()) 
        {
            return it->second;
        }
        else 
        {
            return "";
        }
    }

    void ReadFromFile(const string& filename)
    {
        ifstream file(filename);
        for (string line; getline(file, line);) 
        {
            size_t pos = line.find(':');
            if (pos != string::npos)
            {
                Add(line.substr(0, pos), line.substr(pos + 1));
            }
        }
    }

    void WriteToFile(const string& filename) const 
    {
        ofstream file(filename);
        for (const auto& pair : dictionary_) 
        {
            file << pair.first << ":" << pair.second << endl;
        }
    }

private:
    map<string, string> dictionary_;
};

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Dictionary dictionary;

    dictionary.ReadFromFile("dictionary.txt");

    while (true) 
    {
        cout << "Виберіть дію:\n"
            "1. Пошук слова\n"
            "2. Додавання слова\n"
            "3. Видалення слова\n"
            "4. Редагування слова\n"
            "5. Читання словника з файлу\n"
            "6. Запис словника в файл\n"
            "7. Вихід\n";

        int choice;
        cin >> choice;

        switch (choice) 
        {
        case 1: 
        {
            string word;
            cout << "Введіть слово: ";
            cin >> word;

            if (dictionary.Search(word))
            {
                cout << "Значення слова: " << dictionary.GetDefinition(word) << endl;
            }
            else 
            {
                cout << "Слово не знайдено" << endl;
            }
            break;
        }
        case 2: 
        {
            string word, definition;
            cout << "Введіть слово: ";
            cin >> word;
            cout << "Введіть визначення: ";
            cin.ignore(); 
            getline(cin, definition);

            dictionary.Add(word, definition);
            dictionary.WriteToFile("dictionary.txt"); 
            break;
        }
        case 3: {
            string word;
            cout << "Введіть слово: ";
            cin >> word;

            dictionary.Remove(word);
            dictionary.WriteToFile("dictionary.txt");
            break;
        }
        case 4:
        {
            string word, new_definition;
            cout << "Введіть слово: ";
            cin >> word;
            cout << "Введіть нове визначення: ";
            cin >> new_definition;

            dictionary.Edit(word, new_definition);
            dictionary.WriteToFile("dictionary.txt"); 
            break;
        }
        case 5: 
        {
            string filename;
            cout << "Введіть ім'я файлу: ";
            cin >> filename;

            dictionary.ReadFromFile(filename);
            break;
        }
        case 6:
        {
            string filename;
            cout << "Введіть ім'я файлу: ";
            cin >> filename;

            dictionary.WriteToFile(filename);
            break;
        }
        case 7:
            return 0;
        default:
            cout << "Невірний вибір" << endl;
            break;
        }
    }

    return 0;
}