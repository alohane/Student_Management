#include "S02.h"
#include "S01.h"

void ViewScoreBoardLecturer()
{
	system("cls");
	cout << endl;
	for (int i = 0; i < 40; i++) cout << " ";
	cout << "----------VIEW SCORE BOARD----------" << endl;
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

			system("pause");
			delete[]a;
		}
	}
}

void EditAttendance()
{
	system("cls");
	cout << endl;
	for (int i = 0; i < 40; i++) cout << " ";
	cout << "----------EDIT ATTENDANCE----------" << endl;
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
		//Edit attendance
		if (Load(a, n, x) != 1)
		{
			cout << "No student in this course or class" << endl;
			system("pause");
			return;
		}
		else
		{
			int flag = 0;
			int idCheck = 0;
			string input;

			cout << endl;
			cout << setw(5) << left << "No" << setw(15) << "ID" << setw(20) << "Name" << setw(20) << "Gender";
			cout << setw(15) << "Date" << setw(15) << "Time" << setw(20) << "Status(x/-)" << endl;
			cout << "+-------------------------------------------------------------------------------------------------------------------+" << endl;

			for (int i = 0; i < n; i++)
			{
				PrintAttendance(a[i], n, i);
			}
			do
			{
				cout << endl << "Enter No. of the student you want to edit attendance (0/1/2/3..), 0 to exit: ";
				cin >> idCheck;
				idCheck--;
				if (idCheck == -1)
					return;
				while (idCheck < -1 || idCheck > n - 1 || a[idCheck].student.stat != 1)
				{								
					cout << "Choose again: ";
					cin >> idCheck;
					idCheck--;
					if (idCheck == -1)
						return;
				}
				
				for (int j = 0; j < 30; j++)
				{
					if (a[idCheck].attendance[j].year != -1 && a[idCheck].attendance[j].year != 0 && a[idCheck].attendance[j].year != 1)
					{
						cout << a[idCheck].attendance[j].year << "/";
						cout << a[idCheck].attendance[j].month << "/";
						cout << a[idCheck].attendance[j].day << " ";
						cout << a[idCheck].attendance[j].startHour << ":";
						cout << a[idCheck].attendance[j].startMin << " ";
						cout << a[idCheck].attendance[j].endHour << ":";
						cout << a[idCheck].attendance[j].endMin << " ";
						cout << "Attendance status(-1/1): ";
						cin >> a[idCheck].attendance[j].stat;
						while (a[idCheck].attendance[j].stat != -1 && a[idCheck].attendance[j].stat != 1)
						{
							cout << "Enter Attendance status again(-1/1): ";
							cin >> a[idCheck].attendance[j].stat;
						}
					}
					else
						break;
				}
				cout << endl;
				flag = 1;
				cout << "-----UPDATED SUCCESSFULLY-----" << endl << endl;


				cout << "Do you want to edit more ? (Y/N): ";
				cin >> input;
				while (input != "Y" && input != "N")
				{
					cout << "Choose (Y/N): ";
					cin >> input;
				}

			} while (input == "Y");

			fstream fout;
			fout.open(x);
			fout << n << endl;
			for (int i = 0; i < n; i++)
			{
				fout << a[i].student.id << endl << a[i].student.password << endl << a[i].student.name << endl << a[i].student.DoB << endl << a[i].student.gender << endl;
				fout << a[i].mark.midterm << endl << a[i].mark.bonus << endl << a[i].mark.final << endl << a[i].mark.total << endl;
				for (int j = 0; j < 30; j++)
				{
					if (a[i].attendance[j].year != -1 && a[i].attendance[j].year != 1 && a[i].attendance[j].year != 0)
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
						break;
					}
				}
				fout << a[i].student.stat << endl << endl;
			}
			fout.close();
			delete[]a;
		}
	}
}

