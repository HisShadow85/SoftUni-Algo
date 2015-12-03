#include<iostream>
#include<vector>
#include<sstream>
#include<algorithm>
using namespace std;

struct Task{
	int taskId;
	int value;
	int deadline;
	Task(int value = 0, int deadline = 0,int taskId = 0):value(value),deadline(deadline),taskId(taskId){}
};

class Scheduling{
	  const static int  NUTU = -1; //not used time of unit

	  static int min(int a,int b){
		  return a < b ? a : b;
	  }
	  static void expand(vector<int> &schedule,int newSize){
		  while (schedule.size() <= newSize)
		  {
			  schedule.push_back(NUTU);
		  }
	  }
	
	  static void printTaskSecuqnce(vector<int> &schedule,int value){
		  cout<<"Optimal schedule: ";
		  int i = 1;
		  for (i = 1; i < schedule.size(); i++)
		  {
			  if(schedule[i] != NUTU){
			    cout<<schedule[i];
				break;
		      }
		  }

		  for (i++; i < schedule.size(); i++)
		  {
			  if(schedule[i] != NUTU){
				  cout<<" -> "<<schedule[i];
			  }
		  }
		  cout<<"\nTotal value: "<<value<<endl;
	  }

public:

	static void showSchedule(vector<Task> &tasks){

		int totalValue = 0;
		vector<int> schedule(tasks.size()+1,NUTU);

		struct Compare
		{
			bool operator()(const Task &t1, const Task &t2){
				return  t1.value > t2.value;
			}
		};

		sort(tasks.begin(),tasks.end(),Compare());

		for (int currTask = 0; currTask < tasks.size(); currTask++)
		{
			int deadline = tasks[currTask].deadline;
			if(deadline >= schedule.size()){
				expand(schedule,deadline);
			}
			while(deadline > 0)
			{
				if(schedule[deadline] == NUTU){
                   schedule[deadline] = tasks[currTask].taskId;
				   totalValue+=tasks[currTask].value;
				   break;
				}
				deadline--;
			}
		}

		printTaskSecuqnce(schedule,totalValue);
	}

};



int main(){
	stringstream ss("5\n40  1\n30  2\n15  1\n20  1\n50  2\n3\n25  1\n14  1\n43  1\n6\n5  3\n6  4\n2  1\n3  4\n8  2\n4  3\n");
	for (int i = 1; i < 4; i++)
	{
		cout<<"Example: "<<i<<"\nINPUT\nTasks: ";
		int taskNum;
		ss>>taskNum;
		cout<<taskNum<<endl;
		vector<Task> tasks(taskNum);
		for (int j = 0; j < taskNum; j++)
		{
			ss>>tasks[j].value>>tasks[j].deadline;
			tasks[j].taskId = j+1;
			cout<<tasks[j].value<<" - "<<tasks[j].deadline<<endl;
		}
		cout<<"OUTPUT:\n";
		Scheduling::showSchedule(tasks);
		cout<<"\n--------------------------------------------------------------------------\n";
	}

	return 0;
};