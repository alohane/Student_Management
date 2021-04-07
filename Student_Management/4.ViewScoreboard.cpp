#include "S01.h"
#include "S02.h"

void LoadCurSem(sem& smt)
{
	ifstream fin("CurrentSemester.txt");
	fin >> smt.year >> smt.sem;
}

int Load(course*& a, int& n, string& courseCode)
{
	ifstream fin;
	fin.open(courseCode.c_str());		
	if (!fin.is_open())								
	{										
		return -2;
	}
	else
	{
		fin >> n;
		if (fin.fail())
			return -2;
		a = new course[n];
		for (int i = 0; i < n; i++)
		{
			fin >> a[i].student.id;
			fin >> a[i].student.password;
			fin.ignore(100, '\n');
			getline(fin, a[i].student.name);
			getline(fin, a[i].student.DoB);
			fin >> a[i].student.gender;

			fin >> a[i].mark.midterm;
			fin >> a[i].mark.bonus;
			fin >> a[i].mark.final;
			fin >> a[i].mark.total;

			for (int j = 0; j < 30; j++)
			{
				fin >> a[i].attendance[j].year;
				if (a[i].attendance[j].year != 1 && a[i].attendance[j].year != -1 && a[i].attendance[j].year != 0)
				{
					fin >> a[i].attendance[j].month;
					fin >> a[i].attendance[j].day;
					fin >> a[i].attendance[j].startHour;
					fin >> a[i].attendance[j].startMin;
					fin >> a[i].attendance[j].endHour;
					fin >> a[i].attendance[j].endMin;
					fin >> a[i].attendance[j].stat;
				}
				else
				{
					a[i].student.stat = a[i].attendance[j].year;
					break;
				}
			}
		}
	}
	fin.close();
	return 1;
}

void SaveScore(course info, int n, fstream& fout, int i)
{
	if (info.student.stat != 1)
		return;
	else
	{
		fout << i + 1 << ',';
		fout << info.student.id << ',';
		fout << info.student.name << ',';

		fout << info.mark.midterm << ',';
		fout << info.mark.bonus << ',';
		fout << info.mark.final << ',';
		fout << info.mark.total;
		fout << endl;
	}
}

void PrintScore(course info, int n, int i)
{
	if (info.student.stat != 1) return;
	cout << setw(5) << i + 1;
	cout << setw(15) << info.student.id;
	cout << setw(20) << info.student.name;
	if (info.student.gender == 1)
		cout << setw(15) << "Male";
	else
		cout << setw(15) << "Female";

	cout << setw(15) << info.mark.midterm;
	cout << setw(15) << info.mark.bonus;
	cout << setw(15) << info.mark.final;
	cout << setw(15) << info.mark.total;
	cout << endl;
}

string CheckCourse(string courseCode)
{
	sem smt;
	LoadCurSem(smt);
	string x = smt.year + "-" + smt.sem + "-" + "courseList.txt";
	ifstream fin;
	fin.open(x);
	if (!fin.is_open())
	{
		cout << "Cannot open course list" << endl;
	}
	else
	{
		courseInfo* a;
		int n, idcheck;
		fin >> n;
		a = new courseInfo[n];
		for (int i = 0; i < n; i++)
		{
			fin >> a[i].id;
			fin.ignore(100, '\n');
			getline(fin, a[i].name);
		}

		cout << "  " << setw(5) << left << "No." << setw(15) << left << "Course ID" << setw(20) << left << "Course name" << endl;
		cout << "--------------------------------------------------------------" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "  " << setw(5) << left << i + 1 << setw(15) << left << a[i].id << setw(20) << left << a[i].name << endl;
		}
		cout << endl << "Enter No. of the course code(0/1/2/3), 0 to return: ";
		cin >> idcheck;
		idcheck--;
		
		while (idcheck < -1 || idcheck > n - 1)
		{
			cout << "Choose again: ";
			cin >> idcheck;
			idcheck--;
		}
		if (idcheck == -1)
			return "N";
		else
			courseCode = a[idcheck].id;
		delete[]a;
	}
	fin.close();
	return courseCode;
}

string CheckClass(string classname)		
{
	ifstream fin;
	fin.open("ClassList.txt");
	if (!fin.is_open())
	{
		cout << "Cannot open file";
	}
	else
	{
		string* a;
		int n, idcheck;
		fin >> n;
		a = new string[n];
		for (int i = 0; i < n; i++)
		{
			fin >> a[i];
		}

		cout << endl;
		cout << "  " << setw(5) << left << "No." << setw(10) << left << "Class" << endl;
		cout << "---------------------------------" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "  " << setw(5) << left << i + 1 << setw(10) << left << a[i] << endl;
		}
		cout << endl << "Enter No. of the class name (0/1/2/3...), 0 to return: ";
		cin >> idcheck;
		idcheck--;
		while (idcheck < -1 || idcheck > n - 1)
		{
			cout << "Choose again: ";
			cin >> idcheck;
			idcheck--;
		}
		if (idcheck == -1)
		{
			return  "N";
		}
		else
		{
			classname = a[idcheck];
		}
		delete[]a;
	}
	fin.close();
	return classname;
}

