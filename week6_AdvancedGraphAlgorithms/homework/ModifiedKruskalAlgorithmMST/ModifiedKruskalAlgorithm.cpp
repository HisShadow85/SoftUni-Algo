#include<iostream>
#include<vector>
#include<sstream>
#include<algorithm>
using namespace std;

class Edge{
public:
	int parent;
	int adj;
	int weight;
	Edge(int parent = -1,int adj = -1, int weight = 0):parent(parent),adj(adj),weight(weight){}

	bool operator<(const Edge &other){
		return this->weight < other.weight;
	}
};


class ModifiedKruskalAlgorithm{
	class Node{
	public:
		int parent;
		vector<int> childs;
		Node(int parent = -1):parent(parent){};
	};

	static void stringRepresentation(vector<string> &msf,Edge &edge){
		 string connection("(");
		 char buffer[255];
		 connection.append(itoa(edge.parent,buffer,10));
		 connection.append(" ");
		 connection.append(itoa(edge.adj,buffer,10));
		 connection.append(") -> ");
		 connection.append(itoa(edge.weight,buffer,10));
		 msf.push_back(connection);
	}

public:
	static int getMST(vector<Edge> &edges,int vertexNum,vector<string> &msf){

		int msfWeight = 0;

		vector<Node> mst(vertexNum);
		for (int i = 0; i < vertexNum; i++)
		{
			//initially all nodes are parent of them self
			mst[i].parent = i;
		}
		//sort the edges by weight
		sort(edges.begin(),edges.end());

		//iterate through all of the given edges
		for (int i = 0; i < edges.size(); i++)
		{
			//if the root of the firs vertex from the current edge has a different root from the other one 
			if(mst[edges[i].parent].parent != mst[edges[i].adj].parent){
				//get the root of the second vertex
			    int secondNode = mst[edges[i].adj].parent;
				//get the root of the first vertex
				int root = mst[edges[i].parent].parent;
				//set the parent of the second vertex root to be the root of the forst one
				mst[secondNode].parent = root;
				//set the root of the second vertex to be child of the first vertex's root
				mst[root].childs.push_back(secondNode);
				//get the childs of the second vertex's root 
				vector<int> &childs = mst[secondNode].childs;

				for (int i = 0; i < childs.size(); i++)
				{
					//set the the parren of each child to be the first vertexl's root
					mst[childs[i]].parent=root;
					//add them to the child list
					mst[root].childs.push_back(childs[i]);
				}
				//the second root has no more children
				childs.clear();
				//add the current weight to the total one
				msfWeight+=edges[i].weight;
				//make string representation of the made connection
				stringRepresentation(msf,edges[i]);
			}
			

		}

		return msfWeight;
	}

};


int main(){
	stringstream ss("4 5\n0 1 9\n0 3 4\n3 1 6\n3 2 11\n1 2 5\n9 15\n1 4 8\n4 0 6\n1 7 7\n4 7 10\n4 8 3\n7 8 4\n0 8 5\n8 6 9\n8 3 20\n0 5 4\n0 3 9\n6 3 8\n6 2 12\n5 3 2\n3 2 14\n8 16\n0 1 4\n0 2 5\n0 3 1\n1 2 8\n1 3 2\n2 3 3\n2 4 16\n2 5 9\n3 4 7\n3 5 14\n4 5 12\n4 6 22\n4 7 9\n5 6 6\n5 7 18\n6 7 15\n");
	for (int i = 1; i < 4; i++)
	{
		cout<<"Example: "<<i<<"\nINPUT:\n";
		int nodes,edges;
		ss>>nodes>>edges;
		cout<<"Nodes: "<<nodes<<"\nEdges: "<<edges<<endl;
		vector<Edge> input(edges);
		for (int i = 0; i < edges; i++)
		{
			ss>>input[i].parent;
			cout<<input[i].parent;
			ss>>input[i].adj;
			cout<<' '<<input[i].adj;
			ss>>input[i].weight;
			cout<<' '<<input[i].weight<<endl;
		}
		vector<string> mfsString;
		int msf = ModifiedKruskalAlgorithm::getMST(input,nodes,mfsString);
		cout<<"OUTPUT:\nMinimum spanning forest weight: "<<msf<<endl;

		for (int i = 0; i < mfsString.size(); i++)
		{
			cout<<mfsString[i]<<endl;
		}
		cout<<"------------------------------------------------------------------------\n";
	}
		

	return 0;
}