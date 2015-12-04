#include<iostream>
#include<vector>
#include<sstream>
#include<map>
using namespace std;

class DividingPresents{
	  
	static void dividingPresents(vector<int> &presents,vector<int> &result){

		int maxPrezentsValue = 0;//the total presents value
		int maxFindPresentSum = 0;//this will represent the most closest sum to the wanted one
		int maxPresentsSum = 0;//this will represent the bound of the wanted sum
		//calculates the whole sum of all presents
		for (int i = 0; i < presents.size(); i++)
		{
			maxPrezentsValue+=presents[i];
		}
		maxPresentsSum = maxPrezentsValue>>1;//half sum of all presents
		map<int,int> allPossibleSums;//here we will store the possible sums
		allPossibleSums[0] = 0;//first sum is zero to load the possible sum of the singles element
		for (int i = 0; i < presents.size() && maxFindPresentSum < maxPresentsSum; i++)
		{
			map<int,int> allNewPossibleSums;//create a map which will contains the new sums
			//iterates through all discovered possible sums
			for (map<int,int>::iterator it = allPossibleSums.begin() ; it != allPossibleSums.end(); it++)
			{
				//calculates the new possible sum
				int newSum = it->first + presents[i];
				if(newSum > maxPresentsSum) continue; //avoid sums larger than the wanted one (	maxPresentsSum )
				//if such sum does not exists
				if(allPossibleSums.find(newSum) == allPossibleSums.end())
				{
                   allNewPossibleSums[newSum] = it->first;//put it in the new map
				   if(newSum > maxFindPresentSum) maxFindPresentSum = newSum;//update the max sum that was found, if it needs
				   if(newSum == maxPresentsSum) break; // if we find the wanted sum we do not need to proceed any further
				}
			}
			//append the new found sums to the set of all found
			allPossibleSums.insert(allNewPossibleSums.begin(),allNewPossibleSums.end());

		}

		result.clear();//clear the result arrya if is not empty
		//push the difference between the two share amounts
		result.push_back(maxPrezentsValue - (maxFindPresentSum<<1) );
		//push the smaller share first
		result.push_back(maxFindPresentSum);
	    //push the bigger share first
		result.push_back(maxPrezentsValue-maxFindPresentSum);
		//get the presents which go to the smaller share
		while (maxFindPresentSum > 0)
		{
			//extracting the item of which the maxFindPresentSum is created
            int item = maxFindPresentSum - allPossibleSums[maxFindPresentSum];
			result.push_back(item);
			maxFindPresentSum-=item;
		}
	}


	static void printfSolution(vector<int> &solution){
		  cout<<"Difference: "<<solution[0]<<endl;
		  cout<<"Alan:"<<solution[1]<<" Bob:"<<solution[2]<<endl;
		  cout<<"Alan takes: ";
		  for (int i = 3; i < solution.size(); i++)
		  {
			  cout<<solution[i]<<' ';
		  }
		  cout<<"\nBob takes the rest.\n";
	}

public:

	static void dividePresents(vector<int> &presents){
		  vector<int> solution;
		  dividingPresents(presents,solution);
		  printfSolution(solution);
	}
};

int main(){

	stringstream ss("4\n10\n3 2 3 2 2 77 89 23 90 11\n6\n2 2 4 4 1 1\n12\n7 17 45 91 11 32 102 33 6 3 6 8\n10\n1 1 1 1 1 1 1 1 1 22");
	
	int N,loops;
	ss>>loops;
	for (int i = 1; i <= loops; i++)
	{
		cout<<"Example "<<i<<":\nPresents: ";
		ss>>N;
		vector<int> presents(N);
		for (int i = 0; i < N; i++)
		{
			   ss>>presents[i];
			   cout<<presents[i]<<',';
		}
		cout<<endl;
		DividingPresents::dividePresents(presents);
		cout<<"---------------------------------------------------------------\n";
	}
	while (true)
	{   
		try{
        cout<<"Enter the number of presents: ";
		cin>>N;
		vector<int> presents(N);
		for (int i = 0; i < N; i++)
		{      
			   cout<<"Present "<<i+1<<": ";
			   cin>>presents[i];
		}
		DividingPresents::dividePresents(presents);
		cout<<"---------------------------------------------------------------\n";
		}catch(...){
			cout<<"INVALID INPUT!\n";
			continue;
		}
	}
	return 0;
}

