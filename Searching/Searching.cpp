#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

map <char, int> table(string str) {
    map<char, int> tab;
    for (int i = str.length() - 2; i >= 0; i--) {
        if (tab.find(str.at(i)) == tab.end()) {
            tab[str.at(i)] = str.length() - 1 - i;
        }
    }
    if (tab.find(str.at(str.length()-1)) == tab.end()) {
        tab[str.at(str.length() - 1)] = str.length() - 1;
    }
    return tab;
}

vector<int> suf_shift(string str) { // вычисление таблицы суффиксов
    int m = str.length()-1; 
    vector<int> tab(m+1, m);  // заполняем числом, которое равно последнему индексу в слове
    vector<int> z(m, 0); // заполняем нулями
    int maxZidx = 0, maxZ = 0; //конец и начало максимального префикса
    for (int j = 1; j < m; ++j) {
        if (j <= maxZ) z[j] = min(maxZ - j + 1, z[j - maxZidx]);
        while (j + z[j] < m && str[m - 1 - z[j] == str[m - 1 - (j + z[j])]]) z[j]++; //увеличиваем текущее z пока не найдется символ, не совпадающий с текущим из префикса
        if (j + z[j] - 1 > maxZ) {
            maxZidx = j;
            maxZ = j + z[j] - 1; //меняем максимальный префикс если нашли больше
        }
    }
    for (int j = m - 1; j > 0; j--) tab[m - z[j]] = j; 
    for (int j = 1, r = 0; j <= m - 1; j++) { //вычисляем значения сдвига для каждого элемента
        if (j + z[j] == m) {
            for (; r <= j; r++)
                if (tab[r] == m) tab[r] = j;
        }
    }
    reverse(tab.begin(), tab.end()); // переворачиваем таблицу
    return tab;
}





int search(string str, string substr) {
    int m = substr.length();
    int n = str.length()-1; 
    int i, j;
   vector<int> gs = suf_shift(substr); //получаем таблицу сдвигов для слова
   cout << endl;
   i = 0;
    while(i <= n-m){ // проходимся по всему слову, пока в него может поместиться подстрока
        j = m - 1;
        while(j>0 && str[j+i] == substr[j]){  // уменьшаем j пока символ строки и опдстроки совпадает 
            --j;
        }
        if (j <= 0)
            return(i); // возвращаем индекс если совпало все
        else {
            i += gs[j]; // сдвигаемся соответственно сдвигу в таблице
        }
    }
    return -1;
}

vector<string> num_search(string str) {
    string num = ""; //временная переменная для записи текущего числа
    vector<string> vec;
    bool was_dig = false; // флаг, указывающий, является ли пред. символ цифрой
    bool was_space = false; // ... пробел
    for (int i = 0; i < str.length(); i++) {
        if ((isdigit(str[i]) && ((was_dig == true) || (was_space == true))) || (i == 0))
    { //еси цифра идет после пробела или после числа с начала слова
            num = num + str[i]; // добавляем в текущее число
            was_dig = true;
            was_space = false; // устанавливаем флаги
            if (i + 1 == str.length()) {
                vec.push_back(num); //добавляем в вектор число, если символ был последним
            }
        }
        else {
            if ((str[i] == ' '))  {
                was_space = true; 
                if ((was_dig == true) && (num.length() > 0)) {
                    vec.push_back(num); //добавляем в вектор, если от пробела до пробела шли только цифры
                }
            }
            else {
                was_space = false;
            }
            was_dig = false;
            num = ""; //обнуляем
        }
    }
    return(vec); 
}


int main()
{
    string str;
    getline(cin, str);
    vector<string> vec = num_search(str);
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
}
