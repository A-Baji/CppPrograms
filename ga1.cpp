#include "pch.h"
#include "ArgumentManager.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct player {
	string name;
	string jersey;
	string pos;
	player* next;
};

class list {
private:
	player* head;
	player* tail;
public:
	list();
	void addPlayer(string, string, string);
	void populateList(string);
	void sortList();
	int getIndex(string);

	//temp function
	void print() {
		player *temp = new player;
		temp = head;
		while (temp != 0)
		{
			cout << temp->name << "\t" << temp->jersey << "\t" << temp->pos << endl;
			temp = temp->next;
		}
	};
};

list::list() {
	head = 0;
	tail = 0;
}

void list::addPlayer(string n, string j, string p)
{
	player *temp = new player;
	temp->name = n;
	temp->jersey = j;
	temp->pos = p;
	temp->next = 0;
	if (head == 0) {
		head = temp;
		tail = temp;
		temp = 0;
	}
	else {
		tail->next = temp;
		tail = temp;
	}
}

void list::populateList(string file) {
	ifstream ifile;
	ifile.open(file);

	string line;
	string n;
	string j;
	string p;

	if (ifile.is_open())
	{
		while (getline(ifile, line))
		{
			n = line.substr(0, line.find(", "));
			line.erase(0, line.find(", ") + 2);
			j = line.substr(0, line.find(", "));
			line.erase(0, line.find(", ") + 2);
			p = line;
			addPlayer(n, j, p);
		}
		ifile.close();
	}
}

void list::sortList() {
	//sort list alphabetically
}

int list::getIndex(string n) {
	int i = 0;
	player* cu = new player;
	cu = head;
	while (cu->name != n) {
		//if name doesnt exist return -1
		cu=cu->next;
		i++;
	}
	return i;
}

int main()
{
	list players;
	players.populateList("input.txt");

	//players.print();
	//cout << endl << players.getIndex("Neymar");

	return 0;
}

/*int main(int argc, char* argv[])
{
	if (argc != 3 && argc != 2) {
		cout << "Invalid arguments!\n";
		return 1;
	}
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");

	ofstream ofile;
	ofile.open(output);
}*/
