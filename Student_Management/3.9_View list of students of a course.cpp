#include "S03.h"

void viewListStudent(){
	system("cls");
	semester smt;
	loadCurSemeter(smt);
	bool flag;
	//input class	
		//input class	
	ifstream f;
	flag = false;
	string filename;
	string classname;
	string* c = nullptr;
	int num;
	loadClassList(c, num);
	cout << "VIEW LIST OF STUDENTS\n";
	for (int i = 0; i < num; ++i)
		cout << i + 1 << "\t" << c[i] << "\n";
	int keyy;
	do {
		flag = false;
		cout << "Choose class to add a new course (enter 0 to back)\n";
		cin >> keyy;
		if (keyy == 0) {
			delete[]c;
			system("cls");
			return;
		}
		if (keyy > 0 && keyy <= num) {
			classname = c[keyy - 1];
			filename = smt.year + "-" + smt.hk + "-Schedule-" + classname + ".txt";
			f.open(filename);
			if (!f.is_open()) {
				flag = true;
				cout << "Wrong information, please input again!\n";
				system("cls");
			}
		}
		else flag = true;

	} while (flag);

	delete[]c;

	//end
	int numCourse;
	f >> numCourse;
	if (numCourse < 0) numCourse = 0;
	if (numCourse == 0) {
		cout << "Class have no course!\n";
		return;
	}
	COURSE* a = new COURSE[numCourse];
	for (int i = 0; i < numCourse; ++i) {
		f >> a[i].No >> a[i].ID;
		f.ignore();
		getline(f, a[i].Cname);
		f >> a[i].cl >> a[i].user;
		f.ignore();
		getline(f, a[i].Lname);
		f >> a[i].dgr >> a[i].gen >>
			a[i].sdate.mon >> a[i].sdate.day >> a[i].sdate.year >> a[i].edate.mon >> a[i].edate.day >> a[i].edate.year
			>> a[i].wDate >> a[i].stime.h >> a[i].stime.min >> a[i].etime.h >> a[i].etime.min >> a[i].room;

	}
	f.close();

	cout << "\n\nList course of class " << classname << "\n";
	cout << setw(3) << left << "No" << setw(8) << left << "ID" << setw(30) << left << "Course name" << "\n";
	for (int i = 0; i < numCourse; ++i)
		cout << setw(3) << left << i + 1 << setw(20) << left << a[i].ID << setw(30) << left << a[i].Cname << "\n";

	int numC;
	do {
		flag = false;
		cout << "\nChoose course to view all student\n";
		cin >> numC;
		if (numC <= 0 || numC > numCourse) flag = true;
	} while (flag);
	CourseStudent* b = nullptr;
	num = 0;
	LoadStudentCourse(classname, smt, a[numC - 1].ID, b, num);
	system("cls");
	cout << "List all student of course:\n\n";

	cout << setw(3) << left << "No" << setw(20) << left << "Student Name" << setw(10) << left << "ID" << "\n";
	for (int i = 0; i < num; ++i)
		cout << setw(3) << left << i + 1 << setw(20) << left << b[i].std.name << setw(10) << left << b[i].std.ID << "\n";

	delete[]a;
	delete[]b;
	exitMenu();
}