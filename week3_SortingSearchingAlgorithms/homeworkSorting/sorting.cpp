#include<iostream>
#include<vector>
#include<iterator>
#include<stack>
#include<string>
using namespace std;

template<typename T>
struct ISorter{
	virtual void sort(vector<T> &collection)=0;
};

class BucketSort: public ISorter<int>{

     const static int bucketsNumber = 10;
	 //represent the size of one bucket
	 int bucketSize;

	 class Node{
         public:
               int value;
               Node *next;
			   Node(int value = 0,Node *next = NULL):value(value),next(next){}
     };

	 class Bucket{
	 public:
           Node *head;
		   Bucket():head(NULL){}
     }buckets[bucketsNumber];

	 //insert a element into the proper bucket
	 void insert(int item){
		  //deduce in which bucket the element must be putted
		  int bucket = item/bucketSize;
		  //makes a new node with the given value
		  Node *n = new Node(item,NULL);
		 //if the bucket is empty or the most top element is equal or greater than the given
		 if(buckets[bucket].head==NULL || buckets[bucket].head->value >= item){
			// new node points to the top of the bucket
			n->next=buckets[bucket].head;
			//now the new node is the bucket's top
			buckets[bucket].head=n;
         }
		 else{//if the bucket is not empty and the top element is smaller
			//we start from the head
            Node *temp = buckets[bucket].head;
			//and iterate trought the list until we find a bigger element 
			// or reach the end of the list
            while( temp->next!=NULL && temp->next->value<item ){
                 temp=temp->next;
            }	
			//puts the element into his proper place
            n->next=temp->next;
            temp->next=n;
        }

	 }

	 void concatenate(vector<int> &collection){
	
		 vector<int>::iterator it = collection.begin();

		 for (int i = 0; i < bucketsNumber; i++)
		 {
			 if(buckets[i].head != NULL){
				 Node *curr = buckets[i].head;
				 while(curr != NULL)
				 {
				   Node *toDelete = curr;
				   *it = curr->value;
				   it++;
				   curr=curr->next;
				   delete toDelete;
			     }
				 buckets[i].head = NULL;
			 }
		 }
	 }

public:
	
	void sort(vector<int> &collection){
		if(collection.size() < 2) return;
		//the largest value found in collection
		int max = collection[0];
		//this flag indicates if the collections is already sorted
		bool isAllOrdered = true;

		for (unsigned int i = 1; i < collection.size(); i++)
   		{
			if(isAllOrdered && collection[i-1] > collection[i]){
			   isAllOrdered = false;
			}
			if(max < collection[i]){
               max = collection[i];
			}
		}
		if(isAllOrdered) return;
		//calculate the size of one bucket
		//If the size is 12 the all elements from 0 - 12 is putted in bucket one,
		//elements from 13 - 24 into bucket two and so on
	    bucketSize = (max +bucketsNumber)/(bucketsNumber);
		//insert all of the elements into the buckets
		for (unsigned int i = 0; i < collection.size(); i++)
		{
			insert(collection[i]);
		}
		//concatenates the contents of the buckets into the init. collection
		concatenate(collection);      
	}
};

template<typename T>
struct QuickSort: public ISorter<T>{
	void compexch(T &first, T &second){
         if(second < first) 
			 swap(first,second);
	}

