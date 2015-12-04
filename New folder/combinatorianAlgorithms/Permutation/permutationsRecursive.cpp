#include<iostream>
#include<vector>

using namespace std;

template<class C>
class Permutation{

	static void swap(C &first, C &second){
		if( first == second ){
			return;
		}
		first ^= second;
		second ^= first;
		first ^= second;
	}

	static void print(vector<C> &set){
		int i;
		for (i = 0; i < (int)set.size()-1; i++)
		{
			cout<<set[i]<<", ";
		}
		cout<<set[i]<<endl;
	}

public:

	
	static void printPermutations(vector<C> &set){

		 static int index =-1;
		 static int permutations = 0;
		 index++;
		 //if we have one element to permute or we reached the end of the array 
		 if(index >= (int)set.size()-1){
			 permutations++;
             print(set);
		 }
		 else{
			 for (int i = index; i < (int)set.size(); i++)
			 {   
				 //putting all of the elements one by one on the current position(index)
				 Permutation<C>::swap(set[index],set[i]);
				 //on every step we call the same method for the index + 1 part of the input array
				 printPermutations(set);
				 //restore the previous order of the input array
				 Permutation<C>::swap(set[i],set[index]);
			 }
		 }
		 index--;
		 if(index == -1){
			 cout<<"Total permutations: "<<permutations<<endl;
			 permutations = 0;
		 }
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
	Permutation<int>::printPermutations(input);
	return 0;
}