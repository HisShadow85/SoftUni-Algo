#include<iostream>
#include<vector>

using namespace std;



class CombinationWithoutRepetition{
public:

	static void  combinationWithoutRepetition(int classDegree,vector<int> &set){
		        static unsigned index = -1;
				static unsigned firstNonUsed;
				static vector<int> variations;
				index++;
				if(index == 0){
					variations.clear();
					variations.resize(classDegree);
					firstNonUsed = 0;
				}

				if(index == variations.size()){
					for (int i = 0; i < variations.size(); i++)
					{
						cout<<variations[i]<<' ';
					}
					cout<<endl;
				}else{
					for (int i = firstNonUsed; i < set.size(); i++)
					{
						variations[index] = set[i];
						firstNonUsed = i+1;
						combinationWithoutRepetition(classDegree,set);
					}
				}
				index--;
	}
};


int main(){
	vector<int> set;
	int k,n;
	cin>>k>>n;
	for (int i = 1; i <= n; i++)
	{
		set.push_back(i);
	}

	CombinationWithoutRepetition::combinationWithoutRepetition(k,set);
	return 0;
}