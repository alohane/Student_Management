#ifndef minh_h
#define minh_h
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<iomanip>
#include <cmath>
using namespace std;
// Minh

struct sem {
	string year;
	string sem;
};

struct courseInfo
{
	string id;
	string name;
};

typedef struct student {
	int id=0;			// MSSV
	int number = 0;
	string password;
	string name;
	string DoB;
	string Class;
	int stat=0;
	int gender = 0;
}STU;

struct score {
	float midterm=0;
	float bonus=0;
	float final=0;
	float total=0;
};

typedef struct attendance {
	int year=0;
	int month=0;
	int day=0;
	int startHour=0;	// Giờ bắt đầu học
	int startMin=0;	// Phút bắt đầu học
	int endHour=0;	// Giờ học xong
	int endMin=0;		// Phút học xong
	int stat=0;
}ATD;

struct course
{
	STU student;
	score mark;
	ATD attendance[100];
};

// 2.4
void Save(course*& a, int& n, string& courseCode);
void RemoveMainClass(ifstream& fin, int& n, string classname, int idCheck);
void RemoveStudentDatabase(int removeID);
void LoadCourseList(courseInfo*& courseList, int& numCourse);
void LoadClassList(string*& classList, int& numClass);
void RemoveStudent();

//4.1_2
void LoadCurSem(sem& smt);
int Load(course*& a, int& n, string& courseCode);
void SaveScore(course info, int n, fstream& fout, int i);
void PrintScore(course info, int n, int i);
string CheckCourse(string courseCode);
string CheckClass(string classname);
void ViewScoreBoard();
void ExportScoreBoard();

//5.1_2
void SaveAttendance(course info, int n, fstream& fout, int i);
void PrintAttendance(course info, int n, int i);
void ViewAttendanceList();
void ExportAttendanceList();

//6.1_2_3
void ViewCurSem();
void PrintStudent(course info, int n, int i);
void ViewCourseStudent();
void ViewAttendanceListLecturer();

//6.4_5_6_7
void ViewScoreBoardLecturer();
void EditAttendance();
void EditScoreboard();
int ImportCSV(course*& b, int& n, string& courseCode);
void ImportScoreboard();

#endif