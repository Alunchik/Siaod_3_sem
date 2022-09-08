#include <iostream>
#include <bitset>
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>

using namespace std;

void task_1_a() {
    unsigned int x = 255; //11111111
    cout << endl << "изначальное число: " << x;   
    unsigned char maska = 1;
    x = x & (~(maska << 4)); //5 бит установливаем в 0 - получаем 239

    cout << endl << "результат: " << x << endl;
}

void task_1_b() {
    unsigned int x = 128; //10000000
    cout << endl << "изначальное число: " << x;
    unsigned char maska = 1;
    x = x | (maska << 6); //5 бит установливаем в 1 - получаем 192 
    cout << endl << "результат: " << x << endl;
}

void task_1_c() {
    unsigned int x = 25; // 11001
    const int n = sizeof(int)*8; // = 32 кол-во разрядов в int
    unsigned maska = (1 << n - 1); // 1 в старшем бите 32-разрядной сетки
    cout << "Начальный вид маски: " << bitset<n> (maska) << endl;
    cout << "Результат: ";
    for (int i = 1; i <= n; i++) {
        cout << ((x & maska) >> (n - i)); // смещение 1 в маске на разряд вправо
        maska = maska >> 1;
    }
    cout << endl;
}

void task_2_b() {
    unsigned long long arr = 0;
    unsigned int x;
    int n = 6; // количество чисел в массиве
    unsigned long long maska = 1;
    for (int i = 0; i < n; i++) {
        cin >> x;
        maska = 1;
        arr = arr | (maska << x);
    }
    cout << ("Отсортированный массив: ");
    for (int i = 0; i < 64; i++) {
        maska = 1;
        if (((maska << i) & arr) != 0) {
            cout << i << " ";
        }
    }
}

void task_2_c() {
    unsigned char arr[8] = {0,0,0,0,0,0,0,0};
    unsigned int x;
    int n = 6; // количество чисел в массиве
    unsigned char maska = 1 << 7;
    for (int i = 0; i < n; i++) {
        cin >> x;
        arr[x/8] = arr[x/8] | (maska >> (x%8));
    }
    cout << ("Отсортированный массив: ");
    for (int i = 0; i < 64; i++) {
        if (arr[i/8] & (maska >> (i%8))) {
            cout << i << " ";
        }
    }
}

void task_2_a() {
    unsigned char arr = 0;
    unsigned int x;
    short n = 8;
    unsigned char maska = 1;
    for (int i = 0; i < n; i++) {
        cin >> x;
        maska = 1;
        arr = arr | (maska << x);
    }
    cout << ("Отсортированный массив: ");
    for (int i = 1; i < n; i++) {
        maska = 1;
        if (((maska << i) & arr) != 0) {
            cout << i << " ";
        }
    }
}

void generate_file() {
    //int n = 8*1024*1024; // кол-во чисел
    vector<int> arr;
    for (int i = 0; i < 1000000; i++) {
        arr.push_back(i+1000000);
    }
    shuffle(arr.begin(), arr.end(), random_device());
    ofstream sorted_file("file.txt");
    if (sorted_file.is_open()) {
        for (int i = 0; i < arr.size(); i++) {
            sorted_file << arr[i] << " ";
        }
    }
    sorted_file.close();
}

void task_3_a() {
    time_t start;
    time_t end;
    const int n = 8*1024*1024; // 1 mb
    bitset<n>* arr = new bitset<n>(0);
    int x;

    ifstream unsorted("file.txt");


    if (unsorted.is_open()) {
        time(&start);
        while (unsorted >> x) {
            arr->set(x);
        }
        time(&end);
        unsorted.close();
    }

    time_t time_sort = end - start;

    ofstream sorted_file("file.txt");
    if (sorted_file.is_open()) {
        for (int i = 0; i < n; i++) {
            if (arr->test(i)) {
                sorted_file << i << " ";
            }
        }
        sorted_file.close();
    }
    cout << endl << "Время сортировки: " << time_sort << endl;
    cout << "Размер массива: " << arr->size() / 8 << " байт";
}




int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    task_2_c();
    system("pause");
    return 0;
}