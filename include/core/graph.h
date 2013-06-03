#ifndef _GRAPH_H
#define _GRAPH_H

#include <list>

#include "node.h"
#include "edge.h"

class Graph {
public:
	list<Node> V;
	list<Edge> E;
	Node GetNode(int i);
	Edge GetEdge(int i);
	void Load(char *filename);
	void Save(char *filename);
};

#endif