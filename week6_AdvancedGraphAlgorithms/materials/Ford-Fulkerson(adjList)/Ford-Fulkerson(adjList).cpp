#include<iostream>
#include<vector>
#include<queue>
#include<set>

using namespace std;

class Grap{

public:
	class Edge{
	public:
	    int adjacent;
		int capacity;
		Edge(unsigned int adj = -1, int cap = 0):adjacent(adj),capacity(cap){}

		bool operator<(const Edge &other){
			return this->adjacent < other.adjacent;
		}
		
	};

	Grap(const Grap &other){


	}

	void addEdge(int parent,int child, int weight,bool undirected = false){
		while(parent >= vertices.size() || child >= vertices.size() ){
			vertices.push_back(set<Edge>());
		}

		 vertices[parent].insert(Edge(child,weight));

		 if(undirected){
           vertices[child].insert(Edge(parent,weight));
		 }
	}

	int size(){
		return vertices.size();
	}

	set<Edge> &operator[](int index){
		return vertices[index];
	}
private:
	vector<set<Edge> > vertices;
};

class FordFulkerson{
	class Parent{
	public:
		int parent;
		Grap::Edge *edge;
	};

public:
	static bool BFS(Grap &graph,int source,int sink,vector<Parent> path){
		vector<bool> isVisited(graph.size(),false);
		queue<int> que;
		que.push(source);
		isVisited[source] = true;

		if(source == sink) return false;

		while (!que.empty())
		{
			int currVertex = que.front();que.pop();

			//for every adjacent vertex to the current one
			for (set<Grap::Edge>::iterator it = graph[currVertex].begin(); it != graph[currVertex].end(); it++)
			{
				if(!isVisited[it->adjacent]){
					isVisited[it->adjacent] = true;
					path[it->adjacent].parent = currVertex;
					path[it->adjacent].edge = &(Grap::Edge)(*it);
					if(it->adjacent == sink){
	                    goto exit;
					}
				}
			}
		}

        exit:;

		if( isVisited[sink]){
			return true;
		}else{
			return false;
		}
	}


	static int maxFlow(const Grap &graph){

	}

};