#ifndef GROUP_H
#define GROUP_H

struct EqInfo {
    int x;
    int y;
    int a;
    int b;
    bool good;
};

// 使用扩展欧几里得算法求解ax + by = gcd(a, b)
int extGCD(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

// 函数找到最小正整数x
void toMinPosX(EqInfo& info) {
    int k = (info.x > 0) ? -info.x / info.b : -info.x / info.b + 1;
    info.x += k * info.b;
    info.y -= k * info.a;
}

int gcdRec(int& a, int& b) {
    if (b == 0) {
        return a;
    }
    else {
        a = a % b;
        return gcdRec(b, a);
    }
}

int gcd(int a, int b) {
    int num1 = (a > b) ? a : b;
    int num2 = (a > b) ? b : a;
    return gcdRec(num1, num2);
}

int norm(int a, int n) {
    return ((a % n) + n) % n;
}

int minGen(int g, int n) {
    int normalized_g = norm(g, n);
    int result = gcd(normalized_g, n);
    return result == 0 ? n : result;
}

int modAdd(int a, int b, int k, int n) {
    a = norm(a, n);
    b = norm(b, n);

    int gen = minGen(b, n);
    k = k % (n / gen);

    return norm(a + k * b, n);
}

// 对整数数组中的每个元素执行 modAdd 操作
void arrayAdd(std::vector<int> array, int size, int add_element, int multiple, int modulus) {
    for (int i = 0; i < size; ++i) {
        array[i] = modAdd(array[i], add_element, multiple, modulus);
    }
}


#endif