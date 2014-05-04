#include <iostream>
#include "Node.h"
#include "Graph.h"

int main()
{
	Node n;

	Node m;
	n.addNode(&m);
	n.removeNode(m);

	Graph g(4, 4);
}