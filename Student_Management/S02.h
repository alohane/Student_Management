#ifndef NHON_H
#define NHON_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <conio.h>
using namespace std;


struct Stu {
	string id;
	string pwd;
	string name;
	string dob;
	string cls;
	bool stat;
};
struct Lect {
	string usr;
	string pwd;
	string name;
	string lvl;
	bool gen;
};
struct Staff {
	string usr;
	string pwd;
	string name;
	bool gen;
};
struct classSchedule {
	int No;
	string ID;
	string name;
	string Class;
	string LectID;
	string Lectname;
	string Lectlvl;
	string Lectgen;
	int sd, sm, sy, ed, em, ey;
	string day;
	int sH, sM, eH, eM;
	string room;
};
struct stuLesson {
	int y, m, d, sh, sm, eh, em, att;
};
struct studentCourse {
	string ID;
	string pwd;
	string name;
	string DoB;
	int stat, gen, mid, fin, bns, ttl;
	stuLesson *Lss;
};

//1.1
void inputStudent(Stu*& St, int& n);
void inputLecturer(Lect*& lct, int& n);
void inputStaff(Staff*& stf, int& n);
void checkStaff(string usr, string pwd, int& type, bool& gen, string& name);
void checkLecturer(string usr, string pwd, int& type, bool& gen, string& name);
void checkStudent(string usr, string pwd, int& type, string& name);
void Login(int& type, string& usr);
void secretPwd(string usr, string& pwd);

//1.2
void StuMenu(string usr, int type);
void StaffMenu(string usr, int type);
void LectMenu(string usr, int type);
void ShowLogoutMenu();
void notexistedfunction(int type, string usr);
void LoggedinMenu(int& type, string& usr);
void StaffClassMenu(string usr, int type);
void StaffCoursesMenu(string usr, int type);
void StaffAttendanceMenu(string usr, int type);
void StaffScoreMenu(string usr, int type);

//1.3
void ViewProfile(string& usr, int& type);

//1.4
void getPassword(string& oldpwd, string& newpwd, string& cnewpwd, string oldp);
void changePasswordStu(string usr);
void changePasswordLect(string usr);
void changePasswordStaff(string usr);

//2.1
bool checkExistingClass(string Classname);
int numline(string file);
void inputListOfClass(string*& Class, int& n);
void csvToStu(Stu*& Class, string filename, int& n);
void viewStudentOfClass(string cls);
void StuToTxt(Stu* Class, string filename, int n);
void importStudentCSV(string usr);
bool checkStudentID(string ID);

//2.3
void EditStudent();
void getSID(Stu& s);

//2.6
void sortClassList(string* Class, int n);
void viewClassList(string usr);

//2.7
void viewClassStudentList(string usr);

//7.1
void getListClass(string*& classList, int &n);
void getcurSem(string& curSem);
bool getClassSch(string Class, classSchedule*& Sch, int &n);
bool getStuCourse(studentCourse*& sC, int &n, string CurSem, string Class, string Course, int &m);
bool attendStu(stuLesson& Lss);
void CheckIn(string usr);
void outputStuCourse(studentCourse* sC, int n, string CurSem, string Class, string Course, int m);

//7.2
void viewCheckinResult(string usr);
void viewCheckinResultofCourse(string Course, string usr);

//7.3
void viewSchedule(string usr);
void getschedule(string week[20][6], string ID, string day, int bh, int bm, int eh, int em);
void showSchedule(string week[20][6]);

//7.4
void viewScore(string usr);

#endif
