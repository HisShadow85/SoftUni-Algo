#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<queue>
using namespace std;

//the solution works only for the numbers to 5 included

struct Cell{
			int x,y;
			Cell(int x_=0,int y_=0):x(x_),y(y_){}
			
			bool operator==(const Cell &other)const{
				if( (this->x == other.x) && (this->y == other.y) ) return true;
				else return false;
			}

			bool operator>(const Cell &other)const{
				if(this->y > other.y) return true;
				else if(this->y == other.y){
					if(this->x > other.x) return true;
				}
				return false;
			} 

			 bool operator<(const Cell &other){
				if(this->y < other.y) return true;
				else if(this->y == other.y){
					if(this->x < other.x) return true;
				}
				return false;
			} 

			 friend bool operator<(const Cell &first,const Cell &second);
			
			 Cell(const Cell &init){
				 this->x = init.x;
				 this->y = init.y;
			 }
		};


   bool operator<(const Cell &first,const Cell &second){
				if(first.y < second.y) return true;
				else if(first.y == second.y){
					if(first.x < second.x) return true;
				}
				return false;
			} 



class Snake{

	vector<vector<bool> > matrix;//it marks the cell on which we have stepped
	/*Тhis stupidity will compare whether a form is created or not.
	First we are going to compare by the sum of all adjacent cell 
	for each one cell of the current snake. Then by the squared area which  
	is needed for the visualisation of the snake. If all of this is equal, 
	we try to check if is ti inverted 90 degrees image */
	map<int,map<int,map<Cell,bool> > > hashSet;
	int maxDepth;//count the block that we have putted
	string currentForm;//holds the cuurent found form
	vector<string> forms;//contain all non repeated forms of snakes

	void BFS(){
		//the sum of all adjacent cell for each one cell of the current snake	
		unsigned short adjancentCell = 0;
		//local matrix indicated if we have checked this cell already
		//false - >cheked true-> not checked
		vector<vector<bool> > isVisited(matrix);
        
		/*by these variables we are going to compute the base(in square cells)
		needed for the snake visualization*/
		int mostBottomX = 0;
		int mostBottomY = 0;

		queue<Cell> q;
		q.push(Cell(0,0));
		isVisited[0][0] = false;

		//standart BFS
		while (!q.empty())
		{
			Cell cell = q.front();q.pop();
			
			if(cell.x > mostBottomX) mostBottomX = cell.x;
			if(cell.y > mostBottomY) mostBottomY = cell.y;

			for(int i = cell.x-1; i < cell.x+2; i++)
			{   
				if(i<0 || i >= (int)matrix.size()) continue;
				for (int j = cell.y-1; j < cell.y+2; j++)
				{
				   if(j<0 || j >= (int)matrix[0].size()) continue;
				   if(isVisited[i][j] == true){
						isVisited[i][j] = false;
						 q.push(Cell(i,j));
					}
				   if(matrix[i][j] == true){
                    adjancentCell++;
					}
				}
			}
			//this is because we have add the current cell to his adjacent cells
			adjancentCell--;
		}
		//compute the base for the snake
		int base = (mostBottomX+1)*(mostBottomY+1);

		//find where is the head of the snake
		Cell lastPuttedCell;
		for (int i = 1; i < (int)currentForm.size(); i++)
		{
			switch (currentForm[i])
			{
			case 'R': lastPuttedCell.y++; break;
			case 'D': lastPuttedCell.x++; break;
			case 'L': lastPuttedCell.y--; break;
		    case 'U': lastPuttedCell.x--; break;
			}
		}		

		map<int,map<int,map<Cell,bool> > >::iterator it = hashSet.find(adjancentCell);
		//if there are no matches by adjancenct cells number
		if(it == hashSet.end()){
			hashSet[adjancentCell][base].insert(pair<Cell,bool>(Cell(lastPuttedCell.x,lastPuttedCell.y),true));
			forms.push_back(currentForm);
		}else{
			map<int,map<Cell,bool> >::iterator it2  = it->second.find(base);
			//if there are no matches by base
			if(it2 == it->second.end()){
               hashSet[adjancentCell][base][lastPuttedCell] = true;
			   forms.push_back(currentForm);
			}else{
               //it the snake form is not inverted 90 degrees
			   Cell tempCell(lastPuttedCell.y,lastPuttedCell.x);
               map<Cell,bool>::iterator it3 = it2->second.find(lastPuttedCell);
			   if(it3 == it2->second.end()){
				   map<Cell,bool>::iterator it3 = it2->second.find(tempCell);
				   if(it3 == it2->second.end()){
				     hashSet[adjancentCell][base][lastPuttedCell] = true;
				     forms.push_back(currentForm);
				   }
			   }
			}
		}
	}

public:

	Snake(int size):maxDepth(size),matrix(size,vector<bool>(size,0)){}

	void makeSnake(int x, int y,char direction){

		//set the next direction 
		currentForm.push_back(direction);
		maxDepth--;//count the block that we have putted
		matrix[x][y] = true;//mark as visited

		if(maxDepth <=  0){
			BFS();
		}
		else{
			//step to the four available directions (right, down , left and up)
			// if they are free
			if(y+1 < (int)matrix[0].size() && matrix[x][y+1] != true){
                 makeSnake(x,y+1,'R');
			}
			if(x+1 < (int)matrix.size() && matrix[x+1][y] != true){
                 makeSnake(x+1,y,'D');
			}
			if(y-1 >=0 && (int)matrix[x][y-1] != true){
                 makeSnake(x,y-1,'L');
			}
			if(x-1 >=0 && (int)matrix[x-1][y] != true){
                 makeSnake(x-1,y,'U');
			}			
		}

		matrix[x][y] = false;//mark as unvisited
		maxDepth++;
		currentForm.pop_back();
	}

	void printResult(){
		for (int i = 0; i < (int)forms.size(); i++)
		{
			cout<<forms[i]<<endl;
		}
		cout<<"Snakes count = "<<forms.size();
	}

};

int main(){
	int n;
	cin>>n;
	Snake snake(n);
	snake.makeSnake(0,0,'S');
	snake.printResult();
	return 0;
}