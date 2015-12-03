#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<sstream>

using namespace std;

class ConnectedAreasInaMatrix{  

public:

      class Area{
	  public:
		  int x,y,size;
		  Area(int x_=0,int y_=0,int size_=0):x(x_),y(y_),size(size_){}
		  friend ostream &operator<<(ostream &out,Area &area);
	  };


	  struct Compare{
		  bool operator()(const Area &area1,const Area &area2){
			   if(area1.size > area2.size) return true;
			   else if(area1.size == area2.size){
				   if(area1.x < area2.x) return true;
				   else if(area1.x == area2.x){
					      if(area1.y < area2.y) return true;
				   }
			   }
               return false;
		  }
	  };


	ConnectedAreasInaMatrix(vector<string> &matrix_):matrix(matrix_){}


	void printConnectedAreas(){

		connectedAreas.clear();

		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[0].size(); j++)
			{
				if(matrix[i][j] != VISITED && matrix[i][j] != WALL){
					currentAreaSize = 0;
					getConnectedArea(i,j);
					connectedAreas.insert(Area(i,j,currentAreaSize));
				}

			}
		}

		printResult();

	}

private:
	  vector<string> &matrix;
	  static const char VISITED = 'V';
	  static const char WALL = '*';
	  set<Area,Compare> connectedAreas;
	  int currentAreaSize;

	  void getConnectedArea(int x,int y){
		   if(x<0 || y < 0 || x >= matrix.size() || y>=matrix[0].size()) return;

		   if(matrix[x][y] != VISITED && matrix[x][y] != WALL){
		   currentAreaSize++;
		   matrix[x][y] = VISITED;
		   
		   getConnectedArea(x-1,y);
		   getConnectedArea(x+1,y);
		   getConnectedArea(x,y-1);
		   getConnectedArea(x,y+1);
		   }
	  }

	  void printResult(){
		   	cout<<"Total areas found: "<<connectedAreas.size()<<endl;
			set<Area,Compare>::iterator it = connectedAreas.begin();
			for (int i = 1; i <= connectedAreas.size(); i++,it++)
			{
				cout<<"Area #"<<i<<" at ("<<it->x<<", "<<it->y<<") size: "<<it->size<<endl; 
			}
	  }

};


int main(){

	istringstream ss;
	ss.str("5\n*  *   *  \n*  *   *  \n*  *****  \n*  *   *  \n*  *   *  \n");
	int X;
	ss>>X>>ws;
	vector<string> matrix(X);
	for (int i = 0; i < X; i++)
	{  
		getline(ss,matrix[i]);
	}

	ConnectedAreasInaMatrix caim(matrix);

	caim.printConnectedAreas();
	return 0;
}