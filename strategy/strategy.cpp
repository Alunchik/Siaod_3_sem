#include <vector>
#include <iostream>
#include <set>
#include <iterator>

using namespace std;

vector<int> rand_vec(int n) {
    vector<int> arr;
    for (int i = 0; i < n; i++) {
        arr.push_back(rand());
    }
    return (arr);
}


void brute_force(vector<int> a) {
    int n = a.size();
    vector<int> ind(n, 0);
    vector<int> d(n, 0);
    int last_index = 0; // индекс последнего элемента подпоследовательности
    d[0] = 1;
   int  calls = 0;
    ind[0] = -1;
    int len = 0; // общая длина максимальной подпоследовательности
    for (int i = 1; i < n; ++i) {
        int maxlen = 1;
        ind[i] = -1;
        for (int j = 0; j < i; ++j) {
            calls++;
            if ((d[j] >= maxlen) && (a[j] < a[i])) { // подзадача:  ищем максимальную длину подпоследовательности для элемента
                maxlen = d[j]; // обновляем максимальное значнеие подпоследовательности
                ind[i] = j; // пишем предыдущее значние подпоследовательности для данного элемента
            }
        }
        d[i] = maxlen + 1; // пишем макс. длину подпоследовательности для данного элемента
        if (d[i] > len) {
            len = d[i]; // обновляем общее макс. значение
            last_index = i;
        }
    }
    vector<int> result;
    int index = last_index; // индекс элемента последовательности, который мы вставляем
    while (index != -1) { // пока последовательность не кончилась
        result.push_back(a[index]);
        index = ind[index];
    }
    
    for (int i = result.size() - 1; i >= 0; i--) { // выводим результат
        cout << result[i] << " ";
    }
    cout << "Количество переборов для  метода грубой силы: " << calls << endl;
}

int dynamic(vector<int> input) // метод (возвращает только длину)
{

    // создать пустой упорядоченный набор `s`. i-й элемент в `s` определяется как
    // наименьшее целое, которым заканчивается возрастающая последовательность длины `i`
    set<int> s;
    int calls = 0;
    // обрабатываем каждый элемент один за другим
    for (int i = 0; i < input.size(); i++)
    {
        calls += 1;
        // игнорировать текущий элемент, если он уже присутствует в наборе
        if (s.find(input[i]) != s.end()) {
            continue;
        }

        // вставляем текущий элемент в набор
        auto ret = s.insert(input[i]);

        // получить итератор для вставленного элемента
        set<int>::iterator it;
        if (ret.second) {
            it = ret.first;
        }

        // если элемент не вставлен в конец, то удаляем следующий
        // больший элемент из набора
        if (++it != s.end()) {
            s.erase(it);
        }
    }

    cout << "Количество вызовов для динамического метода: " << calls << endl;
    // длина ЛИС - это общее количество элементов в наборе
    return s.size();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Введите число элементов последовательности" << endl;
    int n;
    int x;
    cin >> n;
    vector<int> arr;
    for (int i = 0; i < n; i++) { // заполняем массив
        cin >> x;
        arr.push_back(x);
    }
    brute_force(arr);
    cout << endl;
    cout << dynamic(arr);
}