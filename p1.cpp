#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <climits>
#include <iostream>
#include <bits/stdc++.h>

/* 
 Problem solved : giving a vector of distances ( i - a node from the graph, v[i] - distance from the root node(1) to the i node), we need to write
at the output the edges of the graph
*/

using namespace std;

const int kNmax = 1005;

class Task {

 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, value; 
	vector<int> values;
	vector< pair<int, int> > nodes;
	vector< pair<int, int> > parents_node;
	
// compare function needed to sort the distance vector
	static bool compare( const pair<int , int> &a, const pair<int, int> &b){
		return a.second < b.second;
	}

	void read_input() {
		ifstream fin("p1.in");
		fin >> n;

		if(n > 0){
			for (int i = 0; i < n; i++){
				fin >> value;
				values.push_back(value);
			} 
			// associating the node with the distance from the root node to the current node
			for (int k = 0; k < n; k++){
				nodes.push_back(make_pair(k + 1, values[k]));
			}
		}else{
			// checking if there are no nodes given
			n = -1;
		}

		fin.close();
    }

	int get_result() {

		int m = 0;
		int nod_parinte = 1;

		if(n == -1){
			return -1;
		}
//sorting the vector so it is easier to find the parent of each node, helping us in finding the path to each node
		sort(nodes.begin(), nodes.end(), compare); 

		if(nodes[1].second == 0){
			return -1;
		}
/*finding the parent for every node ( node[i].first - the node, node[i].second - the distance, 
				    parent_node[i].first - a node, parent_node[i].second - the parentofthe node,
				    m - number of edges
*/		
		for(int i = 0; i < n; i++){

			if(nodes[i].second == nodes[i + 1].second){

				parents_node.push_back(make_pair(nodes[i].first , nod_parinte));
				m++;
				
			}else if(nodes[i].second + 1 == nodes[i + 1].second){

				parents_node.push_back(make_pair(nodes[i].first , nod_parinte));
				nod_parinte = nodes[i].first;
				m++;
		
			}else if(i == n-1){
				parents_node.push_back(make_pair(nodes[n-1].first , nod_parinte));
				return ++m;

			}else{
				return -1;
			}
		}
		

	}
	
// the output 
	void print_output(int result) {

		ofstream fout("p1.out");

		if( result != -1){
			fout << result-1 << '\n';
			for(int j = 1; j < result; j++){
				fout << parents_node[j].second << " "<< parents_node[j].first << '\n';
			}
		}else{
			fout << result << '\n';
		}

		fout.close();	
	}  
};

int main() {
	Task task;
	task.solve();
	return 0;
}
