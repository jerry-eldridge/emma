#ifndef _NODE_H
#define _NODE_H

#include <iostream>
using namespace std;

typedef enum {none, rectangle, circle, connection} box_type;

class Node {
public:
	char label[1024];
	int id;
	box_type box;
	inline Node() { id = -1; strcpy(label,""); box = none; }
	friend ostream & operator <<(ostream &os, const Node &v);
	friend istream & operator >>(istream &is, Node &v);
};

#endif
