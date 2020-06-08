#pragma once
#include <deque>
#include <fstream>
#include <string>
#include <stdexcept>

class Reader {
    std::deque<std::string> file_;
public:
    explicit Reader(const std::string &file) {
        if (std::ifstream ifile(file); ifile) {
            for (std::string temp; std::getline(ifile, temp);) {
                file_.push_back(std::move(temp));
            }
        } else {
            throw std::logic_error("file does not exist");
        }
    }

    bool empty() const {
        return file_.empty();
    }

    std::string get() {
        std::string str = std::move(file_.front());
        file_.pop_front();
        return str;
    }
};
