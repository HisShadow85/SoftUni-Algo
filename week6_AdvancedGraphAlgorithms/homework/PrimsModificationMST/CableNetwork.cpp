#include<iostream>
#include<vector>
#include<queue>
#include<sstream>
#include<set>
#define _SCL_SECURE_NO_WARNINGS

using namespace std;

class CableNetwork{
	class Edge{
	public:
		int adj;
		int cableCost;
		bool isInstalled;//used only to track which connection is instaled in the graph.
		                 //If the edge is not installed it is only available
		Edge(int adj = -1,int cost = 0,bool install = false):adj(adj),cableCost(cost),isInstalled(install){}
	};

	class Connection{
		public:
		 Edge *edg;
		 int parent;
		 Connection(int parent = -1, Edge * edg= NULL):parent(parent),edg(edg){}
	};


	struct Compare{
		bool operator()(const Connection &e1,const Connection &e2){
			return e1.edg->cableCost > e2.edg->cableCost;
		}
	};

	int num;

	vector<vector<Edge>> graph;

	//vector<bool> isConnected;
	vector<int> isConnected;
	//set<int> connectedNodes;
	vector<vector<int> > connectedSets;

public:
	CableNetwork(int num=0):graph(num),isConnected(num,0),num(1){}

	void addConnection(int node, int adj,int cost,bool isConnect =  false){
		if( node < 0 || adj < 0 ){
			return;
		}
		while( node >= graph.size() || adj >= graph.size()){
			graph.push_back(vector<Edge>());
			isConnected.push_back(false);
		}

		graph[node].push_back(Edge(adj,cost,isConnect));
		graph[adj].push_back(Edge(node,cost,isConnect));

	}

	void init(priority_queue<Connection,vector<Connection>,Compare> &que,int budget){
		num = 1;

		for (int i = 0; i < graph.size(); i++)
		{
			if(isConnected[i] == 0)
			          BFS(i);
		}
		
		for (int i = 0; i < connectedSets.size(); i++)
		{
			for (int j = 0; j < connectedSets[i].size(); j++)
			{
				putEdgesInQueue(que,connectedSets[i][j],budget);
			}
		}

		/*
        for (set<int>::iterator it = connectedNodes.begin(); it != connectedNodes.end(); it++)
		{
			putEdgesInQueue(que,*it,budget);
		}
		*/
		
}

	void BFS(int index){
		isConnected[index] = num;
		//connectedNodes.insert(index);
		connectedSets.push_back(vector<int>());
		connectedSets[num-1].push_back(index);
		queue<int> q;
		q.push(index);

		while (!q.empty())
		{
			int curr = q.front();q.pop();

			for (int i = 0; i < graph[curr].size(); i++)
			{
				if(graph[curr][i].isInstalled == true && isConnected[graph[curr][i].adj] != num){
					isConnected[graph[curr][i].adj] = num;
					q.push(graph[curr][i].adj);
					//connectedNodes.insert(graph[curr][i].adj);
					connectedSets[num-1].push_back(graph[curr][i].adj);
				}
			}
		}
		num++;
	}


	void putEdgesInQueue(priority_queue<Connection,vector<Connection>,Compare> &que,int node,int budget){
		 vector<Edge> &adjList = graph[node];
		 for (int j  = 0; j  < adjList.size(); j ++)
		 {
			if(isConnected[adjList[j].adj] > isConnected[node] && adjList[j].cableCost <= budget && adjList[j].isInstalled == false){
				que.push(Connection(node,&adjList[j]));
			}
		 }
	}

	void stringRepresentation(vector<string> &newConnections,int node,Edge &edge){
		 string connection("{");
		 char buffer[255];
		 connection.append(itoa(node,buffer,10));
		 connection.append(", ");
		 connection.append(itoa(edge.adj,buffer,10));
		 connection.append("} -> ");
		 connection.append(itoa(edge.cableCost,buffer,10));
		 newConnections.push_back(connection);
	}

	int extedNetwork(int budget,vector<string> &newConnections){
		int currBudget = budget;
		num = 1;

		priority_queue<Connection,vector<Connection>,Compare> que;

		init(que,budget);

		while (!que.empty())
		{
			Edge *currEdge = que.top().edg;
			int parent = que.top().parent;que.pop();
			if(isConnected[currEdge->adj] != isConnected[parent] && currEdge->cableCost <= currBudget ){
				int adjNum = isConnected[currEdge->adj]-1; 
				int parnt = isConnected[parent]-1; 
				for (int i = 0; i < connectedSets[adjNum].size(); i++)
				{
					isConnected[connectedSets[adjNum][i]] = isConnected[parent];
					connectedSets[parnt].push_back(connectedSets[adjNum][i]);
				}
				connectedSets[adjNum].clear();
				//isConnected[currEdge->adj] = isConnected[parent];
				currEdge->isInstalled = true;
				currBudget-=currEdge->cableCost;
				//connectedNodes.insert(currEdge->adj);
				stringRepresentation(newConnections,parent,*currEdge);
				putEdgesInQueue(que,currEdge->adj,currBudget);
			}
		}

		return budget - currBudget;
	}
};


int main(){

	stringstream ss("20 9 15\n1 4 8\n4 0 6 connected\n1 7 7\n4 7 10\n4 8 3\n7 8 4\n0 8 5 connected\n8 6 9\n8 3 20 connected\n0 5 4\n0 3 9 connected\n6 3 8\n6 2 12\n5 3 2\n3 2 14 connected\n7 4 5\n0 1 9\n0 3 4 connected\n3 1 6\n3 2 11 connected\n1 2 5\n20 8 16\n0 1 4\n0 2 5\n0 3 1\n1 2 8\n1 3 2\n2 3 3\n2 4 16\n2 5 9\n3 4 7\n3 5 14\n4 5 12\n4 6 22\n4 7 9\n5 6 6\n5 7 18\n6 7 15\n");
	for (int i = 1; i < 4; i++)
	{
		int budget,nodeCount,edgeCount;
		ss>>budget>>nodeCount>>edgeCount;
		cout<<"Exaple: "<<i<<"\nINPUT: \nBudget: "<<budget<<"\nNodes: "<<nodeCount<<"\nEdges: "<<edgeCount<<endl;
		CableNetwork cn(nodeCount);
		for (int i = 0; i < edgeCount; i++)
		{   
			string connected;
			int node,adj,cost;
			ss>>node;
			ss>>adj;
			ss>>cost;
			getline(ss,connected);
			cout<<node<<' '<<adj<<' '<<cost<<' '<<connected<<endl;
			cn.addConnection(node,adj,cost,connected.size()>0);
		}
		vector<string> newConnections;
		int spendBudget = cn.extedNetwork(budget,newConnections);
		cout<<"OUTPUT:\n";
		for (int i = 0; i < newConnections.size(); i++)
		{
			cout<<newConnections[i]<<endl;
		}
		cout<<"Budget used: "<<spendBudget<<endl;
		cout<<"---------------------------------------------------------------------------\n";
	}
	return 0;
}