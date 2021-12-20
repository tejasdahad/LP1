#include<bits/stdc++.h>
#include "omp.h"
using namespace std;
list<int>q;
vector<int>w(7,1000);
int visited[7];
int local_q;
struct Comp
{
// Compare 2 Player objects using name
	bool operator ()(const int & a, const int & b)
	{
	return w[a]<w[b];
	}
};
void showlist(list <int> g)
{
	list <int> :: iterator it;
	for(it = g.begin(); it != g.end(); ++it)
	cout<<*it<<" ";
	cout<<endl;
}
void showvec(vector <int> g)
{
	vector <int> :: iterator it;
	for(it = g.begin(); it != g.end(); ++it)
	cout<<*it<<" ";
	cout<<endl;
}
void bfs(int adj_matrix[7][7], int n_nodes)
{
	if(q.empty())
		return;
	q.sort(Comp());
	//showlist(q);
	//showvec(w);
	//pop first element
	int cur_node = q.front();
	q.pop_front();
	printf("%d, ", cur_node);
	omp_set_num_threads(3);
	#pragma omp parallel for shared(visited)
	for(int i=0; i<n_nodes; i++)
	{
		if(adj_matrix[cur_node][i]>0 && visited[i]==0)
		{
			if(w[i] > adj_matrix[cur_node][i]){
				w[i] = adj_matrix[cur_node][i];
				//cout<<i<<" "<<w[i]<<endl;
			}
			q.push_back(i);
			visited[i]=1;
		}
	}
	bfs(adj_matrix, n_nodes);
}
int main()
{
	int th = omp_get_max_threads();
	cout<<"Max Threads : "<<th<<endl;
	int n_nodes = 7;
	for(int i=0; i<n_nodes; i++)
	{
		visited[i] = 0;
	}
	//shows graph connections
	int adj_matrix[7][7] = {
	{0, 10 ,20 ,0 ,0 ,0 ,0},
	{10 ,0 ,30 ,30 ,0 ,0 ,0},
	{20 ,30 ,0 ,0 ,40 ,0 ,0},
	{0 ,30 ,0 ,0 ,20 ,0 ,0},
	{0 ,0 ,40 ,20 ,0 ,10 ,0},
	{0 ,0 ,0 ,0 ,10 ,0 ,20},
	{0 ,0 ,0 ,0 ,0 ,20 ,0}
	};
	int start_node = 3; //set start node as 1
	q.push_back(start_node);
	w[start_node] = 0;
	visited[start_node] = 1;
	//int cur_node;
	bfs(adj_matrix, n_nodes);
	return 0;
}
