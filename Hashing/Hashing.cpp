#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct account {
    int num = 0;
    string fullname;
    string address;
    account(int num, string name,  string address) {
        this->num = num;
        this->fullname = name;
        this->address = address;
    }

};

class Hash_table {
public:
    Hash_table()
    {
        this->accs = 0;
        this->size = 12;
        for (int i = 0; i < 12; i++) {
            vector<account> vec;
            table.push_back(vec);
        }
    }
    int size;
    vector<vector<account>> table;
    int accs;

    int hash(int i) { return i % size; }

    void insert(account acc) {
        table[hash(acc.num)].push_back(acc);
        cout << "Запись вставлена успешно" << endl;
        accs++;
        if (((double)accs+1)/size >=0.75) {
            rehash();
        }
    }

    void remove(int num) {
        if (table[hash(num)].size() > 0) {
            for (int i = 0; i < table[hash(num)].size(); i++) {
                if (table[hash(num)][i].num == num) {
                    table[hash(num)].erase(table[hash(num)].begin() + i);
                }
            }
            cout << "Запись удалена успешно" << endl;
        }
        else cout << "Запись не найдена" << endl;
    }

    void print(int num) {
        if (table[hash(num)].size() > 0) {
            for (int i = 0; i < table[hash(num)].size(); i++) {
                if (table[hash(num)][i].num == num) {
                    cout << "Имя: " << (table[hash(num)][i].fullname) << endl;
                    cout << "Адрес: " << (table[hash(num)][i].address) << endl;
                }
            }
        }
        else cout << "Запись не найдена" << endl;
    }

    account find_key(int num) {
        if (table[hash(num)].size() > 0) {
            for(int i=0; i<table[hash(num)].size(); i++){
                if (table[hash(num)][i].num == num) {
                    return(table[hash(num)][i]);
                }
            }
            cout << "Запись не найдена" << endl;
            return account(0, "", "");
        }
        else {
            cout << "Запись не найдена" << endl;
            return account(0, "", "");
        }
    }
private:

    void rehash() {
        for (int i = 0; i < size; i++) {
            vector<account> vec;
            table.push_back(vec);
        }
        size *=2 ;
        for (int i = 0; i < size; i++) {
            if (table[i].size() > 0) {
                for (int j = 0; j < table[i].size(); j++) {
                    account acc = table[i][j];
                    table[i].erase(table[i].begin() + j);
                    table[hash(acc.num)].push_back(acc);
                }
            }
        }
    }
};



void hint() {
    cout << "1 - вставить запись в таблицу" << endl;
    cout << "2 - удалить запись из таблицы" << endl;
    cout << "3 - найти запись по ключу" << endl;
    cout << "4 - вывод элемента" << endl;
    cout << "5 - завершение работы" << endl;
}

int main()
{
    setlocale(LC_ALL, "rus");
    int i = 0;
    int num;
    Hash_table* ht = new Hash_table();
    hint();
    do {
        (cin >> i).get();
        switch(i) {

        case 1:
        {
            string name;
            string address;
            cout << "Введите имя" << endl;
            getline(cin, name);
            cout << "Введите адрес" << endl;
            getline(cin, address);
            cout << "Введите номер" << endl;
            cin >> num;
            account acc(num, name, address);
            ht->insert(acc);
            break;
        }
        case 2:
            cout << "Введите номер" << endl;
            (cin >> num).get();
            ht->remove(num);
            break;
        case 3:
            cout << "Введите номер" << endl;
            (cin >> num).get();
            ht->find_key(num);
            break;
        case 4:
            cout << "Введите номер" << endl;
            (cin >> num).get();
            ht->print(num);
            break;
        case 5:
            break;
        default:
            cout << "Некорректная команда" << endl;
            hint();
        }
    } while (i != 5);
    system("pause");
}
