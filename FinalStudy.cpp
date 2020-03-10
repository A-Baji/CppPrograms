#include "pch.h"
#include <iostream>

using namespace std;

class Node
{
public:
	Node* next;
	int data;
};

using namespace std;

class LinkedList
{
public:
	int length;
	Node* head;

	LinkedList();
	~LinkedList();
	void add(int data);
	void print();
	void deleteAtN(int);
	void deleteNAfterM(int, int);
	void deleteList();
	void reverse();
	Node lastOcr(int);
	void reverseGrouped(int);
};

LinkedList::LinkedList() {
	this->length = 0;
	this->head = NULL;
}

LinkedList::~LinkedList() {
	std::cout << "LIST DELETED";
}

void LinkedList::add(int data) {
	Node* node = new Node();
	node->data = data;
	if (head == NULL)
	{
		head = node;
	}
	else
	{
		Node* temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
	}
	this->length++;
}

void LinkedList::print() {
	Node* head = this->head;
	if (head == NULL) {
		cout << "EMPTY\n";
		return;
	}
	int i = 1;
	while (head) {
		std::cout << i << ": " << head->data << std::endl;
		head = head->next;
		i++;
	}
}

void LinkedList::deleteAtN(int n) {
	Node* temp = head;
	for (int i = 0; i < n - 1; i++)
		temp = temp->next;
	Node* temp2 = temp->next;
	temp->next = temp2->next;
	delete temp2;
	
}

void LinkedList::deleteNAfterM(int n, int m) {
	Node* temp = head;
	for (int i = 0; i < m; i++)
		temp = temp->next;
	for (int i = 0; i < n; i++) {
		Node* temp2 = temp->next;
		temp->next = temp2->next;
		delete temp2;
	}
}

void LinkedList::deleteList() {
	Node* temp = head;
	Node* next;

	while (temp != NULL) {
		next = temp->next;
		delete temp;
		temp = next;
	}
	head = NULL;
}

void LinkedList::reverse() {
	Node* cu = head;
	Node* prev = NULL;
	Node* next = NULL;

	while (cu != NULL) {
		next = cu->next;
		cu->next = prev;
		prev = cu;
		cu = next;
	}
	head = prev;
}

Node LinkedList::lastOcr(int n) {
	Node* temp = head;
	int i = 0;
	int j = 0;
	while (temp !=  NULL) {
		if (temp->data == n)
			i++;
		temp = temp->next;
	}
	if (i == 1) {
		temp = head;
		while (temp->data != n)
			temp = temp->next;
		return *temp;
	}
	else {
		temp = head;
		while (temp != NULL) {
			temp = temp->next;
			if (temp->data == n)
				j++;
			if (i == j)
				return *temp;
		}
	}

}

int main()
{
	LinkedList* list = new LinkedList();

	for (int i = 0; i < 12; i++)
		list->add(i);
	list->print();
	list->reverseGrouped(3);
	cout << "------------\n";
	list->print();

	delete list;
	return 0;
}
