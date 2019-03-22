#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct  PERSON
{
	char  Name[20];
	float Balance;
};

void printmenu()
{
	cout << "Please enter a choice:" << endl;
	cout << "1. Display records" << endl;
	cout << "2. Deposit funds" << endl;
	cout << "3. Find Highest Balance" << endl;
	cout << "4. Update records" << endl;
	cout << "5. Exit the program" << endl;
}

void Display(PERSON *P, int size)
{
	cout << "Name" << "      " << "Balance" << endl;
	cout << "-------------------------------------" << endl;
	int i;
	for (i = 0; i < size; i++)
		cout << P[i].Name << " " << P[i].Balance << endl;
}

string findRichest(PERSON *P, int size)
{
	int i;
	string Richest = P[0].Name;
	float rMoney = 0;
	for (i = 0; i < size; i++)
	{
		if (P[i].Balance > rMoney)
		{
			rMoney = P[i].Balance;
			Richest = P[i].Name;
		}
	}
	return Richest;
}

void Deposit(PERSON *P, string CustName, int n, float money)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (P[i].Name == CustName)
		{
			P[i].Balance += money;
			cout << "New Balance: " << P[i].Balance << endl;
			return;
		}
	}
	cout << "Record Not Found" << endl;

}

void NewCopy(string file, PERSON *P, int n)
{
	int i;
	ofstream dataFile;
	dataFile.open(file);
	for (i = 0; i < n; i++)
		dataFile << P[i].Name << " " << P[i].Balance << endl;
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

PERSON *setArray(int &n)
{
	int i;
	PERSON *P = new PERSON[n];
	ifstream dataFile;
	string fName, lName, fullName;
	float balance;
	dataFile.open("data.txt");
	for (i = 0; i < n; i++)
	{
		dataFile >> fName;
		dataFile >> lName;
		dataFile >> P[i].Balance;
		fullName = fName.substr(0,9) + " " + lName.substr(0,10);
		strcpy(P[i].Name, fullName.c_str());
	}
	dataFile.close();
	return P;
}

int main()
{
	int n = 0;
	int choice;
	float amount;
	string input, CustName, fName, lName;
	double balance;
	n = checkFile("data.txt");
	PERSON *P = setArray(n);
	do
	{
		printmenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			// Act on display
			Display(P, n);
			break;

		case 2:
			// Act on deposit
			cout << "Enter name: ";
			cin >> fName;
			cin >> lName;
			CustName = fName + " " + lName;
			cout << "Amount: ";
			cin >> amount;
			Deposit(P, CustName, n, amount);
			break;

		case 3:
			// Act highest balance
			cout << "The Richest person is " << findRichest(P, n) << endl;
			break;

		case 4:
			// Act on update records
			NewCopy("data.txt", P, n);
			cout << "File Updated!" << endl;
			break;

		case 5:
			// Must call update records here before exiting the program
			NewCopy("data.txt", P, n);
			break;

		default:
			cout << "Invalid entry" << endl;
			break;
		}
		cout << endl;
	} while (choice != 5);
	delete [] P;
	return 0;
}
