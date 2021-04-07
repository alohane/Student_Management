#include "S3.h"

void exitMenu() {
	cout << endl;
	cout << "Enter 1 to exit, 0 to back\n";
	cin.ignore();
	string s;
	cin >> s;
	if (s == "1")
		exit(0);
	else {
		system("cls");
		return;
	}
}

void viewAllCourse(string year, string hk) {
	// save course list
	int numCourse = 0;
	node* cur1 = nullptr;
	string temp;
	temp = year + "-" + hk + "-courseList.txt";
	fstream courseList(temp);
	courseList >> numCourse;
	if (numCourse < 0) numCourse = 0;
	COURSE* Course = new COURSE[numCourse + 3];
	for (int i = 0; i < numCourse; ++i) {
		courseList >> Course[i].ID;
		courseList.ignore();
		getline(courseList, Course[i].Cname);
	}
	system("cls");
	cout << "\n\tList course:\n";
	for (int i = 0; i < numCourse; ++i)
		cout << setw(3) << left << i + 1 << setw(20) << left << Course[i].ID << "\t" << Course[i].Cname << endl;
	delete[]Course;
}

void viewClassCourse(semester smt, string classname) {
	//2019-2020-HK2-Schedule-19APCS1.txt
	string file = smt.year + "-" + smt.hk + "-Schedule-" + classname + ".txt";
	ifstream f(file);
	if (!f.is_open()) {
		cout << "Class have no course!\n";
		return;
	}
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

	cout << "\n\nList course of class " << classname << "\n";
	cout << setw(3) << left << "No" << setw(20) << left << "ID" << setw(30) << left << "Course name" << "\n";
	for (int i = 0; i < numCourse; ++i)
		cout << setw(3) << left << i + 1 << setw(20) << left << a[i].ID << setw(30) << left << a[i].Cname << "\n";

	

	delete[] a;
	f.close();
}

void viewListCourse(){
	semester smt;
	loadCurSemeter(smt);
	system("cls");
	cout << "VIEW LIST COURSE\n\n";
	ifstream f("ClassList.txt");
	int numClass;
	if (!f.is_open()) {
		cout << "File class doesn't exist!\n";
	}
	f >> numClass;
	string* class_ = new string[numClass];
	for (int i = 0; i < numClass; ++i)
		f >> class_[i];	
	for (int i = 0; i < numClass; ++i) {
		cout << i + 1 << ". " << class_[i] << "\n";
	}
	cout << numClass + 1 << ". All class\n";
	bool flag;
	do {
		flag = false;
		cout << "\n\nChoose option (0 to exit): ";
		int opt;
		cin >> opt;
		if (opt == 0) {
			system("cls");
			delete[]class_;
			return;
		}
		if (opt == numClass+1)
			viewAllCourse(smt.year, smt.hk);
		else if (opt >= 1 && opt <= numClass)
			viewClassCourse(smt, class_[opt - 1]);
		else flag = true;

	} while (flag);

	f.close();
	exitMenu();
}




