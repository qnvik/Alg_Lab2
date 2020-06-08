#include <cstring>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include "tester.hpp"
using namespace std;

static int max_suffix(const string &str, int &p, function<bool(char, char)> f) {
    int ms = -1;
    char a, b;

    for (int j = 0, k = p = 1, size = str.size(); j + k < size;) {
        a = str[j + k];
        b = str[ms + k];

        if (f(a, b)) {
            j += k;
            k = 1;
            p = j - ms;
        } else if (a == b)
            if (k == p) {
                j += p;
                k = 1;
            } else {
                ++k;
            }
        else {
            ms = j;
            j = ms + 1;
            k = p = 1;
        }
    }
    return ms;
}

void two_way(const string &str, const string &sub, std::ostream *os) {
    int ell, per, p, q;

    int i = max_suffix(str, p, [](char a, char b) {
        return a < b;
    });

    int j = max_suffix(str, q, [](char a, char b) {
        return a > b;
    });

    if (i > j) {
        ell = i;
        per = p;
    } else {
        ell = j;
        per = q;
    }

    int size = str.size();
    if (memcmp(str.data(), str.data() + per, ell + 1) == 0) {
        int diff = (int)sub.size() - size;
        int memory = -1;

        for (j = 0; j <= diff;) {
            for (i = max(ell, memory) + 1; i < size && str[i] == sub[i + j]; ++i);

            if (i >= size) {
                for (i = ell; i > memory && str[i] == sub[i + j]; --i);

                if (i <= memory && os != nullptr) {
                    *os << j << ", ";
                }
                j += per;
                memory = size - per - 1;
            } else {
                j += i - ell;
                memory = -1;
            }
        }
    } else {
        int diff = (int)sub.size() - str.size();
        per = max(ell + 1, size - ell - 1) + 1;

        for (j = 0; j <= diff;) {
            for (i = ell + 1; i < size && str[i] == sub[i + j]; ++i);

            if (i >= size) {
                for (i = ell; i >= 0 && str[i] == sub[i + j]; --i);

                if (i < 0 && os != nullptr) {
                    *os << j << ", ";
                }
                j += per;
            } else {
                j += i - ell;
            }
        }
    }
}
