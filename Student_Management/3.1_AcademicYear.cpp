#include "S03.h"
#include "S01.h"


void academicYear() {
	system("cls");
	cout << "ACADEMIC YEAR AND SEMESTER\n\n";
	cout << "1. Creat semester\n";
	cout << "2. Update semester\n";
	cout << "3. Delete semester\n";
	cout << "4. View semesters\n";
	cout << "5. Chooser current semester\n";
	cout << "0. Back\n";
	int input;
	cin.clear();
	cin >> input;
	switch (input)
	{
	case 1: {
		system("cls");
		creatAcademicYear();
		break;
	}
	case 2: {
		system("cls");
		updateAcademic();
		break;
	}
	case 3: {
		system("cls");
		deleteAcademic();
		break;
	}
	case 4: {
		system("cls");
		viewAcademic();
		break;
	}
	case 5: {
		system("cls");
		chooseCurrentSemester();
		break;
	}
	case 0: {
		system("cls");
		return;
	}
	default: {
		system("cls");
		cout << "\nInvail input!\nEnter again\n";
		system("pause");
		system("cls");
		academicYear();
		break;
	}

	}
}

void creatAcademicYear() {
	system("cls");
	ifstream f(semesterFile);
	if (!f.is_open()) {
		cout << "can not open file!\n";
		system("pause");
		int n;
		cout << "Enter 0 to back\n";
		cin >> n;
		if (n == 0)academicYear();
		return;
	} //check did file opened?	

	int n = -1;
	f >> n;//input number of semester
	if (n < 0) n = 0;
	semester* a = new semester[n + 1];
	for (int i = 0; i < n; ++i)//input data
		f >> a[i].year >> a[i].hk;
	f.close();

	int flag = 0;
	do {
		
		cout << "Enter year:(ex 2011-2012)(Enter 0 to back)\n";
		cin >> a[n].year;
		if (a[n].year == "0") {
			delete[]a;
			system("cls");
			return;
		}
		if (a[n].year.length() != 9 || a[n].year[4] != '-')
			flag = 1;
		else flag = 0;
	} while (flag);

	do{
		cout << "Enter semester:(ex: HK1)\n";
		cin >> a[n].hk;
		if (a[n].hk.length() != 3 || a[n].hk.substr(0,2) != "HK")
			flag = 1;
		else flag = 0;
	} while (flag);
	
	ofstream fout(semesterFile);//export new data to file
	fout << ++n << endl;
	for (int i = 0; i < n; ++i)
		fout << a[i].year << endl << a[i].hk << endl << endl;
	fout.close();
	delete[] a;

	

	cout << "Creat semester successfully!\n";
	cout << "\n1.Exit\n2.Continue creat new semester\n0.Back\n";
	cin >> n;
	if (n == 2) creatAcademicYear();
	if (n == 0)academicYear();
	return;
}

void updateAcademic() {
	ifstream f(semesterFile);
	if (!f.is_open()) {
		cout << "can not open file!\n";
		system("pause");
		int n;
		cout << "Enter 0 to back\n";
		cin >> n;
		if (n == 0) academicYear();
		return;
	} //check did file opened?	

	int n;
	f >> n;
	if (n < 0) {
		cout << "No semester has found!\n";
		return;
	}
	semester* a = new semester[n];

	for (int i = 0; i < n; ++i)//input data
		f >> a[i].year >> a[i].hk;


	system("cls");
	cout << "\nList semester\n";
	for (int i = 0; i < n; ++i) {
		cout << i + 1 << ". Year: " << a[i].year << "\tSemester: " << a[i].hk << endl;
	}

	int k;
	bool fl;
	do {
		fl = false;
		cout << "Choose number of semester to update (Enter 0 to back)\n";
		cin >> k;
		if (k == 0) {
			delete[]a;
			system("cls");
			return;
		}
		if (k < 1 || k > n) fl = true;
	} while (fl);
	cout << "Enter new year (example 2018-2019):\n";
	cin >> a[k - 1].year;
	while (a[k - 1].year[4] != '-' || a[k - 1].year.length() != 9) {// check is input invail?
		cout << "Try enter again!\n";
		cin >> a[k - 1].year;
	}
	cout << "Enter new semester (example HK2):\n";
	cin >> a[k - 1].hk;

	while (a[k - 1].hk.substr(0, 2) != "HK" || a[k - 1].hk.length() != 3) {// check is input invail?
		cout << "Try enter again!\n";
		cin >> a[k - 1].hk;
	}

	ofstream fout(semesterFile);

	fout << n << endl;
	for (int i = 0; i < n; ++i)
		fout << a[i].year << endl << a[i].hk << endl << endl;

	system("cls");
	cout << "\nNew list semester\n";
	for (int i = 0; i < n; ++i) {
		cout << i + 1 << ". Year: " << a[i].year << "\tSemester: " << a[i].hk << endl;
	}

	delete[] a;
	cout << "\n\n1. Exit\n2.Continue update semester\n0.Back\nChoose options(1/0)\n";
	cin >> n;
	if (n == 0)academicYear();
	if (n == 2) updateAcademic();
	return;
}

