#include "S01.h"

void viewScore(string usr)
{
	system("cls");
	cout << "VIEW SCORES\n";
	int choice;
	cout << "1. View scores for a course\n2. View for all course\n0. Back\nYour choice: ";
	cin >> choice;
	string course;
	if (choice != 1 && choice != 2) return;
	if (choice == 1) { cout << "\nInput course ID to view (0 - back): "; cin >> course; system("cls"); if (course == "0")viewScore(usr); }
	if (choice == 2) { system("cls"); cout << "Course\t\tMid\tFinal\tBonus\tTotal\n"; }
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
	int iCourse = 0;
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
					if (choice == 2) {
						cout << Sch[ic].ID << "\t";
						if (sC[ic].mid == -1) cout << "-";
						else cout << sC[ic].mid;
						if (sC[ic].fin == -1) cout << "\t-";
						else cout << "\t" << sC[ic].fin;
						if (sC[ic].bns == -1) cout << "\t-";
						else cout << "\t" << sC[ic].bns;
						if (sC[ic].ttl == -1) cout << "\t-" << endl;
						else cout << "\t" << sC[ic].ttl << endl;
					}
					if (choice == 1)
					{
						if (course == Sch[ic].ID)
						{
							cout << "YOUR SCORES IN " << course << ": \n";
							cout << "\nMid: ";
							if (sC[ic].mid == -1) cout << " -\n";
							else cout << "\t" << sC[ic].mid;
							cout << "\nFinal: ";
							if (sC[ic].fin == -1) cout << " -\n";
							else cout << "\t" << sC[ic].fin;
							cout << "\nBonus: ";
							if (sC[ic].bns == -1) cout << " -\n";
							else cout << "\t" << sC[ic].bns;
							cout << "\nTotal: ";
							if (sC[ic].ttl == -1) cout << " -\n" << endl;
							else cout << "\t" << sC[ic].ttl << endl;
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
	if (choice == 1) cout << "\nYou have no class with ID " << course;
}