#include "S03.h"


bool removeFirstX(node*& pH, COURSE x) {
	if (pH == nullptr) return false;

	if (pH->data.ID == x.ID) {
		node* cur = pH;
		pH = pH->next;
		delete cur;
		return true;
	}

	node* cur = pH;
	while (cur->next != nullptr && cur->next->data.ID != x.ID)
		cur = cur->next;
	if (cur->next != nullptr) {
		node* temp = cur->next;
		cur->next = cur->next->next;
		delete temp;
		return true;
	}
	else return false;
}

void removeCourse() {
	system("cls");
	//choose semester to remove course
	
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
	cout << "REMOVE COURSE\n";
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
		getline(fin, a.dgr);
		fin >> a.gen >>
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


	//choose course to remove
	int numEdit;
	do {
		cout << "Choose course number to remove:(Enter 0 to exit)\n";
		cin.ignore(100, '\n');
		cin >> numEdit;
		if (numEdit == 0) {
			system("cls");
			return;
		}
	} while (numEdit <= 0 || numEdit > numCourse);


	//show course current
	cur = pH;
	system("cls");
	for (int i = 0; i < numEdit - 1; ++i) cur = cur->next;
	cout << "\n\nCurrent course\n\n";

	cout << "No: " << cur->data.No << "\n" <<
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

	cout << "\nDo you want to remove this course?(Y/N)\n";
	string ask;
	cin >> ask;
	if (ask == "n" || ask == "N") return;
	removeFirstX(pH, cur->data);


	//export course with new item

	ofstream fout(filename);

	fout << --numCourse << endl;
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
	cout << "\nRemove course successfully!\n";

	//end of export course

	exitMenu();
}

