#include "S03.h"

struct Lecturer_ {
	string name, pwd, user, dgr;
	bool gen;//male=0 , female=1
};

void viewAllLecturer() {
	system("cls");
	cout << "VIEW ALL LECTURERS\n";
	ifstream f("Lecturer.txt");
	if (!f.is_open()) {
		cout << "Can't open file!\n";
		return;
	}

	int num;
	f >> num;
	Lecturer_* a = new Lecturer_[num];
	if (num < 0) num = 0;
	for (int i = 0; i < num; ++i) {
		f >> a[i].user >> a[i].pwd;
		f.ignore();
		getline(f, a[i].name);		
		getline(f, a[i].dgr);
		f >> a[i].gen;
	}
	f.close();

	cout << "\n\nList all lecturers:\n\n";
	cout << setw(5) << left << "No" << setw(20) << left << "Name" << setw(10) << left << "Degree" << setw(10) << left << "Gender (Male=0,Female=1)" << endl;
	for (int i = 0; i < num; ++i)
		cout <<setw(5)<<  left << i + 1 << setw(20) << left << a[i].name << setw(10) << left << a[i].dgr << setw(10) << left << a[i].gen << endl;

	exitMenu();
	delete[]a;
}