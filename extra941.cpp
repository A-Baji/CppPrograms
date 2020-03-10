// extra941.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

struct word {
	char letter;
	word* next;
};

class list {
public:
	word* head;
	word* tail;
	list();
	void addChar(char);
	void pigLatinify();
	void deleteList();
	void firstSoundToLast();
	bool isVowel(char);
	bool isVowelWithY(char);

	void print() {
		word* temp = head;
		while (temp != 0) {
			cout << temp->letter;
			temp = temp->next;
		}
		cout << " ";
	};
};

list::list() {
	head = 0;
	tail = 0;
}

void list::addChar(char c) {
	word* temp = new word;
	temp->letter = c;
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

bool list::isVowel(char c) {
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
		return true;
	else return false;
}

bool list::isVowelWithY(char c) {
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y')
		return true;
	else return false;
}

void list::firstSoundToLast() {
	word* temp = head;
	int count = 0;
	do {
		temp = temp->next;
		count++;
	} while ((!isVowelWithY(temp->letter)) && temp->next != 0);
	
	if (temp->next == 0 && !isVowelWithY(temp->letter)) {
		addChar('w');
		return;
	}

	tail->next = head;
	for (int i = 0; i < count; i++) {
		head = head->next;
		tail = tail->next;
	}
	tail->next = 0;
}

void list::pigLatinify() {
	if (isVowel(head->letter)) {
		addChar('w');
		addChar('a');
		addChar('y');
	}
	else {
		firstSoundToLast();
		addChar('a');
		addChar('y');
	}
}

void list::deleteList()
{
	word* current = head;
	word* next;
	while (current != 0)
	{
		next = current->next;
		free(current);
		current = next;
	}
	head = 0;
}

int main()
{
	list toPig;
	string str;
	cout << "Enter your string: \n";
	getline(cin, str);

	string Word;
	int wc = 0;

	//Get word count
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ')
			wc++;
	}

	//Piglatinify word by word
	for (int i = 0; i < wc+1; i++) {

		//Get single word from string
		Word = str.substr(0, str.find(" "));
		str.erase(0, str.find(" ") + 1);

		//Fill word list with each character
		for (int j = 0; j < Word.length(); j++)
			toPig.addChar(Word[j]);

		//Piglatinify word and print
		toPig.pigLatinify();
		toPig.print();

		//Empty word list
		toPig.deleteList();
	}

	return 0;
}