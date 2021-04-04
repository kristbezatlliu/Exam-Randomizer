#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <filesystem>
#include <ctime>
#include <random>
#include <array>

using namespace std;

void shuffle_array(int arr[], int n)
{
	random_device rd;

	shuffle(arr, arr + n, mt19937(rd()));
}

int main() {
	string Rreshti;
	int nrPyetjeve = 0;
	int nrTezave;
	int line = 0;

	fstream pyetjetFile;
	pyetjetFile.open("Questions.txt");
	array<array<string, 5>, 30> vendet = {};

	if (pyetjetFile.is_open()) {
		while (getline(pyetjetFile, Rreshti)) {
			if (nrPyetjeve <= 30) {
				if (!Rreshti.empty()) {
					if (Rreshti.at(0) == '~') {
						vendet[nrPyetjeve][0] = Rreshti;
					}
					else if (Rreshti.at(0) == 'A' && Rreshti.at(1) == ')') {
						vendet[nrPyetjeve][1] = Rreshti;
					}
					else if (Rreshti.at(0) == 'B' && Rreshti.at(1) == ')') {
						vendet[nrPyetjeve][2] = Rreshti;
					}
					else if (Rreshti.at(0) == 'C' && Rreshti.at(1) == ')') {
						vendet[nrPyetjeve][3] = Rreshti;
					}
					else if (Rreshti.at(0) == 'D' && Rreshti.at(1) == ')') {
						vendet[nrPyetjeve][4] = Rreshti;
						nrPyetjeve++;
					}
				}
			}

			line++;
		}

		cout << "Sa teza deshironi te krijoni?" << endl;
		cin >> nrTezave;

		int h = _mkdir("Tezat");

		for (int i = 1; i <= nrTezave; i++) {
			fstream txtFile;
			txtFile.open("./Tezat/Teza" + to_string(i) + ".txt", fstream::out);

			int rendi[30];
			int rendiAlt[4] = { 1,2,3,4 };

			for (int c = 0; c <= nrPyetjeve; c++) {
				rendi[c] = c;
			}

			shuffle_array(rendi, nrPyetjeve);

			for (int c = 0; c < nrPyetjeve; c++) {
				shuffle_array(rendiAlt, 4);

				vendet[rendi[c]][rendiAlt[0]].replace(0, 2, "A)");
				vendet[rendi[c]][rendiAlt[1]].replace(0, 2, "B)");
				vendet[rendi[c]][rendiAlt[2]].replace(0, 2, "C)");
				vendet[rendi[c]][rendiAlt[3]].replace(0, 2, "D)");

				txtFile << vendet[rendi[c]][0] << endl;

				for (int h = 0; h < 4; h++) {
					txtFile << vendet[rendi[c]][rendiAlt[h]] << endl;
				}

				txtFile << "" << endl;
			}
		}

		pyetjetFile.close();

		return 0;
	}
	else {
		cout << "Ju lutem krijoni nje text file te quajtur 'Questions.txt' dhe lexoni 'readme' per instruksionet e dhena." << endl;
	}
}