void deleteAcademic() {
	ifstream f(semesterFile);
	if (!f.is_open()) {		
		cout << "can not open file!\n";
		system("pause");
		int n;
		cout << "Enter 0 to back\n";
		cin >> n;
		if (n == 0)academicYear();
		return;
	} //check did file opened?	

	int n;
	f >> n;
	if (n < 0) {
		cout << "No semester has found!\n";
		return;
	}
	semester* a = new semester[n];

	for (int i = 0; i < n; ++i)//input data
		f >> a[i].year >> a[i].hk;


	system("cls");
	cout << "\nList semester\n";
	for (int i = 0; i < n; ++i) {
		cout << i + 1 << ". Year: " << a[i].year << "\tSemester: " << a[i].hk << endl;
	}

	int k;
	bool fl;
	do {
		fl = false;
		cout << "Choose number of semester to delete (enter 0 to back)\n";
		cin >> k;
		if (k == 0) {
			delete[]a;
			system("cls");
			return;
		}
		if (k<1 || k>n) fl = true;
	} while (fl);
	delElementArr(a, n, k - 1);

	ofstream fout(semesterFile);

	fout << n << endl;
	for (int i = 0; i < n; ++i)
		fout << a[i].year << endl << a[i].hk << endl << endl;

	system("cls");
	cout << "\nNew list semester\n";
	for (int i = 0; i < n; ++i) {
		cout << i + 1 << ". Year: " << a[i].year << "\tSemester: " << a[i].hk << endl;
	}

	delete[] a;
	cout << "\n\n1. Exit\n2. Continue delete semester\n0.Back\nChoose options(1/0)\n";
	cin >> n;
	if (n == 0)academicYear();
	if (n == 2) deleteAcademic();
	return;
}

void viewAcademic() {
	ifstream f(semesterFile);
	if (!f.is_open()) {
		cout << "can not open file!\n";
		system("pause");
		int n;
		cout << "Enter 0 to back\n";
		cin >> n;
		if (n == 0)academicYear();
		return;
	} //check did file opened?	 
	int n;
	f >> n;
	if (n < 0) return;


	semester* a = new semester[n];
	for (int i = 0; i < n; ++i)
		f >> a[i].year >> a[i].hk;//input data

	system("cls");
	cout << "\nList semester\n";
	for (int i = 0; i < n; ++i) {
		cout << i + 1 << ". Year: " << a[i].year << "\tSemester: " << a[i].hk << endl;
	}

	f.close();


	delete[] a;

	cout << "\n1. Exit\n0.Back\nChoose options(1/0)\n";
	cin >> n;
	if (n == 0)academicYear();
	return;
}

void chooseCurrentSemester(){
	ifstream f(semesterFile);
	if (!f.is_open()) {
		cout << "can not open file!\n";
		system("pause");
		int n;
		cout << "Enter 0 to back\n";
		cin >> n;
		if (n == 0)academicYear();
		return;
	} //check did file opened?	 
	int n;
	f >> n;
	if (n < 0) return;


	semester* a = new semester[n];
	for (int i = 0; i < n; ++i)
		f >> a[i].year >> a[i].hk;//input data
	f.close();

	system("cls");
	semester cur;
	loadCurSemeter(cur);
	cout << "\nCurrent semester: " << cur.year << " " << cur.hk;
	cout << "\nList semester:\n";
	for (int i = 0; i < n; ++i) {
		cout << i + 1 << ". Year: " << a[i].year << "\tSemester: " << a[i].hk << endl;
	}
	cout << "\Choose current semester: ";
	int curSemeseter;
	cin >> curSemeseter;

	ofstream curS("CurrentSemester.txt");
	curS << a[curSemeseter - 1].year << endl << a[curSemeseter - 1].hk << endl;
	curS.close();
	academicYear();


	delete[] a;
}

template <class T>
void delElementArr(T* a, int& n, int pos) {
	if (n <= 0 || pos < 0 || pos >= n || a == nullptr) return;

	for (int i = pos; i < n - 1; ++i)
		a[i] = a[i + 1];
	--n;
}