	void sort(vector<T> &collection){
		/*auxiliary structure containing the indices of the first 
		 and last elements from the current chunk which we are working on */ 
		 struct Chunk{ 
			 int left,right;
			 Chunk(int left,int right):left(left),right(right){}
		 };
		 //we don't proceed with chunks of size 1
		 if(collection.size() < 2) return;

		//avoiding recursion using stack
		stack<Chunk> stak;
        //puts into the stack the whole collection
		stak.push(Chunk(0,collection.size()-1));

		while (!stak.empty())
		{
			//extracts the next chunk of the sortable collection
			Chunk currChunk = stak.top();stak.pop();

			// take the middle element
			int mid = currChunk.left+(currChunk.right-currChunk.left)/2;
	           /*sorting the first, middle and last elements such 
			     that the middle one (in value) is at the last position */
			   compexch(collection[currChunk.left],collection[mid]);
                compexch(collection[currChunk.left],collection[currChunk.right]);
				 compexch(collection[currChunk.right],collection[mid]);
            /*takes far-right element for pivot, it will be the limiter on the right side*/
			T &pivot = collection[currChunk.right];
	        int
			    i = currChunk.left-1, //incrementable index pointing elements larger than the pivot
				j = currChunk.right,  //incrementable index pointing elements smaller than the pivot
				p = currChunk.left,  //index exerting the end of the stacked elements, equal to the pivot, from the left edge
				q = currChunk.right-1; //index exerting the end of the stacked elements, equal to the pivot, from the right edge

			while(true)
			{
				//stops at the first element which is not less than the pivot
				while(collection[++i] < pivot);
				//stops at the first element which is not bigger than the pivot
				while(pivot < collection[--j]) if(j == currChunk.left) break; 
				if(i>=j) break;
				swap(collection[i],collection[j]); //exchange elements to their right places
				/*if a given swapped element is equal to the pivot it moved to his most closer edge,
				 so all elements equal to the pivot are arranged one after another at the two ends*/
				if(collection[i] == pivot) swap(collection[i],collection[p++]);
				if(collection[j] == pivot) swap(collection[j],collection[q--]);
			}
			/*the pivot is moved to so called middle of the current array,so it 
			  is already ordered(in it proper place) and will not be touched anymore*/
			swap(collection[i],collection[currChunk.right]);
			j = i+1; // j points the first element after the pivot from the right side and it will be incrementable
			i--; // i points the first element before the pivot from the left side and it will be decrementable
			/*the next two loops stitch the elements equal the pivot to its both sides*/
			for(int k = currChunk.left; k < p ; k++, i--) swap(collection[i],collection[k]);
			for(int k = currChunk.right-1; k > q  ; k--, j++) swap(collection[j],collection[k]);

			/*putting the largest chunk first into the stack save us a little memory 
	     	  used by the stack,because largest arrays divided into a greater number of 
			  smaller parts resulting in more Chunk structure instances*/
			if(i - currChunk.left > currChunk.right -j){
				if(i - currChunk.left > 0) //we don't proceed with chunks of size 1
				   stak.push(Chunk(currChunk.left,i));
				if(currChunk.right -j > 0) //we don't proceed with chunks of size 1
				   stak.push(Chunk(j,currChunk.right));
			}else{ 
				if(currChunk.right -j > 0)//we don't proceed with chunks of size 1
				   stak.push(Chunk(j,currChunk.right));
				if(i - currChunk.left > 0) //we don't proceed with chunks of size 1
				   stak.push(Chunk(currChunk.left,i));
			}

		}
	}

};

template<typename T>
struct HeapSort : public ISorter<T>
{

	void sort(vector<T> &collection){
		  heapsort(collection.begin(),collection.size());
	}

private:
	    template<typename RandomAccessIterator>
        static void heapsort(RandomAccessIterator &a,int count){
                //input: an unordered array a of length count
 
                //(Build the heap in array a so that largest value is at the root)
                heapify(a, count);

                //(The following loop maintains the invariants that a[0:end] is a heap and every element
                // beyond end is greater than everything before it (so a[end:count] is in sorted order))
                int end = count - 1;
                while (end > 0){
                        //(a[0] is the root and largest value. The swap moves it in front of the sorted elements.)
                        swap(a[end], a[0]);
                        //(the heap size is reduced by one)
                        end = end - 1 ;
                        //(the swap ruined the heap property, so restore it)
                        siftDown(a, 0, end);
                        }
        }
        //(Put elements of 'a' in heap order, in-place)
        template<typename RandomAccessIterator> 
        static void heapify(RandomAccessIterator &a,int count){
                //(start is assigned the index in 'a' of the last parent node)
                //(the last element in a 0-based array is at index count-1; find the parent of that element)
                int start = (count - 2) / 2;
    
                while (start >= 0){
                   // (sift down the node at index 'start' to the proper place such that all nodes below
                        // the start index are in heap order)
                        siftDown(a, start, count - 1);
                        //(go to the next parent node)
                        start = start - 1;
                }
                //(after sifting down the root all nodes/elements are in heap order)
        }

