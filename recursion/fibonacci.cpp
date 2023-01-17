//fibonacci sequence when given the first two terms
#include <iostream>

using namespace std;

int rFibNum(int a, int b, int n);

int main()
{
	int firstFibNum;
	int secondFibNum;
	int nth;

	cout << "Enter the first fibonacci number: ";
	cin >> firstFibNum;
	cout << endl;

	cout << "Enter the second fibonacci number: ";
	cin >> secondFibNum;
	cout << endl;

	cout << "Enter the position of the desired fibonacci number: ";
	cin >> nth;
	cout << endl;

	cout << "The fibonacci number at position " << nth << "is: " << rFibNum(firstFibNum, secondFibNum, nth) << endl;

	return 0;
}