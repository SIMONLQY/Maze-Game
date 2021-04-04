#include "money.h"

int GetMoney() {
	std::ifstream fin;
	fin.open("mdata");
	if (!fin) {
		std::ofstream fout;
		fout.open("mdata");
		fout << 0;
		fout.close();
		fin.open("mdata");
	}
	int num;
	fin >> num;
	fin.close();
	return num;
}

void ChangeMoney(int money) {
	std::ifstream fin;
	fin.open("mdata");
	if (!fin) {
		std::ofstream fout;
		fout.open("mdata");
		fout << 0;
		fout.close();
		fin.open("mdata");
	}
	int num;
	fin >> num;
	num += money;
	std::ofstream fout("mdata");
	fout << num;
	fout.close();
	fin.close();
}