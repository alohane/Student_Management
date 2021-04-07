#include "S03.h"

void editCourseList(semester smt, COURSE old, COURSE new_) {

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
	fin.close();


	for (int i = 0; i < numC; ++i)
		if (a[i].ID == old.ID) {
			a[i].ID = new_.ID;
			a[i].Cname = new_.Cname;
			break;
		}



	ofstream fout(smt.year + "-" + smt.hk + "-" + "courseList.txt");
	fout << numC << endl;
	for (int i = 0; i < numC; ++i) {
		fout << a[i].ID << endl << a[i].Cname << endl << endl;
	}

	fout.close();
	delete[]a;
}

void editAnExistingCourse() {
	system("cls");
	//choose semester to edit course	
	semester smt;
	loadCurSemeter(smt);

	
	//input class	
	ifstream fin;
	bool flag = false;
	string filename;
	string classname;
	string* c = nullptr;
	int num;
	loadClassList(c, num);
	cout << "EDITING AN EXISTING COURSE\n";
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
			fin.open(filename);
			if (!fin.is_open()) {
				flag = true;
				cout << "Wrong information, please input again!\n";
				system("cls");
			}
		}
		else flag = true;

	} while (flag);

	delete[]c;

	//end



	//load course
	node* pH = nullptr;
	int numCourse = 0;
	fin >> numCourse;
	COURSE a;



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


	//show list course
	system("cls");
	node* cur = pH;
	for (int i = 0; i < numCourse; ++i) {
		cout << i + 1 << ". " << cur->data.ID << endl;
		cur = cur->next;
	}
	//end of show list course


	//choose course to edit
	int numEdit;
	do {
		cout << "Choose course number to edit:(Enter 0 to exit)\n";
		cin.ignore(100, '\n');
		cin >> numEdit;
		if (numEdit == 0) return;
	} while (numEdit <= 0 || numEdit > numCourse);
	

	//show course current
	cur = pH;
	
	for (int i = 0; i < numEdit - 1; ++i) cur = cur->next;
	cout << "\n\nCurrent course\n\n";
	
	cout <<"No: "<< cur->data.No << "\n" <<
		"ID: " << cur->data.ID << "\n" << "Course name: " << cur->data.Cname << 
		"\n" << "Class: " << cur->data.cl << "\n" <<
		"Lecturer user: " << cur->data.user
		<< "\n" << "Lecturer name: " << cur->data.Lname << "\n" << 
		"Lecturer Degree: " << cur->data.dgr << "\n" <<
		"Lecturer Gender: " << cur->data.gen << "\n"
		<< "Day start: " << cur->data.sdate.mon << " " << cur->data.sdate.day << " " << cur->data.sdate.year
		<< "\n" << "Day end: " << cur->data.edate.mon << " " << cur->data.edate.day << " " << cur->data.edate.year
		<< "\n" << "Day of week: " << cur->data.wDate
		<< "\n" << "Start time: " << cur->data.stime.h << " " << cur->data.stime.min
		<< "\n" << "End time: " << cur->data.etime.h << " " << cur->data.etime.min << "\n"
		<< "Room: " << cur->data.room << endl << endl;
	//end of show course current
	
	//input new course
	
	cin.ignore(100, '\n');
	do {
		cout << "ID:\n";
		cin >> a.ID;

		if (checkCourseExist(a.ID, classname, pH)) {
			cout << "Course has exist!\nDo you want to continue(Y/N)?\n";
			string a;
			cin >> a;
			if (a == "n" || a == "N")  return;

		}
	} while (checkCourseExist(a.ID, classname, pH));
	//
//CS162,Introduction to Programming,19APCS1,dbtien,Dinh Ba Tien,TS,Male,4/6/20,6/1/20,MON,7,30,11,30,I42
	a.No = cur->data.No;
	cout << "Course Name:\n";
	cin.ignore(100, '\n');
	getline(cin, a.Cname);
	cout << "Class:\n";
	cin >> a.cl;
	cout << "Lecturer username:\n";
	cin >> a.user;
	cout << "Lecturer name:\n";
	cin.ignore(100, '\n');
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
	cur->data = a;
	//input new course


	//export course with new item

	ofstream fout(filename);

	fout << numCourse << endl;	
	saveToCourseList(smt, pH);
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

	fout.close();
	
	delAllNode(pH);
	cout << "Edit course successfully!\n";

	//end of export course

	exitMenu();
}

