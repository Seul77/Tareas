#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;


class Graph {
private:
		int edgesList;
		int edgesMat;
		int nodes;
    	vector<int> *adjList;
		int *adjMatrix;

public:
		Graph();
		void addEdgeAdjList(int, int);
		void addEdgeAdjMatrix(int, int);
		string printAdjList();
		string printAdjMat();
		string DFS(int, int);
		string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&);
		string BFS(int, int);
		string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&);
		string print_visited(list<int>);
		string print_path(vector<vector<int>>&,int ,int);
		bool contains(list<int>, int);
		void sortAdjList();
		void loadGraphList(string, int);
		void loadGraphMat(string, int, int);
};

void Graph::loadGraphList(string input, int a){
	adjList = new vector<int>[a];
	nodes = a;
    for (char &ch : input)
		if (ch == '(' || ch == ',' || ch == ')'){
            ch = ' ';
        }
    stringstream ss(input);
    int u, v;
	while (ss >> u >> v)
		addEdgeAdjList(u, v);
	sortAdjList();
}

void Graph::loadGraphMat(string input, int a, int b){
	adjMatrix = new int [a*b];
	nodes = a;
    for (int i = 0; i < a*b; i++)
		adjMatrix[i] = 0;
    for (char &ch : input)
		if (ch == '(' || ch == ',' || ch == ')') ch = ' ';
    stringstream ss(input);
    int u, v;
    while (ss >> u >> v)
		addEdgeAdjMatrix(u, v);
}

Graph::Graph() {
	edgesList = edgesMat = 0;
}


void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}

string Graph::printAdjList(){
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
		return aux.str();

}

void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++)
		sort(adjList[i].begin(),adjList[i].end());
}

string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

string Graph::DFS(int start, int goal){
	stack<int> sta;
	list<int> visited;
	vector<vector<int>> paths(nodes, vector<int>(1, -1));

	sta.push(start);
	string valor = depthHelper(start, goal, sta, visited, paths);
	valor = valor + print_path(paths, start, goal);
	return valor;
}

string Graph::depthHelper(int current, int goal, stack<int> &st, list<int> &visited, vector<vector<int>> &paths){
	if (current == goal){
		visited.push_back(current);
		return print_visited(visited);
	}
	else if (st.empty()){
		return "node not found";
	}
	else{
		current = st.top();
		st.pop();
		visited.push_back(current);
		for (int i = 0; i<adjList[current].size(); i++){
			int neighbour = adjList[current][i];
			if (!contains(visited, neighbour)){
				st.push(neighbour);
				paths[neighbour][0] = current;
			}
		}
		while (!st.empty() && contains(visited, st.top())){
			st.pop();
		}
		if (st.empty()){
			return "node not found";
		}
		return depthHelper(st.top(), goal, st, visited, paths);
	}
}

string Graph::BFS(int start, int goal){
	queue<int> que;
	list<int> visited;
	vector<vector<int>> paths(nodes, vector<int>(1, -1));
	
	que.push(start);
	string valor = breadthHelper(start, goal, que, visited, paths);
	valor = valor + print_path(paths, start, goal);
	return valor;
}

string Graph::breadthHelper(int current, int goal, queue<int> &qu, list<int> &visited, vector<vector<int>> &paths){
	if (current == goal){
		visited.push_back(current);
		return print_visited(visited);
	}
	else if (qu.empty()){
		return "node not found";
	}
	else{
		current = qu.front();
		qu.pop();
		visited.push_back(current);
		for (int i = 0; i<adjList[current].size(); i++){
			int neighbour=adjList[current][i];
			if (!contains(visited, neighbour)){
				qu.push(neighbour);
				if (paths[neighbour][0]==-1){
					paths[neighbour][0] = current;
				}
			}
		}
		if (qu.empty()){
			return "node not found";
		}
	return breadthHelper(qu.front(), goal, qu, visited, paths);
	}
}


bool Graph::contains(list<int> ls, int node){
		list<int>::iterator it;
		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end())
			return true;
		else
			return false;
}

string Graph::print_visited(list<int> q){
	stringstream aux;
	aux << "visited: ";
	while (!q.empty()){
    aux << q.front() << " ";
    q.pop_front();
  }
	return aux.str();
}

string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;
	aux  << "path:";
	while (node != start) {
		reverse.push(node);
    node = path[node][0];
  }
	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top() ;
		reverse.pop();
  }
	return aux.str();
}
#endif 