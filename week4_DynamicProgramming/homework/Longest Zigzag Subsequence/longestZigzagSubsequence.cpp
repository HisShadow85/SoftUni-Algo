#include<iostream>
#include<vector>
#include<sstream>
using namespace std;

class ZigzagSubsequence{
public:
	 typedef unsigned short length;
	 //the solution follows the principles of the longest increasing substring
	static vector<int> longestZigzagSubsequence(vector<int> &input){
		//BIG element is such that is bigger than the one befor it
		//SMALL element is such that is bigger than the one befor it

		//indicates the largest found sequence ending in the bigger consecutive element  
		length longestAsBig = 0;
		//indicates the largest found sequence ending in the smaller consecutive element  
		length longestAsSmall = 0;
		//contains the lenght of the biggest sequence ended in a certain bigger consecutive element 
		vector<length> listAsBig(input.size(),1);
		//contains the the path for the certain sequence.Indices represent the number of the element 
		//in the input and the cell value the  previous to that number in the sequence
		vector<length> pathAsBig(input.size());
		//contains the lenght of the biggest sequence ended in a certain smaller consecutive element 
		vector<length> listAsSmall(input.size(),1);
		//contains the the path for the certain sequence.Indices represent the number of the element 
		//in the input and the cell value the  previous to that number in the sequence
		vector<length> pathAsSmall(input.size());
		//initially every element is coming from himself in the sequence
		for (length i = 0; i < (length)input.size(); i++)
		{
			pathAsSmall[i] = pathAsBig[i] = i;
		}
		//starts from the second element of the input sequence
		for (length i = 1; i < (length)input.size(); i++)
		{
			//check how long sequence makes with each item before himself
			for (int j = 0; j < i; j++)
			{
				//if the item before "i" is smaller
				if(input[j] < input[i]){ // we are looking to make sequence ending with BIG element
					if(listAsSmall[j] + 1 > listAsBig[i]){
                       listAsBig[i] = listAsSmall[j] + 1;
					   pathAsBig[i] = j;
					   if(listAsBig[i] > listAsBig[longestAsBig]){
						   longestAsBig = i;
					   }
					}
				}//if the item before "i" is bigger
				else if(input[j] > input[i]){
					// we are looking to make sequence ending with SMALL element
					if(listAsBig[j] + 1 > listAsSmall[i]){
                       listAsSmall[i] = listAsBig[j] + 1;
					   pathAsSmall[i] = j;
					   if(listAsSmall[i] > listAsSmall[longestAsSmall]) {
						   longestAsSmall = i;
					   }
					}
				}
			}
		}
		vector<int> result;
		//extracting the sequence is done by jumping from the list of the BIG 
		//elements to one with the SMALL elements and vice versa

		//if the longest zigzag sequence is found ending at BIG element
		if(listAsBig[longestAsBig] > listAsSmall[longestAsSmall]){
			do{
				//puts the last element into the result array
				result.push_back(input[longestAsBig]);
				//takes the next elemet from the opposite path array
				longestAsSmall = pathAsBig[longestAsBig];
				//if the elemets are the same than that is the end of the sequence
				if(longestAsSmall == longestAsBig) break;
				//puts the next number into the result array
				result.push_back(input[longestAsSmall]);
				//takes the next elemet from the opposite path array
				longestAsBig = pathAsSmall[longestAsSmall];
			}while ((longestAsBig != longestAsSmall));		
		}
		else{//if the longest zigzag sequence is found ending at SMALL element
			do{ //same as the case above
				result.push_back(input[longestAsSmall]);
				longestAsBig = pathAsSmall[longestAsSmall];
				if(longestAsBig == longestAsSmall) break;
				result.push_back(input[longestAsBig]);
				longestAsSmall = pathAsBig[longestAsBig];
			}while ((longestAsSmall != longestAsBig));	
		}
		//reversing the result
		for (int i = 0,j = result.size()-1; i < j; i++, j--)
		{
			swap(result[i],result[j]);
		}

		return result;
	}
};

int main(){

	stringstream ss("4\n14\n8 3 5 7 0 8 9 10 20 20 20 12 19 11\n3\n1 2 3\n3\n1 3 2\n12\n24 5 31 3 3 342 51 114 52 55 56 58");

    int N,loops;	
	ss>>loops;
	for (int i = 1; i <= loops; i++)
	{
		cout<<"Example "<<i<<":\nSequence: ";
		ss>>N;
		vector<int> sequence(N);
		for (int i = 0; i < N; i++)
		{
			   ss>>sequence[i];
			   cout<<sequence[i]<<',';
		}
		cout<<endl;
		sequence = ZigzagSubsequence::longestZigzagSubsequence(sequence);
		cout<<"Longest Zigzag Subsequence: ";
		for (int i = 0; i < sequence.size(); i++)
		{
			cout<<sequence[i]<<',';
		}
		cout<<"\n---------------------------------------------------------------\n";
	}

	while (true)
	{
		cout<<"Enter your data!\nEnter the length of the sequence:";
		try{
		cin>>N;
		vector<int> sequence(N);
		for (int i = 0; i < N; i++)
		{      
			   cout<<"Item "<<i+1<<": ";
			   cin>>sequence[i];
		}
		sequence = ZigzagSubsequence::longestZigzagSubsequence(sequence);
		cout<<"Longest Zigzag Subsequence: ";
		for (int i = 0; i < sequence.size(); i++)
		{
			cout<<sequence[i]<<',';
		}
		cout<<"\n---------------------------------------------------------------\n";
		}catch(...){
			cout<<"Invalid input!\n";
			continue;
		}
	}

	return 0;
}