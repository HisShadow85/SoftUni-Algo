#include <iostream>
using namespace std;

void printEgyptian(int numerator, int denominator)
{
    // If either numerator or denominator is 0
    if (numerator == 0 || denominator == 0)
        return;
 
	// If numerator is more than denominator
    if (numerator >= denominator)
    {
        cout <<" Error (fraction is equal to or greater than 1)";
        return;
    }

    // If numerator divides denominator, then simple division
    // makes the fraction in 1/n form
    if (denominator%numerator == 0)
    {
        cout << "1/" << denominator/numerator;
        return;
    }
 
    
    // Here denominator is greater than numerator and denominator%numerator i non-zero
    //Find ceiling of denominator/numerator and print it as firstfraction
    int n = denominator/numerator + 1;
    cout << "1/" << n << " + ";
 
    // Recurse for remaining part
    printEgyptian(numerator*n-denominator, denominator*n);
 }
 
// Driver Program
int main()
{
	int input[5][2] = { {43,48},{3,7},{23,46},{22,7},{134,3151} };
	cout<<"Egyptian Fractions Exaples:\n";
	for (int i = 0; i < 5 ; i++)
	{
		cout<<input[i][0] << "/" << input[i][1] << " = ";
		printEgyptian(input[i][0], input[i][1]);
		cout<<endl;
	}
	cout<<"---------------------------------------------------------------\n";
	cout<<"Enter your own data:\nEnter zero for denominator or numerator to exit.\n";
	int numerator =1, denominator = 1 ;
	while (true)
	{
		cout<<"Enter nominator: ";
		int nomerator;
		cin>>nomerator ;
		cout<<"Enter denominator: ";
		int denominator;
		cin>>denominator;
		if (numerator == 0 || denominator == 0)
           break;
		cout<<nomerator<< "/" << denominator << " = ";
        printEgyptian(nomerator,denominator);
		cout<<"\n------------------------------------------------------------------\n";
	}
 
    return 0;
}