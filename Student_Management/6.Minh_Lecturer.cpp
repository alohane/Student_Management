#include "S02.h"

void PrintStudent(course info, int n, int i) 
{
	if (info.student.stat != 1)
		return;
	else
	{
		cout << setw(5) << left << i + 1;
		cout << setw(15) << info.student.id;
		cout << setw(20) << info.student.name;
		if (info.student.gender == 1)
			cout << setw(15) << "Male";
		else
			cout << setw(15) << "Female";
		cout << setw(20) << info.student.DoB;
		cout << endl;
	}
}

void ViewCurSem()
{
	system("cls");
	cout << endl;
	for (int i = 0; i < 40; i++) cout << " ";
	cout << "----------VIEW COURSES IN THE CURRENT SEMESTER----------" << endl;
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
		courseInfo* a;
		int n;
		fin >> n;
		a = new courseInfo[n];
		for (int i = 0; i < n; i++)
		{
			fin >> a[i].id;
			fin.ignore(100, '\n');
			getline(fin, a[i].name);
		}

		cout << "  " << setw(5) << left << "No." << setw(10) << left << "Course ID" << setw(20) << left << "Course name" << endl;
		cout << "--------------------------------------------------------------" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "  " << setw(5) << left << i+1 << setw(10) << left << a[i].id << setw(20) << left << a[i].name << endl;
		}
		system("pause");
	}
}

void ViewCourseStudent()
{
	system("cls");
	cout << endl;
	for (int i = 0; i < 40; i++) cout << " ";
	cout << "----------VIEW STUDENTS OF A COURSE----------" << endl;
	// Variables
	course* a;
	string courseCode, classname;
	int n;
	sem smt;
	LoadCurSem(smt);

	courseCode = CheckCourse(courseCode);
	if (courseCode == "N")
		return;
	classname = CheckClass(classname);
	if (classname == "N")
		return;
	else
	{
		string x = smt.year + "-" + smt.sem + "-" + classname + "-" + courseCode + "-" + "student.txt";
		//View students of a course
		if (Load(a, n, x) == -1)
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
				temp = 1;
			}
			if (temp == 0)
			{
				cout << "There is no student in this course" << endl;
			}
			delete[]a;
			system("pause");
		}
	}
}

void ViewAttendanceListLecturer()
{
	system("cls");
	cout << endl;
	for (int i = 0; i < 40; i++) cout << " ";
	cout << "----------VIEW ATTENDANCE LIST OF A COURSES----------" << endl;
	// Variables
	course* a;
	string courseCode, classname;
	sem smt;
	LoadCurSem(smt);
	int n;

	courseCode = CheckCourse(courseCode);
	if (courseCode == "N")
		return;
	classname = CheckClass(classname);
	if (classname == "N")
		return;
	else
	{
		//View attendance list
		string x = smt.year + "-" + smt.sem + "-" + classname + "-" + courseCode + "-" + "student.txt";
		if (Load(a, n, x) != 1)
		{
			cout << "No student in this course or class" << endl;
			system("pause");
			return;
		}
		else
		{
			int temp = 0;
			cout << endl;
			cout << setw(5) << "No" << setw(15) << left << "ID" << setw(20) << "Name" << setw(10) << "Gender";
			cout << setw(15) << right << "Date" << setw(15) << "Time" << setw(20) << "Status(x/-)" << endl;
			cout << "+-------------------------------------------------------------------------------------------------------------------+" << endl;

			for (int i = 0; i < n; i++)
			{
				PrintAttendance(a[i], n, i);
			}
			system("pause");
			delete[]a;
		}
	}
}

