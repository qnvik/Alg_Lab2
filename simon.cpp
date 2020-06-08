#include <iostream>
#include <string>
#include <vector>
#include "tester.hpp"
using namespace std;

struct List {
    List *next;
    int data;
};

static int get_transition(const string &str, int p, vector<List *> &list, char c) {
    if (p < (int)str.size() - 1 && str[p + 1] == c) {
        return p + 1;
    } else if (p > -1) {
        for (List *node = list[p]; node != nullptr; node = node->next) {
            if (str[node->data] == c) {
                return node->data;
            }
        }
    }
    return -1;
}

static void set_transition(int p, int q, vector<List *> &list) {
    list[p] = new List{list[p], q};
}

static int preprocessing(const string &str, vector<List *> &list) {
    int ell = -1, k = -1;
    List *node = nullptr;

    for (int i = 1, size = str.size(); i < size; ++i) {
        k = ell;
        node = ell != -1 ? list[k] : nullptr;
        ell = -1;

        if (str[i] == str[k + 1]) {
            ell = k + 1;
        } else {
            set_transition(i - 1, k + 1, list);
        }

        for (; node != nullptr; node = node->next) {
            k = node->data;
            if (str[i] == str[k]) {
                ell = k;
            } else {
                set_transition(i - 1, k, list);
            }
        }
    }
    return ell;
}

void simon(const string &str, const string &sub, std::ostream *os) {
    vector<List *> list((int)str.size() - 2 + 1000, nullptr);
    int ell = preprocessing(str, list);
    int state = -1;

    for (int j = 0, size = sub.size(); j < size; ++j) {
        state = get_transition(str, state, list, sub[j]);

        if (state >= size - 1) {
            if (os != nullptr) {
                cout << j - size + 1 << ' ';
            }
            state = ell;
        }
    }

    for (auto &i : list)
        delete i;
}
