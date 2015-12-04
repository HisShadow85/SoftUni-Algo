#include<iostream>
#include<vector>

using namespace std;

template<class T>
class CombinationsIteratively{

public:

	static void combinationsIteratively(int classDegree,  vector<T> &set){
		int combinationFound = 0;
		/*Here we are going to store the current combination
		 Each cell of the combination array will represent a 
		 certain index from the given set of available elements */
	    vector<int> combination(classDegree);
		//the initial layout of the first combination.size() elements from the set is the first permutation
		for (int i = 0; i < classDegree; i++)
		{
			combination[i]=i;
		}
		/*we are going to proceed from back to front so the starting 
		  index is the last one of the combinations array*/
		int index = combination.size()-1;

		while (true)
		{
			combinationFound++;
			print(combination,set);

			//putting the index of the next available element into the last position
			combination[index]++;
			//if the are no such element (we reached the end of the initial set)
			if(combination[index] >= (int)set.size()){
				index--;//we reverse one position backward
				
				     /*only for clarity*/
					 /*cells which have to be filled with indices of 
					  the available elements that are free to use*/
				    int	cellToFill = combination.size()-index,
					//the number of remaining free to use elements
				    freeElements = set.size()-combination[index]-1;

				/*we are going to move backward until the free element 
				  are enough to fill the required cells*/
				while (cellToFill - freeElements > 0)
				{
					index--;
					/*if we go before the beginning of of the combination's array,
					  there are no more possible combinations*/
					if(index < 0){
						cout<<"Total combinations: "<<combinationFound<<endl;
						return;
					}
					cellToFill = combination.size()-index;
					freeElements = set.size()-combination[index]-1;
				}
				//putting the index of the next available element into the current position
				combination[index]++;
				//until we reach the last position
				while (index < (int)combination.size() - 1)
				{
					index++;//proceeds to the next position
					/*set the current position with the next 
					  available index from the initial set*/
					combination[index] = combination[index-1] + 1;
				}
			}
		}
		
	}

private:

	static void print(vector<int> &combination,vector<T> &set){
		for (int i = 0; i < (int)combination.size(); i++)
		{
			cout<<set[combination[i]]<<' ';
		}
		cout<<endl;
	}
};

int main(){
	int k,n;
	cout<<"Enter the length of the wanted combinations: ";
	cin>>k;
	cout<<"Enter the length of the inital set: ";
	cin>>n;
	vector<int> input(n);
	for (int i = 0; i < n; i++)
	{
		cout<<"Element "<<i+1<<": ";
		cin>>input[i];
	}
	CombinationsIteratively<int>::combinationsIteratively(k,input);
	return 0;
}