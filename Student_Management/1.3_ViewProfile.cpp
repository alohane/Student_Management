#include "S01.h"

void ViewProfile(string& usr, int& type)
{
	system("cls");
	switch (type)
	{
	case 1:
	{
		Staff* stf;
		int n;
		inputStaff(stf,n);
		for (int i = 0; i < n; i++)
		{
			if (stf[i].usr == usr)
			{
				cout << "Username: " << stf[i].usr<<endl;
				cout << "Full Name: " << stf[i].name << endl;
				cout << "Role: Staff\n";
				cout << "Gender: ";
				if (stf[i].gen == 1)cout << "Female";
				else cout << "Male";
				break;
			}
		}
	}
	case 2:
	{
		Lect* lct;
		int n;
		inputLecturer(lct, n);
		for (int i = 0; i < n; i++)
		{
			if (lct[i].usr == usr)
			{
				cout << "Username: " << lct[i].usr << endl;
				cout << "Full Name: " << lct[i].name << endl;
				cout << "Role: Lecturer\n";
				cout << "Level: " << lct[i].lvl << endl;
				cout << "Gender: ";
				if (lct[i].gen == 1)cout << "Female";
				else cout << "Male";
				break;
			}
		}
	}
	case 3:
	{
		Stu* stu;
		int n;
		inputStudent(stu, n);
		for (int i = 0; i < n; i++)
		{
			if (stu[i].id == usr)
			{
				cout << "Student ID: " << stu[i].id << endl;
				cout << "Full Name: " << stu[i].name << endl;
				cout << "Role: Student\n";
				cout << "DoB: " << stu[i].dob << endl;
				cout << "Class: " << stu[i].cls;
				break;
			}
		}
	}
	}
	cout << "\nPress any key to back...";
	_getch();
	system("cls");
	LoggedinMenu(type, usr);
}