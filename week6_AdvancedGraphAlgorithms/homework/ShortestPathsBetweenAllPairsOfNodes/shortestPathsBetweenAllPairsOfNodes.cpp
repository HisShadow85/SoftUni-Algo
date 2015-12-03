#include<iostream>
#include<limits>
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
		graph[adj].push_back(Edge(node,distance));

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
	typedef unsigned short vertex;
    typedef short distance;
	const distance INFINITY ;
	
	ShortesPath(Grap &graph):
	  INFINITY(std::numeric_limits<distance>::max()),
	  NOWAY(std::numeric_limits<vertex>::max()),
      dist(graph.size(),vector<distance>(graph.size(),INFINITY)),
	  next(graph.size(),vector<vertex>(graph.size(),NOWAY)){
	  FloydWarshall(graph);
	}
	

    void FloydWarshall(Grap &graph){
    //for each edge (u,v)
	  for (vertex u = 0; u < graph.size(); u++)
	  {
		  dist[u][u] = 0; //the distance from the vertex to itself
		  for(vertex v = 0; v < graph[u].size(); v++){
			  
            dist[u][graph[u][v].adjacent] = graph[u][v].distance; // the weight of the edge (u,v)
			next[u][graph[u][v].adjacent] = graph[u][v].adjacent; //to pass from u to v we must go first throughout v
			  
		  }
	  }
	  // standard Floyd-Warshall implementation
	  for (vertex k = 0; k < (vertex)graph.size(); k++)
	  {
		  for (vertex i = 0; i < (vertex)graph.size(); i++)
		  {
			  for (vertex j = 0; j < (vertex)graph.size(); j++)
			  {
				  if( (dist[i][k]+ dist[k][j]) < dist[i][j] ){
					   dist[i][j] = dist[i][k] + dist[k][j];
					   next[i][j] = next[i][k];

				  }
			  }
		  }
	  }
}

	void printAllDistances(){
		for (int i = 0; i < dist.size(); i++)
		{
			cout<<i<<'\t';
		}
		cout<<endl;
		for (int i = dist.size(); i > 0; i--)
		{
			cout<<"---\t";
		}
		cout<<endl;
		for (int i = 0; i < dist.size(); i++)
		{
			for (int j = 0; j < dist.size(); j++)
			{
				if(dist[i][j] != INFINITY)
				   cout<<dist[i][j]<<'\t';
				else{
                   cout<<'X\t';
				}
			}
			cout<<endl;
		}
	}

	vector<vertex> getPath(vertex start,vertex end){
		   if (next[start][end] == NOWAY)
			   return vector<vertex>();
		   vector<vertex> path;
		   vertex currNode = start;
		   path.push_back(currNode);
		   while(currNode != end){
			   currNode = next[currNode][end];
			   path.push_back(currNode);
		   }
		   return path;
		}

	distance getLowestDistance(vertex start,vertex end){
		return dist[start][end];
	}

private:
	vector<vector<distance> > dist;//a V*V array of minimum distances initialized to infinity.
	vector<vector<vertex> > next; //a V*V array of vertex indices initialized to null (-1)
	const vertex NOWAY;
};

int main(){
	
	stringstream ss("4 5\n0 2 10\n0 1 12\n1 2 10\n1 3 3\n2 3 6\n10 17\n0 6 10\n0 8 12\n1 4 20\n1 5 6\n1 7 26\n1 9 5\n2 5 9\n2 7 15\n2 8 14\n3 4 5\n3 5 33\n3 6 6\n3 8 3\n4 5 11\n4 6 17\n5 7 20\n7 9 3\n");
	for (int i = 1; i < 3; i++)
	{
		cout<<"Example: "<<i<<"\nINPUT:\n";
		int nodes,edges;
		ss>>nodes>>edges;
		cout<<"Nodes: "<<nodes<<"\nEdges: "<<edges<<endl;
		Grap graph(nodes);
		for (int i = 0; i < edges; i++)
		{
			int parent,adj,cost;
			ss>>parent;
			cout<<parent;
			ss>>adj;
			cout<<' '<<adj;
			ss>>cost;
			cout<<' '<<cost<<endl;
			graph.addEdge(parent,adj,cost);
		}
		
		cout<<"OUTPUT:\nShortest paths matrix:\n";
        ShortesPath sp(graph);
		sp.printAllDistances();
		cout<<"------------------------------------------------------------------------\n";
	}
		

	return 0;

}