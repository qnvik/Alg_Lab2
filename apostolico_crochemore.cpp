#include <iostream>
#include <string>
#include <vector>
#include "tester.hpp"
using namespace std;

static void preprocessing(const string &str, vector<int> &v) {
    int j = v[0] = -1;

    for (int i = 0, size = str.size(); i < size;) {
        for (; j > -1 && str[i] != str[j]; j = v[j]);

        ++i, ++j;
        v[i] = str[i] == str[j] ? v[j] : j;
    }
}

void apostolico_crochemore(const string &str, const string &sub, std::ostream *os) {
    int size = str.size();
    vector<int> v(size);
    int ell = 1;

    preprocessing(str, v);
    for (; str[ell - 1] == str[ell]; ++ell);
    ell == size ? ell = 0 : 0;

    for (int i = ell, j = 0, k = 0; j <= (int)sub.size() - size;) {
        for (; i < size && str[i] == sub[i + j]; ++i);

        if (i >= size) {
            for (; k < ell && str[k] == sub[j + k]; ++k);
            if (k >= ell && os != nullptr) {
                *os << j << ", ";
            }
        }

        j += i - v[i];
        if (i == ell) {
            k = max(0, k - 1);
        } else if (v[i] <= ell) {
            k = max(0, v[i]);
            i = ell;
        } else {
            k = ell;
            i = v[i];
        }
    }
}
