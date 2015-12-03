#include<iostream>
#include<vector>
#include<queue>
#include<sstream>
#include<iomanip>

using namespace std;

	class Grap{
	public:
		class Edge{
		public:
			int adjacent;
			double reliability;
			Edge(int adjacent = -1,double reliability=0):adjacent(adjacent),reliability(reliability/100){}
	};

	vector<vector<Edge> > graph;

	public:
		Grap(int numberOfVertex):graph(numberOfVertex){}

	void addEdge(int node, int adj, int reliability){

		if( node < 0 || adj < 0 ){
			return;
		}
		while( node >= graph.size() || adj >= graph.size()){
			graph.push_back(vector<Edge>());
		}

		graph[node].push_back(Edge(adj,reliability));
		graph[adj].push_back(Edge(node,reliability));

	}

	vector<Edge> &operator[](int index){
		return graph[index];
	}

	int size()const{
		return graph.size();
	}
};


class MostReliablePath{

public:

	static double findMostReliablePath(Grap &grap,int start,int end,vector<int> &direction){

		class AuxNode{
		public:
			int parent;
			int child;
			float reliability;
			AuxNode(int parent,int child,float reliability):reliability(reliability),parent(parent),child(child){}
			AuxNode(){}
		};

		struct Compare{
			bool operator()(const AuxNode &node1,const AuxNode &node2){
				return node1.reliability < node2.reliability;
			}
		};

		priority_queue<AuxNode,vector<AuxNode>,Compare> que;

		vector<bool> visited(grap.size(),false);
		vector<int> path(grap.size());
		vector<float> reliability(grap.size(),0.0f);
		reliability[start] = 1.00f;

		que.push(AuxNode(start,start,100));

		while (!que.empty())
		{
			int currNode = que.top().child;
			if(visited[currNode] == true){
				que.pop();
				continue;
			}

			path[currNode] = que.top().parent; que.pop();	
			visited[currNode] = true;

			if(currNode==end){
				break;
			}

			vector<Grap::Edge> &adjList = grap[currNode];

			for (int i = 0; i < adjList.size(); i++)
			{
				float currReliability = reliability[currNode] * adjList[i].reliability;
				int adjacentNode = adjList[i].adjacent;

				if(visited[adjacentNode] == false && reliability[adjacentNode] < currReliability){
					reliability[adjacentNode] = currReliability;
					que.push(AuxNode(currNode,adjacentNode,currReliability));
				}
			}

		}
		
		if(visited[end]){

			while(end != start){
				direction.push_back(end);
			    end = path[end];
			}
            direction.push_back(start);

			for (int i = 0, j = direction.size()-1; i < j; i++,j--)
			{
				swap(direction[i],direction[j]);
			}

			return reliability[direction[direction.size()-1]];
		}
		else{
			return -1;
		}
	}

};


int main(){
     stringstream ss("7 0 6 10\n0 3 85\n0 4 88\n3 1 95\n3 5 98\n4 5 99\n4 2 14\n5 1 5\n5 6 90\n1 6 100\n2 6 95\n4 0 1 4\n0 1 94\n0 2 97\n2 3 99\n1 3 98\n");
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
		 double reliability = MostReliablePath::findMostReliablePath(graph,start,end,path);
		 cout<<"OUTPUT:\n";
		 if(reliability > -1 ){
			 cout<<"Most reliable path reliability: "<<setprecision(4)<<reliability*100<<"%\n";
			 for (int i = 0; i < path.size()-1; i++)
			 {
				 cout<<path[i]<<" -> ";
			 }
			 cout<<path[path.size()-1];
		 }else{
			 cout<<"There is no path between the nodes";
		 }
		 cout<<"\n-----------------------------------------------------------------------------\n";
	 }
	return 0;
};