#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>

using namespace std;
class Lecture{
public:
	string name;
	int start;
	int finish;
	Lecture(string name = "Unknown",int start = INT_MAX, int finish = INT_MAX ):name(name),start(start),finish(finish){}
};

class BestLecturesSchedule{
public:
	static void chooseLectures(vector<Lecture> &schedule){
		struct Compare{
			bool operator()(const Lecture &l1, const Lecture &l2){
				return l1.finish < l2.finish;
			}
		};

		//activities are sorted according to their finish time.
		sort(schedule.begin(),schedule.end(),Compare());

		vector<int> choosenLectures;

		int choice = 0;
		choosenLectures.push_back(choice);

		for (unsigned int i = 1; i < schedule.size(); i++)
		{
			// If this alecture has start time greater than or equal to the finish
            // time of previously selected lecture, then select it
			if(schedule[i].start >= schedule[choice].finish){
				choice = i;
				choosenLectures.push_back(choice);
			}
		}
		show(schedule,choosenLectures);
	}

	static void show(vector<Lecture> &schedule,vector<int> &choices){
		cout<<"Lectures ("<<choices.size()<<"):\n";
		for (unsigned int i = 0; i < choices.size(); i++)
		{
			cout<<schedule[choices[i]].start<<" - "<<schedule[choices[i]].finish<<" -> "<<schedule[choices[i]].name<<endl;
		}
	}
};

int main(){

	stringstream ss("4\nJava: 1  7\nOOP: 3  13\nC_Programming: 5  9\nAdvanced_JavaScript: 10  14\n3\nProgramming_Basics: 3  5\nPHP: 2  4\nPhotoshop: 1  6\n7\nAdvanced_CSharp: 3  8\nHigh_Quality_Code: 7  10\nDatabases: 5  12\nASP_NET: 9  14\nAngular_JS: 13  15\nAlgorithms: 15  19\nProgramming_Basics: 17  20\n");
	for (int i = 1; i < 4; i++)
	{
		cout<<"Example: "<<i<<"\nINPUT:\n";
		int lectNum;
		ss>>lectNum>>ws;
		cout<<"Lectures: "<<lectNum<<endl;
		vector<Lecture> lectures;
		for (int j = 0; j < lectNum; j++)
		{
			string name;
			int start, finish;
			getline(ss,name,':');
			ss>>start>>finish>>ws;
			cout<<name<<": "<<start<<" -> "<<finish<<endl;
			lectures.push_back(Lecture(name,start,finish));
		}
		cout<<"OUPUT:\n";
		BestLecturesSchedule::chooseLectures(lectures);
		cout<<"------------------------------------------------------------\n";
	}
	return 0;
}