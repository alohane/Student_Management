#include "S03.h"
#include "S01.h"
//No	Course ID	Course name	Class	Lecturer username	
//Lecturer name	Lecturer degree	Lecturer gender	Start date	End date	//
//Day of week	Start hour	Start minutes	End hour	End minute	Room

node* getNode(COURSE k) {//
	node* p = new node;
	p->data = k;
	p->next = nullptr;
	return p;
}

int lengthList(node* pH) {//count number of elements of link list
	int k = 0;
	while (pH != nullptr) {
		++k;
		pH = pH->next;
	}
	return k;
}

void addToLastList(node*& pH, COURSE k) {
	if (pH == nullptr) {
		node* p = getNode(k);
		pH = p;
		return;
	}
	node* cur = pH;
	while (cur->next != nullptr)
		cur = cur->next;
	node* p = getNode(k);
	cur->next = p;
}

void delAllNode(node*& pH){
	while (pH != nullptr) {
		node* cur = pH;
		pH = pH->next;
		delete cur;
	}
}

void loadCurSemeter(semester& smt) {
	ifstream f("CurrentSemester.txt");
	f >> smt.year >> smt.hk;

}

bool checkExist(string ID,COURSE* a, int n) {
	for (int i = 0; i < n; ++i)
		if (ID == a[i].ID) return true;
	return false;
}

//

void saveToCourseList(semester smt,node* pH){
	// save course list
	ifstream fin(smt.year + "-" + smt.hk + "-" + "courseList.txt");
	COURSE* a;
	int numC;	
	fin >> numC;
	if (numC < 0) numC = 0;
	a = new COURSE[numC + 10];
	for (int i = 0; i < numC; ++i) {
		fin >> a[i].ID;
		fin.ignore();
		getline(fin, a[i].Cname);
	}

	while (pH != nullptr) {
		if(!checkExist(pH->data.ID,a,numC))
			a[numC++] = pH->data;
		pH = pH->next;
	}
	fin.close();

	ofstream fout(smt.year + "-" + smt.hk + "-" + "courseList.txt");
	fout << numC << endl;
	for (int i = 0; i < numC; ++i) {
		fout << a[i].ID << endl << a[i].Cname << endl << endl;
	}

	fout.close();
	delete[]a;
}



void importScheduleFromFileData(ifstream& f,node* &pH){
	COURSE a;
	string temp;
	getline(f, temp, '\n');
	while (!f.eof()) {
		//No	Course ID	Course name	Class	Lecturer username	
		//Lecturer name	Lecturer degree	Lecturer gender	Start date	End date	//
		//Day of week	Start hour	Start minutes	End hour	End minute	Room
		getline(f, temp, '\n');
		stringstream ss(temp);// ss=no id name ......		
		string tmp;
		getline(ss, tmp, ',');
		a.No = stoi(tmp);
		getline(ss, tmp, ',');
		a.ID = tmp;
		getline(ss, tmp, ',');
		a.Cname = tmp;
		getline(ss, tmp, ',');
		a.cl = tmp;
		getline(ss, tmp, ',');
		a.user = tmp;
		getline(ss, tmp, ',');
		a.Lname = tmp;
		getline(ss, tmp, ',');
		a.dgr = tmp;
		getline(ss, tmp, ',');//gender
		if (tmp == "Male") a.gen = 1; else a.gen = 0;
		getline(ss, tmp, ',');

		stringstream date(tmp);
		getline(date, tmp, '/');
		a.sdate.mon = stoi(tmp);
		getline(date, tmp, '/');
		a.sdate.day = stoi(tmp);
		getline(date, tmp, '/');
		a.sdate.year = stoi(tmp);

		getline(ss, tmp, ',');
		stringstream date1(tmp);
		getline(date1, tmp, '/');
		a.edate.mon = stoi(tmp);
		getline(date1, tmp, '/');
		a.edate.day = stoi(tmp);
		getline(date1, tmp, '/');
		a.edate.year = stoi(tmp);

		getline(ss, tmp, ',');
		a.wDate = tmp;
		getline(ss, tmp, ',');
		a.stime.h = stoi(tmp);
		getline(ss, tmp, ',');
		a.stime.min = stoi(tmp);
		getline(ss, tmp, ',');
		a.etime.h = stoi(tmp);
		getline(ss, tmp, ',');
		a.etime.min = stoi(tmp);
		getline(ss, tmp, ',');
		a.room = tmp;

		addToLastList(pH, a);
	}
}

void exportToFileSchedule(string year,string hk,string classname,node* pH){
	string temp;	
	temp = year + "-" + hk + "-Schedule-" + classname + ".txt";
	ofstream fout(temp);
	fout << lengthList(pH) << endl;
	node* cur1 = pH;
	while (pH != nullptr) {
		fout << pH->data.No << "\n" << pH->data.ID << "\n" << pH->data.Cname << "\n" << pH->data.cl << "\n" << pH->data.user
			<< "\n" << pH->data.Lname << "\n" << pH->data.dgr << "\n" << pH->data.gen << "\n"
			<< pH->data.sdate.mon << " " << pH->data.sdate.day << " " << pH->data.sdate.year
			<< "\n" << pH->data.edate.mon << " " << pH->data.edate.day << " " << pH->data.edate.year
			<< "\n" << pH->data.wDate
			<< "\n" << pH->data.stime.h << " " << pH->data.stime.min
			<< "\n" << pH->data.etime.h << " " << pH->data.etime.min << "\n"
			<< pH->data.room << endl << endl;

		//No,Course ID,Course name,Class,Lecturer username,Lecturer name,Lecturer degree,
		//Lecturer gender,Start date,End date,Day of week,Start hour,Start minutes,End hour,End minute,Room

		pH = pH->next;
	}
	fout.close();
}

