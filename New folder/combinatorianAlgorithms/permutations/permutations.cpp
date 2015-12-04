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
		for (int i = 0; i < (int)set.size(); i++)
		{
			cout<<set[i]<<' ';
		}
		cout<<endl;
	}

public:

	
	static void printPermutations(vector<C> &set){

		 static int index =-1;
		 index++;
		 if(index >= (int)set.size()){
             print(set);
		 }
		 else{
			 for (int i = index; i < (int)set.size(); i++)
			 {
				 Permutation<C>::swap(set[index],set[i]);
				 printPermutations(set);
				 Permutation<C>::swap(set[i],set[index]);
			 }
		 }
		 index--;
	}
};

static void print(vector<int> &set){
		for (int i = 0; i < (int)set.size(); i++)
		{
			cout<<set[i]<<' ';
		}
		cout<<endl;
	}

void printP(vector<int> p){
	 
}

void printState(int i, int j, vector<int> set, vector<int> p){
	 cout<<"( "<<i<<" < "<<set.size()<<" )\n";
	 cout<<"p["<<i<<"]-- p|";
	 for (int i = 0; i < p.size(); i++)
	 {
		 cout<<p[i]<<"|";
	 }
	 cout<<endl<<"j = "<<(i & 1 ? p[i] : 0);
	 if(i & 1) cout<<" i is odd => p[i]\n";
	 else cout<<" i is even =>0\n";
	 cout<<"swap(a["<<i<<"], a["<<j<<"])\n\t\t\ta| ";
	 print(set);
	 cout<<"i = 1\n";
}
void printWhile(){



}

void QuickPerm(vector<int> &list){
	 
	vector<int> p(list.size()+1);

	for (int i = 0; i < p.size(); i++)
	{
		p[i] = i;
	}

	int i = 1, j = 0;
	//print(list);
	while ( i < list.size() )
	{
			p[i]--;
			j = i & 1 ? p[i] : 0 ;
		    swap(list[j],list[i]);
			//print(list);
			printState(i,j,list,p);
			i = 1;			
			while (p[i] == 0)
			{
                    p[i] = i;
					i++;
			}
	}
}

/*
The Countdown QuickPerm Algorithm:

   let a[] represent an arbitrary list of objects to permute
   let N equal the length of a[]
   create an integer array p[] of size N+1 to control the iteration     
   initialize p[0] to 0, p[1] to 1, p[2] to 2, ..., p[N] to N
   initialize index variable i to 1
   while (i < N) do {
      decrement p[i] by 1
      if i is odd, then let j = p[i] otherwise let j = 0
      swap(a[j], a[i])
      let i = 1
      while (p[i] is equal to 0) do {
         let p[i] = i
         increment i by 1
      } // end while (p[i] is equal to 0)
   } // end while (i < N)
*/

int main(){
	int n = 4;
	vector<int> input;
	for (int i = 1; i <= n; i++)
	{
		input.push_back(i);
	}
	QuickPerm(input);
	//Permutation<int>::printPermutations(input);
    return 0;
}


void run(vector<int> &list){

	vector<int> p(list.size()+1);

	for (int i = 0; i < p.size(); i++)
	{
		p.push_back(i);
	}

	int i = 1, j = 0;

	while ( i < list.size() )
	{
		if( p[i] < i ){
			j = i & 1 ? p[i] : 0;
			swap(list[j],list[i]);
			p[i]++;
			i = 1;
		}
		else{ // (p[i] equals i)
			p[i] = 0;
			i++;
		}
	}



}
/*
   let a[] represent an arbitrary list of objects to permute
   let N equal the length of a[]
   create an integer array p[] of size N to control the iteration       
   initialize p[0] to 0, p[1] to 0, p[2] to 0, ..., and p[N-1] to 0
   initialize index variable i to 1
   while (i < N) do {
      if (p[i] < i) then {
         if i is odd, then let j = p[i] otherwise let j = 0
         swap(a[j], a[i])
         increment p[i] by 1
         let i = 1 (reset i to 1)
      } // end if
      else { // (p[i] equals i)
         let p[i] = 0 (reset p[i] to 0)
         increment i by 1
      } // end else (p[i] equals i)
   } // end while (i < N)
*/