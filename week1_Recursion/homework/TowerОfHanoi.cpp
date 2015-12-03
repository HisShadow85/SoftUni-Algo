#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<string>
#include<iterator>
#include<algorithm>
using namespace std;

class TowerОfHanoi{
	vector<stack<int> > rods;
	int maxAvaliableDisk;
public:
	TowerОfHanoi(int maxDisk){
		rods.resize(3);
		/*initialize the source rod with all available disks from 1(smallest) to maxDisk(biggest) 
		in reverse order, thus the smallest one is on the top of the rod*/
		for (int i = maxDisk; i > 0; i--)
		{
			rods[0].push(i);
		}
	    maxAvaliableDisk=maxDisk;

	}

	void moveAlldisks(){
		 
		 printState();
		 moveDisk(rods[0].size(),rods[0],rods[2],rods[1]);



	}
	 //Move all disks from source to destination starting with the largest (bottom disk)
	void moveDisk(int bottomDisk, stack<int> &source, stack<int> &destination, stack<int> &spare){
		//If the bottom disk is equal to 1(the smallest), we can simply move it
		if(bottomDisk == 1){
			destination.push(source.top());
			source.pop();
			printState();
		
		}//If the bottom disk is larger than 1
		else{
			//move all disks above it (starting from bottom – 1) to the spare rod
			moveDisk(bottomDisk-1,source,spare,destination);
			//move the bottom disk to destination
			destination.push(source.top());
			source.pop();
			printState();
			//move the disks now on spare to destination (back on top of the bottom disk)
			moveDisk(bottomDisk-1,spare,destination,source);
		}
	}



	void printState(){
		vector<string> output(maxAvaliableDisk,string(""));
		vector<stack<int> > auxRods(rods);
		//height
		for (int i = 0; i < maxAvaliableDisk; i++)
		{
			//output.push_back(string(""));
			//rods
			for (int j = 0; j < 3; j++)
			{
				output[i].append("| ");
				int disk;
				if(rods[j].size() < maxAvaliableDisk - i) disk = 0;
				else{
					 disk = auxRods[j].top();auxRods[j].pop();
				}

				for (int k = 0; k < maxAvaliableDisk-disk; k++)
				{
					output[i].push_back(' ');
				}
				for (int k = 0; k < disk; k++)
				{
					output[i].append("**");
				}
				for (int k = 0; k < maxAvaliableDisk-disk; k++)
				{
					output[i].push_back(' ');
				}
				output[i].push_back(' ');
			}
			output[i].push_back('|');
		}
       copy(output.begin(),output.end(),ostream_iterator<string>(cout,"\n"));
	   cout<<endl;
	}
};


int main(){

	TowerОfHanoi toh(6);
	toh.moveAlldisks();


	return 0;
}



