#include "S01.h"

void getSID(Stu& s)
{
	cout << "Input student ID to edit (0 to back): ";
	cin >> s.id;
	Stu* St;
	int n;
	inputStudent(St, n);
	for (int i = 0; i < n; i++)
	{
		if (St[i].id == s.id) {
			s.id = St[i].id;
			s.name = St[i].name;
			s.dob = St[i].dob;
			s.pwd = St[i].pwd;
			return;
		}
	}
	cout << "This student is not existing! Press any key to back...";
	_getch();
	system("cls");
	s.id = "0";
	delete[]St;
}
void EditStudent()
{
	Stu s;
	system("cls");
	getSID(s);
	if (s.id == "0")return;
	cout << "OLD INFO OF " << s.id << endl;
	cout << "Name: " << s.name << endl << "Date of birth: " << s.dob << endl;
	cout << "Password: ";
	for (int i = 0; i < s.pwd.length(); i++)
		cout << "*";
	cout << endl << endl;
	cout << "INPUT NEW INFO OF " << s.id << endl;
	string buffer;
	cout << "New name (0 to use old name and continue, 00 to exit edit): ";
	cin.ignore(256, '\n'); getline(std::cin, buffer);
	if (buffer == "00") return;
	else if(buffer!="0") s.name = buffer;
	cout << "New date of birth (0 to use old date of birth and continue, 00 to exit edit): ";
	getline(std::cin, buffer);
	if (buffer == "00") return;
	else if(buffer != "0") s.dob = buffer;
	cout << "New password (0 to use old password and continue, 00 to exit edit): ";
	getline(std::cin, buffer);
	if (buffer == "00") return;
	else if (buffer != "0") s.pwd = buffer;

	//change in class
	Stu* stu;
	int n;
	inputStudent(stu, n);
	int i;
	string cls;
	for (i = 0; i < n; i++)
	{
		if (stu[i].id == s.id) {
			cls = stu[i].cls;
			break;
		}
	}
	ifstream fin;
	int m;
	Stu* St;
	fin.open("Student-" + cls + ".txt");
	fin >> m;
	St = new Stu[n];
	for (int i = 0; i < n; i++)
	{
		getline(fin, St[i].id);
		getline(fin, St[i].id);
		getline(fin, St[i].id);
		getline(fin, St[i].pwd);
		getline(fin, St[i].name);
		getline(fin, St[i].dob);
		getline(fin, St[i].cls);
		fin >> St[i].stat;
	}
	fin.close();
	for (int j = 0; j < m; j++)
	{
		if (St[j].id == s.id)
		{
			St[j].pwd = s.pwd;
			St[j].dob = s.dob;
			St[j].name = s.name;
		}
	}
	StuToTxt(St, "Student-" + cls, m);
	delete[]St;

	//change in class list
	stu[i].pwd = s.pwd;
	stu[i].dob = s.dob;
	stu[i].name = s.name;
	ofstream fout;
	fout.open("Student.txt");
	fout << n << endl;
	for (i = 0; i < n; i++)
	{
		fout << endl;
		fout << stu[i].id << endl;
		fout << stu[i].pwd << endl;
		fout << stu[i].name << endl;
		fout << stu[i].dob << endl;
		fout << stu[i].cls << endl;
		fout << stu[i].stat << endl;
	}
	fout.close();
	delete[]stu;
	//change in course
	string CurSem;
	getcurSem(CurSem);
	string* ClassList;
	int numClass;
	getListClass(ClassList, numClass);
	classSchedule* Sch;
	int numCourse;
	studentCourse* sC;
	int numStu;
	int numLesson;
	bool b;
	for (int icl = 0; icl < numClass; icl++) {
		b = getClassSch(ClassList[icl], Sch, numCourse);
		if (b == 0) continue;
		for (int ic = 0; ic < numCourse; ic++)
		{
			b = getStuCourse(sC, numStu, CurSem, ClassList[icl], Sch[ic].ID, numLesson);
			if (b == 0) continue;
			for (int is = 0; is < numStu; is++)
			{
				if (sC[is].ID == s.id)
				{
					sC[is].pwd = s.pwd;
					sC[is].DoB = s.dob;
					sC[is].name = s.name;
					outputStuCourse(sC, numStu, CurSem, ClassList[icl], Sch[ic].ID, numLesson);
				}
			}
			for (int is = 0; is < numStu; is++)
				delete[]sC[is].Lss;
			delete[]sC;
		}
		delete[]Sch;
	}
	delete[]ClassList;
	cout << "Edit succesfully! Press any key to back...";
	_getch();
	return;

}
