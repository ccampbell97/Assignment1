#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct  PERSON
{
	char  Name[20];
	float Balance;
};

void Display(PERSON *arr1, int size)
{
	cout << "Name" << "      " << "Balance" << endl;
	cout << "-------------------------------------" << endl;
	int i;
	for (i = 0; i < size; i++)
		cout << arr1[i].Name << " " << arr1[i].Balance << endl;
}

string findRichest(PERSON *arr1, int size)
{
	int i;
	string Richest = arr1[0].Name;
	float rMoney = 0;
	for (i = 0; i < size; i++)
	{
		if (arr1[i].Balance > rMoney)
		{
			rMoney = arr1[i].Balance;
			Richest = arr1[i].Name;
		}
	}
	return Richest;
}

void Deposit(string CustName, PERSON *arr1, int n)
{
	int i;
	float money = 0;
	cout << CustName << ", how much would you like to deposit? ";
	cin >> money;
	for (i = 0; i < n; i++)
	{
		if (arr1[i].Name == CustName)
		{
			arr1[i].Balance += money;
			cout << "Now your new balance is " << arr1[i].Balance << endl;
			return;
		}
	}
	cout << "Your name is not in our database." << endl;

}

void NewCopy(string file, PERSON *arr1, int n)
{
	int i;
	ofstream dataFile;
	dataFile.open(file);
	for (i = 0; i < n; i++)
		dataFile << arr1[i].Name << " " << arr1[i].Balance << endl;
}

int checkFile(string file)
{
	string temp;
	ifstream dataFile;
	int size = 0;
	dataFile.open("data.txt");
	getline(dataFile, temp);
	while (dataFile)
	{
		size++;
		getline(dataFile, temp);
	}
	dataFile.close();
	return size;
}

PERSON *setArray(PERSON *P, int n)
{
	int i;
	ifstream dataFile;
	string fName, lName, fullName;
	float balance;
	dataFile.open("data.txt");
	dataFile >> fName;
	for(i = 0; i < n; i++)
	{
		dataFile >> lName;
		dataFile >> balance;
		P[i].Balance = balance;
		fullName = fName + " " + lName;
		strcpy_s(P[i].Name, fullName.c_str());
		dataFile >> fName;
	}
	dataFile.close();
	return P;
}

int main()
{
	int n = 0;
	string input, temp, CustName, fName, lName;
	double balance;
	n = checkFile("data.txt");
	PERSON *P = new PERSON[n];
	P = setArray(P, n);

	cout << "Press \"q\" to quit the program" << endl << "Press \"o\" to output the current records" << endl << "Press \"d\" to deposit money" << endl << "Press \"r\" to find the richest person" << endl;
	while (input != "q")
	{
		cout << "Please choose an option: ";
		cin >> input;
		if (input == "o")
			Display(P, n);
		else if (input == "d")
		{
			cout << "Enter your full name to deposit money: ";
			cin >> fName;
			cin >> lName;
			CustName = fName + " " + lName;
			Deposit(CustName, P, n);
		}
		else if (input == "r")
			cout << "The Richest person is " << findRichest(P, n) << endl;
		else if (input == "q")
			NewCopy("data.txt", P, n);
		else
			cout << "Not a valid option. Please try again: ";
	}
}
