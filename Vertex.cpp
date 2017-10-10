// Jiayao Li
// username: jiayaoli
// UIN: 42302027
// CSCE-221-507
// jiayaoli@tamu.edu

// please implement it

#include "Vertex.hpp"

Vertex::Vertex(int label){
	this->label = label;
}

void Vertex::connectTo(int end){
	Edge e(label,end,1);
	edgeList.push_back(e);
}