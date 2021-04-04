#include "person.h"
extern int* gPersonHave;
extern int* gPersonMoney;
void InitAllPerson() {
	gPersonHave = new int[7];
	gPersonMoney = new int[7];
	gPersonMoney[0] = 0;
	gPersonMoney[1] = 1000;
	gPersonMoney[2] = 2000;
	gPersonMoney[3] = 3000;
	gPersonMoney[4] = 5000;
	gPersonMoney[5] = 6000;
	gPersonMoney[6] = 7000;
	std::ifstream fin;
	fin.open("pdata");
	if (!fin) {
		gPersonHave[0] = 1;
		for (int i = 1; i < 7; i++) {
			gPersonHave[i] = 0;
		}
		std::ofstream fout;
		fout.open("pdata");
		for (int i = 0; i < 7; i++) {
			fout << gPersonHave[i];
			fout << " ";
		}
		fout.close();
		return;
	}
	for (int i = 0; i < 7; i++) {
		fin >> gPersonHave[i];
	}
	fin.close();
}

void BuyPerson(int person_num) {
	std::ofstream fout;
	gPersonHave[person_num] = 1;
	fout.open("pdata");
	for (int i = 0; i < 7; i++) {
		fout << gPersonHave[i];
		fout << " ";
	}
	fout.close();
}