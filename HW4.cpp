#include "pch.h"
#include "ArgumentManager.h"
#include <iostream>
#include <fstream>
#include <string>

struct BTree {
   int *d;
   BTree **child_ptr;
   bool l;
   int n;
   int level;
}*r = NULL, *np = NULL, *x = NULL;

BTree* init(int degree) {
   int i;
   np = new BTree;
   np->d = new int[degree];
   np->child_ptr = new BTree *[degree+1];
   np->l = true;
   np->n = 0;
   for (i = 0; i < degree+1; i++) {
      np->child_ptr[i] = NULL;
   }
   return np;
}

bool isDuplicate(BTree *p, int num) {
	int i;
	if (p == nullptr)
		return false;
	for (i = 0; i < p->n; i++) {
		if (p->l == false) {
			if (isDuplicate(p->child_ptr[i], num))
				return true;
		}
		if (num == p->d[i])
			return true;
	}
	if (p->l == false) {
		if (isDuplicate(p->child_ptr[i], num))
			return true;
	}
	return false;
}

void traverse(BTree *p) {
	cout << endl;
	int i;
	for (i = 0; i < p->n; i++) {
		if (p->l == false) {
			traverse(p->child_ptr[i]);
		}
		cout << p->d[i] << " ";
	}
	if (p->l == false) {
		traverse(p->child_ptr[i]);
	}
	cout << endl;
}

void traverseLevel(BTree *p, int lvl) {
	
}

void sort(int *p, int n) {
   int i, j, t;
   for (i = 0; i < n; i++) {
      for (j = i; j <= n; j++) {
         if (p[i] >p[j]) {
            t = p[i];
            p[i] = p[j];
            p[j] = t;
         }
      }
   }
}

int split_child(BTree *x, int i, int degree) {
   int j, mid;
   BTree *np1, *np3, *y;
   np3 = init(degree);//create new node
   np3->l = true;
   if (i == -1) {
      mid = x->d[2];//find mid
      x->d[2] = 0;
      x->n--;
      np1 = init(degree);
      np1->l= false;
      x->l= true;
      for (j = 3; j < degree; j++) {
         np3->d[j - 3] = x->d[j];
         np3->child_ptr[j - 3] = x->child_ptr[j];
         np3->n++;
         x->d[j] = 0;
         x->n--;
      }
      for (j = 0; j < degree; j++) {
         x->child_ptr[j] = NULL;
      }
      np1->d[0] = mid;
      np1->child_ptr[np1->n] = x;
      np1->child_ptr[np1->n + 1] = np3;
      np1->n++;
      r = np1;
   } else {
      y = x->child_ptr[i];
      mid = y->d[2];
      y->d[2] = 0;
      y->n--;
      for (j = 3; j < degree ; j++) {
         np3->d[j - 3] = y->d[j];
         np3->n++;
         y->d[j] = 0;
         y->n--;
      }
      x->child_ptr[i + 1] = y;
      x->child_ptr[i + 1] = np3;
   }
   return mid;
}

void insert(int a, int degree) {
   int i, t;
   x = r;
   if (x == NULL) {
      r = init(degree);
      x = r;
   } else {
      if (x->l== true && x->n == degree) {
         t = split_child(x, -1, degree);
         x = r;
         for (i = 0; i < (x->n); i++) {
            if ((a >x->d[i]) && (a < x->d[i + 1])) {
               i++;
               break;
            } else if (a < x->d[0]) {
               break;
            } else {
               continue;
            }
         }
         x = x->child_ptr[i];
      } else {
         while (x->l == false) {
            for (i = 0; i < (x->n); i++) {
               if ((a >x->d[i]) && (a < x->d[i + 1])) {
                  i++;
                  break;
               } else if (a < x->d[0]) {
                  break;
               } else {
                  continue;
               }
            }
            if ((x->child_ptr[i])->n == degree) {
               t = split_child(x, i, degree);
               x->d[x->n] = t;
               x->n++;
               continue;
            } else {
               x = x->child_ptr[i];
            }
         }
      }
   }
   x->d[x->n] = a;
   sort(x->d, x->n);
   x->n++;
}

int main(int argc, char* argv[])
{
	if (argc != 5) {
		cout << "Invalid arguments!\n" << argc;
		return 1;
	}
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string command = am.get("command");
	string output = am.get("output");

	ifstream ifile;
	ifile.open(input);
	ifstream cfile;
	cfile.open(command);
	ofstream ofile;
	ofile.open(output);

	//Get degree
	string line;
	string last;
	int deg;
	getline(cfile, line);
	if (line[line.length() - 2] == '=')
		last = line[line.length() - 1];
	else {
		int i = line.length() - 3;
		while (line[i] != '=')
			i--;
		last = line.substr(i + 1, line.length() - i);
	}
	deg = stoi(last);

	//Fill tree with data
	while (getline(ifile, line)) {
		int count = 1;
		for (int j = 0; j < line.length(); j++) {
			if (line[j] == ' ')
				count++;
		}

		if (count == 1)
			insert(stoi(line), deg);
		else {
			int i = 0;
			while (i < count) {
				if (!isDuplicate(r, stoi(line.substr(0, line.find(" ")))))
					insert(stoi(line.substr(0, line.find(" "))), deg);
				line.erase(0, line.find(" ") + 1);
				i += 1;
			}
		}
	}

	//Execute commands from cfile
	while (getline(cfile, line)) {
		if (line == "Inorder Traversal")
			traverse(r);
		else {
			if (line[line.length() - 2] == ' ')
				last = line[line.length() - 1];
			else {
				int i = line.length() - 3;
				while (line[i] != ' ')
					i--;
				last = line.substr(i + 1, line.length() - i);
			}
			//tree.traverseLevel(1/*stoi(last)*/);
		}
	}
}