        template<typename RandomAccessIterator>
        static void siftUp(RandomAccessIterator &a,int start,int end)
                {
                         // input:  start represents the limit of how far up the heap to sift.
                         // end is the node to sift up.
                         int child = end; 
                         while (child > start)
                         {
                                 int parent = (child-1) / 2 ;
                                 if (a[parent] < a[child] )//then out of max-heap order
                                 {
                                         swap(a[parent], a[child]);
                                         child = parent; //repeat to continue sifting up the parent now
                                 }
                                 else
                                         return;
                         }
        }

        template<typename RandomAccessIterator>
        static void siftDown(RandomAccessIterator &a,int start,int end){
                int root = start;

                while ((root * 2 + 1) <= end){    //(While the root has at least one child)
                        int child = root * 2 + 1 ;     // (Left child)
                        int toSwap = root;                //(Keeps track of child to swap with)

                        if (a[toSwap] < a[child])
                                toSwap = child ;
                        //(If there is a right child and that child is greater)
                        if ( (child+1 <= end) && (a[toSwap] < a[child+1]) )
                                toSwap = child + 1;
                        if (toSwap == root)
                                //(The root holds the largest element. Since we assume the heaps rooted at the
                                // children are valid, this means that we are done.)
                                return;
                        else
                                swap(a[root], a[toSwap]);
                                root = toSwap ;           // (repeat to continue sifting down the child now)
                                }
          }
};

template<typename T>
struct MergeSort : public ISorter<T>
{
       void sort(vector<T> &collection)
         {
			  //copy the content of the collenction into the auxiliary array
			  vector<T> aux(collection);//making an auxiliary array
	          mergeSort(collection.begin(),aux.begin(),0,collection.size()-1);
         }
 

	    /*function which merges  array a(with N elements) with array b(with M elements)
		  into array c*/
	    template<typename RandomAccessIterator>
        void merge(RandomAccessIterator &c,RandomAccessIterator &a,int N,RandomAccessIterator &b, int M)
        {     
			  //i indexes the a array,j indexws the b array
			  //c indexws the b array
	          for(int i = 0, j = 0 , k=0; k<N+M; k++)
	          {
				  if(i==N) { c[k] = b[j++]; continue;} //if there are no more elements from array a 
				  if(j==M) { c[k] = a[i++]; continue;} //the next element will come from array  b
				                                       //and vice versa
				  //if the current element from a is smaler than one from b we palce it in the array c,
				  //if not we place there the current element from b
				  c[k] = (a[i]<b[j])? a[i++] : b[j++];
	          }
        }

	   /*recursive function which splits array "a" into two pieces until there 
	     is more then one element into the array.It use array "b" as an auxiliary 
		 array to store the not merged parts, from array's "a" splitting, from 
		 which makes the sorted sequence in the array "a" with "merge" function.
		 l-the index which is indexing the begining of the array "a"
		 r-the index which is indexing the last element of the array "a"*/
		template<typename RandomAccessIterator>
       void mergeSort(RandomAccessIterator &a,RandomAccessIterator &b, int l , int r)
       {
	         int m = l+(r-l)/2; //splits the array "a" into two pieces
	         if(r<=l) return; //if there is only one piece to split

			 /*with changing the places of the main array "a" and 
			 the auxiliary one ("b") on each recursive call we manage 
			 to avoid one useless copy of already sorted array.
			 We assume that after these calls the auxiliary array "b" 
			 contains the two sorted parts from splitting the array "a"*/
			 mergeSort(b,a,l,m); 
			 mergeSort(b,a,m+1,r); 			                   
			 //merges the two splitted parts represented by array "b"
			 merge(a+l,b+l,m-l+1,b+m+1,r-m);
       }
    
 };

