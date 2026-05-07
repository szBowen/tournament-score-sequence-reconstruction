#ifndef __PERMU_COMBI_H
#define __PERMU_COMBI_H
#include <iostream>
#include <fstream>
using namespace std;



void Printpermu_combi(const int* number, int nDim);
void CombiInit(int M,int* change);
bool Combi_next(int nDim,int max,int* change);
void CombiPrint(int M, int K, int* com, int nDim);

#endif 