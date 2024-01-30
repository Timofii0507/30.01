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
        cout << "������� ��:\n"
            "1. ����� �����\n"
            "2. ��������� �����\n"
            "3. ��������� �����\n"
            "4. ����������� �����\n"
            "5. ������� �������� � �����\n"
            "6. ����� �������� � ����\n"
            "7. �����\n";

        int choice;
        cin >> choice;

        switch (choice) 
        {
        case 1: 
        {
            string word;
            cout << "������ �����: ";
            cin >> word;

            if (dictionary.Search(word))
            {
                cout << "�������� �����: " << dictionary.GetDefinition(word) << endl;
            }
            else 
            {
                cout << "����� �� ��������" << endl;
            }
            break;
        }
        case 2: 
        {
            string word, definition;
            cout << "������ �����: ";
            cin >> word;
            cout << "������ ����������: ";
            cin.ignore(); 
            getline(cin, definition);

            dictionary.Add(word, definition);
            dictionary.WriteToFile("dictionary.txt"); 
            break;
        }
        case 3: {
            string word;
            cout << "������ �����: ";
            cin >> word;

            dictionary.Remove(word);
            dictionary.WriteToFile("dictionary.txt");
            break;
        }
        case 4:
        {
            string word, new_definition;
            cout << "������ �����: ";
            cin >> word;
            cout << "������ ���� ����������: ";
            cin >> new_definition;

            dictionary.Edit(word, new_definition);
            dictionary.WriteToFile("dictionary.txt"); 
            break;
        }
        case 5: 
        {
            string filename;
            cout << "������ ��'� �����: ";
            cin >> filename;

            dictionary.ReadFromFile(filename);
            break;
        }
        case 6:
        {
            string filename;
            cout << "������ ��'� �����: ";
            cin >> filename;

            dictionary.WriteToFile(filename);
            break;
        }
        case 7:
            return 0;
        default:
            cout << "������� ����" << endl;
            break;
        }
    }

    return 0;
}