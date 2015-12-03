#include<iostream>
#include<vector>
#include<stack>
#include<sstream>
/*
  Kosaraju-Sharir Algorithm
  1. DFS for all unvisited Vertices. On exit put in Stack 
  2. Reverse graph
  3. DFS for all unvisited Vertices startig from the top of the stack. On exit put in the new SCC set
    Θ(|V|+|E|) for adjacency list  (linear time)
	O(|V|^2) for adjacency matrix
) 
*/
using namespace std;

class KosarajuSharir{

	const vector<vector<int> > graph;
	vector<vector<int> > reversedGraph;
	vector<vector<int> > SCC;
	vector<bool> isVisited;
	stack<int> stak;

	void reverseEdge(int predecessor, int successors){
		 reversedGraph[successors].push_back(predecessor);
	}

	void DFS_Walk(int vertex){
		//set the vertex as visited
		isVisited[vertex] = true;
	
		//iterates through all  successors
		for (unsigned int successors = 0; successors < graph[vertex].size(); successors++)
		{
			//reverse the graph edge by edge
			reverseEdge(vertex,graph[vertex][successors]);
			//make DFS for all unvisited successors
			if(!isVisited[graph[vertex][successors]]){
				DFS_Walk(graph[vertex][successors]);
			}
		}
		//on exit insert the vertex in the stack
		stak.push(vertex);
    }

	void DFS_Reverse(int vertex){
		//set the vertex as visited
		isVisited[vertex] = true;
		
		//iterates through all  successors
		for (unsigned int successors = 0; successors < reversedGraph[vertex].size(); successors++)
		{
			//make DFS for all unvisited successors
			if(!isVisited[reversedGraph[vertex][successors]]){
				DFS_Reverse(reversedGraph[vertex][successors]);
			}
		}
		//on exit insert the vertex in the next SCC set
		SCC[SCC.size()-1].push_back(vertex);
    }

public:

	KosarajuSharir(const vector<vector<int> > &graph_):
		graph(graph_),reversedGraph(graph_.size()),isVisited(graph_.size(),false){

			for (unsigned int vertex = 0; vertex < graph.size(); vertex++)
			{
				//make DFS for all unvisited vertices
				if(!isVisited[vertex]){
                   DFS_Walk(vertex);
				}
			}

			//reset the array indicating if a certain vector is visited
			for (unsigned int i = 0; i < graph.size(); i++)
			{
				isVisited[i] = false;
			}

			//get the set of SCC
			while (!stak.empty())
			{
				int vertex = stak.top();stak.pop();

				if(!isVisited[vertex]){
					//makes new entry of SCC set
					SCC.push_back(vector<int>());
					//load the set of SCC in the new entry
					DFS_Reverse(vertex);
				}
			}
			//release the used memory
			reversedGraph.clear();
			isVisited.clear();
	}

	void getSCC(vector<vector<int> > &SCC){
		SCC = this->SCC;
	}

	void clearSCC(){
		this->SCC.clear();
	}
};

int main(){

	istringstream in("8\n1 2\n3 3 5 6\n2 4 7\n2 3 8\n2 1 6\n1 7\n1 6\n2 4 7\n");
	int N,M;
	in>>N;
	vector<vector<int> > graph(N);
	for (int i = 0; i < N; i++)
	{
		in>>M;
	    graph[i].resize(M);
		for (int j = 0; j < M; j++)
		{
			in>>graph[i][j];
			graph[i][j]--;//zero based array
		}		
	}
	KosarajuSharir kosarajuSharir(graph);
	kosarajuSharir.getSCC(graph);
	kosarajuSharir.clearSCC();
	for ( unsigned int i = 0; i < graph.size(); i++)
	{
		for (unsigned int j = 0; j < graph[i].size(); j++)
		{
			cout<<graph[i][j]<<' ';
		}
		cout<<endl;
	}
	return 0;
}