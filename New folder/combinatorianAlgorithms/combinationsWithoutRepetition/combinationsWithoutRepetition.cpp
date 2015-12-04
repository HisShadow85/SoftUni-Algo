#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class  PermutationsWithRepetition{
public:
/** 
 * Given ps, integer set with repetitions, it sorts it, and
 * calls the method to permute it.
 *
 * @param ps Array of integers with repetitions, set of 
 * elements to permute.
 */
static void permutationsRep(vector<int> &ps) {
		sort(ps.begin(),ps.end());
		permuteRep(ps, 0, ps.size());
	}
  
/** 
 * Calls doSomething() method with all the permutations
 * of the ps set.
 *
 * It considers when elements are repeated.
 *
 * Initial call: permute(ps, 0, ps.length);
 *
 * @param ps Array of integers with repetitions, set of 
 * elements to permute.
 * @param start Index where permutation begins.
 * @param n Number of elements of ps.
 */
static void permuteRep(vector<int> &ps, int start, int n) {
    print(ps);
	int tmp;
    if (start < n) {
      for (int i = n - 2; i >= start; i--) {
        for (int j = i + 1; j < n; j++) {
          if (ps[i] != ps[j]) {
            swap(ps[i],ps[j]);

            permuteRep(ps, i + 1, n);
          }
        }
        // Undo all modifications done by
        // recursive calls and swapping
        tmp = ps[i];
        for (int k = i; k < n - 1;)
          ps[k] = ps[++k];
        ps[n - 1] = tmp;
      } //end for (int i = n - 2; i >= start; i--)
    }//end  if (start < n)
  }

static void print(vector<int> &ps){
	for (int i = 0; i < ps.size(); i++)
	{
		cout<<ps[i]<<' ';
	}
	cout<<endl;
}


};


class PermutationsWithRepetition2{

public:

static void PermuteRep(vector<int> &arr, int start, int end)
{
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
}

static void print(vector<int> &ps){
	for (int i = 0; i < ps.size(); i++)
	{
		cout<<ps[i]<<' ';
	}
	cout<<endl;
}
};

int main(){
	vector<int> _array;
	_array.push_back(1);_array.push_back(3);_array.push_back(5);_array.push_back(5);_array.push_back(5);
	PermutationsWithRepetition2::PermuteRep(_array,0,4);
	return 0;
}