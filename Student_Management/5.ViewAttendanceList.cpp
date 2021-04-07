#include "S02.h"

void SaveAttendance(course info, int n, fstream& fout, int i)
{
	if (info.student.stat != 1)
		return;
	else
	{
		fout << i + 1 << ',';
		fout << info.student.id << ',';
		fout << info.student.name << ',';

		if (info.attendance[0].year != -1 && info.attendance[0].year != 1 && info.attendance[0].year != 0)
		{
			fout << info.attendance[0].year << "/";
			fout << info.attendance[0].month << "/";
			fout << info.attendance[0].day << ',';

			fout << info.attendance[0].startHour << ":";
			fout << info.attendance[0].startMin << "-";
			fout << info.attendance[0].endHour << ":";
			fout << info.attendance[0].endMin << ',';
			fout << info.attendance[0].stat << endl;

		}
		for (int j = 1; j < 30; j++)
		{
			fout << ',' << ',' << ',';
			if (info.attendance[j].year != -1 && info.attendance[j].year != 1 && info.attendance[j].year != 0)
			{
				fout << info.attendance[j].year << "/";
				fout << info.attendance[j].month << "/";
				fout << info.attendance[j].day << ',';
				fout << info.attendance[j].startHour << ":";
				fout << info.attendance[j].startMin << "-";
				fout << info.attendance[j].endHour << ":";
				fout << info.attendance[j].endMin << ",";
				fout << info.attendance[j].stat << endl;
			}
			else
				break;
		}
		fout << endl;
	}
}

void PrintAttendance(course info, int n, int i)
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
		cout << " ";
		if (info.attendance[0].year != -1 && info.attendance[0].year != 1 && info.attendance[0].year != 0)
		{
			cout << info.attendance[0].year << "/";
			cout << info.attendance[0].month << "/";
			cout << info.attendance[0].day << "          ";

			cout << info.attendance[0].startHour << ":";
			cout << info.attendance[0].startMin << "-";
			cout << info.attendance[0].endHour << ":";
			cout << info.attendance[0].endMin << "          ";

			if (info.attendance[0].stat == 1)
				cout << "x" << endl;
			else
				cout << "-" << endl;
		}
		for (int j = 1; j < 30; j++)
		{
			if (info.attendance[j].year != -1 && info.attendance[j].year != 1 && info.attendance[j].year != 0)
			{
				cout << setw(60) << right;
				cout << info.attendance[j].year << "/";
				cout << info.attendance[j].month << "/";
				cout << info.attendance[j].day << "         ";

				cout << info.attendance[j].startHour << ":";
				cout << info.attendance[j].startMin << "-";
				cout << info.attendance[j].endHour << ":";
				cout << info.attendance[j].endMin << "          ";

				if (info.attendance[j].stat == 1)
					cout << "x" << endl;
				else
					cout << "-" << endl;
			}
			else
				break;
		}
		cout << endl;
	}
}

void ViewAttendanceList()
{
	system("cls");
	cout << endl;
	for (int i = 0; i < 40; i++) cout << " ";
	cout << "----------VIEW ATTENDANCE LIST OF A COURSE----------" << endl;
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
			cout << setw(5) << "No." << setw(15) << "ID" << setw(20) << "Name" << setw(10) << "Gender";
			cout << setw(15) << right << "Date" << setw(15) << right << "Time"  << setw(20) << "Status(x/-)" << endl;
			cout << "+-------------------------------------------------------------------------------------------------------------------+" << endl;

			for (int i = 0; i < n; i++)
			{
				PrintAttendance(a[i], n, i);
				temp = 1;
			}
			if (temp == 0)
			{
				cout << "No student in class " << classname << " is in this course" << endl;
			}
			else
			{
				// Export to a csv file
				char input;
				cout << "Do you want to export this to a csv file (Y/N): "; cin >> input;
				while (input != 'Y' && input != 'N')
				{
					cout << "Choose (Y/N): ";
					cin >> input;
				}
				if (input == 'Y')
				{
					string file;
					cout << "Enter name of the csv file name you want to save to (.csv), 0 to exit: ";
					cin >> file;
					if (file == "0")
						return;
					fstream fout;
					fout.open(file);
					if (!fout.is_open())
					{
						cout << "Cannot create file " << endl;
					}
					else
					{
						fout << "No." << ',' << "ID" << ',' << "Name" << ',';
						fout << "Attendance day" << ',' << "Attendance time" << ',' << "Attendance status" << ',' << endl;
						for (int i = 0; i < n; i++)
						{
							SaveAttendance(a[i], n, fout, i);
						}
						cout << "Save successfully, open file " << '"' << file << '"' << " to see the result" << endl;
					}
					system("pause");
					fout.close();
					delete[]a;
				}
				else
				{
					delete[]a;
					return;
				}
			}
		}
	}
}

void ExportAttendanceList()
{
	system("cls");
	cout << endl;
	for (int i = 0; i < 40; i++) cout << " ";
	cout << "----------EXPORT ATTENDANCE LIST TO A CSV FILE----------" << endl;
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
	//View attendance list
	else
	{
		string x = smt.year + "-" + smt.sem + "-" + classname + "-" + courseCode + "-" + "student.txt";
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
			cout << setw(5) << left << "No." << setw(15) << "ID" << setw(20) << "Name" << setw(10) << "Gender";
			cout << setw(15) << right << "Date" << setw(15) << "Time" << setw(20) << "Status(x/-)" << endl;
			cout << "+-------------------------------------------------------------------------------------------------------------------+" << endl;

			for (int i = 0; i < n; i++)
			{
				PrintAttendance(a[i], n, i);
			}
			// Export to a csv file
			string file;
			cout << "Enter name of the csv file name you want to save to(.csv), 0 to exit: ";
			cin >> file;
			if (file == "0")
				return;
			fstream fout;
			fout.open(file);
			if (!fout.is_open())
			{
				cout << "Cannot open file csv" << endl;
				system("pause");
			}
			else
			{
				fout << "No." << ',' << "ID" << ',' << "Name" << ',';
				fout << "Attendance days" << ',' << "Attendance time" << ',' << "Attendance status" << ',' << endl;
				for (int i = 0; i < n; i++)
				{
					SaveAttendance(a[i], n, fout, i);
				}
				cout << "Save successfully, open file " << '"' << file << '"' << " to see the result" << endl;
				system("pause");
			}
			fout.close();
			delete[]a;
		}
	}
}