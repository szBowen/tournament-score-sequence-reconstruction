#ifndef TOURNDEG_H
#define TOURNDEG_H

#include <algorithm> // 包含标准排序算法
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib> // 包含rand()和srand()
#include <ctime>
#include <vector>
#include"show.h"
#include "group.h"
#include <list>
#include <map>

struct re_part {
    int preSz = 0;
    int preVal = 0;
    int num = 0;
};

struct Info_recall {
    std::list<re_part> re;
};

struct Info_val {
    std::map<int, Info_recall> val;
};

struct Info_size {
    std::map<int, Info_val> size;
};

std::map<int, Info_size> Info_layer;
std::map<int, Info_recall> Info_final;
bool good;

void Init_Info() {
    Info_layer = std::map<int, Info_size>();
    Info_final = std::map<int, Info_recall>();
}

class TournDeg;
bool check(TournDeg& obj);

class TournDeg {
public:
    std::vector<int> scores;
    std::vector<int> exps;
    int size;
    bool sorted; // 用来跟踪scores是否已排序

    // 默认构造函数
    TournDeg() : size(0), sorted(false) {}

    TournDeg(int nsize, int maxval) {
        Rand(nsize, maxval);
    }

    TournDeg(int nsize, int* score) {
        size = nsize;
        initMem(nsize);
        for (int i = 0; i < nsize; i++) {
            scores[i] = score[i];
            exps[i] = 0;
        }
    }

    void Rand(int nsize, int maxval) {
        size = nsize;
        initMem(nsize);
        
        for (int i = 0; i < nsize; i++) {
            scores[i] = rand() % maxval;
            exps[i] = 0;
        }
        scores[size - 1] = maxval;
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
    }

    // 初始化内存
    void initMem(int sz) {
        size = sz;
        scores.resize(size);
        exps.resize(size);
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
        std::copy(sortedScores.begin(), sortedScores.end(), scores.begin());
        std::copy(sortedExps.begin(), sortedExps.end(), exps.begin());
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
        std::cout << count <<" "<<size << std::endl;
        for (; count<size; ) {
            int i = 0;
            
            outFile << "$ ";
            for (i = 0; i < 10&&count+i<size; i++) {
                outFile << scores[count + i] << ", ";
            }
            outFile << "& ";
            for (i = 0; i < 10 && count + i < size; i++) {
                outFile << exps[count + i] << ", ";
            }
            count += 10;
            outFile << "\\ ";
        }
        outFile << "\hline";
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
            os << td.exps[i] << ", ";
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
        int delta = a * a + 8 * (curVal - curSz * (curSz - 1) / 2);
        if (delta < 0)return -1;
        return (a + static_cast<int>(sqrt(delta))) / 2;  // 取整的平方根
    }


    ////////
    
    void InitInfo_recall(Info_recall& infoRecall, int layer) {
        infoRecall.re.clear();
        //std::cout << " Init_recall ";

        if (layer == 0) {
            re_part Thisrp = { 0, 0, -1 };
            infoRecall.re.push_back(Thisrp);
        }
    }
    /*
    void InitInfo_val(Info_val& infoVal, int layer) {
        int bound = ((layer >= 1) ? (2 * scores[layer - 1] + 1) * scores[layer - 1] + 1 : 1);
        infoVal.val.resize(bound);
        //std::cout << " Init_val ";

        for (int i = 0; i < bound; i++) {
            InitInfo_recall(infoVal.val[i], layer);
        }
    }
    
    void InitInfo_size(Info_size& infoSize, int layer) {
        int bound = ((layer >= 1) ? 2 * scores[layer - 1] + 2 : 1);
        infoSize.size.resize(bound);
        //std::cout << " Init_size ";

        for (int i = 0; i < bound; i++) {
            InitInfo_val(infoSize.size[i], layer);
        }
    }

    void InitInfo_layer(int layer) {
        Info_layer.resize(layer + 1);
        //std::cout << " Init_layer ";

        for (int i = 0; i < layer + 1; i++) {
            InitInfo_size(Info_layer[i], i);
        }
    }
    */

    bool int_equal(int x, int y) {
        if (y == 0)return x == 0;
        return x % y == 0;
    }

