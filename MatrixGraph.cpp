#include "MatrixGraph.h"
#include <assert.h>
#include <iostream>

using namespace std;

MatrixGraph::MatrixGraph(int numNodes) {
	num_edges = 0;
	M = vector<vector<unsigned> >(numNodes,vector<unsigned>(numNodes));
	for(int i = 0; i < numNodes; i++) {
		for(int t = 0; t < numNodes; t++) {
			M[i][t] = 0;
		}
	}
}

MatrixGraph::~MatrixGraph() {

}

void MatrixGraph::addEdge(NodeID u, NodeID v) {
	assert(u != v);
	assert(u >= 0 && u < M.size());
	assert(v >= 0 && v < M.size());
	assert(!isEdge(u,v));
	M[u][v] = 1;
	M[v][u] = 1;
	num_edges++;
}

bool MatrixGraph::isEdge(NodeID u, NodeID v) const{
	assert(u >= 0 && u < M.size());
	assert(v >= 0 && v < M.size());
	return M[u][v] == 1;
}

EList MatrixGraph::getAdj(NodeID u) const {
	assert(u >= 0 && u < M.size());
	EList list;
	for(int i = 0; i < M.size(); i++) {
		if(M[u][i] == 1) {
			list.push_back(NodeID(i));
		}
	}
	return list;
}

unsigned MatrixGraph::degree(NodeID u) const {
	assert(u >= 0 && u < M.size());
	int count = 0;
	for(int i = 0; i < M.size(); i++) {
		if(M[u][i] == 1) {
			count++;
		}
	}
	return count;
}

unsigned MatrixGraph::size() const {
	return M.size();
}

unsigned MatrixGraph::numEdges() const {
	return num_edges;
}

/*
int main() {
	MatrixGraph l(6);
	l.addEdge(0,1);
	l.addEdge(0,2);
	l.addEdge(4,5);
	cout << l.size() << endl;
	cout << l.numEdges() << endl;
	cout << l.degree(0) << endl;
	cout << l.isEdge(0,1) << endl;
}
*/
