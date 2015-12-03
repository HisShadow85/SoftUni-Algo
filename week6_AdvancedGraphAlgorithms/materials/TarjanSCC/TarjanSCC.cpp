#include<iostream>
#include<vector>
#include<stack>
#include<sstream>

#define MIN(a,b) ((a)<(b)?(a):(b))

using namespace std;

/*
algorithm tarjan is
  input: graph G = (V, E)
  output: set of strongly connected components (sets of vertices)

  index := 0
  S := empty
  for each v in V do
    if (v.index is undefined) then
      strongconnect(v)
    end if
  end for

  function strongconnect(v)
    // Set the depth index for v to the smallest unused index
    v.index := index
    v.lowlink := index
    index := index + 1
    S.push(v)
    v.onStack := true

    // Consider successors of v
    for each (v, w) in E do
      if (w.index is undefined) then
        // Successor w has not yet been visited; recurse on it
        strongconnect(w)
        v.lowlink  := min(v.lowlink, w.lowlink)
      else if (w.onStack) then
        // Successor w is in stack S and hence in the current SCC
        v.lowlink  := min(v.lowlink, w.index)
      end if
    end for

    // If v is a root node, pop the stack and generate an SCC
    if (v.lowlink = v.index) then
      start a new strongly connected component
      repeat
        w := S.pop()
        w.onStack := false
        add w to current strongly connected component
      until (w = v)
      output the current strongly connected component
    end if
  end function
*/




class Tarjan{
  /*
  input: graph G = (V, E)
  output: set of strongly connected components (sets of vertices)
  */
  int index;
  stack<int> stak;
  vector<int> indices;
  vector<int> lowlink;
  vector<bool> onStack;
  vector<vector<int> > SCC;
  const vector<vector<int> > &graph;

  void strongconnect(int vertex){
	  // Set the depth index for v to the smallest unused index
	  indices[vertex] = index;
      lowlink[vertex] = index;
      index++;
      stak.push(vertex);
      onStack[vertex] = true;

	  // Consider successors of v
	  for (unsigned int i = 0; i < graph[vertex].size(); i++)
	  {
		  //only for clarity
		  int successor = graph[vertex][i];

		  //if successor is undefined)
		  if(indices[successor] == 0){
			  // Successor has not yet been visited; recurse on it
              strongconnect(successor);
			  lowlink[vertex] = MIN(lowlink[vertex],lowlink[successor]);
		  }else if(onStack[successor]){
			  lowlink[vertex] = MIN(lowlink[vertex],indices[successor]);
		  }
	  }
    
	  // If vertex is a root node, pop the stack and generate an SCC
      if(lowlink[vertex] == indices[vertex]){
		  // start a new strongly connected component
		  vector<int> newSCC;
		  int sccVertex;//the current vertex which is to be added in the new SCC

		  do{
			  sccVertex = stak.top();stak.pop();
			  onStack[sccVertex] = false;
			  // add sccVertex to current strongly connected component
			  newSCC.push_back(sccVertex);
		  }while(sccVertex != vertex);
		  
		  SCC.push_back(newSCC);
	  }
  }

public:
	Tarjan(const vector<vector<int> > &graph_):
		graph(graph_),
		onStack(graph_.size(),false),
		lowlink(graph_.size(),0),
		indices(graph_.size(),0),
		index(1){

		for (unsigned int vertex = 0; vertex < graph.size(); vertex++){
			//for every undefined vertex
			if(indices[vertex] == 0){
				strongconnect(vertex);
			}
		}

		//release the used memory
		indices.clear();
        lowlink.clear();
        onStack.clear();
	}

	void getSCC(vector<vector<int> > &SCC){
		SCC = this->SCC;
	}

	void clearSCC(){
		this->SCC.clear();
	}
};

int main(){
	//Nodes: 14//Edges: 21
	istringstream in("14 21\n1 2\n3 3 5 6\n2 4 7\n2 3 8\n2 1 6\n1 7\n1 6\n2 4 7\n");
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
	Tarjan tarjan(graph);
	tarjan.getSCC(graph);
	tarjan.clearSCC();
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