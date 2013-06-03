#ifndef _EDGE_H
#define _EDGE_H

// Directed edge (i,j)
class Edge {
public:
	int i;
	int j;
	char label[1024];
	char inlabel[10];
	char outlabel[10];
	friend ostream & operator <<(ostream &os, const Edge &v);
	friend istream & operator >>(istream &is, Edge &v);
	inline Edge() { i = j = -1; strcpy(label,""); 
		strcpy(inlabel,""); strcpy(outlabel,""); }
};

#endif