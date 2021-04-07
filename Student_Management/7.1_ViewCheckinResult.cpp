#include "S01.h"

void viewCheckinResult(string usr )
{
	system("cls");
	cout << "VIEW CHECK - IN RESULT\nChoice Course to view check - in result:\n";
	string* Course = new string[6];
	string* CourseID = new string[6];
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
	int iCourse=0;
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
				if (sC[is].ID == usr)
				{
					Course[iCourse] = CurSem;
					Course[iCourse] += "-";
					Course[iCourse] += ClassList[icl];
					Course[iCourse] += "-";
					Course[iCourse] += Sch[ic].ID;
					CourseID[iCourse] = Sch[ic].ID;
					Course[iCourse] += "-Student.txt";
					cout << iCourse + 1 << ". " << Sch[ic].ID<<endl;
					iCourse++;
				}
			}
			for (int is = 0; is < numStu; is++)
				delete[]sC[is].Lss;
			delete[]sC;
		}
		delete[]Sch;
	}
	delete[]ClassList;
	cout << "Your choice (0-" << iCourse + 1 << "): ";
	int choice; cin >> choice;
	if (choice == 0) return;
	system("cls");
	cout << "VIEW CHECK IN RESULT FOR " << CourseID[choice-1] << endl;
	viewCheckinResultofCourse(Course[choice-1], usr);
	delete[]Course;
	delete[]CourseID;
}
void viewCheckinResultofCourse(string Course, string usr)
{
	studentCourse* sC; int n; int m;
	ifstream f;
	f.open(Course);
	if (!f.is_open()) return;
	f >> n;
	sC = new studentCourse[n];
	for (int i = 0; i < n; i++)
	{
		if (i > 0) getline(f, sC[i].ID);
		getline(f, sC[i].ID);
		getline(f, sC[i].ID);
		getline(f, sC[i].pwd);
		getline(f, sC[i].name);
		getline(f, sC[i].DoB);
		f >> sC[i].gen;
		f >> sC[i].mid;
		f >> sC[i].fin;
		f >> sC[i].bns;
		f >> sC[i].ttl;
		sC[i].Lss = new stuLesson[20];
		f >> sC[i].Lss[0].y;
		m = 0;
		while (1)
		{
			if (sC[i].Lss[m].y < 10) break;
			else {
				f >> sC[i].Lss[m].m;
				f >> sC[i].Lss[m].d;
				f >> sC[i].Lss[m].sh;
				f >> sC[i].Lss[m].sm;
				f >> sC[i].Lss[m].eh;
				f >> sC[i].Lss[m].em;
				f >> sC[i].Lss[m].att;
				m++;
				f >> sC[i].Lss[m].y;
			}
		}
		sC[i].stat = sC[i].Lss[m].y;
	}
	f.close();
	for (int i = 0; i < n; i++)
	{
		if (sC[i].ID == usr)
		{
			for (int j = 0; j < n; j++)
			{
				//if (sC[i].Lss[j].y < 10) cout << 0;
				cout << sC[i].Lss[j].y << "/";
				if (sC[i].Lss[j].m < 10) cout << 0;
				cout << sC[i].Lss[j].m << "/";
				if (sC[i].Lss[j].d < 10) cout << 0;
				cout << sC[i].Lss[j].d << ": ";
				if (sC[i].Lss[j].att == 1) cout << "YES" << endl;
				else cout << "NO"<< endl;
			}
		}
	}
	for (int i = 0; i < m; i++)
		delete[]sC[i].Lss;
	delete[]sC;
}