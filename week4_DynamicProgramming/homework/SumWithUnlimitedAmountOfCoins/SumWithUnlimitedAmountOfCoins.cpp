#include<iostream>
#include<vector>
#include<sstream>

using namespace std;

class Change{

public:
	typedef unsigned int sum;

	static int change(const vector<int> &coints, int wantedSum){
		if(wantedSum < 0 || coints.empty()) return 0;
        /*indices reppresent all avalible sums including the maxSum
		cell values are the posible ways to be build the coresponding sum*/
		vector<sum> sums(wantedSum+1,0);
		//the zero sum can be achieved only by doing one thing - precisely nothing
		sums[0]++;

		for (unsigned i = 0; i < coints.size(); i++)
		{
			int cuurCoin = coints[i];
			for (sum j = 0; j < (sum)sums.size(); j++)
			{
				sum currSum = j+cuurCoin;
				if(currSum < (sum)sums.size()){
					sums[currSum]+=sums[j];
				}
			}
		}
		return sums[wantedSum];
	}
};

int main(){
	
	stringstream ss("4\n6 5\n1 2 3 4 6\n5 3\n1 2 5\n13 4\n1 2 5 10\n100 7\n1 2 5 10 20 50 100");
	
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
		cout<<Change::change(coins,wantedSum);
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
			 cout<<"Coin type "<<i+1<<':';
	         cin>>coins[i];
		}
		cout<<Change::change(coins,wantedSum);
		cout<<"\n-----------------------------------------------------------\n";
		}catch(...){
			cout<<"Invalid Input!\n";
			continue;
		}
	}
	
	return 0;
}