#include<iostream>
#include<vector>
#include<stack>

using namespace std;

class Edge{
public:
	int first, second;
	Edge(int first = -1, int second = 1):first(first),second(second){}
};

class articulationPoints{
	/*
	A O(V+E) algorithm to find all Articulation Points (APs)
    The idea is to use DFS (Depth First Search). In DFS, we follow vertices in tree form called DFS tree. In DFS tree, 
	a vertex u is parent of another vertex v, if v is discovered by u (obviously v is an adjacent of u in graph). 
	In DFS tree, a vertex u is articulation point if one of the following two conditions is true.
    1) u is root of DFS tree and it has at least two children.
    2) u is not root of DFS tree and it has a child v such that no vertex in subtree rooted with v has a back edge 
	   to one of the ancestors (in DFS tree) of u.
	*/
	static const int NIL = -1;
	int time; //
	vector<bool> isVisited;
	vector<int> discovery; //stores discovery time of vertices
	vector<int> lowlink; //stores the oldest discovered vertexies connected to the certain one
	                     // It is used to detect if successor of  vertex V has a back edge 
	                     //to one of the ancestors of that vertex V
	vector<int> parent; //stores parent of certain vertex
	vector<int> artPoints;
	const vector<vector<int> > &graph;
	stack<Edge> stak;

	//A O(V+E) algorithm to find all Articulation Points (APs)
	void DFS_tarjan(int vertex){
		bool isAP = false;
		// Count of children in DFS Tree
        int children = 0;
		// Mark the current node as visited
        isVisited[vertex] = true;
		// Initialize discovery time and lowlink value
        discovery[vertex] = lowlink[vertex] = ++time;

	    // Go through all vertices aadjacent to this
		for (unsigned int i = 0; i < graph[vertex].size(); i++)
		{
			// adj is current adjacent of vertex
			int adj = graph[vertex][i];

			// If adj is not visited yet, then make it a child of vertex
            // in DFS tree and recur for it
			if(!isVisited[adj]){
               children++;
               parent[adj] = vertex;
			   //store the edge in stack
			   stak.push(Edge(vertex,adj));

			   DFS_tarjan(adj);

			   // Check if the subtree rooted with adj has a connection to
               // one of the ancestors of current vertex and update the lowlink of the current vertex
			   lowlink[vertex]  = min(lowlink[vertex], lowlink[adj]);

			   // current vertex is an articulation point in following cases

			   // (1) vertex is root of DFS tree and has two or more chilren.
               if ((parent[vertex] == NIL && children > 1) ||
				    (parent[vertex] != NIL && lowlink[adj] >= discovery[vertex]) ){
			        
						while (stak.top().first != vertex || stak.top().second != adj)
						{
							cout << stak.top().first << "--" << stak.top().second << " ";
                            stak.pop();
						}

						cout << stak.top().first << "--" << stak.top().second <<endl;
						stak.pop();
			   }
 
               
			}// Update lowlink value of vertex for parent function calls.
			else if(adj != parent[vertex] && discovery[adj] < lowlink[vertex]){
				lowlink[vertex]  = min(lowlink[vertex], discovery[adj]);
				//store the edge in stack
				stak.push(Edge(vertex,adj));			
			}          
		}

		if(isAP){
          artPoints.push_back(vertex);
		}
	}

public:
	articulationPoints(const vector<vector<int> > &graph_):
		graph(graph_),
		isVisited(graph_.size(),false),
		discovery(graph_.size()),
		lowlink(graph_.size()),
		parent(graph_.size(),NIL),
	    time(0){
     
        // Call the recursive function to find articulation points
		// in DFS tree rooted with vertex 'i'
		for (unsigned int i = 0; i < graph.size(); i++)
			if (isVisited[i] == false)
				DFS_tarjan(i);

		//If stack is not empty, pop all edges from stack
		while(!stak.empty())
        {
            cout << stak.top().first << "--" << stak.top().second << " ";
            stak.pop();
        }

		isVisited.clear();
	    discovery.clear();
	    lowlink.clear();
	    parent.clear();

	}
	void getArticulationPoints(vector<int> &artPoints){
		artPoints = artPoints;
	}

	void deleteArtPoints(){
		artPoints.clear();
	}
};

int main(){

 int a[17][2] ={ {0, 1},
				{0, 2},
				{0, 6},
				{0, 7},
				{0, 9},
				{1, 6},
				{2, 7},
				{3, 4},
				{4, 6},
				{4, 10},
				{5, 7},
				{6, 8},
				{6, 10},
				{6, 11},
				{7, 9},
				{7, 12},
				{8, 11} };
 vector<vector<int> > graph(13);
 for (int i = 0; i < 17; i++)
 {
	 graph[a[i][0]].push_back(a[i][1]);
	 graph[a[i][1]].push_back(a[i][0]);
 }
   articulationPoints ap(graph);
   
	return 0;
}