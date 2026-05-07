#include<ostream>
#include"TournamentDegree.h"
#include"permu_combi.h"


int A1() {
	int score[4] = { 1, 2, 5, 15 };
	/*
	for (int i = 0; i < 10; i++) {
		score[i] = 7 * i;
	}
	*/
	TournDeg obj(4,score);
	///*
	//std::cin >> obj;
	//obj.read(11);
	std::cout << obj;
	if (obj.restore()) {
		std::cout << obj;
		obj.write(102);
	}
	else std::cout << "false" << std::endl;
	//*/
	/*i < 1000 
	int i = 0;
	int numexps = 16, numfile = 13;
	srand(static_cast<unsigned int>(time(NULL)));
	for (; i<2147483646; i++) {
		obj.Rand(30);
		std::cout << i << " ";
		if (!obj.restore()) {
			std::cout << "false" << std::endl;
			std::cout << "false" << std::endl;
			break;
		}
		if (needback) {
			std::cout << "start" << std::endl;
			obj.restore();
			obj.write(100);
			needback = false;
			break;
		}
		if (obj.exps[numexps] != 1) {
			std::cout << std::endl << obj;
			obj.write(numfile);
			numexps--;
			numfile++;
			if (numexps < 0) {
				break;
			}
		}
		
	}
	
	*/
	return 0;
}

#include <chrono>

int calculation_all_11(int minsize, int maxsize, int maxval) {
	int count = 0;
	for (int i = minsize; i <= maxsize; i++) {
		int* score = new int[i];
		CombiInit(i, score);

		for (;;) {
			/*
			TournDeg obj(i, score);
			if (!obj.restore()) {
				
				std::cout << "false" << std::endl;
			}
			*/
			/*
			else {
				if (i >= 4 && obj.exps[i - 4] != 1) {
					//std::cout << i << std::endl;
					//std::cout << obj;
				}
				
				count++;
				std::cout << count << " ";
			}
			*/
			count++;
			
			if (!Combi_next(i, maxval, score))break;
		}
		std::cout << count << " ";

		delete[]score;
	}
	return 0;
}

int calctime() {
	// 记录开始时间
	auto start = std::chrono::high_resolution_clock::now();

	// 调用你想要测量时间的函数
	//calculation_all_11(4, 4, 100);
	A1();

	// 记录结束时间
	auto end = std::chrono::high_resolution_clock::now();

	// 计算运行时间
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	// 输出结果
	std::cout << "Function took " << duration.count() << " milliseconds to execute." << std::endl;

	return 0;
}

int main() {
	//A1();
	calctime();
	return 0;
}