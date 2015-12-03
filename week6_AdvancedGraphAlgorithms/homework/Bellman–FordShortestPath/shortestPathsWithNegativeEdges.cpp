#include<iostream>
#include<vector>
#include<sstream>

using namespace std;

class Grap{
	public:
		class Edge{
		public:
			int adjacent;
			int distance;
			Edge(int adjacent = -1,int distance = 0):adjacent(adjacent),distance(distance){}
	};

	vector<vector<Edge> > graph;

	public:
		Grap(int numberOfVertices):graph(numberOfVertices){}

	void addEdge(int node, int adj, int distance){

		if( node < 0 || adj < 0 ){
			return;
		}
		while( node >= graph.size() || adj >= graph.size()){
			graph.push_back(vector<Edge>());
		}

		graph[node].push_back(Edge(adj,distance));

	}

	vector<Edge> &operator[](int index){
		return graph[index];
	}

	int size()const{
		return graph.size();
	}
};


class ShortesPath{
public:
		static	void  getCycle(vector<int> &path,vector<int> &tempPath,int vertex){
			int end = vertex;
			tempPath.clear();
			do{
			   vertex = path[vertex];
			   tempPath.push_back(vertex);
			}while(vertex != end);

			for (int i = 0, j = tempPath.size()-1; i < j; i++,j--)
			{
				swap(tempPath[i],tempPath[j]);
			}
		}

		static void getPath(vector<int> &path,vector<int> &tempPath,int end){
			tempPath.clear();
			tempPath.push_back(end);
			while (end != path[end])
			{
				end = path[end];
				tempPath.push_back(end);
			}
			for (int i = 0, j = tempPath.size()-1; i < j; i++,j--)
			{
				swap(tempPath[i],tempPath[j]);
			}
		}

		static bool BellmanFord(Grap &graph, int src,int des,int &destination,vector<int> &thePath)
		{
			// Step 1: Initialize distances from src to all other vertices
			// as INFINITE
			vector<int> dist(graph.size(),INT_MAX);
			vector<int> path(graph.size());
			for (int i = 0; i < path.size(); i++)
			{
				path[i] = i;
			}
     
			dist[src] = 0;
 
			// Step 2: Relax all edges |V| - 1 times. A simple shortest 
			// path from src to any other vertex can have at-most |V| - 1 
			// edges
			for (int i = 1; i < graph.size(); i++)
			{
				for (int j = 0; j < graph.size(); j++)
				{
					for (int k = 0; k < graph[j].size(); k++)
					{
						int curr = j;
						int adj = graph[j][k].adjacent;
						int weight = graph[j][k].distance;

						if (dist[curr] != INT_MAX && dist[curr] + weight < dist[adj]){
							 dist[adj] = dist[curr] + weight;
							 path[adj] = curr;
						}
               
					}
            
            
				}
			}
    
			// Step 3: check for negative-weight cycles.  The above step 
			// guarantees shortest distances if graph doesn't contain 
			// negative weight cycle.  If we get a shorter path, then there
			// is a cycle.
			int cycleNode = 0;
			for (int j = 0; j < graph.size(); j++)
				{
					for (int k = 0; k < graph[j].size(); k++)
					{
						int curr = j;
						int adj = graph[j][k].adjacent;
						int weight = graph[j][k].distance;

						if (dist[curr] != INT_MAX && dist[curr] + weight < dist[adj]){
							 dist[adj] = dist[curr] + weight;
							 path[adj] = curr;
							 cycleNode = curr;
							 goto cycle;
						}
               
					}
			}

			 if(false){
				 cycle:
				 getCycle(path,thePath,cycleNode);
				 return false;
			 }else{
				 if(dist[des] != INT_MAX){
					 getPath(path,thePath,des);
				 }      
				 destination = dist[des];
				 return true;
			 }
	}



};

int main(){
	 stringstream ss("10 0 9 19\n0 3 -4\n0 6 10\n0 8 12\n1 9 -50\n2 5 12\n2 7 -7\n3 2 -9\n3 5 15\n3 6 6\n3 8 -3\n4 1 20\n4 3 -5\n5 1 -6\n5 4 11\n5 7 -20\n6 4 17\n7 1 26\n7 9 3\n8 2 15\n4 0 3 5\n0 2 10\n0 1 12\n2 1 -10\n1 3 3\n3 2 6\n");

     for (int i = 1; i < 3; i++)
	 {
		 cout<<"Exampele: "<<i<<endl;
		 int nodes,start,end,edges;
		 ss>>nodes>>start>>end>>edges;
		 cout<<"INPUT:\nNodes: "<<nodes<<"\nPath: "<<start<<" - "<<end<<"\nEdges: "<<edges<<endl;
		 Grap graph(nodes);
		 for (int i = 0; i < edges; i++)
		 {
			 int node,adj,reliability;
			 ss>>node>>adj>>reliability;
			 cout<<node<<' '<<adj<<' '<<reliability<<endl;
			 graph.addEdge(node,adj,reliability);
		 }
		 vector<int> path;
		 int distance;
		 bool noCycle = ShortesPath::BellmanFord(graph,start,end,distance,path);
		 cout<<"OUTPUT:\n";
		 if(noCycle){
			 cout<<"Distance ["<<start<<" -> "<<end<<"]: ";
			 if(distance != INT_MAX) cout<<distance<<"\nPath: ";
			 else cout<<"there is no avaliable path";		 
		 }else{
			 cout<<"Negative cycle detected: ";
		 }
		 for (int i = 0; i < path.size()-1; i++)
		 {
				 cout<<path[i]<<" -> ";
		 }
		 cout<<path[path.size()-1];
		 cout<<"\n-----------------------------------------------------------------------------\n";
	 }


	return 0;
}