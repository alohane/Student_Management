#include "S02.h"

void Save(course*& a, int& n, string& courseCode)
{
	fstream fout;
	fout.open(courseCode.c_str());
	if (!fout.is_open())
	{
		return;
	}
	else
	{
		fout << n << endl;
		for (int i = 0; i < n; i++)
		{
			fout << a[i].student.id << endl;
			fout << a[i].student.password << endl;
			fout << a[i].student.name << endl;
			fout << a[i].student.DoB << endl;
			fout << a[i].student.gender << endl;

			fout << a[i].mark.midterm << endl;
			fout << a[i].mark.bonus << endl;
			fout << a[i].mark.final << endl;
			fout << a[i].mark.total << endl;

			for (int j = 0; j < 30; j++)
			{
				if (a[i].attendance[j].year != 1 && a[i].attendance[j].year != -1 && a[i].attendance[j].year != 0)
				{
					fout << a[i].attendance[j].year << " ";
					fout << a[i].attendance[j].month << " ";
					fout << a[i].attendance[j].day << " ";
					fout << a[i].attendance[j].startHour << " ";
					fout << a[i].attendance[j].startMin << " ";
					fout << a[i].attendance[j].endHour << " ";
					fout << a[i].attendance[j].endMin << " ";
					fout << a[i].attendance[j].stat << endl;
				}
				else
				{
					fout << a[i].student.stat << endl;
					break;
				}
			}
			fout << endl << endl;
		}
	}
	fout.close();
}

void RemoveMainClass(ifstream& fin,int& n, string classname, int removeID)
{
	STU* a;
	a = new STU[n];
	for (int i = 0; i < n; i++)
	{
		fin >> a[i].id;
		fin >> a[i].password;
		fin.ignore(100, '\n');
		getline(fin, a[i].name);
		getline(fin, a[i].DoB);
		fin >> a[i].Class;
		fin >> a[i].stat;
	}
	
	for (int i = 0; i < n; i++)
	{
		if (a[i].id == removeID)
		{
			a[i].stat = 0;
		}
	}
	fstream fout;
	fout.open("Student-" + classname + ".txt");
	fout << n << endl;
	for (int i = 0; i < n; i++)
	{
		fout << a[i].id << endl;
		fout << a[i].password << endl;
		fout << a[i].name << endl;
		fout << a[i].DoB << endl;
		fout << a[i].Class << endl;
		fout << a[i].stat << endl << endl;
	}
	fout.close();
	delete[]a;

}

void RemoveStudentDatabase(int removeID)
{
	int n;
	STU* a;
	ifstream fin;
	fin.open("student.txt");
	if (!fin.is_open())
		return;
	else
	{
		fin >> n;
		a = new STU[n];
		for (int i = 0; i < n; i++)
		{
			fin >> a[i].id;
			fin >> a[i].password;
			fin.ignore(100, '\n');
			getline(fin, a[i].name);
			getline(fin, a[i].DoB);
			fin >> a[i].Class;
			fin >> a[i].stat;
		}

		for (int i = 0; i < n; i++)
		{
			if (a[i].id == removeID)
			{
				a[i].stat = 0;
			}
		}
		fstream fout;
		fout.open("Student.txt");
		if (!fout.is_open())
		{
			return;
		}
		else
		{
			fout << n << endl;
			for (int i = 0; i < n; i++)
			{
				fout << a[i].id << endl;
				fout << a[i].password << endl;
				fout << a[i].name << endl;
				fout << a[i].DoB << endl;
				fout << a[i].Class << endl;
				fout << a[i].stat << endl << endl;
			}
		}
		fout.close();
		delete[]a;
	}
}

void LoadCourseList(courseInfo*& courseList, int& numCourse)
{
	sem smt;
	LoadCurSem(smt);
	string x = smt.year + "-" + smt.sem + "-" + "courseList.txt";
	ifstream fin;
	fin.open(x);
	if (!fin.is_open())
	{
		cout << "Cannot open file" << endl;
	}
	else
	{
		fin >> numCourse;
		courseList = new courseInfo[numCourse];
		for (int i = 0; i < numCourse; i++)
		{
			fin >> courseList[i].id;
			fin.ignore(100, '\n');
			getline(fin, courseList[i].name);
		}
	}
}

void LoadClassList(string*& classList, int& numClass)
{
	ifstream fin;
	fin.open("ClassList.txt");
	if (fin.is_open())
	{
		fin >> numClass;
		classList = new string[numClass];
		for (int i = 0; i < numClass; i++)
		{
			fin >> classList[i];
		}
	}
	else
	{
		return;
	}
}

void RemoveStudent()
{
	system("cls");
	//change in main class
	cout << endl;
	for (int i = 0; i < 40; i++) cout << " ";
	cout << "----------REMOVE A STUDENT----------" << endl << endl;
	
	string courseCode, classname;
	course* a;
	int idCheck, n;
	int removeID;

	courseCode = CheckCourse(courseCode);
	if (courseCode == "N")
		return;
	classname = CheckClass(classname);
	if (classname == "N")
		return;
	sem smt;
	LoadCurSem(smt);

	ifstream fin;
	fin.open("Student-" + classname + ".txt");
	fin >> n;
	if (fin.fail())
	{
		cout << "No student in this course or class" << endl;
		system("pause");
		return;
	}
	string x = smt.year + "-" + smt.sem + "-" + classname + "-" + courseCode + "-" + "student.txt";
	//View students of a course
	if (Load(a, n, x) != 1)
	{
		cout << "No student in this course or class" << endl;
		system("pause");
		return;
	}
	else
	{
		cout << endl;
		cout << setw(5) << left << "No." << setw(15) << "ID" << setw(20) << "Name" << setw(15) << "Gender" << setw(20) << "DoB" << endl;
		cout << "+----------------------------------------------------------------+" << endl;
		int temp = 0;
		for (int i = 0; i < n; i++)
		{
			PrintStudent(a[i], n, i);
		}
		

	}
	cout << endl << "Enter No. of the student you want to remove (0/1/2/3..), 0 to exit: ";
	cin >> idCheck;
	idCheck--;
	if (idCheck == -1)
		return;
	while (idCheck < -1 || idCheck > n - 1 || a[idCheck].student.stat!= 1)
	{
		cout << "Choose again: ";
		cin >> idCheck;
		idCheck--;
		if (idCheck == -1)
			return;
	}
	
	removeID = a[idCheck].student.id;
	cout << "ID need to remove: " << removeID << endl;
	system("pause");
	delete[]a;
	// Change in main class
	RemoveMainClass(fin, n, classname, removeID);\
	fin.close();
	RemoveStudentDatabase(removeID);


	//change in course
	courseInfo* courseList;
	int numCourse;
	string* classList;
	string fileName;
	int numClass;
	course* b;
	int m;
	LoadCourseList(courseList, numCourse);
	LoadClassList(classList, numClass);
	for (int i = 0; i < numClass; i++)
	{
		for (int j = 0; j < numCourse; j++)
		{
			fileName = smt.year + "-" + smt.sem + "-" + classList[i] + "-" + courseList[j].id + "-" + "student.txt";
			if (Load(b, m, fileName) != 1)
				continue;
			else
			{
				for (int k = 0; k < m; k++)
				{
					if (b[k].student.id == removeID)
					{
						b[k].student.stat = 0;
						Save(b, m, fileName);
						delete[]b;
					}
					else
					{
						continue;
					}
				}
				
			}
		}
	}

	return;
}