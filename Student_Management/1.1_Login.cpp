#include "S01.h"

void secretPwd(string usr, string& pwd)
{
	char k;
	while (1)
	{
		if (_kbhit()) {
			k = _getch();
			if (pwd.length() > 0 && k == 8)
			{
				pwd.pop_back();
				system("cls");
				cout << "username: " << usr << endl;
				cout << "password: ";
				for (int i = 0; i < pwd.length(); i++)
					cout << "*";
			}
			else {
				if (k == 13)
					break;
				else {
					if (k != 8)
					{
						pwd += k;
						cout << "*";
					}
				}
			}
		}
	}
}
void inputStudent(Stu*& St, int& n)
{
	ifstream fin;
	fin.open("Student.txt");
	fin >> n;
	St = new Stu[n];
	for (int i = 0; i < n; i++)
	{
		getline(fin, St[i].id);
		if (St[i].id == "") getline(fin, St[i].id);
		if (St[i].id == "") getline(fin, St[i].id);
		getline(fin, St[i].pwd);
		getline(fin, St[i].name);
		getline(fin, St[i].dob);
		getline(fin, St[i].cls);
		fin >> St[i].stat;
	}
	fin.close();
}
void inputLecturer(Lect*& lct, int& n)
{
	ifstream fin;
	fin.open("Lecturer.txt");
	fin >> n;
	lct = new Lect[n];
	for (int i = 0; i < n; i++)
	{
		getline(fin, lct[i].usr);
		if (lct[i].usr == "") getline(fin, lct[i].usr);
		if (lct[i].usr == "")getline(fin, lct[i].usr);
		getline(fin, lct[i].pwd);
		getline(fin, lct[i].name);
		getline(fin, lct[i].lvl);
		fin >> lct[i].gen;
	}
}
void inputStaff(Staff*& stf, int&n)
{
	ifstream fin;
	fin.open("Staff.txt");
	fin >> n;
	stf = new Staff[n];
	for (int i = 0; i < n; i++)
	{
		getline(fin, stf[i].usr);
		if (stf[i].usr == "") getline(fin, stf[i].usr);
		if (stf[i].usr == "") getline(fin, stf[i].usr);
		getline(fin, stf[i].pwd);
		getline(fin, stf[i].name);
		fin >> stf[i].gen;
	}
}
void checkStaff(string usr, string pwd, int& type, bool& gen, string& name)
{
	Staff* stf;
	int n;
	inputStaff(stf,n);
	for (int i = 0; i < n; i++)
	{
		if (usr == stf[i].usr && pwd == stf[i].pwd)
		{
			type = 1;
			name = stf[i].name;
			gen = stf[i].gen;
			break;
		}
	}
	delete[]stf;
}
void checkLecturer(string usr, string pwd, int& type, bool&gen, string&name)
{
	Lect* lct;
	int n;
	inputLecturer(lct, n);
	for (int i = 0; i < n; i++)
	{
		if (usr == lct[i].usr && pwd == lct[i].pwd)
		{
			type = 2;
			name = lct[i].name;
			gen = lct[i].gen;
			break;
		}
	}
	delete[]lct;
}
void checkStudent(string usr, string pwd, int& type, string& name)
{
	Stu* St;
	int n;
	inputStudent(St, n);
	for (int i = 0; i < n; i++)
	{
		if (usr == St[i].id && pwd == St[i].pwd)
		{
			type = 3;
			name = St[i].name;
			break;
		}
	}
	delete[]St;
}
void Login(int& type, string& usr)
{
	type = 0; //1:staff 2:lecturer 3:student
	bool gen = 0;
	string name;
	string pwd;
	cout << "username: "; cin >> usr;
	cout << "password: "; secretPwd(usr, pwd);
	checkStaff(usr,pwd,type, gen, name);
	if (type == 0)
		checkLecturer(usr, pwd, type, gen, name);
	if (type == 0)
		checkStudent(usr, pwd, type, name);
	if (type == 0) // login false
	{
		cout << "\nUsername or password is wrong!!\nPress any key to continue...\n";
		_getch();
		system("cls");
		ShowLogoutMenu();
	}
	else {system("cls"); cout << "Login successfully" << endl; }
	if (type == 1 || type == 2)
	{
		cout << "Welcome, ";
		if (gen == 1) cout << "Ms.";
		if (gen == 0)cout << "Mr.";
		cout << name << endl;
	}
	if (type == 3)
	{
		cout << "Welcome, ";
		cout << name<<endl;
	}
}