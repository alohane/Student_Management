#include "S03.h"

void changeGlobal(string ID, string newclass) {
	ifstream f("Student.txt");
	if (!f.is_open()) return;
	int n;
	f >> n;
	if (n < 0) {
		n = 0;
		return;
	}
	

	Student* a = new Student[n];
	for (int i = 0; i < n; ++i) {
		f >> a[i].ID >> a[i].pwd;
		f.ignore();
		getline(f, a[i].name);
		f >> a[i].Dob.year >> a[i].Dob.mon >> a[i].Dob.day >> a[i].clas >> a[i].stat;
	}

	for (int i = 0; i < n; ++i)
		if (a[i].ID == ID) {
			a[i].clas = newclass;
			break;
		}
	f.close();

	ofstream fout("Student.txt");
	fout << n << "\n\n";
	for (int i = 0; i < n; ++i)
		fout << a[i].ID << "\n" << a[i].pwd <<"\n"<< a[i].name<<"\n" << a[i].Dob.year << " " << a[i].Dob.mon << " " << a[i].Dob.day << "\n"
		<< a[i].clas << "\n" << a[i].stat << "\n\n";
	fout.close();
	delete[]a;
}

void addToNewClass(Student a, string newclass) {
	ifstream f("Student-" + newclass + ".txt");
	a.clas = newclass;
	int n;
	f >> n;
	Student* s = new Student[n+1];
	for (int i = 0; i < n; ++i) {
		f >> s[i].ID >> s[i].pwd;
		f.ignore();
		getline(f, s[i].name);
		f >> s[i].Dob.year >> s[i].Dob.mon >> s[i].Dob.day >> s[i].clas >> s[i].stat;
	}
	s[n] = a;
	++n;
	
	
	f.close();

	ofstream fout("Student-" + newclass + ".txt");
	fout << n << "\n\n";
	for (int i = 0; i < n; ++i)
		fout << s[i].ID << "\n" << s[i].pwd << "\n" <<s[i].name<<"\n"<< s[i].Dob.year << " " << s[i].Dob.mon << " " << s[i].Dob.day << "\n"
		<< s[i].clas << "\n" << s[i].stat << "\n\n";

	fout.close();
	delete[]s;

}

void removeOldClass(Student s) {
	fstream f;
	f.open("Student-" + s.clas + ".txt", ios::in);
	int n;
	f >> n;
	if (n <= 0) return;

	Student* a = new Student[n];
	for (int i = 0; i < n; ++i) {
		f >> a[i].ID >> a[i].pwd;
		f.ignore();
		getline(f, a[i].name);
		f >> a[i].Dob.year >> a[i].Dob.mon >> a[i].Dob.day >> a[i].clas >> a[i].stat;
	}
	f.close();

	int index=999;
	for (int i = 0; i < n; ++i)
		if (s.ID == a[i].ID) {
			index = i;
			break;
		}

	f.open("Student-" + s.clas + ".txt", ios::out);
	--n;
	f << n << "\n\n";
	for (int i = 0; i < index; ++i)
		f << a[i].ID << "\n" << a[i].pwd << "\n"<<a[i].name<<"\n" << a[i].Dob.year << " " << a[i].Dob.mon << " " << a[i].Dob.day << "\n"
		<< a[i].clas << "\n" << a[i].stat << "\n\n";
	for (int i = index + 1; i < n+1; ++i)
		f << a[i].ID << "\n" << a[i].pwd << "\n" <<a[i].name<<"\n"<< a[i].Dob.year << " " << a[i].Dob.mon << " " << a[i].Dob.day << "\n"
		<< a[i].clas << "\n" << a[i].stat << "\n\n";
	f.close();
	delete[]a;
}

void chooseClass(string& oldclass,bool &back) {
	ifstream f("ClassList.txt");
	if (!f.is_open()) return;
	int n;
	f >> n;
	if (n < 0) return;
	string* list = new string[n];
	for (int i = 0; i < n; ++i)
		f >> list[i];

	cout << "\n";
	for (int i = 0; i < n; ++i) {
		cout << i + 1 << ". " << list[i] << "\n";
	}
	int k;
	do {
		cout << "\n Class number (0 to back): ";
		cin >> k;
		if (k == 0) {
			delete[] list;
			back = true;
			system("cls");
			return;
		}
	} while (k <= 0 || k > n);
	k--;
	oldclass = list[k];
	delete[]list;
}

void changeClassStudent() {
	system("cls");
	cout << "CHANGE CLASS OF STUDENT\n";
	string oldclass;
	ifstream f;

	cout << "\nChoose old class have student to change ";
	bool back = false;
	chooseClass(oldclass,back);
	if (back) {
		return;
	}
	f.open("Student-" + oldclass + ".txt");
	///

	int n;
	f >> n;
	if (n < 0) {
		n = 0; return;
	}
	Student* a = new Student[n];
	for (int i = 0; i < n; ++i) {
		f >> a[i].ID >> a[i].pwd;
		f.ignore();
		getline(f, a[i].name);
		f >> a[i].Dob.year >> a[i].Dob.mon >> a[i].Dob.day >> a[i].clas >> a[i].stat;
	}
	f.close();

	cout << "\nList student of class:\n";
	for (int i = 0; i < n; ++i) {
		cout << i + 1 << ". " << a[i].ID << "\t" << a[i].name << "\n";
	}
	int k;
	do {
		cout << "\nChoose student to change class:(0 to back) ";
		cin >> k;
		if (k == 0) {
			delete[]a;
			system("cls");
			return;
		}

	} while (k <= 0 || k > n);
	--k;

	cout << "\nChoose new class to change";
	string newclass;
	chooseClass(newclass,back);
	if (back) {
		system("cls");
		delete[]a;
		return;
	}

	changeGlobal(a[k].ID, newclass);
	addToNewClass(a[k], newclass);
	removeOldClass(a[k]);

	cout << "Change class of student successfully!\n";
	delete[]a;
	exitMenu();

}