template<typename T>
struct InsertionSort : public ISorter<T>
{
	void sort(vector<T> &collection){
		 int 
			 i,
			 l = 0,
			 r = collection.size()-1;
		     
		 /*into the below snippet of code we arrange the elements(like buble sort)
		   so the smallest element is at the beginning of the array on so there is 
		   no need to check if we are reached the most left edge*/
		for(i = r;i>l;i--) {
				if(collection[i] < collection[i-1]){
					T tmp = collection[i];
					collection[i] = collection[i-1];
					collection[i-1] = tmp;
				  }
		}
		/*since we have putted the smallest element into the very beginning 
		  the next comparison will be between the second and third element*/
		for(i = l+2; i<=r; i++)
		{
			int j = i; T tmp = collection[i];

				while(tmp < collection[j-1]){
					collection[j] =collection[j-1]; j--; }
	
			collection[j] = tmp;
		}
	}
};

template<typename T>
class SortableCollection{

	  vector<T> *items;
public:

	SortableCollection():items(new vector<T>()){}
	SortableCollection(vector<T> &init):items(new vector<T>(init)){}
	~SortableCollection(){ delete items;}
	SortableCollection<T> &operator=(const SortableCollection<T> &other){
		 if(this != &other){
            delete items;
			items = new vector<T>(*(other.items));
		 }
		 return *this;
	}
	SortableCollection<T> &operator=(const vector<T> &other){
		   if(this->items != &other){
			  delete items;
              items = new vector<T>(other);
		   }
		   return *this;
	}
	int count()const {return items->size();}
	const vector<T> &getItems()const{ return *items; }

	void sort(ISorter<T> &sorter){
		sorter.sort(*items);
	}

	int binarySearch(const T& key,bool mostLeft = true){
	    int left = 0;
		int right = items->size()-1;
		vector<T> &arr = *items;
		if(key < arr[left] && key > arr[right]) return -1;
		if(arr[right] == arr[left]){
			if(arr[left] == key) return left;
			else return -1;
		}
		//finds the most left appearance of the wanted element
		if(mostLeft){
			while (left<right)
			{
				int mid = left + (right - left)/2;

				if(arr[mid] < key){
					left = mid+1;
				}else{
					right = mid;
				}
			}

			if(arr[left] == key) return left;
			else return -1;
		}
		else{//finds the first matching of the wanted element
			while (left<=right)
			{
				int mid = left + (right - left)/2;

				if(arr[mid] < key){
					left = mid+1;
				}else if(arr[mid] > key){
					right = mid-1;
				}else{
					return mid;
				}
			}
			return -1;
		}
	}

    int interpolationsSearch(const T &key,bool mostLeft = true)
    {
		int left = 0;
		int right = items->size()-1 ;
		int mid ;
		vector<T> &arr = *items;

		while (arr[right] != arr[left] && key >= arr[left] && key <= arr[right])  {
			double k = (double)((key - arr[left]) * (double(right - left) / ( arr[right] - arr[left])));
			mid = (int)(left + k) ;

			if (arr[mid] < key)
				left = mid + 1 ;
			else if (key < arr[mid])
				right = mid+1;
			else{
				left = mid;
				break;
			}
		} 

		if (key == arr[left]){
			if(mostLeft){
			    int tmp = left;
				while (arr[left] == arr[tmp]) tmp--;
				return tmp+1;
			}else{
				return left;
			}
		}
		else
			return -1;
     }

    void shuffle() {
		   vector<T> &arr = *items; 
		  for(unsigned int n = items->size() - 1; n >= 1; --n) {
			   unsigned int k = rand() % (n + 1);
			   swap(arr[k],arr[n]);
          }

    }

};

