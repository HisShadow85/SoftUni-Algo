#include<iostream>
#include<vector>
#include<algorithm> // for copy
#include<iterator> // for ostream_iterator

using namespace std;

//without OOP
void nestedLoopsToRecursion(int n,int depth = 0){
		 //initialize at the first call
		 static vector<int> combinations;
		 if(depth == 0) combinations.resize(n);
		 if(n<0 || depth <0 || depth > combinations.size() || depth > n) return;

		 //the real loop simulation
		 if(depth == n){//if we have reached the end of the current combination we print the content
            copy(combinations.begin(), combinations.end(), ostream_iterator<int>(cout, " "));
			cout<<endl;
		 }
		 else{

			 for (int i = 1; i <= n; i++)
			 {
				 combinations[depth]=i;
				 nestedLoopsToRecursion(n,depth+1);
			 }

		 }

	}


class NestedLoopsToRecursion{

	vector<int> combinations;
	int numbers, depth;

	void nestedLoopsToRecursion(){

		 depth++;

		 if(depth == numbers){//if we have reached the end of the current combination we print the content
              copy(combinations.begin(), combinations.end(), ostream_iterator<int>(cout, " "));
			  cout<<endl;
		 }
		 else{

		    for (int i = 1; i <= numbers; i++)
			{
			  combinations[depth]=i;
			  nestedLoopsToRecursion();
			}

		 }

        depth--;
	}

public:

	NestedLoopsToRecursion(int n):numbers(n){
		combinations.resize(numbers);
	}

	void printAllCombinations(){
		 depth=-1;
		 nestedLoopsToRecursion();
	}
	

};


int main(){

	int loopNumber;
	cin>>loopNumber;
	NestedLoopsToRecursion nl(loopNumber);
	//nestedLoopsToRecursion(loopNumber);
	nl.printAllCombinations();
	return 0;
}

