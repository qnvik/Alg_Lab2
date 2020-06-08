#pragma once
#include "reader.hpp"
#include <chrono>
#include <functional>
#include <iostream>
#include <string>

void apostolico_crochemore(const std::string &str, const std::string &sub, std::ostream *os);
void simon(const std::string &str, const std::string &sub, std::ostream *os);
void two_way(const std::string &str, const std::string &sub, std::ostream *os);

class Tester {
    Reader data_;
    Reader example_;

    std::string data_file_name_;
    std::string example_file_name_;

    std::function<void(const std::string &, const std::string &, std::ostream *)> algorithm_;
public:
    Tester(const std::string &data, const std::string &ex, std::function<void(const std::string &, const std::string &, std::ostream *)> algorithm)
        : data_(data)
        , example_(ex)
        , data_file_name_(data)
        , example_file_name_(ex)
        , algorithm_(algorithm) {}

    void test() {
        std::chrono::system_clock::time_point start_tp, end_tp;

        while (!data_.empty() && !example_.empty()) {
            std::string d = data_.get();
            std::string e = example_.get();
            std::chrono::nanoseconds sum(0);

            std::cout << "<<" << e << ">> ";
            algorithm_(d, e, &std::cout);
            std::cout << std::endl;

            for (int i = 0; i < 100; ++i) {
                start_tp = std::chrono::system_clock::now();
                algorithm_(d, e, nullptr);
                end_tp = std::chrono::system_clock::now();
                sum += end_tp - start_tp;
            }

            std::cout << 100 << ' ' << (sum.count() / 10) << std::endl;
        }
    }
};
