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

vector<int> suf_shift(string str) {
    int m = str.length()-1;
    vector<int> tab(m+1, m);
    vector<int> z(m, 0);
    int maxZidx = 0, maxZ = 0;
    for (int j = 1; j < m; ++j) {
        if (j <= maxZ) z[j] = min(maxZ - j + 1, z[j - maxZidx]);
        while (j + z[j] < m && str[m - 1 - z[j] == str[m - 1 - (j + z[j])]]) z[j]++;
        if (j + z[j] - 1 > maxZ) {
            maxZidx = j;
            maxZ = j + z[j] - 1;
        }
    }
    for (int j = m - 1; j > 0; j--) tab[m - z[j]] = j;
    for (int j = 1, r = 0; j <= m - 1; j++) {
        if (j + z[j] == m) {
            for (; r <= j; r++)
                if (tab[r] == m) tab[r] = j;
        }
    }
    reverse(tab.begin(), tab.end());
    return tab;
}





int search(string str, string substr) {
    int m = substr.length();
    int n = str.length()-1; 
    int i, j;
   vector<int> gs = suf_shift(substr);
   for (i = 0; i < gs.size(); i++) {
       cout << gs[i];
   }
   cout << endl;
   i = 0;
    while(i <= n-m){
        cout << endl << i;
        j = m - 1;
        while(j>0 && str[j+i] == substr[j]){
            --j;
            cout << j;
        }
        if (j <= 0)
            return(i);
        else {
            i += gs[j];
        }
    }
    return -1;
}

vector<string> num_search(string str) {
    string num = "";
    vector<string> vec;
    bool was_dig = false;
    bool was_space = false;
    for (int i = 0; i < str.length(); i++) {
        if (isdigit(str[i]) && ((was_dig == true) || (was_space == true))) {
            num = num + str[i];
            was_dig = true;
            was_space = false;
            if (i + 1 == str.length()) {
                vec.push_back(num);
            }
        }
        else {
            if ((str[i] == ' '))  {
                was_space = true;
                if ((was_dig == true) && (num.length() > 0)) {
                    vec.push_back(num);
                }
            }
            was_dig = false;
            num = "";
        }
    }
    return(vec);
}


int main()
{
    string str;
    string substr;
    cin >> str >> substr;
    int a = search(str, substr);
    cout << a;
}
