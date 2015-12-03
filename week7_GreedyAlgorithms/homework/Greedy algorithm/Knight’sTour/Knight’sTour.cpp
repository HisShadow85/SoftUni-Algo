#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

class Knight’sTour{

	static const int NC = -1; //not calculated 

	static int getAvaliableMoves(int x, int y,vector<vector<int> > &tour,vector<vector<int> > &avaliableMoves){
		if(avaliableMoves[x][y] == NC){
			avaliableMoves[x][y] = 0;
			if(isSave(x+1,y-2,tour)){ avaliableMoves[x][y]++;}
			if(isSave(x+1,y+2,tour)){ avaliableMoves[x][y]++;}
			if(isSave(x-1,y-2,tour)){ avaliableMoves[x][y]++;}
			if(isSave(x-1,y+2,tour)){ avaliableMoves[x][y]++;}
			if(isSave(x+2,y-1,tour)){ avaliableMoves[x][y]++;}
			if(isSave(x+2,y+1,tour)){ avaliableMoves[x][y]++;}
			if(isSave(x-2,y-1,tour)){ avaliableMoves[x][y]++;}
			if(isSave(x-2,y+1,tour)){ avaliableMoves[x][y]++;}
		}else{
			avaliableMoves[x][y]--;
		}
		return avaliableMoves[x][y];
	}

	static bool isSave(int x,int y,vector<vector<int> > &tour){
		if(	x >= 0 && x < (int)tour.size() && y >= 0 && y < (int)tour.size() &&  tour[x][y] < 1){
			return true;
		}
		else{
			return false;
		}
	}

	static void getNexPosition(int &x,int &y,vector<vector<int> > &tour,vector<vector<int> > &avaliableMoves){
		int smaller = INT_MAX;
		int currPositionMoves;
		int xNext = x;
		int yNext = y;
		for (int i = x-1; i < x + 2; i+=2)
		{
			for (int j = y-2;  j < y + 3; j+=4)
			{
				if(isSave(i,j,tour)){
                   currPositionMoves = getAvaliableMoves(i,j,tour,avaliableMoves);
				   if(currPositionMoves < smaller) { 
					   smaller = currPositionMoves; 
					   xNext = i; yNext = j ; 
				   }
				}
			}
		}

		for (int i = x-2; i < x + 3; i+=4)
		{
			for (int j = y-1;  j < y + 2; j+=2)
			{
				if(isSave(i,j,tour)){
                   currPositionMoves = getAvaliableMoves(i,j,tour,avaliableMoves);
				   if(currPositionMoves < smaller) { 
					   smaller = currPositionMoves; 
					   xNext = i; yNext = j ; 
				   }
				}
			}
		}

		x=xNext;
		y=yNext;		
	}

	static int getDigitsNum(int num){
		int digits = 1;
		while (num/=10)
		{
			digits++;
		}
		return digits;
	}

	static void printTour(vector<vector<int> > &tour){
		int maxDigits = getDigitsNum(tour.size()*tour.size());
		cout<<'-';
		for (unsigned int i = 0; i < tour.size(); i++)
		{
			for (int j = 0; j < 3+maxDigits; j++)
			{
				cout<<'-';
			}
		}
		cout<<endl;
		for (int i = 0; i < (int)tour.size(); i++)
		{
			cout<<'|';
			for (int j = 0;  j < (int)tour[i].size();  j++)
			{
				cout<<' ';
				for (int k = maxDigits - getDigitsNum(tour[i][j]); k > 0 ; k--)
				{
					cout<<' ';
				}
				cout<<tour[i][j]<<" |";
			}
			cout<<"\n-";
			for (unsigned int z = 0; z < tour.size(); z++)
		    {
				for (int p = 0; p < 3+maxDigits; p++)
				{
					cout<<'-';
				}
		    }
		    cout<<endl;
		}
	}

public:
	static void makeKnightTour(int tableSize){
		if(tableSize < 5) { return; }
		int maxMoves = tableSize*tableSize;

		vector<vector<int> > tour(tableSize,vector<int>(tableSize,0));
		//memoization of the avaliable moves for each position -> performance gaining
	    vector<vector<int> > avaliableMoves(tableSize,vector<int>(tableSize,NC));
		int x = 0, y = 0;
		for (int i = 1; i <= maxMoves; i++)
		{
			tour[x][y] = i;
			getNexPosition(x,y,tour,avaliableMoves);
		}

		printTour(tour);
	}

};

int main(){
	cout<<"Knight’s Tour solution\n";
	int size;
	do{
		cout<<"Enter a size of the board or zero to exit : ";
		cin>>size;
		if(size < 5) { cout<<"Input out of range.Please enter value from 5 and above\n"; continue;}
		Knight’sTour::makeKnightTour(size);
	}while(size != 0);
	

	return 0;
}

