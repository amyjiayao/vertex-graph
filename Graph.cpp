// Jiayao Li
// username: jiayaoli
// UIN: 42302027
// CSCE-221-507
// jiayaoli@tamu.edu

// please implement it
#include "Graph.hpp"

Graph::Graph(){
	
}

Graph::Graph(vector<list<Edge>> adjl){
	
}

void Graph::buildGraph(ifstream& input){
	string line;
	int counter = 0;
	// read in input
	getline(input, line);
	while(getline(input,line)){
		string num;
		istringstream iss(line);
		list<Edge> le;
		Vertex v(counter);
		while(iss>>num){
			if(num!="-1"){
				v.connectTo(stoi(num));
				Edge ed(counter,stoi(num),1);
				le.push_back(ed);
			}
		}
		adj_list.push_back(le);
		vertices.push_back(v);
		counter++;
	}
}

void Graph::displayGraph(){
	for(int i=0; i<adj_list.size(); i++){
		cout << i << ":";
		for (list<Edge>::iterator it=adj_list[i].begin(); it != adj_list[i].end(); ++it){
			cout << " " << it->end;
		}
		cout << endl;
	}
}

bool Graph::check_input(int x, int y){
	// initialize variables to track group numbers
	int x_group = 0;
	int y_group = 0;
	// check if x and y belong to group 1
	for(int i=0; i<groupA.size(); i++){
		if(x == groupA[i]){
			x_group = 1;
		}
		if(y == groupA[i]){
			y_group = 1;
		}
	}
	// check if x and y belong to group 2
	for(int i=0; i<groupB.size(); i++){
		if(x == groupB[i]){
			x_group = 2;
		}
		if(y == groupB[i]){
			y_group = 2;
		}
	}
	// determine if x and y belong to the same group
	if(x_group == y_group){
		return true;
	}
	else {
		return false;
	}
}

bool Graph::sortGroups(){
	vector<int> visited(vertices.size());
	for(int i=0; i<visited.size(); i++){
		visited[i] = -1; // unvisted
	}
	list<int> queue;
	int p = 0;
	while(p<visited.size()){
		if(visited[p]!=-1){
			p++;
		}
		else{
			int point = vertices[p].label;
			visited[point] = 0;
			groupA.push_back(point);
			queue.push_back(point);
			while(!queue.empty()){
				int j = queue.front();
				queue.pop_front();
				for(list<Edge>::iterator it=adj_list[j].begin(); it != adj_list[j].end(); ++it){
					if(visited[j]==0){
						if(visited[it->end]==0){
							cout << "Input data cannot be sorted into groups!" << endl;
							return false;
						}
						if(visited[it->end]==-1){
							visited[it->end] = 1;
							groupB.push_back(it->end);
							queue.push_back(it->end);
						}
					}
					if(visited[j]==1){
						if(visited[it->end]==1){
							cout << "Input data cannot be sorted into groups!" << endl;
							return false;
						}
						if(visited[it->end]==-1){
							visited[it->end] = 0;
							groupA.push_back(it->end);
							queue.push_back(it->end);
						}
					}
				}
			}
		}
	}
	cout << "Group 1: ";
	for(int i=0; i<groupA.size(); i++){
		cout << groupA[i] << " ";
	}
	cout << endl;
	cout << "Group 2: ";
	for(int i=0; i<groupB.size(); i++){
		cout << groupB[i] << " ";
	}
	cout << endl;
	return true;
}

void Graph::findPath(int start, int end){
	// initialize variables
	vector<bool> visited(vertices.size(), false);
    vector<int> parent(vertices.size(), -1);
    list<int> path;
    list<Vertex*> q;  
    Vertex* cur;
	visited[start] = true;
    q.push_back(&vertices[start]);
	// BFS
    while(q.size() > 0) {
		cur = q.back();
        q.pop_back();
        if(cur->label == end){
			break;
        } 
		else{
			for (auto edge = cur->edgeList.begin(); edge != cur->edgeList.end(); edge++){
				if (!visited[edge->end]) {
					visited[edge->end] = true;
					parent[edge->end] = cur->label;
                    q.push_back(&vertices[edge->end]);
                }    
            }
       } 
    }

    int next = end;
    // error message
	if(parent[next]==-1){
		cout << "The input cities are not connected!" << endl;
	}
	else{ // output results
		while(next != start){
			path.push_front(next);
			next = parent[next];
		}
		path.push_front(start);
		int count = 0;
		cout << "Path: ";
		for (auto it = path.begin(); it != path.end(); it++){
			if (count > 0) {
				cout << "->";    
			}
			cout << *it;
			count++;
		}
		cout << endl << "Depth: "<< count-1 << endl;
	}
}
