#include "S03.h"



bool checkCourseExist(string x,string classname, node* pH) {
	while (pH != nullptr) {
		if (pH->data.ID == x&& classname==pH->data.cl)
			return true;
		pH = pH->next;
	}
	return false;
}


void ManualAddANewCourse() {
	system("cls");
	cout << "ADD A NEW COURSE\n";
	semester smt;
	loadCurSemeter(smt);

	//input class	
	fstream fin;
	bool flag=false;
	string filename;
	string classname;
	string* c = nullptr;
	int num;
	loadClassList(c,num);
	cout << "\n";
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
			fin.open(filename,ios::in);
			if (!fin.is_open()) {
				fin.close();
				fin.open(filename, ios::out);
				fin.close();
				fin.open(filename, ios::in);
			}
		}
		else flag = true;
		
	} while (flag);
	
	delete[]c;
	
	//end
	//end of inputing class

	//load course
	COURSE a;
	node* pH = nullptr;
	int numCourse = 0;
	fin >> numCourse;
	if (numCourse < 0) {
		numCourse = 0;		
	}	



	fin.ignore(1, '\n');
	for (int i = 0; i < numCourse; ++i) {
		fin >> a.No >> a.ID;
		fin.ignore();
		getline(fin, a.Cname);
		fin >> a.cl >> a.user;
		fin.ignore();
		getline(fin, a.Lname);
		fin >> a.dgr >> a.gen >>
			a.sdate.mon >> a.sdate.day >> a.sdate.year >> a.edate.mon >> a.edate.day >> a.edate.year
			>> a.wDate >> a.stime.h >> a.stime.min >> a.etime.h >> a.etime.min >> a.room;
		addToLastList(pH, a);
	}
	fin.close();
	//end load course

	//input new course
	if (a.No < 0) a.No = 1;
	else ++a.No;
	cin.ignore(100, '\n');
	do {
		cout << "ID:\n";
		cin >> a.ID;
		
		if (checkCourseExist(a.ID,classname,pH)) {
			cout << "Course has exist!\nDo you want to continue(Y/N)?\n";
			string a;
			cin >> a;
			if (a == "n" || a == "N")  return;

		}
	} while (checkCourseExist(a.ID, classname,pH));
	//
//CS162,Introduction to Programming,19APCS1,dbtien,Dinh Ba Tien,TS,Male,4/6/20,6/1/20,MON,7,30,11,30,I42

	cout << "Course Name:\n";
	cin.ignore(100,'\n');	
	getline(cin, a.Cname);
	cout << "Class:\n";
	cin >> a.cl;
	cout << "Lecturer username:\n";
	cin >> a.user;
	cout << "Lecturer name:\n";
	cin.ignore(100,'\n');
	getline(cin, a.Lname);
	cout << "Lecturer Degree:\n";	
	getline(cin, a.dgr);
	cout << "Lecturer Gender (Male=1/Female=0):\n";
	cin >> a.gen;
	
	do {
		flag = false;
		cin.ignore(100, '\n');
		cin.clear();
		cout << "Start Mon: "; cin >> a.sdate.mon;
		cout << " Day: "; cin >> a.sdate.day;
		cout << " Year: "; cin >> a.sdate.year;
		cout << "\nEnd Mon: "; cin >> a.edate.mon;
		cout << " Day: "; cin >> a.edate.day;
		cout << " Year: "; cin >> a.edate.year;
		if (a.sdate.day < 0 || a.sdate.day>31 || a.sdate.mon < 0 || a.sdate.mon>12
			|| a.edate.day < 0 || a.edate.day>31 || a.edate.mon < 0 || a.edate.mon>12) {
			cout << "Error Input!\n";
			flag = true;
		}
	} while (flag);
	
	do {
		flag = false;
		cin.ignore(100, '\n');
		cin.clear();
		cout << "\nDay of week(MON/TUE/...): \n";
		cin >> a.wDate;
		if (a.wDate.length() != 3) flag = true;
	} while (flag);

	flag = false;
	do {
		cin.ignore(100, '\n');
		cin.clear();
		cout << "\nStar hour: ";
		cin >> a.stime.h;
		cout << " minute: ";
		cin >> a.stime.min;
		cout << "\nEnd hour: ";
		cin >> a.etime.h;
		cout << " minute: ";
		cin >> a.etime.min;
		cout << endl;
		if (a.stime.h < 0 || a.stime.h>20 || a.etime.h < 0 || a.etime.h>20 ||
			a.stime.min < 0 || a.stime.min>60 || a.etime.min < 0 || a.etime.min>60) flag = true;
	} while (flag);
	cout << "\Room:\n";
	cin >> a.room;	

	addToLastList(pH, a);
	//input new course



	//export new course

	ofstream fout(filename);

	fout << ++numCourse << endl;
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

		pH = pH->next;
	}
	pH = cur1;
	fout.close();

	saveToCourseList(smt, pH);

	CourseStudent* b = nullptr;
	int numStudent = 0;
	importListStudent(b, numStudent, classname);

	ListAttendance atd = importCalendar(a.sdate, a.edate, a.stime, a.etime);
		for (int i = 0; i < numStudent; ++i)
			b[i].atd = atd;
		exportStudentCourse(classname, smt, a.ID, b, numStudent);
		

	delAllNode(pH);
	cout << "Add New course successfully!\n";
	

	cout << "Enter 1 to exit, 0 to back\n";
	string s;
	cin >> s;
	system("cls");
	if (s == "1") {//back function}
		exit(0);
	}

}