void ViewScoreBoard() 
{
	system("cls");
	cout << endl;
	for (int i = 0; i < 40; i++)
	{
		cout << " ";
	}
	cout << "----------VIEW SCORE BOARD----------" << endl << endl;
	// Variables
	course* a;
	string classname, courseCode;
	int n;
	sem smt;
	LoadCurSem(smt);
	courseCode = CheckCourse(courseCode);
	if (courseCode == "N")
		return;
	classname = CheckClass(classname);
	if (classname == "N")
		return;
	string x = smt.year + "-" + smt.sem + "-" + classname + "-" + courseCode + "-" + "student.txt";

	//View Score Board
	if (Load(a, n, x) != 1)
	{
		cout << "No student in this course or class" << endl;
		system("pause");
		return;
	}
	else
	{
		cout << endl;
		cout << setw(5) << "No." << setw(15) << "ID" << setw(20) << "Name" << setw(15) << "Gender";
		cout << setw(15) << "Midterm" << setw(15) << "Bonus" << setw(15) << "Final" << setw(15) << "Total" << endl;
		cout << "+-------------------------------------------------------------------------------------------------------------------+" << endl;
		for (int i = 0; i < n; i++)
		{
			PrintScore(a[i], n, i);
		}

		//Export to a csv file
		string input;
		cout << endl << "Do you want to export this to a csv file (Y/N): ";
		cin >> input;
		while (input != "Y" && input != "N")
		{
			cout << "Choose (Y/N): ";
			cin >> input;
		}
		if (input == "Y")
		{
			fstream fout;
			string file;
			cout << "Enter name of the csv file name you want to save(.csv), 0 to exit: ";			
			cin >> file;
			
			if (file == "0")
				return;
			else
			{
				fout.open(file);
				if (!fout.is_open())
				{
					cout << "Cannot open file " << endl;
					system("pause");
				}
				else
				{
					fout << "No." << ',' << "ID" << ',' << "Name" << ',';
					fout << "Midterm" << ',' << "Bonus" << ',' << "Final" << ',' << "Total" << endl;
					for (int i = 0; i < n; i++)
					{
						SaveScore(a[i], n, fout, i);
					}
					cout << "Save successfully, open file " << '"' << file << '"' << " to see the result" << endl;
					system("pause");
				}
				delete[]a;
				fout.close();
			}
		}
		else
		{
			delete[]a;
			return;
		}
	}
}

void ExportScoreBoard()
{
	system("cls");
	cout << endl;
	for (int i = 0; i < 40; i++) cout << " ";
	cout << "----------EXPORT SCORE BOARD----------" << endl << endl;
	// Variables
	course* a;
	string classname, courseCode;
	int n;
	sem smt;
	LoadCurSem(smt);
	courseCode = CheckCourse(courseCode);
	if (courseCode == "N")
		return;
	classname = CheckClass(classname);
	if (classname == "N")
		return;

	string x = smt.year + "-" + smt.sem + "-" + classname + "-" + courseCode + "-" + "student.txt";
	//Save Score Board
	if (Load(a, n, x) == -1)
	{
		cout << "No student in this course or class" << endl;
		system("pause");
		return;
	}
	else
	{
		int temp = 0;

		cout << endl;
		cout << setw(5) << "No." << setw(15) << "ID" << setw(20) << "Name" << setw(15) << "Gender";
		cout << setw(15) << "Midterm" << setw(15) << "Bonus" << setw(15) << "Final" << setw(15) << "Total" << endl;
		cout << "+-------------------------------------------------------------------------------------------------------------------+" << endl;
		for (int i = 0; i < n; i++)
		{
			PrintScore(a[i], n, i);
			temp = 1;
		}
		if (temp == 0)
		{
			cout << "No student in class " << classname << " is in this course" << endl;
		}
		else
		{
			
			string fileName;
			cout << endl << "Enter name of the csv file name you want to save(.csv), 0 to exit: ";
			cin >> fileName;
			if (fileName == "0")
				return;
			else
			{
				fstream fout(fileName);
				if(!fout.is_open())
				{
					cout << "Cannot open file " << endl;
					system("pause");
				}
				else
				{
					int flag = 0;
					fout << "No." << ',' << "ID" << ',' << "Name" << ',';
					fout << "Midterm" << ',' << "Bonus" << ',' << "Final" << ',' << "Total" << endl;
					for (int i = 0; i < n; i++)
					{
						SaveScore(a[i], n, fout, i);
						flag = 1;
					}
					if (flag == 0)
					{
						fout << "No student in class " << classname << " is in this course" << endl;
					}
					cout << "Save successfully, open file " << '"' << fileName << '"' << " to see the result" << endl;
					system("pause");
				}
				fout.close();
			}
			delete[]a;
			
		}
	}
}
