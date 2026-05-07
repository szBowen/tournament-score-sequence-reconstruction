#ifndef SHOW_H
#define SHOW_H
#include <iostream>
#include <iomanip> // 包含setw函数所需的头文件
#include <string>
#include <vector>
#include "Group.h"

void showarr(std::vector<int> arr, int size, std::string s) {
    std::cout << s << "(" << size << ")" << ": " << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << std::setw(6) << arr[i]<<","; // 设置每个数字的显示宽度为6
    }
    std::cout << std::endl;
}

void showarr(std::vector<std::vector<int>>& arr, int size, std::string s) {
    std::cout << s << "(" << size << ")" << ": " << std::endl;
    for (const auto& row : arr) {
        for (const auto& elem : row) {
            std::cout << std::setw(6) << elem << ","; // 设置每个数字的显示宽度为6
        }
        std::cout << std::endl;
    }
}

void showarr(std::vector<std::vector<EqInfo>>& arr, int size, std::string s) {
    std::cout << s << "(" << size << ")" << ": " << std::endl;
    for (const auto& row : arr) {
        for (const auto& elem : row) {
            std::cout << "{"
                << "x: " << std::setw(6) << elem.x << ", "
                << "y: " << std::setw(6) << elem.y << ", "
                << "a: " << std::setw(6) << elem.a << ", "
                << "b: " << std::setw(6) << elem.b << ", "
                << "good: " << std::boolalpha << elem.good << "}, ";
        }
        std::cout << std::endl;
    }
}

#endif