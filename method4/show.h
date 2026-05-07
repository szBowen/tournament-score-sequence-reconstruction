#ifndef SHOW_H
#define SHOW_H
#include <iostream>
#include <iomanip> // 包含setw函数所需的头文件
#include <string>

void showarr(int* arr, int size, std::string s) {
    std::cout << s << ": " << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << std::setw(6) << arr[i]<<","; // 设置每个数字的显示宽度为3
    }
    std::cout << std::endl;
}

#endif