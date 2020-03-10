#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
#define SIZE 10

template <class T>
class queue {
	T *arr;
	int front;
	int rear;
	int capacity;
public:
	queue(int size = SIZE);
	void enqueue(T);
	T dequeue();
	bool isEmpty();
	bool isFull();
	int count();
	void print() {
		if (rear < front) {
			for (int k = front; k < capacity; k++)
				cout << arr[k] << " ";
			for (int k = 0; k < rear; k++)
				cout << arr[k] << " ";
		}
		else {
			for (int k = front; k <= rear; k++)
				cout << arr[k] << " ";
		}
		cout << endl;
	}
	~queue() {
		delete[] arr;
	}
};

template <class T>
queue<T>::queue(int size) {
	arr = new T[size];
	capacity = size;
	front = -1;
	rear = -1;
}

template <class T>
void queue<T>::enqueue(T t) {
	if (isFull()) {
		cout << "OverFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}
	else if (isEmpty())
		rear = front = 0;
	else
		rear++;
	arr[rear] = t;
}

template <class T>
T queue<T>::dequeue() {
	T x;
	if (isEmpty()) {
		cout << "UnderFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}
	else if (front == rear) {
		x = arr[front];
		rear = front = -1;
	}
	else {
		x = arr[front];
		front = (front + 1) % capacity;
	}
	return x;
}

template <class T>
bool queue<T>::isEmpty() {
	if (front == -1 && rear == -1)
		return true;
	else
		return false;
}

template <class T>
bool queue<T>::isFull() {
	if ((rear + 1) % capacity == front)
		return true;
	else
		return false;
}
template <class T>
int queue<T>::count() {
	int i;
	if (isFull())
		return capacity;
	else if (rear < front) {
		i = 0;
		for (int k = front; k < capacity; k++)
			i++;
		for (int k = 0; k < rear; k++)
			i++;
		return i;
	}
	else {
		i = 0;
		for (int k = front; k <= rear; k++)
			i++;
		return i;
	}
}

int main() {
	queue<int> q;
	q.enqueue(1);
	q.print();
	q.enqueue(4);
	q.print();
	q.enqueue(8);;
	q.dequeue();
	q.print();
}
