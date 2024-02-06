#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

class train {
public:
    string departure;
    string arrival;
    int train_number;
    int ticket_price;

    train() {
        departure = "";
        arrival = "";
        train_number = 0;
        ticket_price = 0;
    }

    train(string dp, string a, int tn, int tp) {
        departure = dp;
        arrival = a;
        train_number = tn;
        ticket_price = tp;
    }

    friend ostream& operator<<(ostream& out, train& obj) {
        return out << obj.departure << endl << obj.arrival << endl << obj.train_number << endl << obj.ticket_price << endl;
    }
};

class railway_station {
private:
    vector<train> station;

public:
    railway_station() {
        load_from_file();
    }

    void add_train() {
        string departure, arrival;
        int train_number, ticket_price;

        cout << "" << endl;
        cout << "Введіть станцію відправлення: ";
        cin >> departure;
        cout << "Введіть станцію прибуття: ";
        cin >> arrival;
        cout << "Введіть номер потяга: ";
        cin >> train_number;
        cout << "Введіть вартість квитка: ";
        cin >> ticket_price;

        station.push_back(train(departure, arrival, train_number, ticket_price));
    }

    void print_all_trains() {
        for (auto train : station) {
            cout << train << endl;
        }
    }

    void search_train(int train_number) {
        auto it = find_if(station.begin(), station.end(), [train_number](train t) { return t.train_number == train_number; });
        if (it != station.end()) {
            cout << *it << endl;
        }
        else {
            cout << "Поїзд з номером " << train_number << " не знайдено" << endl;
        }
    }

    void save_to_file() {
        ofstream file("trains.txt");
        for (auto train : station) {
            file << train.departure << endl;
            file << train.arrival << endl;
            file << train.train_number << endl;
            file << train.ticket_price << endl;
        }
        file.close();
    }

    void load_from_file() {
        ifstream file("trains.txt");
        if (file.is_open()) {
            station.clear();
            string departure, arrival;
            int train_number, ticket_price;

            while (file >> departure >> arrival >> train_number >> ticket_price) {
                station.push_back(train(departure, arrival, train_number, ticket_price));
            }

            file.close();
        }
    }

    void start() {
        int choice;
        do
        {
            cout << "1. Ввести дані про поїзд" << endl;
            cout << "2. Вивести дані про всі поїзди" << endl;
            cout << "3. Вивести дані про запитуваний поїзд" << endl;
            cout << "4. Вийти" << endl;
            cin >> choice;

            switch (choice)
            {
            case 1:
                add_train();
                break;
            case 2:
                print_all_trains();
                break;
            case 3:
                int train_number;
                cout << "" << endl;
                cout << "Введіть номер потяга: ";
                cin >> train_number;
                search_train(train_number);
                break;
            case 4:
                save_to_file();
                return;
            default:
                break;
            }
        } while (choice != 4);
    }
};

int main() {
    railway_station station;
    station.start();
    return 0;
}
