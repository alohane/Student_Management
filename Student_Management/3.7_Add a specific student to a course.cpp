#include "S03.h"

void loadListCourse(COURSE*& a, int& numC,semester smt) {
	//2019-2020-HK2-courseList.txt
	ifstream f(smt.year + "-" + smt.hk + "-courseList.txt");
	if (!f.is_open()) return;

	f >> numC;
	if (numC < 0) numC = 0;
	a = new COURSE[numC];
	for (int i = 0; i < numC; ++i) {
		f >> a[i].ID;
		f.ignore();
		getline(f, a[i].Cname);
	}
	f.close();
}

void loadClassList(string*& a,int& numS){
	ifstream f("ClassList.txt");
	if (!f.is_open()) return;

	f >> numS;
	a = new string[numS];
	for (int i = 0; i < numS; ++i)
		f >> a[i];
	f.close();
}

bool CheckIDStudent(string ID,CourseStudent& s) {
	CourseStudent* a; int numStudent;
	/*
	6
19126001
20010401
Trinh Van Minh
2001 04 01
19APCS1
1*/
	ifstream f("Student.txt");
	f >> numStudent;
	a = new CourseStudent[numStudent];
	for (int i = 0; i < numStudent; ++i) {
		f >> a[i].std.ID >> a[i].std.pwd;
		f.ignore();
		getline(f, a[i].std.name);
		f >> a[i].std.Dob.year >> a[i].std.Dob.mon >> a[i].std.Dob.day >> a[i].std.clas >> a[i].std.stat;
	}

	for(int i=0;i<numStudent;++i)
		if (a[i].std.ID == ID) {
			s.std.ID = a[i].std.ID;
			s.std.pwd = a[i].std.pwd;
			s.std.name = a[i].std.name;
			s.std.Dob.year = a[i].std.Dob.year;
			s.std.Dob.mon = a[i].std.Dob.day;
			s.std.Dob.day = a[i].std.Dob.day;
			s.std.clas = a[i].std.clas;
			s.std.stat = 1;
		

			delete[]a;
			f.close();
			return true;
		}
	
	delete[] a;
	f.close();
	return false;

}

void exportStudentCourse(string classname, semester smt, string IDcourse,CourseStudent s) {
	CourseStudent* a; int num;
	ifstream f(smt.year + "-" + smt.hk + "-" + classname + "-" + IDcourse + "-Student.txt");
	f >> num;
	if (num < 0) num = 0;
	a = new CourseStudent[num+1];
	for (int i = 0; i < num; ++i) {
		f >> a[i].std.ID
			>> a[i].std.pwd;
		f.ignore();
		getline(f, a[i].std.name);
		f >> a[i].std.Dob.year >> a[i].std.Dob.mon >> a[i].std.Dob.day
			>> a[i].std.stat
			>> a[i].scr.mid
			>> a[i].scr.final
			>> a[i].scr.bonus
			>> a[i].scr.total;

		a[i].atd.num = 0;
		for (int j = 0; j < 20; ++j) {
			f >> a[i].atd.att[j].day.year;
			if (a[i].atd.att[j].day.year != 0 && a[i].atd.att[j].day.year != 1) {
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
		a[i].CourseStat = a[i].atd.att[a[i].atd.num].day.year;
	}

	f.close();
	s.CourseStat = 1;	
	for (int j = 0; j < a[num-1].atd.num; ++j) {
		s.atd.att[j].day.year = a[num - 1].atd.att[j].day.year;
		s.atd.att[j].day.mon = a[num - 1].atd.att[j].day.mon;
		s.atd.att[j].day.day = a[num - 1].atd.att[j].day.day;
		s.atd.att[j].stime.h = a[num - 1].atd.att[j].stime.h;
		s.atd.att[j].stime.min = a[num - 1].atd.att[j].stime.min;
		s.atd.att[j].etime.h = a[num - 1].atd.att[j].etime.h;
		s.atd.att[j].etime.min = a[num - 1].atd.att[j].etime.min;
		s.atd.att[j].status = -1;
	}
	s.atd.num = a[num - 1].atd.num;
	a[num] = s;
	++num;

	ofstream fout(smt.year + "-" + smt.hk + "-" + classname + "-" + IDcourse + "-Student.txt");	
	fout << num << endl;

	for (int i = 0; i < num; ++i) {
		fout << a[i].std.ID << "\n"
			<< a[i].std.pwd << "\n"
			<< a[i].std.name << "\n"
			<< a[i].std.Dob.year << " " << a[i].std.Dob.mon << " " << a[i].std.Dob.day << "\n"
			<< a[i].std.stat << "\n"
			<< a[i].scr.mid << "\n"
			<< a[i].scr.final << "\n"
			<< a[i].scr.bonus << "\n"
			<< a[i].scr.total << "\n";

		for (int j = 0; j < a[i].atd.num; ++j) {
			fout << a[i].atd.att[j].day.year << " " << a[i].atd.att[j].day.mon << " " << a[i].atd.att[j].day.day << " "
				<< a[i].atd.att[j].stime.h << " " << a[i].atd.att[j].stime.min << " "
				<< a[i].atd.att[j].etime.h << " " << a[i].atd.att[j].etime.min << " "
				<< a[i].atd.att[j].status << "\n";
		}
		fout << a[i].CourseStat << "\n" << endl;
	}

	fout.close();

	delete[]a;
}


void addSpecificStudentToCourse(){
	system("cls");
	semester smt;
	loadCurSemeter(smt);

	//input class	
	ifstream f;
	bool flag = false;
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
			
		}
		else flag = true;

	} while (flag);

	delete[]c;

	//end

	
	//2019-2020-HK2-Schedule-19APCS1.txt
	
	f.open(filename);
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
	cout << setw(3) << left << "No" << setw(8) << left << "ID" << setw(30) << left << "Course name" << "\n";
	for (int i = 0; i < numCourse; ++i)
		cout << setw(3) << left << i + 1 << setw(8) << left << a[i].ID << setw(30) << left << a[i].Cname << "\n";
	f.close();
	//end show list course

	do {
		flag = false;
		cout << "\nChoose course to add new student: ";
		cin >> keyy;
		if (keyy <= 0 || keyy > numCourse) flag = true;
	} while (flag);
	string courseID = a[keyy - 1].ID;
	//

	string ID;
	bool check;
	CourseStudent s;
	do {
		cout << "\nEnter ID Student:";
		cin >> ID;
		check = CheckIDStudent(ID, s);
		if (!check) {
			cout << "ID doesn't exist!\nDo you want to continue?(Y/N)\n";
			string x;
			cin >> x;
			if (x == "n" || x == "N") {
				system("cls");
				return;
			}
		}
		else {
			cout << "\n" << s.std.name << "\t" << s.std.Dob.day << "/" << s.std.Dob.mon << "/" << s.std.Dob.year << "\n";
		}
	} while (!check);
	//

	cout << "\nDo you want to add this student to course?(Y/N)\n";
	string x;
	cin >> x;
	if (x == "Y" || x == "y") {
		exportStudentCourse(classname, smt, courseID, s);
		cout << "\nAdd student successfully!\n";
		
	}
	delete[] a;
	exitMenu();
	

}