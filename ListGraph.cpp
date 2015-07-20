#include "ListGraph.h"
#include <assert.h>
#include <iostream>
#include <queue>

using namespace std;

ListGraph::ListGraph(int numNodes) {
	edgeList = vector<EList>(numNodes);
	num_edges = 0;
}

ListGraph::~ListGraph() {
	
}

void ListGraph::addEdge(NodeID u, NodeID v) {
	assert(u != v);
	assert(u >= 0 && u < edgeList.size());
	assert(v >= 0 && v < edgeList.size());
	assert(!isEdge(u,v));
	num_edges++;
	EList l = edgeList[u];
	l.push_back(v);
	edgeList[u] = l;
	l = edgeList[v];
	l.push_back(u);
	edgeList[v] = l;
}

bool ListGraph::isEdge(NodeID u, NodeID v) const {
	assert(u >= 0 && u < edgeList.size());
	assert(v >= 0 && v < edgeList.size());
	EList l = edgeList[u];
	for(EList::iterator it = l.begin(); it != l.end(); it++) {
		if(*it == v) {
			return true;
		}
	}
	return false;
}

EList ListGraph::getAdj(NodeID u) const {
	assert(u >= 0 && u < edgeList.size());
	return edgeList[u];
}

unsigned ListGraph::degree(NodeID u) const {
	assert(u >= 0 && u < edgeList.size());
	int i = 0;
	EList l = edgeList[u];
	for(EList::iterator it = l.begin(); it != l.end(); it++) {
		i++;
	}
	return i;
}

unsigned ListGraph::size() const {
	return edgeList.size();
}

unsigned ListGraph::numEdges() const {
	return num_edges;
}

void ListGraph::bfs(NodeID s) const {
	NodeID * d = new NodeID[edgeList.size()];
	NodeID * parent = new NodeID[edgeList.size()];
	for(int i = 0; i < edgeList.size(); i++) {
		d[i] = -1;
		parent[i] = -1;
	}
	std::queue<NodeID> q;
	q.push(s);
	d[s] = s;
	parent[s] = s;
	while(!q.empty()) {
		NodeID cur = q.front();
		if (cur != s) {
			cout << "(" << parent[cur] << "," << cur << ")" << endl;
		}
		q.pop();
		EList list = getAdj(cur);
		for(EList::iterator it = list.begin(); it != list.end(); it++) {
			if(d[*it] == -1) {
				d[*it] = d[cur] + 1;
				parent[*it] = cur;
				q.push(*it);
			}
		}
	}
}

int main() {
	ListGraph l(6);
	l.addEdge(0,1);
	l.addEdge(0,2);
	l.addEdge(2,5);
	cout << l.size() << endl;
	cout << l.numEdges() << endl;
	cout << l.degree(0) << endl;
	cout << l.isEdge(0,1) << endl;
	cout << endl;
	l.bfs(0);
}
