#include "S01.h"

void viewClassStudentList(string usr)
{
	system("cls");
	cout << "VIEW LIST OF STUDENTS IN CLASS:\n";
	string* Class; int n;
	inputListOfClass(Class, n);
	sortClassList(Class, n);
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << ". " << Class[i] << endl;
	}
	cout << "0. Back\n";
	int choice;
	cout << "Input class to view list of students (0-" << n << "): ";
	cin >> choice;
	if(choice==0){ system("cls"); StaffClassMenu(usr, 1); }
	viewStudentOfClass(Class[choice - 1]);
	delete[]Class;
	cout << "\nPress any key to back...";
	_getch();
	system("cls");
	StaffClassMenu(usr, 1);
}