#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>
#include<iomanip>
using namespace std;

class Item{
public:
	int value;
	int weight;
	Item(int value = 0, int weight = 0):value(value),weight(weight){}
	
	bool operator<(const Item &other){
		return this->value / this->weight > other.value /other.weight ;
	}
};

class FractionalKnapsack{
public:
	static void fillKnapsack(vector<Item> &items,int capacity){
		sort(items.begin(),items.end());
		float maxValue = 0;
		for (int currItem = 0; currItem < items.size() && capacity != 0; currItem++)
		{
			float percentageToTake;
			if(items[currItem].weight <= capacity){
				maxValue+=items[currItem].value;
				capacity-=items[currItem].weight;
				percentageToTake = 100.0f;
			}else{
			    percentageToTake = (float)capacity/items[currItem].weight;
				maxValue += percentageToTake*items[currItem].value;
				percentageToTake*=100;
				capacity = 0;
			}

			strRepresentation(percentageToTake,items[currItem].value,items[currItem].weight);
		}

		cout<<"Total price: "<<setprecision(5)<<maxValue<<endl;

	}

	static void strRepresentation(float percentage,int price ,int weight){
		cout<<"Take " <<setprecision(4)<<percentage<<"% of item with price "<<price<<".00 and weight "<<weight<<endl;
	}

};


int main(){
	stringstream ss("16 3\n25  10\n12  8\n16  8\n13 2\n13  7\n15  7\n22 4\n50  25\n34  25\n41  25\n3  25\n134 9\n12  14\n45  54\n98  78\n21  51\n64  11\n90  117\n33  17\n64  23\n7  3\n");
	for (int i = 1; i < 5; i++)
	{
		cout<<"Exapmle: "<<i<<"\nINPUT:\n";
	    int capacity , itemCount;
		ss>>capacity>>itemCount;
		cout<<"Capacity: "<<capacity<<"Items: "<<itemCount<<endl;;
		vector<Item> items(itemCount);
		for (int i = 0; i < items.size(); i++)
		{
			ss>>items[i].value>>items[i].weight;
			cout<<items[i].value<<" -> "<<items[i].weight<<endl;;
		}
		FractionalKnapsack::fillKnapsack(items,capacity);
		cout<<"\n----------------------------------------------------------------------------\n";
	}
	
	return 0;
}