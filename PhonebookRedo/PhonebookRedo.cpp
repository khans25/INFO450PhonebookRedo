// PhonebookRedo.cpp : Defines the entry point for the console application.
// Complete!

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

class phonebook
{
	char name[100];
	int hphone;
	int mphone;
public:
	phonebook();
	void setPhonebook(char n[], int h, int m);
	void display();
	friend class phonelist;
};

phonebook::phonebook()
{
	strcpy_s(name, "");
	hphone = 0000000000;
	mphone = 0000000000;
}

void phonebook::setPhonebook(char n[], int h, int m)
{
	strcpy_s(name, n);
	hphone = h;
	mphone = m;
}

void phonebook::display()
{
	printf("----------------------------------------\n");
	printf("Name: %s  Home Phone#: %10 Mobile Phone #: %10\n", name, hphone, mphone);
	printf("----------------------------------------\n");
}

class phonelist
{
	char filename[100];
	int phoneCount;
	phonebook **mylist;
public:
	phonelist();
	~phonelist();
	void setFilename(char f[]);
	int getCount();
	void phonelist::addToList(phonebook *p);
	void phonelist::showList();
	int saveList();
	void readList();
};

phonelist::phonelist()
{
	mylist = new phonebook*[100];
	phoneCount = 0;
}

phonelist::~phonelist()
{
	delete mylist;
}

void phonelist::setFilename(char f[])
{
	strcpy_s(filename, f);
}

void phonelist::addToList(phonebook *p)
{
	mylist[phoneCount] = p;
	phoneCount++;;
}

int phonelist::getCount()
{
	return phoneCount;
}

void phonelist::showList()
{
	for (int i = 0; i < phoneCount; i++)
	{
		mylist[i]->display();
	}
}

int phonelist::saveList()
{
	ofstream output(filename);
	if (!output)
	{
		cout << "Sorry, file didn't work." << endl;
		return -1;
	}
	for (int i = 0; i < phoneCount; i++)
	{
		output << mylist[i]->name << ",";
		output << mylist[i]->hphone << ",";
		output << mylist[i]->mphone << endl;
	}
	output.close();
	return 0;
}

void phonelist::readList()
{
	ifstream infile(filename);
	if (!infile)
	{
		return;
	}

	while (!infile.eof())
	{
		phonebook *ptr;
		char name[100];
		char hphone[10];
		char mphone[10];

		infile.getline(name, 100, ',');
		if (strlen(name))
		{
			infile.getline(hphone, 10, ',');
			infile.getline(mphone, 10);
			ptr = new phonebook();
			ptr->setPhonebook(name, atoi(hphone), atoi(mphone));
			addToList(ptr);
		}
	}
	infile.close();
}

int main()
{
	char answer = 'y';
	char name[100];
	int hphone;
	int mphone;
	char filename[100];

	phonelist *pList = new phonelist();

	cout << "Enter full path filename" << endl;
	gets_s(filename);
	pList->setFilename(filename);

	pList->readList();
	if (pList->getCount() == 0)
	{
		cout << "List empty, create files. " << endl;
	}
	else
	{
		cout << "In list, there are: " << pList->getCount() << endl;
	}

	cout << "Press Y to enter in new phonebook, otherwise enter any other key to exit" << endl;
	cin >> answer;

	while (answer == 'Y' || answer == 'y')
	{
		cin.ignore();
		cin.clear();

		cout << "Enter Name" << endl;
		gets_s(name);
		cout << "Enter Home Phone" << endl;
		cin >> hphone;
		cout << "Enter Mobile Phone" << endl;
		cin >> mphone;

		phonebook *mylist = new phonebook();
		mylist->setPhonebook(name, hphone, mphone);
		pList->addToList(mylist);


		cout << "Enter Y to add another; other keys to leave" << endl;
		cin >> answer;
	}

	pList->showList();
	pList->saveList();

	return 0;
}

