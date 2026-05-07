#ifndef TOURNDEG_H
#define TOURNDEG_H

#include <algorithm> // 包含标准排序算法
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib> // 包含rand()和srand()
#include <ctime>
#include"show.h"
#include "Group.h"

int ctok = 0;
bool needback = false;
bool Error = false;

class TournDeg;
bool check(TournDeg& obj);

class TournDeg {
public:
    int* scores;
    int* exps;
    int size;
    bool sorted; // 用来跟踪scores是否已排序

    // 默认构造函数
    TournDeg() : scores(nullptr), exps(nullptr), size(0), sorted(false) {}

    TournDeg(int nsize) {
        Rand(nsize);
    }

    TournDeg(int nsize, int* score) {
        size = nsize;
        initMem(nsize);
        for (int i = 0; i < nsize; i++) {
            scores[i] = score[i];
            exps[i] = 0;
        }
    }

    void Rand(int nsize) {
        size = nsize;
        initMem(nsize);
        
        for (int i = 0; i < nsize; i++) {
            scores[i] = rand() % 20000;
            exps[i] = 0;
        }
        cut_reputition();
    }

    void cut_reputition() {
        checkAndSort();
        //showarr(scores, size, "scores_jener:");
        for (int i = 0; i < size; i++) {
            if (scores[i] <= ((i == 0) ? -1 : scores[i - 1])) {
                scores[i] = (i == 0) ? scores[i] + 1 : scores[i - 1] + 1;
            }
        }
    }

    // 拷贝构造函数
    TournDeg(const TournDeg& other) : size(other.size) {
        initMem(size);
        for (int i = 0; i < size; i++) {
            scores[i] = other.scores[i];
            exps[i] = other.exps[i];
        }
    }

    ~TournDeg() {
        delete[] scores;
        delete[] exps;
    }

    // 初始化内存
    void initMem(int sz) {
        delete[] scores;
        delete[] exps;
        size = sz;
        scores = new int[size];
        exps = new int[size];
        sorted = false; // 每次重新初始化内存时，设置排序状态为false
    }

    // 新增排序函数
    void checkAndSort() {
        if (!sorted) {
            sortScores();
            sorted = true;
        }
    }

    void sortScores() {
        std::vector<int> indices(size);
        std::generate(indices.begin(), indices.end(), [n = 0]() mutable { return n++; });

        std::sort(indices.begin(), indices.end(),
            [&](int i, int j) { return scores[i] < scores[j]; });

        std::vector<int> sortedScores(size);
        std::vector<int> sortedExps(size);
        for (int i = 0; i < size; i++) {
            sortedScores[i] = scores[indices[i]];
            sortedExps[i] = exps[indices[i]];
        }
        std::copy(sortedScores.begin(), sortedScores.end(), scores);
        std::copy(sortedExps.begin(), sortedExps.end(), exps);
    }

    // 读文件函数
    void read(int fileNum) {
        std::ostringstream oss;
        oss << "tourndeg" << fileNum << ".txt";
        std::ifstream inFile(oss.str());
        if (inFile) {
            inFile >> *this;
            sorted = false; // 读取文件后将sorted设置为false
        }
        inFile.close();
    }

    void write(int fileNum) {
        std::ostringstream oss;
        oss << "tourndeg" << fileNum << ".txt";
        std::ofstream outFile(oss.str());
        outFile << *this;
        outFile.close();
    }

    void write1(int fileNum) {
        std::ostringstream oss;
        oss << "tourndeg" << fileNum << ".txt";
        std::ofstream outFile(oss.str(), std::ios::app);
        int count = 0;
        std::cout << count << " " << size << std::endl;
        for (; count < size; ) {
            int i = 0;

            outFile << "$ ";
            if (count == 0)outFile << "\\{ ";
            for (i = 0; i < 8 && count + i < size; i++) {
                outFile << scores[count + i] << ", ";
            }
            if (count+8 >= size)outFile << "\\} ";
            outFile << "$ & $ ";
            if (count == 0)outFile << "\\{ ";
            for (i = 0; i < 8 && count + i < size; i++) {
                outFile << exps[count + i] << ", ";
            }
            if (count + 8 >= size)outFile << "\\} ";
            count += 8;

            outFile << "$ & \\\\ ";
        }
        outFile << "\\hline" << std::endl;
        outFile.close();
    }