class Shell{
	 bool isSorted;
	 SortableCollection<int> workArray;
	 int getCommand(int min,int max){
		 string input;
		 while (true)
		 {
			cin>>input;
		    int result;
			try{
              result = stoi(input);
			  if(result < min || result > max){
				  throw invalid_argument("Number out of range\n");
			  }else return result;
		    }catch(invalid_argument e){
				cout<<e.what();
				//cout<<"Invalid Input.Please enter a number from the menu\n";
				continue;
		    }
		 }



	 }
	 bool yesNo(){
		 string input;
		 while (true)
		 {
			  cout<<"Yes/No:";
		      cin>>input;
			  if(input.size() == 0) continue;
			  if(input[0] == 'Y' || input[0] == 'y') return true;
			  if(input[0] == 'N' || input[0] == 'n') return true;
		 }		
	 }
	 void show(){
		  const vector<int> &content = workArray.getItems();
		  cout<<'[';
		  unsigned int i;
		  for (i = 0; i < content.size()-1; i++)
		  {
			  cout<<content[i]<<", ";
		  }
		  cout<<content[i]<<"]\n";
	 }
	 void sort(){
		 while (true)
		 {
			 switch(sortMenu()){
			 case 1: workArray.sort(BucketSort());isSorted = true;cout<<"Done!\n";break;
			 case 2: workArray.sort(InsertionSort<int>());isSorted = true;cout<<"Done!\n";break;
			 case 3: workArray.sort(MergeSort<int>());isSorted = true;cout<<"Done!\n";break;
			 case 4: workArray.sort(QuickSort<int>());isSorted = true;cout<<"Done!\n";break;
			 case 5: workArray.sort(HeapSort<int>());isSorted = true;cout<<"Done!\n";break;
			 case 6: workArray.shuffle();isSorted = false;cout<<"Done!\n";break;
			 case 7: show();break;
			 case 8: return;
			 }
		 }
	 }
	 void search(bool mostLeft){
		 int bin,inter,number;
		 if(!isSorted){
			 cout<<"The collection in not sorted\nOperation Aborted!\n";
			 return;
		 }
		 cout<<"Enter the number you want to seach: ";
		 number = getCommand(-100000000,100000000);
		 cout<<endl;
		 bin = workArray.binarySearch(number,mostLeft);
		 inter = workArray.interpolationsSearch(number,mostLeft);
		 cout<<"Binary Search ->";
		 if(bin != -1) cout<<bin<<" position\n";
		 else cout<<"not found\n";
		 cout<<"InterpolationsSearch ->";
		 if(inter != -1) cout<<bin<<" position\n";
		 else cout<<"not found\n";
	 }
	 void search(){
		 while (true)
		 {   
			 switch(searchMenu()){
			 case 1: search(true);break;
			 case 2: search(false);break;
			 case 3: show();break;
			 case 4: return;
			 }
		 }
	 }

public:

	int mainMenu(){		
		cout<<"Choose option:\n"
		<<"1.Generate collection\n"
		<<"2.Shuffle the collection\n"
		<<"3.Sort the collection\n"
		<<"4.Search into the collection\n"
		<<"5.Show the collection\n"
		<<"6.Exit\n";
        return getCommand(1,6);
	}

	int sortMenu(){
        cout<<"Choose option:\n"
		<<"1.Bucket sort\n"
		<<"2.Insertion sort\n"
		<<"3.Merge sort\n"
		<<"4.Quick sort\n"
		<<"5.Heap sort\n"
		<<"6.Shuffle the collection\n"
		<<"7.Show the collection\n"
		<<"8.Back\n";
         return getCommand(1,8);
	}
	int searchMenu(){
        cout<<"Choose option:\n"
		<<"1.Search the element in the most left position\n"
		<<"2.Search the element in any position\n"
		<<"3.Show the collection\n"
		<<"4.Back\n";
         return getCommand(1,4);
	}

	void generateCollection(){
		cout<<"Enter the size of the working collection\nConstraints->Size from 2 to 100 milions\n";
		vector<int> temp(getCommand(2,100000000));
		cout<<"Enter the max value for the random generator\nConstraints->Size from 1 to 100 milions\n";
		int maxValue = getCommand(1,100000000)+1;
		for (unsigned int i = 0; i < temp.size(); i++)
		{
			temp[i] = rand()%maxValue;
		}
		workArray = temp;
		isSorted = false;
	}

	void run(){
		 generateCollection();
		 while (true)
		 {
			 switch(mainMenu()){
			 case 1: generateCollection() ; break;
             case 2: workArray.shuffle();isSorted = false;cout<<"Done!\n";break;
             case 3: sort(); break;
             case 4: search(); break;
			 case 5: show();break;
             case 6: return;
			 }
		 }
	}
};

int main(){
	Shell shell;
    shell.run();
	
	return 0;
}
