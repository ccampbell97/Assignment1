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

void Deposit(PERSON *arr1, int size)
{
	string fName, lName, fullName;
	int i;
	float money = 0;
	cout << "Enter your full name to deposit money: ";
	cin >> fName;
	cin >> lName;
	fullName = fName + " " + lName;
	cout << fullName << ", how much would you like to deposit? ";
	cin >> money;
	for (i = 0; i < size; i++)
	{
		if (arr1[i].Name == fullName)
		{
			arr1[i].Balance += money;
			cout << "Now your new balance is " << arr1[i].Balance << endl;
			return;
		}
	}
	cout << "Your name is not in our database." << endl;
	
}

void NewCopy(string file, PERSON *arr1, int size)
{
	int i;
	ofstream dataFile;
	dataFile.open(file);
	for (i = 0; i < size; i++)
		dataFile << arr1[i].Name << " " << arr1[i].Balance << endl;
}

int main()
{
	int i = 0;
	int size = 0;
	string input = "a";
	string temp;
	double balance;
	string fName, lName, fullName;
	ifstream dataFile;
	dataFile.open("data.txt");
	getline(dataFile, temp);
	while (dataFile)
	{
		size++;
		getline(dataFile, temp);
	}
	dataFile.close();
	dataFile.open("data.txt");
	PERSON* arr1 = new PERSON[size];
	dataFile >> fName;
	while (dataFile)
	{
		dataFile >> lName;
		dataFile >> balance;
		arr1[i].Balance = balance;
		fullName = fName + " " + lName;
		strcpy_s(arr1[i].Name, fullName.c_str());
		dataFile >> fName;
		i++;
	}
	dataFile.close();

	cout << "Press \"q\" to quit the program" << endl << "Press \"o\" to output the current records" << endl << "Press \"d\" to deposit money" << endl << "Press \"r\" to find the richest person" << endl;

	while (input != "q")
	{
		cout << "Please choose an option: ";
		cin >> input;

		if (input == "o")
			Display(arr1, size);
		else if (input == "d")
			Deposit(arr1, size);
		else if (input == "r")
			cout << "The Richest person is " << findRichest(arr1, size) << endl;
		else if (input == "q")
			NewCopy("data.txt", arr1, size);
		else
			cout << "Not a valid option. Please try again: ";

		cout << endl << "Press \"q\" to quit the program" << endl << "Press \"o\" to output the current records" << endl << "Press \"d\" to deposit money" << endl << "Press \"r\" to find the richest person" << endl;
	}
}