#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <utility>
#include <set>
#include <bits/stdc++.h>
#include <tuple>
/* Problem solved: almost same problem as 3. The only difference is that, here, all edges have their own penalty
*/
using namespace std;

const int kNmax = 1005;
//compare implemented from the priority queue we will used in the Dijkstra algorithm
struct compare
{
    bool operator()(tuple <int, int, int> l, tuple <int, int, int> r)
    {
        return (get<1> (l) ) > (get<1> (r) );
    }
};

class Task {

 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, m, t; 
	vector<int>penalty;
	vector<tuple<int, int, int> > adj[kNmax];

	void read_input() {

		ifstream fin("p4.in");

		int i, x, y, w, type, type_penalty;

		fin >> n >> m >> t;

		for (i = 1; i <= m; i++) {
		    fin >> x >> y >> w >>type;
		    adj[x].push_back(make_tuple(y, w, type));
		    adj[y].push_back(make_tuple(x, w, type));
		}

		penalty.resize(m + 1);

		for(i = 1; i <= t; i++){
			fin >> type_penalty;
			penalty[i] = type_penalty;

		}

	       fin.close();

	}
//Dijkstra 
	int get_result() {

		int i,u;
		vector<int> cost(n + 1, 0);
		priority_queue< tuple<int, int, int>, vector< tuple <int, int, int> >, compare > q;
		vector<int> vizited(n + 1, 0);
		vector<int> penalty_applied(m + 1, 0);

		int source = 1;
//Dijkstra
		q.push(make_tuple(source, 0, 0));
		cost[source] = 0;
		vizited[source] = 1;

		for (i = 1; i <= n; i++) {
		    if (i != source) {
			cost[i] = (1<<30);
		    }
		}

		while (!q.empty()) {
		    u = get <0> (q.top());
			
		    q.pop();
		    vizited[u] = 1;

		    int type_edge_applied = get<2> (q.top());

		    penalty_applied[type_edge_applied] = 1;

		    for (i = 0; i < adj[u].size(); i++) {
			tuple<int, int, int> tup = adj[u][i];
			int adj_node = get<0> (tup);
			int cost_edge = get<1> (tup);
			int type_edge = get<2> (tup);

			if(penalty_applied[type_edge] == 0){
				cost_edge += penalty[type_edge];
			}

			if(vizited[adj_node] == 0){
				if(cost[adj_node] > cost[u] + cost_edge) {
					cost[adj_node] = cost[u] + cost_edge;
					q.push(make_tuple(adj_node, cost[adj_node], type_edge));
				}
			    } 
		    }
		}    


		if(vizited[n] == 0){
			cost[n] = -1;
		}

		return cost[n];

	}

	void print_output(int result) {

		ofstream fout("p4.out");

		fout << result << "\n";

		fout.close();	
	}  
};

int main() {
	Task task;
	task.solve();
	return 0;
}