    bool pot(int* solRange, int size, int element, int add) {
        for (int i = 0; i < size; i++) {
            if (int_equal(modAdd(solRange[i] ,add, 1, size), element)) {
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
            grpElems[i] = norm(feed - scores[i], grpElems[size - 2]);
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

    void calInfo() {
        //InitInfo_layer(this->size - 1);
        //std::cout << "this" << std::endl;
        //std::cout << *this;
        InitInfo_recall(Info_layer[0].size[0].val[0], 0);
        int mod = 0;
        int* grpElems = Initgroup(scores[size - 1]);

        mod = grpElems[size - 2];

        int* minGens = InitminGens(grpElems, mod);

        int* solRange = InitsolRange(mod);

        /*
        showarr(scores, size, "score");
        showarr(grpElems, size - 1, "grpElems");
        showarr(minGens, size - 1, "minGens");
        showarr(solRange, mod, "solRange");
        */
        for (int i1 = 1; i1 <= size - 1; i1++) {
            //std::cout << "layer: " << i1 << " ";
            int bound2 = 2 * scores[i1 - 1] + 2;
            //int bound3 = ((i1 == 1) ? 1 : 2 * scores[i1 - 2] + 2);
            //int bound4 = ((i1 == 1) ? 1 : (2 * scores[i1 - 2] + 1) * scores[i1 - 2] + 1);
            for (int i2 = 1; i2 < 2; i2++) {
                int add2 = i2 * scores[i1 - 1];
                /*
                for (int i3 = 0; i3 < bound3; i3++) {
                    for (int i4 = 0; i4 < bound4; i4++) {
                        if (!Info_layer[i1 - 1].size[i3].val[i4].re.empty()) {
                            if (calcBound(i3, i4, scores[i1 - 1]) >= i2) {
                                //if (Info_layer[i1].size[i3 + i2].val[i4 + add2].re.empty()) {
                                    re_part Thisrp4 = { i3, i4, i2 };
                                    Info_layer[i1].size[i3 + i2].val[i4 + add2].re.push_back(Thisrp4);
                                //}
                                
                            }
                        }
                    }
                }
                */
                int tmpbound2_1 = 0;
                for (auto& Mi3 : Info_layer[i1 - 1].size) {
                    int i3 = Mi3.first;
                    for (auto& Mi4 : Mi3.second.val) {
                        int i4 = Mi4.first;
                        int tmpbound2_2 = calcBound(i3, i4, scores[i1 - 1]);
                        if (tmpbound2_2 >= i2) {
                            
                            if (pot(solRange, mod, minGens[i1], scores[this->size - 1] * (i3 + i2) - i4 - add2)) {
                                if (Info_layer[i1].size[i3 + i2].val[i4 + add2].re.empty()) {
                                    re_part Thisrp4 = { i3, i4, i2 };
                                    Info_layer[i1].size[i3 + i2].val[i4 + add2].re.push_back(Thisrp4);
                                }
                            }

                        }
                        if (tmpbound2_2 > tmpbound2_1) {
                            tmpbound2_1 = tmpbound2_2;
                        }
                    }
                }
                if (bound2 > tmpbound2_1) {
                    bound2 = tmpbound2_1;
                }
            }
            for (int i2 = 2; i2 < bound2; i2++) {
                int add2 = i2 * scores[i1 - 1];
                for (auto& Mi3 : Info_layer[i1 - 1].size) {
                    int i3 = Mi3.first;
                    for (auto& Mi4 : Mi3.second.val) {
                        int i4 = Mi4.first;
                        int tmpbound2_2 = calcBound(i3, i4, scores[i1 - 1]);
                        if (tmpbound2_2 >= i2) {

                            if (pot(solRange, mod, minGens[i1], scores[this->size - 1] * (i3 + i2) - i4 - add2)) {
                                if (Info_layer[i1].size[i3 + i2].val[i4 + add2].re.empty()) {
                                    re_part Thisrp4 = { i3, i4, i2 };
                                    Info_layer[i1].size[i3 + i2].val[i4 + add2].re.push_back(Thisrp4);
                                }
                            }

                        }
                    }
                }
            }
        }
        delete[] grpElems;
        delete[] minGens;
        delete[] solRange;
        //std::cout << " end_calInfo ";
        //showInfo();
    }

    int eqcalcbound(int curSz, int curVal, int score) {
        //std::cout << "Bound: " << curSz << " " << curVal << " " << score << std::endl;
        int a = 2 * (score - curSz) + 1;
        int delta = a * a + 8 * (curVal - curSz * (curSz - 1) / 2);
        if (delta < 0)return -1;
        int root = sqrt(delta);
        int squre = root * root;
        if (squre == delta) {
            int tmp = (a + root) % 2;
            if (tmp == 0) {
                tmp = (a + root) / 2;
                if (tmp >= 1)return tmp;
            }
        }
        return -1;
    }

    bool restore() {
        checkAndSort();
        if (size <= 0)return true;
        if (size == 1) {
            exps[size - 1] = calcBound(0, 0, scores[size - 1]);
            if (check(*this)) {
                return true;
            }
            else {
                return false;
            }
        }
        int bound_final = 2 * scores[this->size - 1] + 2;
        /*
        Info_final.resize(bound_final);
        for (int i = 0; i < bound_final; i++) {
            InitInfo_recall(Info_final[i], 2);
        }
        */
        //std::cout << " calInfo ";
        calInfo();
        /*
        int bound1 = 2 * scores[size - 2] + 1 + 1;
        int bound2 = (2 * scores[size - 2] + 1) * scores[size - 2] + 1;
        for (int i1 = 1; i1 < bound1; i1++) {
            for (int i2 = 1; i2 < bound2; i2++) {
                if (!Info_layer[size - 1].size[i1].val[i2].re.empty()) {
                    int tmp = eqcalcbound(i1, i2, scores[size - 1]);
                    if (tmp != -1) {
                        re_part Thisrp4 = { i1, i2, tmp };
                        Info_final[tmp].re.push_back(Thisrp4);
                    }
                }
            }
        }
        */
        for (auto& Mi1 : Info_layer[size - 1].size) {
            int i1 = Mi1.first;
            for (auto& Mi2 : Mi1.second.val) {
                int i2 = Mi2.first;
                int tmp = eqcalcbound(i1, i2, scores[size - 1]);
                if (tmp != -1) {
                    re_part Thisrp4 = { i1, i2, tmp };
                    Info_final[tmp].re.push_back(Thisrp4);
                }
            }
        }
        //return true;
        good = false;
        if (print_all()) {
            return true;
        }
        

        /*
        showarr(scores, size, "score");
        showarr(grpElems, size - 1, "grpElems");
        showarr(minGens, size - 1, "minGens");
        showarr(solRange, mod, "solRange");
        */

        return false;
    }

    // 输出 Info_recall
    void showrecall(Info_recall& recall) {
        for (std::list<re_part>::iterator i1 = recall.re.begin(); i1 != recall.re.end(); i1++) {
            std::cout << "Info: " << i1->preSz << " " << i1->preVal << " " << i1->num << std::endl;
        }
    }

    // 输出 Info_val
    void showval(Info_val& val, int layer) {
        /*
        if (layer < 1)return;
        
        int bound = (2 * scores[layer - 1] + 1) * scores[layer - 1] + 1;
        for (int i = 0; i < bound; i++) {
            std::cout << "val: " << i << " ,";
            showrecall(val.val[i]);
        }
        */
        if (layer < 0)return;
        for (auto& Mi : val.val) {
            std::cout << "val: " << Mi.first << " ,";
            showrecall(Mi.second);
        }
    }

    // 输出 Info_size
    void showsize(Info_size& size, int layer) {
        /*
        if (layer < 1)return;
        
        int bound = 2 * scores[layer - 1] + 2;
        for (int i = 0; i < bound; i++) {
            std::cout << "size: " << i << " ,";
            showval(size.size[i], layer);
        }
        */
        if (layer < 0)return;
        for (auto& Mi : size.size) {
            std::cout << "size: " << Mi.first << " ,";
            showval(Mi.second, layer);
        }
    }

    // 输出 Info_full
    void showInfo() {
        /*
        int bound1 = 2 * scores[size - 1] + 2;
        for (int i1 = 0; i1 < bound1; i1++) {
            showrecall(Info_final[i1]);
        }
        for (int i1 = size-1; i1 >=0; i1--) {
            std::cout << "layer: " << i1 << " ,";
            showsize(Info_layer[i1], i1);
        }
        std::cout << "layer: 0 ,";
        showrecall(Info_layer[0].size[0].val[0]);
        */
        for (auto& Mi1 : Info_final) {
            showrecall(Mi1.second);
        }
        for (auto& Mi1 : Info_layer) {
            std::cout << "layer: " << Mi1.first << " ,";
            showsize(Mi1.second, Mi1.first);
        }
    }

    /////////////////////

    bool print_all_part(int curSz, int curVal, int layer) {
        if (good)return true;
        if (layer < 1) {
            if (check(*this)) {
                std::cout << *this;
                //
                //good = true;
                return true;
            }
            else {
                std::cout << "this false" << std::endl;
                return false;
            }
        }
        for (std::list<re_part>::iterator i1 = Info_layer[layer].size[curSz].val[curVal].re.begin(); i1 != Info_layer[layer].size[curSz].val[curVal].re.end(); i1++) {
            int sz = i1->preSz;
            int val = i1->preVal;
            exps[layer - 1] = i1->num;
            print_all_part(sz, val, layer - 1);
            if (good)return true;
        }
        return false;
    }

    bool print_all() {
        int Return = false;
        /*
        int bound1 = 2 * scores[size - 1] + 2;
        for (int i1 = 1; i1 < bound1; i1++) {
            if (!Info_final[i1].re.empty()) {
                for (std::list<re_part>::iterator i2 = Info_final[i1].re.begin(); i2 != Info_final[i1].re.end(); i2++) {
                    int sz = i2->preSz;
                    int val = i2->preVal;
                    exps[size - 1] = i2->num;
                    if (print_all_part(sz, val, size - 1)) {
                        Return = true;
                    }
                    if (good)return true;
                }
            }
        }
        */
        for (auto& Mi1 :Info_final) {
            for (std::list<re_part>::iterator i2 = Mi1.second.re.begin(); i2 != Mi1.second.re.end(); i2++) {
                int sz = i2->preSz;
                int val = i2->preVal;
                exps[size - 1] = i2->num;
                if (print_all_part(sz, val, size - 1)) {
                    Return = true;
                }
                if (good)return true;
            }
        }
        return Return;
    }

    //////////////////////////
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