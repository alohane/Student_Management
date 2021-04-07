#include "S01.h"

int numline(string file) // return number of file line
{
	int numline = 0;
	char x;
	ifstream fin;
	fin.open(file);
	while (fin)
	{
		fin.get(x);
		if (x == '\n')
			numline++;
	}
	fin.close();
	return numline;
}

void inputListOfClass(string*& Class, int& n)
{
	fstream file;
	file.open("ClassList.txt");
	Class = new string[numline("ClassList.txt") - 1];
	file >> n;
	Class = new string[n];
	getline(file, Class[0], '\n');
	for (int i = 0; i < n; i++)
	{
		getline(file, Class[i], '\n');
	}
	file.close();
}

bool checkExistingClass(string Classname)
{
	string* Class;
	int n;
	inputListOfClass(Class, n);
	if (n == 0) return 0;
	for (int i = 0; i < n; i++)
	{
		if (Classname == Class[i])
			return 1;
	}
	return 0;
}

bool checkStudentID(string ID)
{
	Stu* St;
	int n;
	inputStudent(St, n);
	for (int i = 0; i < n; i++)
	{
		if (ID == St[i].id)
		{
			delete[]St;
			return 1;
		}
	}
	delete[]St;
	return 0;
}

void csvToStu(Stu*& Class, string filename, int& n)//convert file csv to struct student
{
	ifstream fin;
	fin.open(filename);
	n = numline(filename) - 2; //header line
	if (n == 0) return;
	Class = new Stu[n];
	getline(fin, Class[0].name, '\n');
	for (int i = 0; i < n; i++)
	{
		getline(fin, Class[i].id, ',');
		getline(fin, Class[i].id, ',');
		getline(fin, Class[i].name, ',');
		getline(fin, Class[i].dob, ',');
		for (int j = 0; j < Class[i].dob.length(); j++)
		{
			if (Class[i].dob[j] == '-')
				Class[i].dob[j] = ' ';
		}
		Class[i].pwd = Class[i].dob;
		for (int j = 0; j < Class[i].pwd.length(); j++)
		{
			if (Class[i].pwd[j] == ' ')
			{
				Class[i].pwd.erase(Class[i].pwd.begin() + j);
			}
		}
		getline(fin, Class[i].cls, '\n');
		Class[i].stat = 1;
	}
}

void StuToTxt(Stu* Class, string filename, int n)
{
	ofstream fout;
	fout.open(filename + ".txt");
	fout << n << endl;
	for (int i = 0; i < n; i++)
	{
		fout << endl;
		fout << Class[i].id << endl;
		fout << Class[i].pwd << endl;
		fout << Class[i].name << endl;
		fout << Class[i].dob << endl;
		fout << Class[i].cls << endl;
		fout << Class[i].stat << endl;
	}
}


void viewStudentOfClass(string cls)
{
	ifstream fin;
	fin.open("Student-" + cls + ".txt");
	int n;
	fin >> n;
	Stu* St;
	St = new Stu[n];
	system("cls");
	cout << "LIST STUDENTS IN CLASS " << cls << endl;
	cout << "\nNo\tID\t\tName\t\t\tDoB\t\tClass\n";
	for (int i = 0; i < n; i++)
	{
		getline(fin, St[i].id);
		getline(fin, St[i].id);
		if(St[i].id=="") getline(fin, St[i].id);
		getline(fin, St[i].pwd);
		getline(fin, St[i].name); getline(fin, St[i].dob); getline(fin, St[i].cls); fin >> St[i].stat;
		if (St[i].stat == 1) {
			cout << i + 1;
			cout << "\t" << St[i].id;
			cout << "\t" << St[i].name;
			if (St[i].name.length() < 16)cout << "\t";
			cout << "\t" << St[i].dob;
			cout << "\t" << St[i].cls;
			cout << endl;
		}
		else { i--; n--; }
	}
	fin.close();
	delete[]St;
}

void importStudentCSV(string usr)
{
	system("cls");
	cout << "IMPORT A CLASS FROM CSV FILE\n";
	cout << "Input new class's name (0 to back): ";
	string newclsname;
	cin >> newclsname;
	if (newclsname == "0")
	{
		system("cls");
		StaffClassMenu(usr, 1);
		return;
	}
	if (checkExistingClass(newclsname) == 1)
	{
		cout << "This class is existing!\nPress any key to back...";
		_getch();
		system("cls");
		StaffClassMenu(usr, 1);
		return;
	}
	string filelink;
	cout << "Input the link to file: ";
	cin >> filelink;
	ifstream file;
	file.open(filelink);
	if (!file.is_open())
	{
		cout << "Cannot open the file! Press any key to back...";
		_getch();
		system("cls");
		file.close();
		StaffClassMenu(usr, 1);
	}
	else{
		Stu* AllStu, * NewClassStu;
		int m;
		inputStudent(AllStu, m);
		int n;
		csvToStu(NewClassStu, filelink, n);
		for (int i = 0; i < n; i++) //check if id is existing
		{
			if (checkStudentID(NewClassStu[i].id) == 1)
			{
				cout << "Student ID " << NewClassStu[i].id << " is existing!\nPress any key to back...";
				_getch();
				system("cls");
				StaffClassMenu(usr, 1);
			}
		}
		string* Classlist;
		int numclass;
		inputListOfClass(Classlist, numclass);
		ofstream fout;
		fout.open("ClassList.txt");
		fout << numclass + 1 << endl;
		for (int i = 0; i < numclass; i++)
		{
			fout << Classlist[i] << endl;
		}
		fout << newclsname;
		fout.close();

		// input class to all student class
		fout.open("Student.txt");
		fout << n + m << endl;
		for (int i = 0; i < m; i++)
		{
			fout << endl;
			fout << AllStu[i].id << endl;
			fout << AllStu[i].pwd << endl;
			fout << AllStu[i].name << endl;
			fout << AllStu[i].dob << endl;
			fout << AllStu[i].cls << endl;
			fout << AllStu[i].stat << endl;
		}
		for (int i = 0; i < n; i++)
		{
			fout << endl;
			fout << NewClassStu[i].id << endl;
			fout << NewClassStu[i].pwd << endl;
			fout << NewClassStu[i].name << endl;
			fout << NewClassStu[i].dob << endl;
			fout << NewClassStu[i].cls << endl;
			fout << NewClassStu[i].stat << endl;
		}
		fout.close();

		// input student to class
		StuToTxt(NewClassStu, "Student-" + newclsname, n);

		cout << "Import Successfully! Press any key to continue...\n";
		delete[]AllStu;
		delete[]NewClassStu;
		delete[]Classlist;
		_getch();
		system("cls");
		file.close();
		StaffClassMenu(usr, 1);
	}
}