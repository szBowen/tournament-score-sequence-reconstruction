#include<ostream>
#include"TournamentDegree.h"
#include"permu_combi.h"


int i_A2 = 80;
int i_size = 20;

int A1() {
	int score[4] = { 2, 4, 7, 14 };
	/*
	for (int i = 0; i < 10; i++) {
		score[i] = 7 * i;
	}
	*/
	std::cout << "start" << std::endl;
	TournDeg obj(4, score);
	///*
	//std::cin >> obj;
	//obj.read(11);
	std::cout << obj;
	//obj.calInfo();
	if (obj.restore()) {
		std::cout << obj;
	}
	else {
		std::cout << "false" << std::endl;
	}
	return 0;
}

int A2() {
	TournDeg obj;

	for (int i = i_size; i <= i_size; i += 1) {
		obj.Rand(i_size,i_A2);//28
		//std::cout << i << " ";
		if (obj.restore()) {
			//std::cout << obj;
			//obj.write(i);
			obj.print_all();
		}
		else {
			std::cout << "false" << std::endl;
		}
	}
	return 0;
}

int A2_1() {
	int con = 0;

	for (int i1 = 1; i1 <= i_size; i1++) {
		for (int i2 = 1; i2 <= 2 * i_A2 + 1; i2++) {
			for (int i3 = 1; i3 <= 2 * i_A2 + 1; i3++) {
				for (int i4 = 1; i4 <= (2 * i_A2 + 1) * i_A2; i4++) {
					for (int Const = 1; Const <= 8; Const++) {
						con = 0;
					}
				}
			}
		}
	}
	return 0;
}

#include <chrono>

int calctime() {
	// 记录开始时间
	Init_Info();
	auto start = std::chrono::high_resolution_clock::now();

	// 调用你想要测量时间的函数
	//calculation_all_11(4, 4, 100);
	//A1();
	//A2();
	A2_1();

	// 记录结束时间
	auto end = std::chrono::high_resolution_clock::now();

	// 计算运行时间
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	// 输出结果
	//std::cout << "Function took " << duration.count() << " milliseconds to execute." << std::endl;
	std::cout << '(' << i_size << ", " << ((double)duration.count())/1000 << ")" << std::endl;

	return 0;
}


int A3() {
	for (; i_A2 >=8; i_A2-=2) {
		//std::cout << i_A2 << std::endl;
		calctime();
		//int contin = 0;
		//std::cin >> contin;
		//if (contin >= 0)i_A2 = 23;
	}
	return 0;
}

int A3_1() {
	for (; i_size >= 7; i_size -= 1) {
		//std::cout << i_A2 << std::endl;
		calctime();
		//int contin = 0;
		//std::cin >> contin;
		//if (contin >= 0)i_A2 = 23;
	}
	return 0;
}

int A4() {
	TournDeg obj;
	for (int i = 1; i <= 14; i++) {
		obj.read(i);
		obj.write1(1000);
	}
	return 0;
}


int main() {
	srand(time(NULL));
	//A1();
	A2();
	//A3_1();
	//calctime();
	/*
	int Text = 0;
	for (; Text >= 0; std::cin >> Text) {
		i_A2 = 28;
		A3();
	}
	*/
	//A4();
	
	return 0;
}