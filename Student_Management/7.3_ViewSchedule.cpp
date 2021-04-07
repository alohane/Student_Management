#include "S01.h"
void viewSchedule(string usr)
{
	system("cls");
	cout << "YOUR SEMESTER COURSE\n";
	string week[20][6];
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 6; j++)
			week[i][j] = "  -";
	}
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
				if (sC[is].ID == usr)
				{
					getschedule(week, Sch[ic].ID, Sch[ic].day, Sch[ic].sH, Sch[ic].sM, Sch[ic].eH, Sch[ic].eM);
					cout <<endl<< Sch[ic].ID << " - " << ClassList[icl] << ":\nLecturer: " << Sch[ic].Lectname << "\nBegin: " << Sch[ic].sy << "/" <<Sch[ic].sm << "/" << Sch[ic].sd;
					cout<<"\nEnd: " << Sch[ic].ey<< "/" << Sch[ic].em << "/" << Sch[ic].ed;
					cout << "\nRoom: " << Sch[ic].room << endl << "At " << Sch[ic].day << " " << Sch[ic].sH << ":" << Sch[ic].sM << " to " << Sch[ic].eH << ":" << Sch[ic].eM << endl ;
				}
			}
			for(int is = 0; is < numStu; is++)
				delete[]sC[is].Lss;
			delete[]sC;
		}
		delete[]Sch;
	}
	delete[]ClassList;
	cout << endl << "1. View Schedule in table\n0. Back to main menu\nYour choice: ";
	int choice; cin >> choice;
	system("cls");
	if(choice==0) return;
	showSchedule(week);
	cout << endl << "1. View all course information\n0. Back to main menu\nYour choice: ";
	cin >> choice;
	if (choice == 0) return;
	else viewSchedule(usr);
}

void getschedule(string week[20][6], string ID, string day, int bh, int bm, int eh, int em)
{
	if (bm == 30) { bh = (bh - 7.5) * 2 + 1; } //class from 7h30 to 17h30 from MON to SAT
	else bh = (bh-7.5)*2;
	if (em == 30) { eh = (eh - 7.5) * 2 + 1; }
	else eh = (eh - 7.5) * 2;
	if (day == "MON")
	{
		for (int i = bh; i < eh; i++)
			week[i][0] = ID;
		return;
	}
	if (day == "TUE")
	{
		for (int i = bh; i < eh; i++)
			week[i][1] = ID;
		return;
	}
	if (day == "WED")
	{
		for (int i = bh; i < eh; i++)
			week[i][2] = ID;
		return;
	}
	if (day == "THU")
	{
		for (int i = bh; i < eh; i++)
			week[i][3] = ID;
		return;
	}
	if (day == "FRI")
	{
		for (int i = bh; i < eh; i++)
			week[i][4] = ID;
		return;
	}
	if (day == "SAT")
	{
		for (int i = bh; i < eh; i++)
			week[i][5] = ID;
		return;
	}
}

void showSchedule(string week[20][6]) {
	system("cls");
	cout << "YOUR SCHEDULES\n";
	int h=7, m=30;
	if (h < 10)cout << "0";
	cout << h << "h";
	if (m < 10)cout << "0";
	cout << m << "_\t|  MON\t|  TUE\t|  WED\t|  THU\t|  FRI\t|  SAT\t|\n";
	for (int i = 0; i < 20; i++)
	{
		if (m == 30) { h++; m = 0; }
		else { m += 30; }
		if (h < 10)cout << "0";
		cout << h << "h";
		if (m < 10)cout << "0";
		cout  << m << "_\t";
		for (int j = 0; j < 6; j++)
		{
			if (week[i][j].length() > 6) { week[i][j].erase(6, week[i][j].length() - 1); }
			if (week[i][j].length() < 6) { cout << " "; }
			cout <<" "<< week[i][j] << "\t";
		}
		cout << endl;
	}
}