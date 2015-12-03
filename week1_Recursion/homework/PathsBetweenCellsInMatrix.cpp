#include<iostream>
#include<vector>
#include<string>
//#include<stack>
#include<iterator>
#include<algorithm>
#include<sstream>

using namespace std;

class PathsBetweenCellsInMatrix{
    static const char START = 's';
	static const char EXIT = 'e';
	static const char WALL = '*';
	static const char VISITED = 'v';
	static const char UNVISITED = ' ';
	vector<string> &maze;
	//stack<char> path;
	int startX,startY,pathNumber;
	vector<char> path;

	void findPath(int row, int col, char direction){
		//if we have stepped out of the labyrinth
		if(row < 0 || col < 0 || row >= maze.size() || col >= maze[0].size() ) return;
		//if we reach a wall
		if(maze[row][col] == WALL) return;
		//if the current cell is in the path stack already
		if(maze[row][col] == VISITED) return;
		// Append the direction to the path
		path.push_back(direction);
		// Check if we have found the exit
		if(maze[row][col] == EXIT){
			pathNumber++;
			//if so we print the directions which we have to take to exit the maze
			printPath();
		}
		else{// backtracking algorithm
			// The current cell is free. Mark it as visited
			maze[row][col] = VISITED;
			findPath(row,col-1,'L');//moving left
			findPath(row,col+1,'R');//moving right
		    findPath(row+1,col,'D');//moving down
			findPath(row-1,col,'U');//moving up
			// Mark back the current cell as free
			maze[row][col] = UNVISITED;
		}
		//remove the cuurent cell from the path
		path.pop_back();
	}

	void printPath(){
		copy( ++path.begin(),path.end(),ostream_iterator<char>(cout) );
		cout<<endl;
	}
public:

	PathsBetweenCellsInMatrix(vector<string> &maze_):maze(maze_){
		//extracts the coordinates of the starting point
		bool breakFlag = true;
		for (int i = 0; breakFlag && i < maze_.size(); i++)
		{
			for (int j = 0; j < maze_[0].size(); j++)
			{
				if(maze[i][j] == START){
                   startX = i;
				   startY = j;
				   breakFlag = false;
				   break;
				}
			}
		}
	}

	void printAllPaths(){
		pathNumber = 0;
		findPath(startX,startY,'S');
		cout<<"Total paths found: "<<pathNumber<<endl;
	}
};

int main(){


    stringstream ss;
    ss.str ("5\ns     \n ** * \n ** * \n *e   \n   *  \n");
	int X;
	ss>>X>>ws;
	vector<string> maze(X);
	for(int i = 0; i < X; i++){
       getline(ss,maze[i]);
	}
	PathsBetweenCellsInMatrix pbcim(maze);
	pbcim.printAllPaths();

	return 0;
}