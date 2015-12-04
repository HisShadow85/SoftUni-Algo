#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>

using namespace std;

//without OOP
void combinationsWithRepetition(unsigned begin, unsigned end, int depth){
	
	 //initialize at the first call
	 static vector<int> combinations;
	 if(depth > combinations.size()) combinations.resize(depth);

	 depth--;

	 if(depth < 0 ) {
         copy(combinations.begin(),combinations.end(), ostream_iterator<int>(cout," "));
		 cout<<endl;
		
	 }
	 else{
		 for (int i =begin; i <= end; i++)
		 {
			  combinations[depth]=i;
			  combinationsWithRepetition(i,end,depth);
		 }
		
	 }
	 
}

class CombinationsWithRepetition{

	vector<int> combinations;
	unsigned begin, end;
	int depth;

	void combinationsWithRepetition(unsigned begin_){

	 depth++;

	 if(depth == combinations.size() ) {
         copy(combinations.begin(),combinations.end(), ostream_iterator<int>(cout," "));
		 cout<<endl;
	 }
	 else{
		 for (int i =begin_; i <= end; i++)
		 {
			  combinations[depth]=i;
			  combinationsWithRepetition(i);
		 }
		
	 }
	  depth--;
}

public:

	CombinationsWithRepetition(unsigned begin_, unsigned end_, int depth):begin(begin_),end(end_){
		combinations.resize(depth);
	}

	void printAllCombinations(){
		 depth=-1;
		 combinationsWithRepetition(begin);
	}

};

int main(){

	int n,k;
	cin>>n>>k;
	CombinationsWithRepetition cr(1,n,k);
	//combinationsWithRepetition(1, n,k);
	cr.printAllCombinations();
   return 0;
};