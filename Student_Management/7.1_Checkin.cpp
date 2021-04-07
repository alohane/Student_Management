#include "S01.h"
void getListClass(string*& classList, int &n)
{
	ifstream f;
	f.open("ClassList.txt");
	f >> n;
	classList = new string[n];
	getline(f, classList[0]);
	for (int i = 0; i < n; i++)
	{
		getline(f, classList[i]);
	}
	f.close();
	return;
}
void getcurSem(string& curSem)
{
	ifstream f;
	f.open("CurrentSemester.txt");
	getline(f, curSem);
	curSem += '-';
	string cur;
	getline(f, cur);
	curSem += cur;
	f.close();
}
bool getClassSch(string Class, classSchedule*& Sch, int& n)
{
	ifstream f;
	string curSem;
	getcurSem(curSem);
	f.open(curSem + "-Schedule-" + Class + ".txt");
	if (!f.is_open()) return 0;
	f >> n;
	string buffer;
	Sch = new classSchedule[n];
	for (int i = 0; i < n; i++)
	{
		f >> Sch[i].No;
		getline(f, Sch[i].ID);
		getline(f, Sch[i].ID);
		getline(f, Sch[i].name);
		getline(f, Sch[i].Class);
		getline(f, Sch[i].LectID);
		getline(f, Sch[i].Lectname);
		getline(f, Sch[i].Lectlvl);
		getline(f, Sch[i].Lectgen);
		f >> Sch[i].sd;
		f >> Sch[i].sm;
		f >> Sch[i].sy;
		f >> Sch[i].ed;
		f >> Sch[i].em;
		f >> Sch[i].ey;
		getline(f, Sch[i].day);
		getline(f, Sch[i].day);
		f >> Sch[i].sH;
		f >> Sch[i].sM;
		f >> Sch[i].eH;
		f >> Sch[i].eM;
		getline(f, Sch[i].room);
		getline(f, Sch[i].room);
		getline(f, buffer);
	}
	f.close();
	return 1;
}
bool getStuCourse(studentCourse*& sC, int& n, string CurSem, string Class, string Course, int& m)
{
	ifstream f;
	f.open(CurSem + "-" + Class + "-" + Course + "-Student.txt");
	if (!f.is_open()) return 0;
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
	return 1;
}
bool attendStu(stuLesson& Lss)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	ltm->tm_year -= 100;
	ltm->tm_year += 2000;
	ltm->tm_mon += 1;
	if (
		(ltm->tm_year == Lss.y && ltm->tm_mon == Lss.m && ltm->tm_mday == Lss.d)
		&&
		((ltm->tm_hour > Lss.sh) || (ltm->tm_hour == Lss.sh && ltm->tm_min >= Lss.sm))
		&&
		((ltm->tm_hour < Lss.eh) || (ltm->tm_hour == Lss.sh && ltm->tm_min < Lss.em) || (ltm->tm_hour == Lss.sh && ltm->tm_min == Lss.em && ltm->tm_sec == 0))
		)
	{
		Lss.att = 1;
		return 1;
	}
	return 0;
}
void outputStuCourse(studentCourse* sC, int n, string CurSem, string Class, string Course, int m)
{
	ofstream f;
	f.open(CurSem + "-" + Class + "-" + Course + "-Student.txt");
	if (!f.is_open()) return;
	f << n;
	for (int i = 0; i < n; i++)
	{
		f << endl << sC[i].ID << endl;
		f << sC[i].pwd << endl;
		f << sC[i].name << endl;
		f << sC[i].DoB << endl;
		f << sC[i].gen << endl;
		f << sC[i].mid << endl;
		f << sC[i].fin << endl;
		f << sC[i].bns << endl;
		f << sC[i].ttl << endl;
		for (int j = 0; j < m; j++)
		{
			f << sC[i].Lss[j].y << " ";
			f << sC[i].Lss[j].m << " ";
			f << sC[i].Lss[j].d << " ";
			f << sC[i].Lss[j].sh << " ";
			f << sC[i].Lss[j].sm << " ";
			f << sC[i].Lss[j].eh << " ";
			f << sC[i].Lss[j].em << " ";
			f << sC[i].Lss[j].att << endl;
		}
		f << sC[i].stat << endl;
	}
	f.close();
}

void CheckIn(string usr)
{
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
		b=getClassSch(ClassList[icl], Sch, numCourse);
		if (b == 0) continue;
		for(int ic=0;ic<numCourse;ic++)
		{
			b = getStuCourse(sC, numStu, CurSem, ClassList[icl], Sch[ic].ID, numLesson);
			if (b == 0) continue;
			for (int is = 0; is < numStu; is++)
			{
				if (sC[is].ID == usr)
				{
					for (int il = 0; il < numLesson; il++)
					{
						if (sC[is].Lss[il].att == 1)
						{
							cout << "You have checked-in for " << Sch[ic].ID << " before!";
							return;
						}
						b = attendStu(sC[is].Lss[il]);
						if (b == 1) {
							outputStuCourse(sC, numStu, CurSem, ClassList[icl], Sch[ic].ID, numLesson);
							cout << "You have checked-in for" << Sch[ic].ID;
							for (int is = 0; is < numStu; is++)
								delete sC[is].Lss;
							delete[]sC;
							delete[]Sch;
							delete[]ClassList;
							return;
						}
					}
				}
			}
			for (int is = 0; is < numStu; is++)
				delete[]sC[is].Lss;
			delete[]sC;
		}
		delete[]Sch;
	}
	delete[]ClassList;
	cout << "You have no class now!";
}