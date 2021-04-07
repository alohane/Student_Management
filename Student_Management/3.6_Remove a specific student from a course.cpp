#include "S03.h"

void LoadStudentCourse(string classname, semester smt, string IDcourse, CourseStudent*& a, int& num) {
	ifstream f(smt.year + "-" + smt.hk + "-" + classname + "-" + IDcourse + "-Student.txt");
	f >> num;
	if (num < 0) num = 0;
	a = new CourseStudent[num];	
	for (int i = 0; i < num; ++i) {
		f >> a[i].std.ID
			>> a[i].std.pwd;
		f.ignore();
		getline(f, a[i].std.name);
		f>> a[i].std.Dob.year >> a[i].std.Dob.mon >> a[i].std.Dob.day
			>> a[i].std.stat
			>> a[i].scr.mid
			>> a[i].scr.final
			>> a[i].scr.bonus
			>> a[i].scr.total;	

		a[i].atd.num = 0;
		for (int j = 0; j < 20; ++j) {
			f >> a[i].atd.att[j].day.year;
			if (a[i].atd.att[j].day.year!=0 && a[i].atd.att[j].day.year != 1) {
				f >> a[i].atd.att[j].day.mon >> a[i].atd.att[j].day.day
					>> a[i].atd.att[j].stime.h >> a[i].atd.att[j].stime.min
					>> a[i].atd.att[j].etime.h >> a[i].atd.att[j].etime.min
					>> a[i].atd.att[j].status;
				++a[i].atd.num;
			}
			else {				
				break;
			}
		}
		a[i].CourseStat= a[i].atd.att[a[i].atd.num].day.year;
	}

	f.close();
}

void deactiveStudent(CourseStudent* a, int num, string ID) {
	for(int i=0;i<num;++i)
		if (a[i].std.ID == ID) {
			a[i].CourseStat = 0;
			break;
		}
}

void RemoveStudentCourse() {
	system("cls");
	semester smt;
	loadCurSemeter(smt);

	//input class	
	
	bool flag;
	

		//2019-2020-HK2-19APCS1-CM101-Student.txt
	
		//input class	
	ifstream f;
	flag = false;
	string filename;
	string classname;
	string* c = nullptr;
	int num;
	loadClassList(c, num);
	cout << "REMOVE A SPECIFIC STUDENT\n";
	for (int i = 0; i < num; ++i)
		cout << i + 1 << "\t" << c[i] << "\n";
	int keyy;
	do {
		flag = false;
		cout << "Choose class to add a new student to course (enter 0 to back)\n";
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
				cout << "Class have no course, please input again!\n";
				system("cls");
			}
		}
		else flag = true;

	} while (flag);

	delete[]c;

	//end





		

		//list course of class
	
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
		cout << setw(3) << left << "No" << setw(13) << left << "ID" << setw(30) << left << "Course name" << "\n";
		for (int i = 0; i < numCourse; ++i)
			cout << setw(3) << left << i + 1 << setw(13) << left << a[i].ID << setw(30) << left << a[i].Cname << "\n";
		
		int numC;
		do {
			flag = false;
			cout << "\nChoose course to remove student\n";			
			cin >> numC;
			if (numC <= 0 || numC > numCourse) flag = true;
		} while (flag);
		CourseStudent* b=nullptr;
		num=0;
		LoadStudentCourse(classname, smt, a[numC - 1].ID, b, num);
		
		cout << "List all student of course:\n\n";

		cout << setw(3) << left << "No" << setw(20) << left << "Student Name" << setw(10) << left << "ID" << "\n";
		for (int i = 0; i < num; ++i)
			cout << setw(3) << left << i + 1 << setw(20) << left << b[i].std.name << setw(10) << left << b[i].std.ID << "\n";
		
		do {
			flag = true;
			cout << "\nInput student ID to remove\n";
			string ID;
			cin >> ID;
			for (int i = 0; i < num; ++i)
				if (b[i].std.ID == ID) {
					cout << "\nStudent Information: " << b[i].std.name << "\t " << b[i].std.ID << "\n";
					cout << "\nDo you want to remove this student?(Y/N)\n";
					string x;
					cin >> x;
					if (x == "N" || x == "n") {
						flag = false;
						break;
					}
					b[i].CourseStat = 0;
					flag = false;
					break;
				}
			if (flag) {
				cout << "Wrong ID student\n";
				cout << "Input 1 to continue, 0 to exit\n";
				int opt;
				cin >> opt;
				if (opt == 0) return;
			}
		} while (flag);

		cout << "\nRemove student successfully!\n";

		exportStudentCourse(classname, smt, a[numC - 1].ID, b, num);
		delete[]a;
		delete[]b;
		system("cls");
	//end of inputing class
}