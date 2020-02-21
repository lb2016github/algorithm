#include "Graph.hpp"

bool test()
{
	Graph<int>* graph = new LGraph<int>(5);
	int i = 1;
	graph->insert(0, 1, i);
}