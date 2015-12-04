#include<iostream>
#include<vector>
#include<string>
using namespace std;

class BinomialCoefficients{
public:
	  //Returns value of Binomial Coefficient C(n, k) Bottom Up solution
	  //Time complexity-> O(n*k)
      //Auxiliary space-> O(k) - !!!space efficient!!!
	  static unsigned binomialCoefficients(int n,int k){
		  if(k > n || n < 0 || k < 0) return 0;
		  //in case C(n,0) or C(n,n) for n>=0
		  else if(k == 0 || k == n) return 1;
		  //The working array at which we are going to save our results
		  //Represents always the last row of the pascal's triangle
		  vector<unsigned int> lastRowArray(k+1,0);//filled with zero values
		  lastRowArray[0] = 1;//init the starting position
		  n++;//incremented by one to save the equality comparison i <= n -> i < n
		  //in case 1 <= k <= n-1 for n>0
		  for (int i = 1; i < n; i++)
		  {   
			  /*Aways takes the minimum between the current i and k.
			   Thus if current row of the pascal's triangle has less cell than the 
			   value of coefficient "k" it will consider "i" for the most right edge 
			   of the triangle row ,if other way, it will consider k .*/
			  int backwardIt = i < k ? i : k;

			  for (; backwardIt > 0; backwardIt--)
			  {
				  //currRow[currCell] = prevRow[currCell] + prevRow[currCell -1];
				  lastRowArray[backwardIt]+=lastRowArray[backwardIt - 1];
			  }
		  }

		  return lastRowArray[k];
	  }
};

int main(){
	int n, k;
    
	while (true)
	{
		try{
		  string input;
		  cout<<"n = ";
		  cin>>input;
		  n = stoi(input);
		  cout<<"k = ";
		  cin>>input;
		  k = stoi(input);
		  cout<<"Binomial Coefficient is "<<BinomialCoefficients::binomialCoefficients(n,k)<<endl;

		}catch(...){
		  cout<<"Invalid Input!\n";
		  continue;
		}
	}
	
return 0;
}
