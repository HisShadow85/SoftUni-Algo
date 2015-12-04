#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>

using namespace std;

class ChangeLimitedCoins{
public:
	typedef unsigned int sum;

	static int changeLimitedCoinsconst(vector<int> &coints, int wantedSum){
		sort(coints.begin(),coints.end());    
		vector<vector<sum> > workMatrix(coints.size()+1,vector<sum>(wantedSum+1,0));
		//fills the first column with 1 
		for (int row = 0; row < (int)workMatrix.size(); row++)
		{
			workMatrix[row][0] = 1;
		}
	    
		sum prevCoin = coints[0]; //represent the previus used coin
		//iterate trought each coin represented by row -1
		for (int  row = 1;  row < workMatrix.size(); row++)
		{
			sum currCoin = coints[row -1];
			//for given coin interate trought all the sum and check all posible 
			//combination for making the sum with this coin and the previus ones
			for (sum currSum = 1; currSum < (sum)workMatrix[0].size(); currSum++)
			{
				//we take the value of the upper cell which represents the all 
				//possible ways the current sum is made from the previus set of coins
				sum upperCell = workMatrix[row-1][currSum];
				//if the coin value is biger than the current sum it is obvius it 
				//cant be considering in the sum making
				if(currCoin > currSum){
					//so we just copy the possible ways from the upper cell
					workMatrix[row][currSum] = upperCell;
				}
				else{
					sum shiftedCell = workMatrix[row-1][currSum - currCoin];
					//if we are not use the same value as the previus coin has
					if(currCoin != prevCoin){
						workMatrix[row][currSum] = shiftedCell + upperCell;
					}
					else{//if we use the same coin value
                        workMatrix[row][currSum] = upperCell > shiftedCell ? upperCell : shiftedCell;
					}
				}
			}
			prevCoin = currCoin;
		}
		return workMatrix[workMatrix.size()-1][wantedSum];
	}
};

int main(){

	stringstream ss("4\n6 7\n1 2 2 3 3 4 6\n5 4\n1 2 2 5\n13 6\n1 2 2 5 5 10\n100 7\n50 20 20 10 20 20 20");
	
	int loops,wantedSum, N;
	ss>>loops;
	for (int i = 0; i < loops; i++)
	{
		ss>>wantedSum>>N;
		cout<<"Exaple "<<i+1<<":\nSum = "<<wantedSum<<"\nCoins = {";
		vector<int> coins(N);
		for (int i = 0; i < N; i++)
		{
	      ss>>coins[i];
		  cout<<coins[i]<<',';
		}
		cout<<"}\nCombinations = ";
		cout<<ChangeLimitedCoins::changeLimitedCoinsconst(coins,wantedSum);
		cout<<"\n-----------------------------------------------------------\n";
	}

	while (true)
	{
		try{
        cout<<"Enter the wanted sum:";
		cin>>wantedSum;
		cout<<"Enter the number of coins which will be used:";
		cin>>N;
		vector<int> coins(N);
		for (int i = 0; i < N; i++)
		{
			 cout<<"Coin"<<i+1<<':';
	         cin>>coins[i];
		}
		cout<<ChangeLimitedCoins::changeLimitedCoinsconst(coins,wantedSum);
		cout<<"\n-----------------------------------------------------------\n";
		}catch(...){
			cout<<"Invalid Input!\n";
			continue;
		}
	}
	return 0;
};