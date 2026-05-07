#ifndef __PERMU_COMBI_H
#define __PERMU_COMBI_H
#include <iostream>
#include <fstream>



void Printpermu_combi(const int* number, int nDim) {
	std::cout << std::endl;
	for (int i = 0; i < nDim; i++) {
		std::cout << number[i] << " ";
	}
	std::cout << std::endl;
}

void CombiInit(int M, int* change) {
	for (int i = 0; i < M; i++)
		change[i] = i + 1;
}

bool Combi_next(int nDim, int max, int* change) {
	for (int i = 0; i < nDim; i++) {
		if ((i == nDim - 1 && change[i] < max) || (i < nDim - 1 && change[i] < change[i + 1] - 1)) {
			change[i] += 1;//printf("\n %d \n",i);
			CombiInit(i, change);
			return 1;
		}
	}
	return 0;
}

void CombiPrint(int M, int K, int* com, int nDim) {
	if (M <= 0) {
		Printpermu_combi(com, nDim);
		return;
	}
	if (K > 0) {
		com[K - 1] = M;
		CombiPrint(M - 1, K - 1, com, nDim);
	}
	if (K < M) {
		CombiPrint(M - 1, K, com, nDim);
	}
}

#endif 