void EditScoreboard()
{
	system("cls");
	cout << endl;
	for (int i = 0; i < 40; i++) cout << " ";
	cout << "----------EDIT SCORE BOARD----------" << endl;
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
		//Edit attendance
		string x = smt.year + "-" + smt.sem + "-" + classname + "-" + courseCode + "-" + "student.txt";
		if (Load(a, n, x) != 1)
		{
			cout << "No student in this course or class" << endl;
			system("pause");
			return;
		}
		else
		{
			int flag = 0;
			int idCheck = 0;
			int remove = 0;
			string input;
			cout << endl;
			cout << setw(5) << "No." << setw(15) << "ID" << setw(20) << "Name" << setw(15) << "Gender";
			cout << setw(15) << "Midterm" << setw(15) << "Bonus" << setw(15) << "Final" << setw(15) << "Total" << endl;
			cout << "+-------------------------------------------------------------------------------------------------------------------+" << endl;
			for (int i = 0; i < n; i++)
			{
				PrintScore(a[i], n, i);
			}
			do
			{
				cout << endl << "Enter No. of the student you want to edit score (0/1/2/3), 0 to exit: ";
				cin >> idCheck;
				idCheck--;
				if (idCheck == -1)
					return;
				while(idCheck < -1 || idCheck > n - 1 || a[idCheck].student.stat != 1)
				{
					cout << "Choose again: ";
					cin >> idCheck;
					idCheck--;
					if (idCheck == -1)
						return;
				}
				
				cout << "Enter midterm score: ";
				cin >> a[idCheck].mark.midterm;
				while (a[idCheck].mark.midterm < 0.0 || a[idCheck].mark.midterm > 10.0)
				{
					cout << "Midterm score is not approriate, enter again(0->10): ";
					cin >> a[idCheck].mark.midterm;
				}

				cout << "Enter bonus score: ";
				cin >> a[idCheck].mark.bonus;
				while (a[idCheck].mark.bonus < 0.0 || a[idCheck].mark.bonus > 10.0)
				{
					cout << "Bonus score is not approriate, enter again(0->10): ";
					cin >> a[idCheck].mark.bonus;
				}

				cout << "Enter final score: ";
				cin >> a[idCheck].mark.final;
				while (a[idCheck].mark.final < 0.0 || a[idCheck].mark.final > 10.0)
				{
					cout << "Final score is not approriate, enter again(0->10): ";
					cin >> a[idCheck].mark.final;
				}

				cout << "Enter total score: ";
				cin >> a[idCheck].mark.total;
				while (a[idCheck].mark.total < 0.0 || a[idCheck].mark.total > 10.0)
				{
					cout << "Total score is not approriate, enter again(0->10): ";
					cin >> a[idCheck].mark.total;
				}

				cout << endl;
				cout << "-----UPDATED SUCCESSFULLY-----" << endl << endl;
				flag = 1;


				if (flag == 0)
				{
					cout << "The student ID is incorrect or the student is not in this course" << endl;
				}
				cout << "Do you want to edit more ? (Y/N): ";
				cin >> input;
				while (input != "Y" && input != "N")
				{
					cout << "Choose (Y/N): ";
					cin >> input;
				}

			} while (input == "Y");

			fstream fout;
			fout.open(x);
			fout << n << endl;
			for (int i = 0; i < n; i++)
			{
				fout << a[i].student.id << endl << a[i].student.password << endl << a[i].student.name << endl << a[i].student.DoB << endl << a[i].student.gender << endl;
				fout << a[i].mark.midterm << endl << a[i].mark.bonus << endl << a[i].mark.final << endl << a[i].mark.total << endl;
				for (int j = 0; j < 30; j++)
				{
					if (a[i].attendance[j].year != -1 && a[i].attendance[j].year != 1)
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
						break;
				}
				fout << a[i].student.stat << endl << endl;
			}
			fout.close();
			delete[]a;
		}
	}
}

