#include "S03.h"

bool CheckStudentID(string ID, Student*& a, int& n) {
	ifstream f("Student.txt");
	f >> n;
	if (n <= 0) return false;

	a = new Student[n + 2];
	for (int i = 0; i < n; ++i) {
		f >> a[i].ID >> a[i].pwd;
		f.ignore();
		getline(f, a[i].name);
		f >> a[i].Dob.year >> a[i].Dob.mon >> a[i].Dob.day >> a[i].clas >> a[i].stat;
	}

	for (int i = 0; i < n; ++i)
		if (a[i].ID == ID) {
			delete[]a;
			n = 0;
			f.close();
			return true;
		}
	f.close();
	return false;
}

void exportStudentInformation(Student* a, int n, Student std) {
	ofstream f("Student.txt");
	string mon, day;
	mon = (std.Dob.mon >= 10) ? to_string(std.Dob.mon) : ("0" + to_string(std.Dob.mon));
	day = (std.Dob.day >= 10) ? to_string(std.Dob.day) : ("0" + to_string(std.Dob.day));
	std.pwd = to_string(std.Dob.year) + mon + day;
	a[n++] = std;
	f << n << "\n";
	for (int i = 0; i < n; ++i)
		f << a[i].ID << "\n" << a[i].pwd << "\n" << a[i].name << "\n" << a[i].Dob.year << " " << a[i].Dob.mon << " " << a[i].Dob.day << "\n"
		<< a[i].clas << "\n" << a[i].stat << endl << "\n";
	f.close();

	ifstream c("Student-" + std.clas + ".txt");
	if (!c.is_open()) {
		cout << "Class doesn't exist!\n";
		return;
	}

	int num;
	c >> num;
	Student* tmp;
	tmp = new Student[num + 1];
	for (int i = 0; i < num; ++i) {
		c >> tmp[i].ID >> tmp[i].pwd;
		c.ignore();
		getline(c, tmp[i].name);
		c >> tmp[i].Dob.year >> tmp[i].Dob.mon >> tmp[i].Dob.day >> tmp[i].clas >> tmp[i].stat;
	}
	tmp[num++] = std;
	c.close();

	f.open("Student-" + std.clas + ".txt");
	f << num << "\n";
	for (int i = 0; i < num; ++i)
		f << tmp[i].ID << "\n" << tmp[i].pwd << "\n" << tmp[i].name << "\n" << tmp[i].Dob.year << " " << tmp[i].Dob.mon << " " << tmp[i].Dob.day << "\n"
		<< tmp[i].clas << "\n" << tmp[i].stat << endl << "\n";
	f.close();
	delete[] tmp;
}

void manuallyAddNewStudentToClass() {
	/*19126001
	20010401
		Trinh Van Minh
		2001 04 01
		19APCS1
		1*/
	Student a;
	Student* s;
	int n;
	cout << "MANUALLY ADD A NEW STUDENT TO CLASS\n";

	bool exist;
	do {
		cout << "\nEnter ID student (0 to back): ";
		cin >> a.ID;
		if (a.ID == "0") return;
		exist = CheckStudentID(a.ID, s, n);
		if (exist) {
			cout << "\nStudent has existed! Do you want to continue?(Y/N) \n";
			string x;
			cin >> x;
			if (x == "N" || x == "n") return;
		}
	} while (exist);
	cin.ignore(5, '\n');
	cout << "\nName: ";
	getline(cin, a.name);
	cout << "\nDate of birth\nYear: ";
	cin >> a.Dob.year;
	cout << "\nMonth: ";
	cin >> a.Dob.mon;
	cout << "\nDay: ";
	cin >> a.Dob.day;
	cout << "\nClass: ";
	cin >> a.clas;

	exportStudentInformation(s, n, a);
	cout << "\nAdd student successfully!\n";
	exitMenu();
	delete[]s;
}