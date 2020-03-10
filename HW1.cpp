#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

//code referenced from https://drive.google.com/file/d/1O099oR3hEY0jXFuH0KiEW-32sRq3Mf4V/view

class Kiwi {
private:
	int** field;
	int s;
	int ripe;
	int rotten;

public:
	Kiwi(ifstream &i);
	void replaceRow(int);
	void incrementRow(int);
	bool needsHarvest(int);
	void farm();

	int getKiwi(int, int);
	int getSize();
	int getRipe();
	int getRotten();
};

Kiwi::Kiwi(ifstream &i) {
	i >> s;
	ripe = 0;
	rotten = 0;
	field = new int *[s];
	for (int i = 0; i < s; i++) {
		field[s] = new int[s];
	}
	for (int i = 0; i < s; i++)
		for (int k = 0; k < s; k++)
			i >> field[i][k];
}

void Kiwi::replaceRow(int r) {
	for (int i = 0; i < s; i++)
		field[r][i] = 0;
}

void Kiwi::incrementRow(int r) {
	for (int i = 0; i < s; i++)
		field[r][i] += 1;
}

bool Kiwi::needsHarvest(int r) {
	int atleastRipe = 0;
	for (int i = 0; i < s; i++) {
		if (field[r][i] >= 6)
			atleastRipe += 1;
	}
	if (atleastRipe >= s / 2) {
		for (int i = 0; i < s; i++) {
			if (field[r][i] >= 6 && field[r][i] <= 8)
				ripe += 1;
			else if (field[r][i] >= 9)
				rotten += 1;
		}
		return true;
	}
	else
		return false;
}

void Kiwi::farm() {
	for (int i = 0; i < 7; i++)
		for (int k = 0; k < s; k++) {
			if (needsHarvest(k))
				replaceRow(k);
			else
				incrementRow(k);
		}
	for (int i = 0; i < s; i++)
		if (needsHarvest(i))
			replaceRow(i);
}

int Kiwi::getKiwi(int r, int c) {
	return field[r][c];
}

int Kiwi::getSize() {
	return s;
}

int Kiwi::getRipe() {
	return ripe;
}

int Kiwi::getRotten() {
	return rotten;
}

int main(int argc, char* argv[])
{
	if (argc != 3 && argc != 2) {
		cout << "Invalid arguments!\n";
		return 1;
	}
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");

	ifstream file;
	file.open(input);

	ofstream ofile;
	ofile.open(output);

	Kiwi kiwiFarm(file);
	kiwiFarm.farm();

	for (int i = 0; i < kiwiFarm.getSize(); i++)
		for (int k = 0; k < kiwiFarm.getSize(); k++) {
			ofile << kiwiFarm.getKiwi(i, k) << " ";
			ofile << endl;
		}
	ofile << "Harvested kiwis: " << kiwiFarm.getRipe() << endl;
	ofile << "Rotten kiwis: " << kiwiFarm.getRotten();

	file.close();
	ofile.close();

	return 0;
}
