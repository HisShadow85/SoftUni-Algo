#include<iostream>
#include<string>
#include<vector>
#include<sstream>

using namespace std;

class EditDistance {
	
public:
	typedef short cost;
	static vector<string> editDistance(string &toConvert, string &convertTo,vector<cost> &costs){
		//here we are going to calculate the cost of the operations 
		vector<vector<cost> > workMatrix( convertTo.size()+1,vector<cost>(toConvert.size()+1) );
		//here we going to store the characters corresponding to the procedure needed for this cell'state
		vector<vector<char> > pathMatrix( convertTo.size()+1,vector<char>(toConvert.size()+1) );
		//only for clarity
		int 
			costReplace = costs[0],
			costInsert = costs[1],
			costDelete = costs[2];
		//here we calculate the cost for making the input string(toConvert) into empty one
		for (unsigned int y = 1; y < workMatrix.size(); y++)
		{
			workMatrix[y][0] = y*costInsert; 
			pathMatrix[y][0] = 'I';
		}
		/*here we calculate the cost for making the output string(convertTo) from empty one*/
		for (unsigned int x = 1; x < workMatrix[0].size(); x++)
		{
			workMatrix[0][x] = x*costDelete;
			pathMatrix[0][x] = 'D';
		}
		pathMatrix[0][0] = 'N'; //
		

		//the starting position is 1x1
		for (unsigned int i = 1; i < workMatrix.size(); i++)
		{
			for (unsigned int j = 1; j < workMatrix[0].size(); j++)
			{
				//if the two characters are the same we do not need to do anything
				if(convertTo[i-1] == toConvert[j-1]){
					workMatrix[i][j] = workMatrix[i-1][j-1];
					pathMatrix[i][j] = 'N';//N for nothing
				}else{
					char procedure;//character corresponding to the lowest cost procedure
					//choose the minimum of all the three possible procedures
                    workMatrix[i][j] = min(workMatrix[i][j-1]+costDelete,
						                   workMatrix[i-1][j]+costInsert,
										   workMatrix[i-1][j-1]+costReplace,
										   procedure);
                    pathMatrix[i][j] = procedure;//update the needed procedure for the cuurent state
				}
			}
		}
	
		vector<string> procedures;//here we going to store the procedures
		//extracts the procedures backward
		for (int i = convertTo.size(),j = toConvert.size(); i >= 0 && j>=0;)
		{
			switch (pathMatrix[i][j])
			{
				case 'N': i--;j--; break;
				case 'R': procedures.push_back(replace(j-1,convertTo[i-1]));i--;j--; break;
				case 'I': procedures.push_back(insert(i-1,convertTo[i-1])); i--;break;
				case 'D': procedures.push_back(del(j-1));j--;break;
			}
		}
		//the needed cost for the all procedures will be stored in the most down right cell of the working matrix
		procedures.push_back(NumberToString(workMatrix[workMatrix.size()-1][workMatrix[0].size()-1]));
		return procedures;
	}

	static void showCost(string &toConvert, string &convertTo,vector<cost> &costs){
		vector<string> procedures = editDistance(toConvert,convertTo,costs);
		cout<<"Minimum edit distance: "<<procedures.back()<<endl;
		for (int i = procedures.size()-2; i >= 0; i--)
		{
			cout<<procedures[i]<<endl;
		}
	}
private:
	//return the minimum cost amongst the three and loads the corresponding procedure
	static int min(cost del,cost insert,cost replace,char &procedureCode){
	   int result;
	   if(insert < del){
		   if(insert < replace){
			   result = insert, procedureCode = 'I';
		   }else{
			    result = replace, procedureCode = 'R';
		   }
	   }else{
		   if(del < replace){
			   result = del, procedureCode = 'D';
		   }else{
			   result = replace, procedureCode = 'R';
		   }
	   }
	  
		return result;
	}
	//return string coresponding to the replace procedure
	static string replace(int index,char ch){
		  string precedure("REPLACE(");
		  precedure.push_back(index + '0');
		  precedure.append(", ");
		  precedure.push_back(ch);
		  precedure.push_back(')');
		  return precedure;
	}
	//return string coresponding to the insert procedure
	static string insert(int index,char ch){
		  string precedure("INSERT(");
		  precedure.push_back(index + '0');
		  precedure.append(", ");
		  precedure.push_back(ch);
		  precedure.push_back(')');
		  return precedure;
	}
	//return string coresponding to the delete procedure
	static string del(int index){
		  string precedure("DELETE(");
		  precedure.push_back(index + '0');
		  precedure.push_back(')');
		  return precedure;
	}
	//C++ is not very good when comes to the regular expressions
	template <typename T>
    static string NumberToString ( T Number )
    {
		 ostringstream ss;
		 ss << Number;
		 return ss.str();
   }
};

int main(){

	string str1;
	string str2;
	stringstream ss("4\n3 2 1\nabracadabra\nmabragabra\n5 2 1\nnqma bira\nima bira\n3 3 3\nequal\nequal\n1 1 1\nequal\ndifferent");
	int loops;
	ss>>loops;
	for (int i = 0; i < loops; i++)
	{
		vector<EditDistance::cost> costs(3);
		ss>>costs[0]>>costs[1]>>costs[2]>>ws;
		getline(ss,str1);
		getline(ss,str2);
		EditDistance::showCost(str1,str2,costs);
		cout<<"----------------------------------------------------------\n";
	}
	cout<<"Enter your own input!\n";
	while (true)
	{
		vector<EditDistance::cost> costs(3);
		cout<<"cost-replace:";
		cin>>costs[0];
		cout<<"cost-insert:";
		cin>>costs[1];
		cout<<"cost-delete:";
		cin>>costs[2];
		cout<<"String to be converted:\n";
		cin>>ws;
		getline(cin,str1);
		cout<<"The string in which the previus string to be converted:\n";
		getline(cin,str2);
		EditDistance::showCost(str1,str2,costs);
		cout<<"----------------------------------------------------------\n";
	}
	return 0;

}