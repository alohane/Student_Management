#ifndef TUAN_H
#define TUAN_H
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#include<direct.h>
#include<process.h>
#include<time.h>
#include<string.h>
#include<windows.h>
#include <vector>
#include <sstream>
#include <iomanip>

#define semesterFile "Semester.txt"
struct semester {
	string year;
	string hk;
};
void academicYear();
void creatAcademicYear();
void updateAcademic();
void deleteAcademic();
void viewAcademic();
template <class T>
void delElementArr(T* a, int& n, int pos);
void chooseCurrentSemester();
//3.1

//3.2
struct date {
	int mon, day, year;
};
struct timess {
	int h, min;
};
typedef struct course_schedule {
	int No;
	string ID, Cname, cl, user, Lname, dgr;
	bool gen; //male=1; female=0
	date sdate, edate;
	timess stime, etime;
	string wDate;
	string room;
}COURSE;

struct node {
	COURSE data;
	node* next;
};
/*

18127100
20200402
Thang Nguyen
2020 04 02
19APCS1
1
9.5

9.5
2020 04 06 7 30 11 30 -1

2020 06 08 7 30 11 30 -1
1*/
struct Score {
	float mid = -1, final = -1, bonus = -1, total = -1;		//Midterm,Final,Bonus,Total
};
struct Attendance {
	date day;
	timess stime, etime;
	int status = -1;
};

struct ListAttendance {
	Attendance att[20];
	int num = 0;
};
struct Student {
	string name, ID, clas, pwd;
	date Dob;
	bool stat = true;
};

struct CourseStudent {
	Student std;
	Score scr;
	ListAttendance atd;
	bool CourseStat=true;
};

void importCourses();
int lengthList(node* pH);
void addToLastList(node*& pH, COURSE k);
node* getNode(COURSE k);
void delAllNode(node*& pH);
bool checkExist(string ID, COURSE* a, int n);
void saveToCourseList(semester smt, node* pH);
void inputClassName(string& classname, ifstream& f);
void importScheduleFromFileData(ifstream& f, node*& pH);
void exportToFileSchedule(string year, string hk, string classname, node* pH);
void importListStudent(CourseStudent*& a, int& numStudent, string classname);
ListAttendance importCalendar(date sdate, date edate, timess stime, timess etime);
void plusDay(date& a);
bool isLeapYear(date a);
void exportStudentCourse(string classname, semester smt, string IDcourse, CourseStudent* a, int num);
void loadCurSemeter(semester& smt);
////


//3.3 
void ManualAddANewCourse();
bool checkCourseExist(string x, string classname, node* pH);

//

//3.4
void editAnExistingCourse();
void editCourseList(semester smt, COURSE old, COURSE new_);
//

//3.5

bool removeFirstX(node*& pH, COURSE x);

void removeCourse();

//3.6
void RemoveStudentCourse();
void LoadStudentCourse(string classname, semester smt, string IDcourse, CourseStudent*& a, int& num);

//3.7
void loadListCourse(COURSE*& a, int& numC, semester smt);

void loadClassList(string*& a, int& numS);

bool CheckIDStudent(string classname, string ID,CourseStudent&);

void addSpecificStudentToCourse();

//3.8
void viewListCourse();
void viewAllCourse(string year, string hk);
void viewClassCourse(semester smt, string classname);

void exitMenu();
//

//3.9
void viewListStudent();

//3.11
void viewAllLecturer();

//2.4
void manuallyAddNewStudentToClass();

//2.5
void changeClassStudent();


//Login

void mainpage();




#endif // !Header_3_Tuan_H