    void w_error(int fileNum, bool appendMode, std::string baseFileName) {
        std::ostringstream oss;
        oss << baseFileName << fileNum << ".txt";
        std::string filename = oss.str();

        // 根据 appendMode 确定文件打开模式
        std::ofstream outFile;
        if (appendMode) {
            outFile.open(filename, std::ios::app); // 打开文件进行追加
        }
        else {
            outFile.open(filename); // 默认打开模式为覆盖（std::ios::out）
        }

        if (outFile) {
            outFile << *this; // 假设当前类已经定义了输出运算符重载
            outFile.close();
        }
        else {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
        }
    }


    // 重载 << 和 >> 运算符，>> 运算符在读取数据后不改变sorted状态
    friend std::ostream& operator<<(std::ostream& os, const TournDeg& td) {
        os << "Size: " << td.size << "\n";
        os << "Scores: ";
        for (int i = 0; i < td.size; i++) {
            os << td.scores[i] << " ";
        }
        os << "\nExponents: ";
        for (int i = 0; i < td.size; i++) {
            os << td.exps[i] << " ";
        }
        os << "\n";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, TournDeg& td) {
        std::string line;
        std::getline(is, line);
        std::istringstream iss(line.substr(5)); // 修改这里以匹配新的 "Size: " 标签长度
        int sz;
        iss >> sz;
        td.initMem(sz);
        std::getline(is, line);
        iss.str(line.substr(7)); // Scores:
        iss.clear();
        for (int i = 0; i < sz; i++) {
            iss >> td.scores[i];
        }

        std::getline(is, line);
        iss.str(line.substr(11)); // Exponents:
        iss.clear();
        for (int i = 0; i < sz; i++) {
            iss >> td.exps[i];
        }
        return is;
    }

    ////////////还原部分
    
    ////部分计算函数

    int calcBound(int curSz, int curVal, int score) {
        //std::cout << "Bound: " << curSz << " " << curVal << " " << score << std::endl;
        int a = 2 * (score - curSz) + 1;
        int sum = curVal - curSz * (curSz - 1) / 2;
        if (sum < 0)return -1;
        int delta = a * a + 8 * sum;
        return (a + static_cast<int>(sqrt(delta))) / 2;  // 取整的平方根
    }

    int calcBound_is_int(int curSz, int curVal, int score) {
        //std::cout << "Bound: " << curSz << " " << curVal << " " << score << std::endl;
        int a = 2 * (score - curSz) + 1;
        int sum = curVal - curSz * (curSz - 1) / 2;
        if (sum < 0)return -1;
        int delta = a * a + 8 * sum;
        int result = (a + static_cast<int>(sqrt(delta))) / 2;
        int Test = (result * 2) - a;
        if (Test * Test == delta)return result;
        else {
            return -1;
        }
    }

    int is_int(int a, int b) {
        int tmp = a / b;
        if (tmp * b == a) {
            return tmp;
        }
        else {
            return -1;
        }
    }

    bool int_equal(int x, int y) {
        if (y == 0)return x == 0;
        return x % y == 0;
    }

    bool pot(int* solRange, int size, int element) {
        for (int i = 0; i < size; i++) {
            if (int_equal(solRange[i], element)) {
                //std::cout << solRange[i] << " " << element << std::endl;
                return true;
            }
        }
        return false;
    }


    ////////

    int* Initgroup(int feed) {
        int* grpElems = new int[size - 1];
        grpElems[size - 2] = feed - scores[size - 2];
        for (int i = 0; i < size - 2; i++) {
            grpElems[i] = norm(feed - scores[i],grpElems[size-2]);
        }
        return grpElems;
    }

    int* InitminGens(int* grpElems, int mod) {
        int* minGens = new int[size - 1];
        /*
        minGens[size - 2] = minGen(grpElems[size - 2], mod);
        for (int i = size - 3; i >= 0; i--) {
            int gcdVal = gcd(grpElems[i], minGens[i + 1]);
            minGens[i] = minGen(gcdVal, mod);
        }
        */
        int m = scores[size - 1] - scores[size - 2];
        for (int i = size - 2; i >= 0; i--) {
            minGens[i] = gcd(grpElems[i], m);
            m = minGens[i];
        }
        return minGens;
    }

