#include "S01.h"

void sortClassList(string* Class, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (Class[i] < Class[j]) swap(Class[i], Class[j]);
}

void viewClassList(string usr)
{
	system("cls");
	cout << "VIEW LIST OF CLASS\n\n";
	string* Class; int n;
	inputListOfClass(Class, n);
	sortClassList(Class, n);
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 <<". "<< Class[i] << endl;
	}
	cout << "\nPress any key to back...";
	delete[]Class;
	_getch();
	system("cls");
	StaffClassMenu(usr, 1);
}
