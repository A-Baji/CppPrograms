#include "pch.h"
#include "ArgumentManager.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct node {
	string s;
	node* next;
};

class list {
private:
	node *head, *tail;
public:
	list() {
		head = 0;
		tail = 0;
	}
	void addString(string);
	void findFirst();
	void sort();

	void print(string fname) {
		ofstream ofile;
		ofile.open(fname);
		node* temp = head;
		while (temp != 0) {
			ofile << temp->s;
			ofile << endl;
			temp = temp->next;
		}
		ofile.close();
	};
};

void list::addString(string str) {
	node* temp = new node;
	temp->s = str;
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

void list::findFirst() {
	node* temp = head;
	node* temp2 = new node;
	string t;
	int count;
	while (temp->next != 0) {
		string firstw = temp->s.substr(0, temp->s.find(" "));
		for (int i = 0; i < firstw.size(); ++i)
		{
			if (!((firstw[i] >= 'a' && firstw[i] <= 'z') || (firstw[i] >= 'A' && firstw[i] <= 'Z')))
			{
				firstw.erase(i);
			}
		}
		firstw[0] = tolower(firstw[0]);
		temp2 = head;
		count = 0;
		while (temp2 != 0) {
			string lastw = temp2->s.substr(temp2->s.find_last_of(" ") + 1, temp2->s.length());
			for (int i = 0; i < lastw.size(); ++i)
			{
				if (!((lastw[i] >= 'a' && lastw[i] <= 'z') || (lastw[i] >= 'A' && lastw[i] <= 'Z')))
				{
					lastw.erase(i);
				}
			}
			lastw[0] = tolower(lastw[0]);
			if (firstw == lastw) {
				count++;
				break;
			}
			else
				temp2 = temp2->next;
		}
		if (count == 0) {
			string t = temp->s;
			temp->s = head->s;
			head->s = t;
			return;
		}
		else
			temp = temp->next;
	}
	return;
}

void list::sort() {
	node* temp = head;
	node* temp2 = new node;
	string t;
	while (temp->next != 0) {
		string lastw = temp->s.substr(temp->s.find_last_of(" ") + 1, temp->s.length());
		for (int i = 0; i < lastw.size(); ++i)
		{
			if (!((lastw[i] >= 'a' && lastw[i] <= 'z') || (lastw[i] >= 'A' && lastw[i] <= 'Z')))
			{
				lastw.erase(i);
			}
		}
		lastw[0] = tolower(lastw[0]);
		temp2 = temp->next;
		while (temp2 != 0) {
			string firstw = temp2->s.substr(0, temp2->s.find(" "));
			for (int i = 0; i < firstw.size(); ++i)
			{
				if (!((firstw[i] >= 'a' && firstw[i] <= 'z') || (firstw[i] >= 'A' && firstw[i] <= 'Z')))
				{
					firstw.erase(i);
				}
			}
			firstw[0] = tolower(firstw[0]);
			if (lastw == firstw) {
				t = temp2->s;
				temp2->s = temp->next->s;
				temp->next->s = t;
				break;
			}
			else
				temp2 = temp2->next;
		}
		temp = temp->next;
	}
	return;
}

int main(int argc, char* argv[])
{
	if (argc != 1 && argc != 3) {
		cout << "Invalid arguments!\n";
		return 1;
	}
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");

	fstream ifile;
	ifile.open(input);

	list sentences;
	string line;

	//Fill linked list
	while (getline(ifile, line)) {
		sentences.addString(line);
	}
	//Find first sentence
	sentences.findFirst();

	//Sort sentences
	sentences.sort();

	//Print to file
	sentences.print(output);

	ifile.close();

	return 0;
}