    int* InitsolRange(int mod) {
        int* solRange = new int[mod];
        for (int i = 0; i < mod; i++) {
            solRange[i] = norm(i * (2 * scores[size - 1] + 1 - 2 * i), mod);
        }
        return solRange;
    }

    bool restore() {
        checkAndSort();
        if (size <= 0)return true;
        if (size == 1)return end(0, 0, 0, 0, 0, nullptr, nullptr, nullptr);

        int mod = 0;
        int* grpElems = Initgroup(scores[size - 1]);

        mod = grpElems[size-2];

        int* minGens = InitminGens(grpElems, mod);

        int* solRange = InitsolRange(mod);

        /*
        showarr(scores, size, "score");
        showarr(grpElems, size - 1, "grpElems");
        showarr(minGens, size - 1, "minGens");
        showarr(solRange, mod, "solRange");
        */

        bool result = recur_restore(0, 0, 0, mod, grpElems, minGens, solRange);

        delete[] grpElems;
        delete[] minGens;
        delete[] solRange;

        return result;
    }

    bool recur_restore(int depth, int curSz, int curVal, int mod, int* grpElems, int* minGens, int* solRange) {
        if (depth >= size - 2) {
            /*
            showarr(solRange, mod, "solRange");
            showarr(exps, size, "exps");
            */
            for (int i = 0; i < mod; i++) {
                if (solRange[i] == 0) {
                    if (end(depth, i, curSz, curVal, mod, grpElems, minGens, solRange)) {
                        return true;
                    }
                }
            }
            //std::cout << "this " << std::endl << std::endl;
            //Error = true;
            return false;
        }

        int boundary = calcBound(curSz, curVal, scores[depth]);
        int i = 1;
        for (; i <= boundary; i++) {
            arrayAdd(solRange, mod, grpElems[depth], -1, mod);
            
            exps[depth] = i;
            

            if (pot(solRange, mod, minGens[depth + 1])) {
                /*
                showarr(solRange, mod, "solRange");
                showarr(exps, size, "exps");
                */
                if (recur_restore(depth + 1, curSz + i, curVal + i * scores[depth], mod, grpElems, minGens, solRange)) {
                    return true;
                }
                //Error = true;
            }
        }
        arrayAdd(solRange, mod, grpElems[depth], i - 1, mod);
        //exps[depth] = -100;
        return false;
    }

    bool end(int depth, int key, int curSz, int curVal, int mod, int* grpElems, int* minGens, int* solRange/*, int* exps*/) {
        if (size < 0) {
            throw std::runtime_error("Error: depth exceeds expected maximum at depth " + std::to_string(depth));
        }
        else if (size == 0) { return true; }
        else if(size == 1){
            exps[size - 1] = calcBound(0, 0, scores[size - 1]);
            if (check(*this)) return true;
            //exps[size - 1] = -100;
        }
        else if (size >= 2) {
            int sum = curSz*scores[size-1]-curVal;
            int h = 2 * scores[size - 1] + 1;
            int bound1 = h / 2;
            int bound2 = calcBound(curSz, curVal, scores[size - 2]);
            for (key; key <= bound1; key += mod) {
                int tmp1 = is_int(((h - 2 * key) * key - sum), mod);
                    //((h - 2 * key) * key - sum) / mod;
                if (tmp1 >= 1 && tmp1 <= bound2) {
                    int tmp2 = calcBound_is_int(curSz + tmp1, curVal + tmp1 * scores[size - 2], scores[size - 1]);
                    if (tmp2 >= 1) {//
                        exps[size - 2] = tmp1;
                        exps[size - 1] = tmp2;
                        if (check(*this)) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        return false;
    }

    /////////////////////
};

bool check(TournDeg& obj) {
    obj.checkAndSort();
    /*
    std::cout << "checking exps:" << std::endl;
    showarr(obj.exps, obj.size, "obj.exps");
    showarr(obj.scores, obj.size, "obj.scores");
    */
    //std::cout << "be there"<<std::endl;

    int sumProducts = 0, sumexps = 0, triangularNumber = 0;
    for (int i = 0; i < obj.size; i++) {
        sumProducts += obj.scores[i] * obj.exps[i];
        sumexps += obj.exps[i];
        triangularNumber = sumexps * (sumexps - 1) / 2;

        if (triangularNumber > sumProducts || obj.exps[i] == 0) {
            return false;
        }
    }

    return  triangularNumber == sumProducts;
}

#endif // TOURNDEG_H