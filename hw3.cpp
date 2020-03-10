#include "ArgumentManager.h"
#include <iostream>
#include <fstream>
#include <string>
#define SIZE 20
using namespace std;

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
	};
	arr[++top] = t;
}

template <class T>
T stack<T>::pop() {
	if (isEmpty()) {
		throw "error";
	}
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

int prio(char c)
{
	if (c == '^')
		return 3;
	else if (c == '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}

string infToPost(string s)
{
	int l = s.length();
	stack<char> st(l);
	st.push('E');
	int k;
	string pf;

	for (int i = 0; i < l; i++) {
		if ((s[i] >= '0' && s[i] <= '9')) {
			k = 1;
			while (i + k <= l && (s[i + k] >= '0' && s[i + k] <= '9'))
				k++;
			pf += s.substr(i, k);
			pf += ' ';
			i += k - 1;
		}
		else if (s[i] == '(')
			st.push('(');
		else if (s[i] == ')') {
			if (s[i + 1] >= '0' && s[i + 1] <= '9')
				return "error";
			if (st.peek() == 'E')
				return "error";
			while (st.peek() != 'E' && st.peek() != '(') {
				char c = st.peek();
				st.pop();
				pf += c;
				pf += ' ';
			}
			if (st.peek() == '(') {
				char c = st.peek();
				st.pop();
			}
		}
		else if (s[i] == '-' && (i == 0 || s[i - 1] == '('))
			pf += s[i];
		else if (s[i] == '+' && (i == 0 || s[i - 1] == '('))
			continue;
		else {
			while (st.peek() != 'E' && prio(s[i]) <= prio(st.peek())) {
				char c = st.peek();
				st.pop();
				pf += c;
				pf += ' ';
			}
			st.push(s[i]);
		}
	}
	while (st.peek() != 'E') {
		char c = st.peek();
		st.pop();
		pf += c;
		pf += ' ';
	}
	return pf;
}

long long evalPostfix(string s) {
	int l = s.length();
	stack<long long> st(l);
	int k;

	for (int i = 0; i < l; i++) {
		l = s.length();
		if (s[i] == ' ')
			continue;
		else if ((s[i] == '-' && (i == 0 || ((s[i + 1] >= '0' && s[i + 1] <= '9') || s[i + 1] == '-'))) || s[i] >= '0' && s[i] <= '9') {
			if (s[i + 1] == '-') {
				s.erase(i, 2);
				i--;
			}
			else {
				k = 1;
				while (i + k <= l && (s[i + k] >= '0' && s[i + k] <= '9'))
					k++;
				string test = s.substr(i, k);
				st.push(stoll(test));
				i += k - 1;
			}
		}
		else {
			long long v1;
			long long v2;

			try {
				v1 = st.pop();
				v2 = st.pop();
			}
			catch (const char* msg) {
				return -1;
			}

			if (s[i] == '+')
				st.push(v1 + v2);
			else if (s[i] == '-')
				st.push(v2 - v1);
			else if (s[i] == '*')
				st.push(v1 * v2);
			else if (s[i] == '/')
				st.push(v2 / v1);
		}
	}
	return st.pop();
}

int main(int argc, char* argv[])
{
	if (argc != 2 && argc != 3) {
		cout << "Invalid arguments!\n";
		return 1;
	}
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");

	ifstream ifile;
	ifile.open(input);
	ofstream ofile;
	ofile.open(output);

	string line;
	long long value;
	string pfix;
	int pcount;

	while (getline(ifile, line)) {
		pcount = 0;
		pfix = infToPost(line);
		for (int i = 0; i < pfix.length(); i++)
			if (pfix[i] == '(' || pfix[i] == ')')
				pcount++;
		if (pcount > 0) {
			ofile << "error";
			continue;
		}
		if (pfix == "error")
			ofile << pfix;
		else {
			value = evalPostfix(pfix);
			if (value == -1)
				ofile << "error";
			else
				ofile << line << "=" << value;
		}
		ofile << endl;
	}
	ifile.close();
	ofile.close();

	return 0;
}