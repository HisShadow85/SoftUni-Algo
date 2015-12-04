#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class PermutationsWithRepetition{

	static void PermuteRep(vector<int> &arr, int start, int end){
		static int permutations = 0;
		permutations++;
		print(arr);		
		for (int left = end - 1; left >= start; left--)
		{
			for (int right = left + 1; right <= end; right++)
				if (arr[left] != arr[right])
				{
					swap(arr[left],arr[right]);
					PermuteRep(arr, left + 1, end);
				}
			// Undo all modifications done by
			// recursive calls and swapping
			int firstElement = arr[left];
			for (int i = left; i <= end - 1; i++)
					arr[i] = arr[i + 1];
			arr[end] = firstElement;
		}
		if(start == 0){
			cout<<"Total permutations: "<<permutations<<endl;
		}
	}

	static void print(vector<int> &ps){
			int i;
			cout<<"{ ";
			for (i = 0; i < (int)ps.size()-1; i++){
				cout<<ps[i]<<", ";
			}
			cout<<ps[i]<<" }\n";
	}

public:
	static void permutationsWithRepetition(vector<int> &arr){
		   std::sort(arr.begin(),arr.end());
		   PermuteRep(arr,0,arr.size()-1);
	}
};

int main(){
	int n;
	cout<<"Enter the numbers to be permuted: ";
	cin>>n;
	cout<<"Enter repetitive elements in value!\n";
	vector<int> input(n);
	for (int i = 0; i < n; i++)
	{
		cout<<"Element "<<i+1<<": ";
		cin>>input[i];
	}
	PermutationsWithRepetition::permutationsWithRepetition(input);
	return 0;
}