int ImportCSV(course*& b, int& m, string& courseCode)
{
	ifstream fin;
	fin.open(courseCode.c_str());
	if (!fin.is_open())								
	{										
		return -1;
	}
	else
	{
		string line;
		m = numline(courseCode) - 2;
		b = new course[m];
		getline(fin, line,'\n');
		for (int i = 0; i < m; i++)
		{
			fin >> b[i].student.number;

			fin.ignore(100, ',');
			fin >> b[i].student.id;

			fin.ignore(100, ',');
			getline(fin,b[i].student.name,',');
	
			fin >> b[i].mark.midterm;

			fin.ignore(100, ',');
			fin >> b[i].mark.bonus;
			

			fin.ignore(100, ',');
			fin >> b[i].mark.final;

			fin.ignore(100, ',');
			fin >> b[i].mark.total;
		

		}
		fin.close();
		return 1;
	}
}

void ImportScoreboard()
{
	system("cls");
	cout << endl;
	for (int i = 0; i < 40; i++) cout << " ";
	cout << "----------IMPORT SCOREBOARD FROM A CSV FILE----------" << endl;
	int m, n;
	string fileName, courseCode, classname, temp;
	course* a, * b;
	cout << "Enter the CSV FILE you want to import (.csv), 0 to exit: ";
	cin >> fileName;
	if (fileName == "0")
		return;
	
	ifstream fin;
	fin.open(fileName.c_str());
	while (!fin.is_open())
	{
		string input;
		cout << "File name is incorrect or not existed, do you want to try again ? (Y/N): ";
		cin >> input;
		while (input != "Y" && input != "N")
		{
			cout << "Choose (Y/N): ";
			cin >> input;
		}
		if (input == "Y")
		{
			cout << "Enter the CSV FILE you want to import (.csv), 0 to exit: ";
			cin >> fileName;
			if (fileName == "0")
				return;
			fin.open(fileName.c_str());

		}
		else return;
	}
	
	if (ImportCSV(b, m, fileName) != 1)
	{
		cout << "Cannot open file csv " << endl;
	}
	cout << endl;
	cout << setw(5) << "No" << setw(15) << "ID" << setw(20) << "Name" << setw(15) << "Gender";
	cout << setw(15) << "Midterm" << setw(15) << "Bonus" << setw(15) << "Final" << setw(15) << "Total" << endl;
	cout << "+-------------------------------------------------------------------------------------------------------------------+" << endl;
	
	for (int j = 0; j < m; j++)
	{
		cout << setw(5) << b[j].student.number;
		cout << setw(15) << b[j].student.id;
		cout << setw(20) << b[j].student.name;
		
		cout << setw(15) << b[j].mark.midterm;
		cout << setw(15) << b[j].mark.bonus;
		cout << setw(15) << b[j].mark.final;
		cout << setw(15) << b[j].mark.total;
		cout << endl;
	}

	sem smt;
	LoadCurSem(smt);
	cout << endl << "Choose the course code and class you want to import scoreboard to" << endl;
	courseCode = CheckCourse(courseCode);
	if (courseCode == "N")
		return;
	classname = CheckClass(classname);
	if (classname == "N")
		return;
	else
	{
		string x = smt.year + "-" + smt.sem + "-" + classname + "-" + courseCode + "-" + "student.txt";
		if (Load(a, n, x) != 1)
		{
			cout << "No student in this course or class" << endl;
			system("pause");
			return;
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					if (a[i].student.id == b[j].student.id)
					{
						a[i].mark.midterm = b[j].mark.midterm;
						a[i].mark.bonus = b[j].mark.bonus;
						a[i].mark.final = b[j].mark.final;
						a[i].mark.total = b[j].mark.total;
					}
				}
			}
			fstream fout;
			fout.open(x);
			if (!fout.is_open())
			{
				cout << "Cannot open the file of class " << classname << "and course code " << courseCode << endl;
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
						if (a[i].attendance[j].year != -1 && a[i].attendance[j].year != 0 && a[i].attendance[j].year != 1)
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
					fout << endl;
				}
				fout.close();
			}
			cout << endl;
			for (int i = 0; i < 40; i++) cout << " ";
			cout  << "----IMPORT SUCCESSFULLY----" << endl;
			system("pause");
		}
		delete[]a;
	}
	delete[]b;
}