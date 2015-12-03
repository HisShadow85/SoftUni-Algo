#include<iostream>
#include<vector>

using namespace std;

class EightQueens{
	  
	  unsigned short size;
	  vector<vector<bool> > chessboard;
	  vector<bool> 
		  attackedRows, 
		  attackedLeftDiagonals , /* \ */
		  attackedRightdiagonals; /* / */
public:
	  EightQueens(int size_):size(size_){
		  chessboard.resize(size,vector<bool>(size,false));
		  attackedRows.resize(size,false);
		  attackedLeftDiagonals.resize(size*2-1,false);
		  attackedRightdiagonals.resize(size*2-1,false);
	  }

	  void markAttackedPositions(unsigned short col, unsigned short row){

		   attackedRows[row] = true;
		   attackedLeftDiagonals[row-col+this->size-1] = true;
		   attackedRightdiagonals[row+col] = true;
		   chessboard[row][col] = true;
	  }

	  void unmarkAttackedPositions(unsigned short col, unsigned short row){

		   attackedRows[row] = false;
		   attackedLeftDiagonals[row-col+this->size-1] = false;
		   attackedRightdiagonals[row+col] = false;
		   chessboard[row][col] = false;
	  }

	  bool canPlaceQueen(unsigned short col, unsigned short row){
		
		  return ! (attackedRows[row] || attackedLeftDiagonals[row-col+size-1] 
		                              || attackedRightdiagonals[row+col] );
	  }

	  void printSolution(){
		  static unsigned int solutions = 1;
		  cout<<"solution No:"<<solutions<<endl;
		  for (int row = 0; row < size; row++)
		  {
			  for (int col = 0; col < size; col++)
			  {
				  cout<<(chessboard[row][col]?"* ":"- ");
			  }
			  cout<<endl;
		  }
		  cout<<endl;
		  solutions++;
	  }

	  void putQueen(unsigned short col){

		  if(col == size){
             printSolution();
		  }
		  else{
             
			  for (unsigned short row = 0; row < size; row++)
			  {
				  if(canPlaceQueen(col,row)){
                     markAttackedPositions(col,row);
					 putQueen(col+1);
					 unmarkAttackedPositions(col,row);
				  }
			  }

		  }

	  }
};

int main(){

	EightQueens eq(8);
	eq.putQueen(0);

	return 0;
}