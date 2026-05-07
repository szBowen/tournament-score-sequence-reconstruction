#include<ostream>
#include"TournamentDegree.h"
#include"permu_combi.h"

int num = 100;

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
	//obj.read(num);
	//std::cout << obj;
	if (obj.restore()) {
		std::cout << obj;
		//obj.write(num);
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
		if (Error)break;
		
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
			///*
			TournDeg obj(i, score);
			if (!obj.restore()) {
				
				std::cout << "false" << std::endl;
			}
			//*/
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
		//std::cout << count << " ";

		delete[]score;
	}
	return 0;
}

int calctime() {
	// 记录开始时间
	auto start = std::chrono::high_resolution_clock::now();

	// 调用你想要测量时间的函数
	//calculation_all_11(4, 4, 100);
	//calculation_all_11(1, 12, 12);
	A1();

	// 记录结束时间
	auto end = std::chrono::high_resolution_clock::now();

	// 计算运行时间
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	// 输出结果
	std::cout << "Function took " << duration.count() << " milliseconds to execute." << std::endl;

	return 0;
}

int A3() {
	for (; num <= 102; num++) {
		calctime();
	}
	return 0;
}

int A4() {
	TournDeg obj;
	for (int i = 8; i <= 26; i+=2) {
		obj.read(i);
		//std::cout << obj << i << std::endl;
		if (!check(obj)) {
			std::cout << i << std::endl;
		}
	}
	return 0;
}

int A5() {
	TournDeg obj;
	for (int i = 4; i <= 14; i++) {
		obj.read(i);
		obj.write1(1000);
	}
	return 0;
}

int A6() {
	TournDeg obj;
	for (int i = 4; i <= 10000000; i++) {
		obj.Rand(1000);
		obj.restore();
		std::cout << i << " ";
	}
	return 0;
}

int main() {
	//A1();
	//calctime();
	//A3();
	//A4();
	//A5();
	A6();
	return 0;
}