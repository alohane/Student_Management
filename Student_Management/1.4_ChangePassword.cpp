#include "S01.h"
void changePasswordLect(string usr)
{
	system("cls");
	string oldpwd, newpwd, cnewpwd, oldp;
	Lect* lct;
	int choice;
	int n;
	inputLecturer(lct, n);
	int i;
	for (i = 0; i < n; i++)
	{
		if (lct[i].usr == usr)
		{
			oldp = lct[i].pwd;
			break;
		}
	}
	getPassword(oldpwd, newpwd, cnewpwd, oldp);
	if (oldp != oldpwd)
	{
		delete[]lct;
		cout << "\n1. Continue change password\n0. Back to main menu\nYour choice: ";
		cin >> choice;
		if (choice == 1) changePasswordLect(usr);
		return;
	}
	else {
		if (newpwd != cnewpwd)
		{
			cout << "\nConfirm password is wrong!";
			delete[]lct;
			cout << "\n1. Continue change password\n0. Back to main menu\nYour choice: ";
			cin >> choice;
			if (choice == 1) changePasswordLect(usr);
			return;
		}
		else {
			if (newpwd == oldpwd)
			{
				cout << "\nNew password is same as old!";
				delete[]lct;
				cout << "\n1. Continue change password\n0. Back to main menu\nYour choice: ";
				cin >> choice;
				if (choice == 1) changePasswordLect(usr);
				return;
			}
			else {
				cout << "\nYour Password has been changed";
				cout << "\nPress any key to back...";
				_getch();
				system("cls");
			}
		}
	}
	lct[i].pwd = newpwd;
	ofstream fout;
	fout.open("Lecturer.txt");
	fout << n << endl << endl;
	for (i = 0; i < n; i++)
	{
		fout << lct[i].usr<<endl;
		fout << lct[i].pwd << endl;
		fout << lct[i].name << endl;
		fout << lct[i].lvl << endl;
		fout << lct[i].gen << endl << endl;
	}
	fout.close();
	delete[]lct;
	return;

}
void changePasswordStaff(string usr)
{
	system("cls");
	string oldpwd, newpwd, cnewpwd, oldp;
	Staff* stf;
	int choice;
	int n;
	inputStaff(stf, n);
	int i;
	for (i = 0; i < n; i++)
	{
		if (stf[i].usr == usr)
		{
			oldp = stf[i].pwd;
			break;
		}
	}
	getPassword(oldpwd, newpwd, cnewpwd, oldp);
	if (oldp != oldpwd)
	{
		delete[]stf;
		cout << "\n1. Continue change password\n0. Back to main menu\nYour choice: ";
		cin >> choice;
		if (choice == 1) changePasswordStaff(usr);
		return;
	}
	else {
		if (newpwd != cnewpwd)
		{
			cout << "\nConfirm password is wrong!";
			delete[]stf;
			cout << "\n1. Continue change password\n0. Back to main menu\nYour choice: ";
			cin >> choice;
			if (choice == 1) changePasswordStaff(usr);
			return;
		}
		else {
			if (newpwd == oldpwd)
			{
				cout << "\nNew password is same as old!";
				delete[]stf;
				cout << "\n1. Continue change password\n0. Back to main menu\nYour choice: ";
				cin >> choice;
				if (choice == 1) changePasswordStaff(usr);
				return;
			}
			else {
				cout << "\nYour Password has been changed";
				cout << "\nPress any key to back...";
				_getch();
				system("cls");
			}
		}
	}
	stf[i].pwd = newpwd;
	ofstream fout;
	fout.open("Staff.txt");
	fout << n << endl << endl;
	for (i = 0; i < n; i++)
	{
		fout << stf[i].usr << endl;
		fout << stf[i].pwd << endl;
		fout << stf[i].name << endl;
		fout << stf[i].gen << endl << endl;
	}
	fout.close();
	delete[]stf;
	return;

}
void changePasswordStu(string usr)
{
	system("cls");
	string oldpwd, newpwd, cnewpwd, oldp;
	Stu* stu;
	int choice;
	int n;
	inputStudent(stu, n);
	int i;
	string cls;
	for (i = 0; i < n; i++)
	{
		if (stu[i].id == usr) {
			oldp = stu[i].pwd;
			cls = stu[i].cls;
			break;
		}
	}
	getPassword(oldpwd, newpwd, cnewpwd, oldp);
	if (oldp != oldpwd)
	{
		delete[]stu;
		cout << "\n1. Continue change password\n0. Back to main menu\nYour choice: ";
		cin >> choice;
		if (choice == 1) changePasswordStu(usr);
		return;
	}
	else {
		if (newpwd != cnewpwd)
		{
			cout << "\nConfirm password is wrong!";
			delete[]stu;
			cout << "\n1. Continue change password\n0. Back to main menu\nYour choice: ";
			cin >> choice;
			if (choice == 1) changePasswordStu(usr);
			return;
		}
		else {
			if (newpwd == oldpwd)
			{
				cout << "\nNew password is same as old!";
				delete[]stu;
				cout << "\n1. Continue change password\n0. Back to main menu\nYour choice: ";
				cin >> choice;
				if (choice == 1) changePasswordStu(usr);
				return;
			}
			else {
				cout << "\nYour Password has been changed";
				cout << "\nPress any key to back...";
				_getch();
				system("cls");
			}
		}
	}
	//change in class
	ifstream fin;
	int m;
	Stu* St;
	fin.open("Student-" + cls + ".txt");
	fin >> m;
	St = new Stu[n];
	for (int i = 0; i < n; i++)
	{
		getline(fin, St[i].id);
		getline(fin, St[i].id);
		getline(fin, St[i].id);
		getline(fin, St[i].pwd);
		getline(fin, St[i].name);
		getline(fin, St[i].dob);
		getline(fin, St[i].cls);
		fin >> St[i].stat;
	}
	fin.close();
	for (int j = 0; j < m; j++)
	{
		if (St[j].id == usr)
		{
			St[j].pwd = newpwd;
		}
	}
	StuToTxt(St, "Student-" + cls, m);
	delete[]St;

	//change in class list
	stu[i].pwd = newpwd;
	ofstream fout;
	fout.open("Student.txt");
	fout << n << endl;
	for (i = 0; i < n; i++)
	{
		fout << endl;
		fout << stu[i].id << endl;
		fout << stu[i].pwd << endl;
		fout << stu[i].name << endl;
		fout << stu[i].dob << endl;
		fout << stu[i].cls << endl;
		fout << stu[i].stat << endl;
	}
	fout.close();
	delete[]stu;
	//change in course
	string CurSem;
	getcurSem(CurSem);
	string* ClassList;
	int numClass;
	getListClass(ClassList, numClass);
	classSchedule* Sch;
	int numCourse;
	studentCourse* sC;
	int numStu;
	int numLesson;
	bool b;
	for (int icl = 0; icl < numClass; icl++) {
		b = getClassSch(ClassList[icl], Sch, numCourse);
		if (b == 0) continue;
		for (int ic = 0; ic < numCourse; ic++)
		{
			b = getStuCourse(sC, numStu, CurSem, ClassList[icl], Sch[ic].ID, numLesson);
			if (b == 0) continue;
			for (int is = 0; is < numStu; is++)
			{
				if (sC[is].ID == usr)
				{
					sC[is].pwd = newpwd;
					outputStuCourse(sC, numStu, CurSem, ClassList[icl], Sch[ic].ID, numLesson);
				}
			}
			for (int is = 0; is < numStu; is++)
				delete[]sC[is].Lss;
			delete[]sC;
		}
		delete[]Sch;
	}
	delete[]ClassList;
	return;
}

