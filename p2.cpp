#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <climits>
#include <iostream>
#include <tuple>
#include <bits/stdc++.h>

using namespace std;

const int white = 0;
const int grey = 1;
const int black = -1;

class Task {

 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, m, k; 
	vector <vector<long int>> matrix;

	void read_input() {
		ifstream fin("p2.in");
		fin >> n >> m >> k;

		long int value;
		matrix.resize(n + 1 , vector<long int>(m + 1));

		for(int i = 1; i <=n ; i++){

			for(int j = 1; j <= m ; j++){
				fin >> value;
				matrix[i][j] = value;
            }
		}

		fin.close();

	}

	bool checkIfValid(long int value, long int min_value, long int max_value){

		if(value - min_value > k){

			return false;

		}else if(max_value  - value > k){

			return false;
		}	

		return true;
	}		


	vector<tuple<int, int, long int>> getAdiacentNodes(tuple <int, int, long int> node_curr){

		vector< tuple <int, int, long int> > adiacent_nodes_vect;

		const int i = get<0> (node_curr);
		const int j = get<1> (node_curr);

		if (i > 1 ) {
		    adiacent_nodes_vect.push_back(make_tuple(i - 1, j, matrix[i - 1][j]));
		}

		if (i < n) {
		    adiacent_nodes_vect.push_back(make_tuple(i + 1, j, matrix[i + 1][j]));
		}

		  
		if (j > 1) {
		    adiacent_nodes_vect.push_back(make_tuple(i, j - 1, matrix[i][j - 1]));
		} 

	
		if (j < m) {
		    adiacent_nodes_vect.push_back(make_tuple(i, j + 1, matrix[i][j + 1]));
		}

		return adiacent_nodes_vect;

	}

	int bfs (tuple<int, int, long int> source){

			long int min_value, max_value = get<2> (source);

			int visited[n + 1][m + 1] = {white};

			int area = 0;

			queue<tuple<int, int, int>> q;

			q.push(source);

			while(!q.empty()){

                tuple<int, int, long int> u = q.front();
                long int value_u = get<2> (u);


                if(value_u > max_value){
               		max_value = value_u;
               	}else if(value_u < min_value){
               		min_value = value_u;
               	}
                	
	            vector<tuple<int, int, long int>> adiacent_nodes;
	            adiacent_nodes = getAdiacentNodes(u);

	           	for(tuple<int, int, long int> new_node : adiacent_nodes){

	                if(visited[get<0> (new_node)][get<1> (new_node)] == white){

					    if(checkIfValid(get<2> (new_node), min_value, max_value)){
								
							visited[get<0> (new_node)][get<1> (new_node)] = grey;
							q.push(new_node);
		                }

		            }
				}


	            visited[get<0>(u)][get<1> (u)] = black; 
	            q.pop();

	            area = area + 1;
        	}

		return area;
	}		 

	int get_result() {

		int maxim_array = 0;

		for(int iter1 = 1; iter1 <= n; iter1 ++){
			for(int iter2 = 1; iter2 <= m; iter2 ++){

				tuple<int, int, long int> source = make_tuple(iter1, iter2, matrix[iter1][iter2]);

				int array = 0;

				array = bfs(source);

				if(array > maxim_array){
					maxim_array = array;
				} 
			}
		} 
		
		return maxim_array;

	}

	void print_output(int result) {

		ofstream fout("p2.out");
        //fout 
        fout<< result << '\n';
		fout.close(); 
		
	}  
};

int main() {
	Task task;
	task.solve();
	return 0;
}
