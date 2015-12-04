#include<iostream>
#include<vector>

using namespace std;

class VariationsWithoutRepetition{

	public:
	static void variationsWithoutRepetition(int classDegree, vector<int> &set){
		   
		 static vector<int> variation;
		 static int index = -1;
		 static int couter = 0;
		 index++;
		 if(index == 0){
			 variation.clear();
			 variation.resize(classDegree);
		 }

		 if(index == variation.size()){
			 for (int i = 0; i < variation.size(); i++)
			 {
				 cout<<variation[i]<<' ';
			 }
			 cout<<endl<<++couter<<endl;;
		 }else{
			 for (int i = 0; i < set.size()-index; i++)
			 {
				 variation[index] = set[i];
				 swap(set[i],set[set.size()-index-1]);
				 variationsWithoutRepetition(classDegree,set);
				 swap(set[set.size()-index-1],set[i]);
			 }
		 }
		 index--;
	}

};

int main(){
	int k,n;
	vector<int> input;
	cin>>k>>n;
	for (int i = 0; i < n; i++)
	{
		input.push_back(i);
	}
	VariationsWithoutRepetition::variationsWithoutRepetition(k,input);
	return 0;
}