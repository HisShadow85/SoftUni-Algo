#include<iostream>
#include<vector>
#include<sstream>
using namespace std;

class ConnectingCables{

		/* Finds longest strictly increasing subsequence. O(n log k) algorithm. */
		static void find_lis(vector<int> &input, vector<int> &ls)
		{
			
			vector<int> path(input.size());
			int min, max;
 
			if (input.empty()) return;
 
			ls.push_back(0);
 
			for (size_t i = 1; i < input.size(); i++) 
			{
						
				if (input[ls.back()] < input[i]) 
				{
					path[i] = ls.back();				
					ls.push_back(i); 
					continue; 
				}
				 
				for (min = 0, max = ls.size()-1; min < max;) 
				{
					int mid = (min + max) / 2;
					if (input[ls[mid]] < input[i]){
						min=mid+1;
					}
					else{
						max=mid;
					}
				}
 
				if (input[i] < input[ls[min]]) 
				{
					if (min > 0){
						path[i] = ls[min-1];
					}
					ls[min] = i;
				}	
			}

			for (min = ls.size(), max = ls.back(); min--; max = path[max]){
				ls[min] = max;
			}
		}

		static void bubleSort(vector<int> &arr){
				int j = arr.size()-1;
				bool isSorted = false;
				while (!isSorted){
					isSorted = true;
					for (int i = 0; i < j; i++){
						if (arr[i] > arr[i + 1]){
							swap(arr[i], arr[i + 1]);
							isSorted = false;
						}
					}
					j--;
				}
		}
public:

	static vector<int> connectingCables(vector<int> &side1, vector<int> &side2){
		    //firs side must be sorted
		    bubleSort(side1);//this is not needed if the side1 is already sorted
			//To solve the taks we just have to get the longest increasing subsequence from the second side
			//Thus we know that cables are straight and not overlaped
			vector<int> indicesOfSide2;//here we will sore the indices of the elemets that make the LIS
			//the fastest algorithm for finding the longest increasing subsequence.
			find_lis(side2,indicesOfSide2);

			vector<int> result;//extract the elements
			for (int i = 0; i < indicesOfSide2.size(); i++)
			{
				result.push_back(side2[indicesOfSide2[i]]);
			}
			return result;
	}
   
   static void showConnectingCables(vector<int> &side1, vector<int> &side2){
	        vector<int> result = connectingCables(side1,side2);
	        cout<<"Maximum pairs connected: "<<result.size()<<"\nConnected pairs: ";
			for (int i = 0; i < result.size(); i++)
			{
				cout<<result[i]<<' ';
			}
			cout<<endl;
   }
};

int main(){
	 
	stringstream ss("3 9\n1 2 3 4 5 6 7 8 9\n2 5 3 8 7 4 6 9 1\n4\n1 2 3 4\n4 3 2 1\n3\n1 2 3\n1 2 3");
	int loops;
	ss>>loops;
	for (int i = 0; i < loops; i++)
	{
		int N;
		ss>>N;
		vector<int> side1(N);
		for (int i = 0; i < N; i++)
		{
			ss>>side1[i];
		}
		vector<int> side2(N);
		for (int i = 0; i < N; i++)
		{
			ss>>side2[i];
		}
		ConnectingCables::showConnectingCables(side1,side2);
		cout<<"------------------------------------------------\n";
	}
	cout<<"Enter your own input!\n";
	while (true)
	{
		int N;
		cout<<"Enter the number of poins to be connected:";
		cin>>N;
		vector<int> side1(N);
		cout<<"SIDE 1:\n";
		for (int i = 0; i < N; i++)
		{   
			cout<<"Point 1:";
			cin>>side1[i];
		}
		cout<<"SIDE 2:\n";
		vector<int> side2(N);
		for (int i = 0; i < N; i++)
		{
			cout<<"Point 1:";
			cin>>side2[i];
		}
		ConnectingCables::showConnectingCables(side1,side2);
		cout<<"------------------------------------------------\n";
	}
	return 0;
}


