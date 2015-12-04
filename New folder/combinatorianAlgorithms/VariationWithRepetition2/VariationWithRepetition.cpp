#include<iostream>
#include<vector>

using namespace std;

class VariationsWithRepetition{
public:

	static void variationsWithRepetition(int classDegree,vector<int> &set){
				  static int z = 0;
		        static unsigned index = -1;
				static vector<int> variations;
				index++;
				if(index == 0){
					variations.clear();
					variations.resize(classDegree);
				}

				if(index == variations.size()){
					for (int i = 0; i < variations.size(); i++)
					{
						cout<<variations[i]<<' ';
					}
					cout<<endl;
					cout<<++z<<endl;
				}else{
					for (int i = 0; i < set.size(); i++)
					{
						variations[index] = set[i];
						variationsWithRepetition(classDegree,set);
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
	VariationsWithRepetition::variationsWithRepetition(k,set);
	//VariationsWithoutRepetition::variationsWithoutRepetition(k,set);
	return 0;
}