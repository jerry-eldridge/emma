#include <iostream>
using namespace std;
#include <list>
#include <string>
#include <fstream>

#include "core/core.h"

Node Graph::GetNode(int i)
{
	Node nod;
	if (i >= V.size()) return nod;
	list<Node>::const_iterator p;
	int n = 0;
	for (p = V.begin(); p != V.end(); p++) {
		if (n==i) return (*p);
		n++;
	}
	return nod;

}

Edge Graph::GetEdge(int i)
{
	Edge edg;
	if (i >= E.size()) return edg;
	list<Edge>::const_iterator p;
	int n = 0;
	for (p = E.begin(); p != E.end(); p++) {
		if (n==i) return (*p);
		n++;
	}
	return edg;

}

void Graph::Load(char *filename)
{
	ifstream in(filename);
	int nv, ne, i;
	char line[4096]="";

	in >> nv;
	in.getline(line,4096);
	list<Node>::iterator p = V.begin();
	for (i=0; i<nv; i++) {
		Node v;
		in >> v;
		cout << v << endl;
		V.insert(p,v);
	}
	in >> ne;
	in.getline(line,4096);
	list<Edge>::iterator q = E.begin();
	for (i=0; i<ne; i++) {
		Edge e;
		in >> e;
		cout << e << endl;
		E.insert(q,e);
	}

	in.close();

}

void Graph::Save(char *filename)
{
	ofstream out(filename);
	int nv, ne, i;

	nv = V.size();
	ne = E.size();

	out << nv << endl;
	list<Node>::iterator p;
	for (p=V.begin(); p!=V.end(); p++) {
		out << (*p) << endl;
	}
	out << ne << endl;
	list<Edge>::iterator q;
	for (q=E.begin(); q!=E.end(); q++) {
		out << (*q) << endl;
	}

	out.close();

}