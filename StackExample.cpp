// StackExample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
#define SIZE 10

template <class T>
class stack {
	T *arr;
	int top;
	int capacity;
public:
	stack(int size = SIZE);
	void push(T);
	T pop();
	T peek();
	int size();
	bool isEmpty();
	bool isFull();
	void print() {
		for (int i = top; i > -1; i--)
			cout << arr[i] << endl;
		cout << endl;
	}
	~stack() {
		delete[] arr;
	}
};

template <class T>
stack<T>::stack(int size) {
	arr = new T[size];
	capacity = size;
	top = -1;
}

template <class T>
void stack<T>::push(T t) {
	if (isFull()) {
		cout << "OverFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}
	cout << "Inserting " << t << endl;
	arr[++top] = t;
}

template <class T>
T stack<T>::pop() {
	if (isEmpty()) {
		cout << "UnderFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}
	cout << "Popping " << peek() << endl;
	return arr[top--];
}

template <class T>
T stack<T>::peek() {
	if (isEmpty()) {
		cout << "Empty";
		exit(EXIT_FAILURE);
	}
	return arr[top];
}

template <class T>
int stack<T>::size() {
	return top + 1;
}

template <class T>
bool stack<T>::isEmpty() {
	return top == -1;
}

template <class T>
bool stack<T>::isFull() {
	return top == capacity - 1;
}

int main()
{
	stack<string> pt(2);
	pt.push("A");
	pt.print();
	pt.push("B");
	pt.print();
	pt.pop();
	pt.print();
	pt.pop();
	pt.print();
	pt.push("C");
	pt.print();

	// Prints the top of the stack
	cout << "Top element is: " << pt.peek() << endl;

	// Returns the number of elements present in the stack
	cout << "Stack size is " << pt.size() << endl;
	pt.pop();

	// check if stack is empty or not
	if (pt.isEmpty())
		cout << "Stack Is Empty\n";
	else
		cout << "Stack Is Not Empty\n";

	//pt.~stack();

	return 0;
}