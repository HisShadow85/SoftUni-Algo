#include<iostream>
#include<vector>

using namespace std;

class Permutations{

	static void print(vector<int> &set){
		int i;
		for (i = 0; i < (int)set.size()-1; i++)
		{
			cout<<set[i]<<", ";
		}
		cout<<set[i]<<endl;
	}

public:
	static void permutations(vector<int> &list){
		        int permutations = 1;
		        //An integer array iterations[] of size list.size()+1 used to control the iteration
                vector<int> iterations(list.size()+1);
				//initialize "iterations" array with values from 0 to list.size() included
				for (int i = 0; i < iterations.size(); i++)
				{
					iterations[i] = i;
				}

				int 
					index = 1, //initialize index variable to 1
					j = 0;/*represents the index of the element which is to be 
					       swapped with the one at the position refered by the v */

				print(list);//the initial layout is the first permutation
				while ( index < list.size() ) //loops until it reaches the index of the last element
				{
						iterations[index]--;
						//if index is odd, then let j = p[i] otherwise let j = 0
						j = index & 1 ? iterations[index] : 0 ;
						swap(list[j],list[index]);
						permutations++;
						print(list);
						index = 1;	//reset index to 1		
						while (iterations[index] == 0)
						{
								iterations[index] = index;
								index++;
						}
				}
				cout<<"Total permutations: "<<permutations<<endl;
	}
};

int main(){
	int n;
	cout<<"Enter the numbers to be permuted: ";
	cin>>n;
	vector<int> input(n);
	for (int i = 0; i < n; i++)
	{
		cout<<"Element "<<i+1<<": ";
		cin>>input[i];
	}
	Permutations::permutations(input);
	return 0;
}