void getPassword(string & oldpwd, string & newpwd, string & cnewpwd, string oldp)
{
	char k;
	cout << "CHANGE PASSWORD\n";
	cout << "Old password:\t  ";
	while (1)
	{
		if (_kbhit()) {
			k = _getch();
			if (oldpwd.length() > 0 && k == 8)
			{
				oldpwd.pop_back();
				system("cls");
				cout << "CHANGE PASSWORD\n";
				cout << "Old password:\t  ";
				for (int i = 0; i < oldpwd.length(); i++)
					cout << "*";
			}
			else {
				if (k == 13)
					break;
				else {
					if (k != 8)
					{
						oldpwd += k;
						cout << "*";
					}
				}
			}
		}
	}
	if (oldpwd != oldp) 
	{ 
		cout << "\nWrong password!";	
		return;
	}
	cout << "\nNew password:\t  ";
	while (1)
	{
		if (_kbhit()) {
			k = _getch();
			if (newpwd.length() > 0 && k == 8)
			{
				newpwd.pop_back();
				system("cls");
				cout << "CHANGE PASSWORD\n";
				cout << "Old password:\t  ";
				for (int i = 0; i < oldpwd.length(); i++)
					cout << "*";
				cout << "\nNew password:\t  ";
				for (int i = 0; i < newpwd.length(); i++)
					cout << "*";
			}
			else {
				if (k == 13)
					break;
				else {
					if (k != 8)
					{
						newpwd += k;
						cout << "*";
					}
				}
			}
		}
	}
	cout << "\nConfirm password: ";
	while (1)
	{
		if (_kbhit()) {
			k = _getch();
			if (cnewpwd.length() > 0 && k == 8)
			{
				cnewpwd.pop_back();
				system("cls");
				cout << "CHANGE PASSWORD\n";
				cout << "Old password:\t  ";
				for (int i = 0; i < oldpwd.length(); i++)
					cout << "*";
				cout << "\nNew password:\t  ";
				for (int i = 0; i < newpwd.length(); i++)
					cout << "*";
				cout << "\nConfirm password: ";
				for (int i = 0; i < cnewpwd.length(); i++)
					cout << "*";
			}
			else {
				if (k == 13)
					break;
				else {
					if (k != 8)
					{
						cnewpwd += k;
						cout << "*";
					}
				}
			}
		}
	}
}