// Jiayao Li
// username: jiayaoli
// UIN: 42302027
// CSCE-221-507
// jiayaoli@tamu.edu

#include <iostream>
#include <string>

#include "Graph.hpp"

int main(int argc, const char * argv[]) {
    try{
        if (argc != 2) throw invalid_argument("Usage: ./main <file name>");
        ifstream in(argv[1]);
        if (!in) throw invalid_argument("Invalid file name or unable to open file.");
        Graph g;
        g.buildGraph(in);
        g.displayGraph();
		if(g.sortGroups()){
			cout << "Enter 2 cities from the same group the find the shortest path." << endl;
			cout << "Please enter departure city: ";
			int user_input_1;
			cin >> user_input_1;
			cout << "Please enter destination city: ";
			int user_input_2;
			cin >> user_input_2;
			if(g.check_input(user_input_1, user_input_2)){
				g.findPath(user_input_1, user_input_2);
			}
			else{
				cout << "Invalid input! Input must be two cities from the same group!" << endl;
			}
		}
        return 0;
    }
    catch (exception& error){
        cerr << "Error: " << error.what() << endl;
    }
}

