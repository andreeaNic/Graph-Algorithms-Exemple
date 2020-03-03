#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <utility>
#include <set>
#include <bits/stdc++.h>
#include <tuple>

using namespace std;

const int kNmax = 1005;

class Task {

 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, m, t; 
	vector<vector<long int>>penalty;
	vector<tuple<int, long int, int> > adj[kNmax];

	void read_input() {

		ifstream fin("p3.in");

		int i, x, y, type, j;
        long int cost, type_penalty;

		fin >> n >> m >> t;

		for (i = 1; i <= m; i++) {
            fin >> x >> y >> cost >>type;
            adj[x].push_back(make_tuple(y, cost, type));
            adj[y].push_back(make_tuple(x, cost, type));
        }

        penalty.resize(t + 1, vector<long int>(t + 1));

        for(i = 1; i <= t; i++){
            for(j = 1; j <= t; j++){
                fin >> type_penalty;
            	penalty[i][j] = type_penalty;
            }
        }

       fin.close();

	}

	int get_result() {

        int source = 1;
        int dest = n;
        int iter, i;


        long int costs[n + 1][t + 1];
        for(iter = 1; iter <= t; iter ++){
            costs[source][iter] = 0;
        }

        for(int iter1 = 2; iter1 <= n; iter1 ++){
            for(int iter2 = 1; iter2 <=t; iter2 ++){
                costs[iter1][iter2] = INT_MAX;
            }
        }

        queue<int > nodes_found;
        nodes_found.push(source);
       
        while(!nodes_found.empty()){

            int node = nodes_found.front();
            nodes_found.pop();

            for (i = 0; (unsigned)i < adj[node].size(); i++) {

                int nod_adiacent = get<0> (adj[node][i]);
                long int cost_edge = get<1> (adj[node][i]);
                int type_edge = get<2>(adj[node][i]);

                for(iter = 1; iter <= t; iter ++){

                    if(costs[nod_adiacent][type_edge] > costs[node][iter] + cost_edge + penalty[iter][type_edge]){

                        costs[nod_adiacent][type_edge] = costs[node][iter] + cost_edge + penalty[iter][type_edge];

                        nodes_found.push(nod_adiacent);
                    }
                }        
            }
        }

        long int cost_minim = INT_MAX;

        for(iter = 1; iter <= t; iter++){
            if(cost_minim > costs[dest][iter]){
                cost_minim = costs[dest][iter];
            }
        } 

        return cost_minim;
    }

	void print_output(long int result) {

		ofstream fout("p3.out");

        if(result == INT_MAX){
            fout << -1 << endl;
        }else{
            fout << result << endl;
        }

		fout.close();	
	}  
};

int main() {
	Task task;
	task.solve();
	return 0;
}
