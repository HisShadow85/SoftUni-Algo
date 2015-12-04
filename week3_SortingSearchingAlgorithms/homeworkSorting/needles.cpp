#include<iostream>
#include<vector>
#include<sstream>

using namespace std;

class Needless{
	  vector<int> &haystack;
	  vector<int> indices;

public:

	Needless(vector<int> &haystack):haystack(haystack){
		int i = 0;
		while(i < (int)haystack.size() && haystack[i] == 0){ i++;}
		if(i < (int)haystack.size()){
			indices.push_back(i++);
			for (; i < (int)haystack.size(); i++)
			{   
				if(haystack[i] != 0 && haystack[i] != indices.back() ){
				   indices.push_back(i);
				}
			}
		}
	}

	int findPlace(int key){
		if(indices.size() == 0) return 0;
		int 
			low = 0,
			hight = indices.size()-1,
		    mid;
		if(key <= haystack[indices[low]]){
			return indices[low];
		}
	    if(key > haystack[indices[hight]]){
			int result = indices[hight];
			while (result < (int)haystack.size() && haystack[result] > 0) result++;
		    return result;
		}

		while (low < hight)
		{
			mid = low + (hight - low)/2;
			if( key > haystack[indices[mid]]){
				low = mid + 1;
			}else{
				hight = mid;
			}
		}
		if(haystack[indices[low-1]+1] >= key){
			 return indices[low];
		}
		else return indices[low-1] +1;
		
	}
};

int main(){
	//stringstream input("23 9\n3 5 11 0 0 0 12 12 0 0 0 12 12 70 71 0 90 123 140 150 166 190 0\n5 13 90 1 70 75 7 188 12");
	stringstream input("11 4\n2 0 0 0 0 0 0 0 0 0 3\n4 3 2 1");
	int n,k;
	ios_base::sync_with_stdio(false);
	input>>n>>k;
	vector<int> haystack(n);
	for (int i = 0; i < n; i++)
	{
		input>>haystack[i];
	}
	Needless need(haystack);
	for (int i = 0; i < k-1; i++)
	{
		input>>n;
		cout<<need.findPlace(n)<<' ';
	}
	input>>n;
	cout<<need.findPlace(n)<<endl;
	return 0;
}