void importListStudent(CourseStudent*& a, int& numStudent,string classname) {
	/*
	6
19126001
20010401
Trinh Van Minh
2001 04 01
19APCS1
1*/	
	ifstream f("Student-" + classname + ".txt");
	f >> numStudent;
	a = new CourseStudent[numStudent];
	for (int i = 0; i < numStudent; ++i) {
		f >> a[i].std.ID >> a[i].std.pwd;
		f.ignore();
		getline(f, a[i].std.name);
		f >> a[i].std.Dob.year >> a[i].std.Dob.mon >> a[i].std.Dob.day >> a[i].std.clas >> a[i].std.stat;
	}	
		
	f.close();
}

void plusDay(date& a) {
	switch (a.mon)
	{
	case 2: {
		if (a.day >= 23) {
			if (isLeapYear(a))
				a.day -= 22;
			else a.day -= 21;
			++a.mon;
			return;
		}
		break;
	}
	case 1: case 3: case 5: case 7: case 8: case 10: {
		if (a.day >= 25) {
			a.day -= 24;
			++a.mon;
			return;
		}
		break;
	}
	case 4: case 6: case 9: case 11: {
		if (a.day >= 24) {
			a.day -= 23;
			++a.mon;
			return;
		}
		break;
	}
	case 12: {
		if (a.day >= 25) {
			a.day -= 24;
			a.mon = 1;
			++a.year;
			return;
		}
	}
	default:
		return;
	}

	a.day += 7;
}

bool isLeapYear(date a) {
	if (a.year % 4 != 0) return false;
	if (a.year % 400 == 0) return true;
	if (a.year % 100 == 0) return false;
	return true;
}

ListAttendance importCalendar(date sdate, date edate, timess stime, timess etime) {
	ListAttendance a;
	a.num = 0;
	int y = edate.year * 1000 + edate.mon * 100 + edate.day;
	int x = sdate.year * 1000 + sdate.mon * 100 + sdate.day;
	while (x <= y) {
		a.att[a.num].day = sdate;
		a.att[a.num].stime = stime;
		a.att[a.num].etime = etime;
		a.att[a.num].status = -1;
		a.num++;		
		plusDay(sdate);
		x = sdate.year * 1000 + sdate.mon * 100 + sdate.day;
	}
	return a;
}

void exportStudentCourse(string classname,semester smt,string IDcourse,CourseStudent* a,int num){
	ofstream f(smt.year + "-" + smt.hk + "-" + classname + "-" + IDcourse + "-Student.txt");
	f << num << endl;

	for (int i = 0; i < num; ++i) {
		f << a[i].std.ID << "\n"
			<< a[i].std.pwd << "\n"
			<< a[i].std.name << "\n"
			<< a[i].std.Dob.year << " " << a[i].std.Dob.mon << " " << a[i].std.Dob.day << "\n"
			<< a[i].std.stat << "\n"
			<< a[i].scr.mid << "\n"
			<< a[i].scr.final << "\n"
			<< a[i].scr.bonus << "\n"
			<< a[i].scr.total << "\n";

		for (int j = 0; j < a[i].atd.num; ++j) {
			f << a[i].atd.att[j].day.year << " " << a[i].atd.att[j].day.mon << " " << a[i].atd.att[j].day.day << " "
				<< a[i].atd.att[j].stime.h << " " << a[i].atd.att[j].stime.min << " "
				<< a[i].atd.att[j].etime.h << " " << a[i].atd.att[j].etime.min << " "
				<< a[i].atd.att[j].status << "\n";
			}
		f << a[i].CourseStat << "\n" << endl;
	}

	f.close();
}

void importCourses() {
	system("cls");
	cout << "IMPORT COURSE\n\n";
	//choose semester to import	
	semester smt;
	loadCurSemeter(smt);
	//end choose semester


	//load class
	string classname;
	string* c = nullptr;
	int num;
	loadClassList(c, num);

	for (int i = 0; i < num; ++i)
		cout << i + 1 << "\t" << c[i] << "\n";
	int keyy;
	do {
		cout << "\nChoose class to import course:(Enter 0 to back)";
		cin >> keyy;
		if (keyy == 0) {
			delete[]c;
			system("cls");
			return;
		}
		if (keyy<0 || keyy>num) {
			cout << "Input not vail!\n";
		}
	} while (keyy<0 || keyy>num);
	classname = c[keyy - 1];
	string filename;
	cin.ignore(100, '\n');
	ifstream f;
	do {
		cout << "\nEnter file name:\n";
		cin >> filename;
		f.open(filename);
		if (!f.is_open()) {
			cout << "File doesn't exist!\nDo you want to continue?(Y/N)?\n";
			string tmp;
			cin >> tmp;
			if (tmp == "N" || tmp == "n") {
				delete[]c;
				system("cls");
				return;
			}
			
		}
	} while (!f.is_open());
	//end


	node* pH = nullptr;
	importScheduleFromFileData(f, pH);
	exportToFileSchedule(smt.year, smt.hk, classname, pH);
	saveToCourseList(smt, pH);

	CourseStudent* a = nullptr;
	int numStudent = 0;
	importListStudent(a, numStudent, classname);

	while (pH != nullptr) {
		ListAttendance atd = importCalendar(pH->data.sdate, pH->data.edate, pH->data.stime, pH->data.etime);
		for (int i = 0; i < numStudent; ++i)
			a[i].atd = atd;
		exportStudentCourse(classname, smt, pH->data.ID, a, numStudent);
		pH = pH->next;
	}

	delAllNode(pH);
	cout << "Import courses successfully!\n";
	delete[]a;
	exitMenu();

};


