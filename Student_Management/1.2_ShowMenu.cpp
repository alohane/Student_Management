#include "S01.h"
#include "S02.h"
#include "S03.h"

void notexistedfunction(int type, string usr)
{
	system("cls");
	cout << "This function is not available\nPlease choice other function:\n";
	switch (type) {
	case 1: { //staff menu
		StaffMenu(usr, type);
	}
	case 2: { //lecturer menu
		LectMenu(usr, type);
	}
	case 3: { //student menu
		StuMenu(usr, type);
	}
	}
}

//Student
void StuMenu(string usr, int type) {
	cout << "STUDENT MENU\n";
	cout << "1. Check-in\n2. View Check-in result\n3. View schedules\n4. View scores\n5. View profile\n6. Change password \n0. Logout\nYour choice: ";
	int choice;
	cin >> choice;
	switch (choice) {
	case 1: { //check-in
		system("cls");
		time_t now = time(0);
		tm* ltm = localtime(&now);
		ltm->tm_year -= 100;
		ltm->tm_mon += 1;
		cout << "CHECK-IN AT " << ltm->tm_year +2000<< "/";
		if (ltm->tm_mon < 10) cout << "0";
		cout << ltm->tm_mon << "/";
		if (ltm->tm_mday < 10) cout << "0";
		cout << ltm->tm_mday << " ";
		if (ltm->tm_hour < 10) cout << "0";
		cout << ltm->tm_hour << "h";
		if (ltm->tm_min < 10) cout << "0";
		cout << ltm->tm_min << "m";
		if (ltm->tm_sec < 10) cout << "0";
		cout << ltm->tm_sec << "s" << endl;
		CheckIn(usr);
		cout << "\nPress any key to back...";
		_getch();
		system("cls");
		StuMenu(usr, 3);

	}
	case 2: { //view check-in result
		viewCheckinResult(usr);
		cout << "\nPress any key to back...";
		_getch();
		system("cls");
		StuMenu(usr, 3);

	}
	case 3: { //view schedules
		viewSchedule(usr);
		system("cls");
		StuMenu(usr, 3);

	}
	case 4: { //view scores
		viewScore(usr);
		cout << "\nPress any key to back...";
		_getch();
		system("cls");
		StuMenu(usr, 3);
	}
	case 5: { //view profile
		ViewProfile(usr, type);
	}
	case 6: { //change password
		changePasswordStu(usr);
		system("cls");
		StuMenu(usr, 3);
	}
	case 0: { //logout
		system("cls");
		ShowLogoutMenu();
	}
	default: {
		system("cls");
		cout << "Your choice must be 0-6!!\n";
		StuMenu(usr, type);
	}
	}
}
//Staff
void StaffMenu(string usr, int type) {
	cout << "STAFF MENU\n";
	cout << "1. Class\n2. Courses\n3. Score board\n4. Attendance\n5. View profile\n6. Change password\n0. Logout\nYour choice: ";
	int choice;
	cin >> choice;
	switch (choice) {
	case 1: { //class
		system("cls");
		StaffClassMenu(usr, 1);
	}
	case 2: { //courses
		system("cls");
		StaffCoursesMenu(usr, 1);
	}
	case 3: { //score board
		system("cls");
		StaffScoreMenu(usr, 1);
	}
	case 4: { //attendance
		system("cls");
		StaffAttendanceMenu(usr, 1);
	}
	case 5: { //profile
		ViewProfile(usr, type);
	}
	case 6: { //change password
		changePasswordStaff(usr);
		system("cls");
		StaffMenu(usr, 1);
	}
	case 0: { //logout
		system("cls");
		ShowLogoutMenu();
	}
	default: {
		system("cls");
		cout << "Your choice must be 0-6!!\n";
		StaffMenu(usr, type);
	}
	}
}
void StaffClassMenu(string usr, int type)
{
	cout << "STAFF's CLASS MENU\n";
	cout << "1. Import class form csv file\n2. Add new student to class\n3. Edit an existing student\n4. Remove a student\n5. Change class of a student\n6. View list of class\n7. View list of student of a class\n0. Back\nYour choice: ";
	int choice;
	cin >> choice;
	switch (choice) {
	case 1: {
		importStudentCSV(usr);
	}
	case 2: {
		system("cls");
		manuallyAddNewStudentToClass();
		system("cls");
		StaffClassMenu(usr, 1);
	}
	case 3: {
		EditStudent();
		system("cls");
		StaffClassMenu(usr, 1);
	}
	case 4: {
		RemoveStudent();
		system("cls");
		StaffClassMenu(usr, 1);
	}
	case 5: {
		changeClassStudent();
		system("cls");
		StaffClassMenu(usr, 1);
	}
	case 6: {
		viewClassList(usr);
	}
	case 7: {
		viewClassStudentList( usr);
	}
	case 0: {
		system("cls");
		StaffMenu(usr, 1);
	}
	default: {
		system("cls");
		cout << "Your choice must be 0-7!!\n";
		StaffClassMenu(usr, 1);
	}
	}
}
void StaffCoursesMenu(string usr, int type)
{
	cout << "STAFF's COURSES MENU\n";
	cout << "1. Create/Updata/Delete/View academic year\n2. Import courses form csv file\n3. Add new course\n4. Edit an existing course\n5. Remove a course\n6. Remove a student from a course\n7. Add a special student to a course\n8. View list of a course\n9. List of student of a course\n10. View attendance list of course\n11. View all lecturer\n0. Back\nYour choice: ";
	int choice;
	cin >> choice;
	switch (choice) {
	case 1: {
		academicYear();
		StaffCoursesMenu(usr, 1);
	}
	case 2: {
		importCourses();
		StaffCoursesMenu(usr, 1);
	}
	case 3: {
		ManualAddANewCourse();
		StaffCoursesMenu(usr, 1);
	}
	case 4: {
		editAnExistingCourse();
		StaffCoursesMenu(usr, 1);
	}
	case 5: {
		removeCourse();
		StaffCoursesMenu(usr, 1);
	}
	case 6: {
		RemoveStudentCourse();
		StaffCoursesMenu(usr, 1);
	}
	case 7: {
		addSpecificStudentToCourse();
		StaffCoursesMenu(usr, 1);
	}
	case 8: {
		viewListCourse();
		StaffCoursesMenu(usr, 1);
	}
	case 9: {
		viewListStudent();
		StaffCoursesMenu(usr, 1);
	}
	case 10: {
		ViewAttendanceList();
		StaffCoursesMenu(usr, 1);
	}
	case 11: {
		viewAllLecturer();
		StaffCoursesMenu(usr, 1);
	}
	case 0: {
		system("cls");
		StaffMenu(usr, 1);
	}
	default: {
		system("cls");
		cout << "Your choice must be 0-11!!\n";
		StaffCoursesMenu(usr, 1);
	}
	}
}
void StaffScoreMenu(string usr, int type)
{
	cout << "STAFF's SCORE MENU\n";
	int choice;
	cout << "1. View score board of a course\n2. Export score board to a csv file\n0. Back\nYour choice: ";
	cin >> choice;
	switch (choice) {
	case 1: {
		ViewScoreBoard();
		system("cls");
		StaffScoreMenu(usr, 1);
	}

	case 2: {
		ExportScoreBoard();	
		system("cls");
		StaffScoreMenu(usr, 1);
	}
	case 0: {
		system("cls");
		StaffMenu(usr, 1);
	}
	default: {
		system("cls");
		cout << "Your choice must be 0-2!!\n";
		StaffScoreMenu(usr, 1);
	}
	}
}
void StaffAttendanceMenu(string usr, int type)
{
	cout << "STAFF's ATTENDANCE MENU\n";
	cout << "1. View attendance list of a course\n2. Export attendance list form csv file\n0. Back\nYour choice: ";
	int choice;
	cin >> choice;
	switch (choice) {
	case 1: {
		ViewAttendanceList();
		system("cls");
		StaffAttendanceMenu(usr, 1);
	}
	case 2: {
		ExportAttendanceList();
		system("cls");
		StaffAttendanceMenu(usr, 1);
	}
	case 0: {
		system("cls");
		StaffMenu(usr, 1);
	}
	default: {
		system("cls");
		cout << "Your choice must be 0-2!!\n";
		StaffAttendanceMenu(usr, 1);
	}
	}
}
//Lecturer
void LectMenu(string usr, int type) {
	cout << "LECTURER MENU\n";
	cout << "1. View current courses\n2. View students of a course\n3. View attendance list of a course\n4. Edit Attendance\n5. Import score board\n6. Edit grade\n7. View scoreboard\n8. View profile\n9. Change password\n0. Logout\nYour choice: ";
	int choice;
	cin >> choice;
	switch (choice) {
	case 1: { //courses
		ViewCurSem();
		system("cls");
		LectMenu(usr, 2);
	}
	case 2: { //students of course
		ViewCourseStudent();
		system("cls");
		LectMenu(usr, 2);
	}
	case 3: { //view attendance
		ViewAttendanceListLecturer();
		system("cls");
		LectMenu(usr, 2);
	}
	case 4: { //edit attendance
		EditAttendance();
		system("cls");
		LectMenu(usr, 2);
	}
	case 5: { //score board
		ImportScoreboard();
		system("cls");
		LectMenu(usr, 2);

	}
	case 6: { //Edit grade
		EditScoreboard();
		system("cls");
		LectMenu(usr, 2);
	}
	case 7: { //ViewScoreboard
		ViewScoreBoardLecturer();
		system("cls");
		LectMenu(usr, 2);
	}
	case 8: { //View profile
		ViewProfile(usr, type);
	}
	case 9: { //Change password
		changePasswordLect(usr);
		system("cls");
		StuMenu(usr, 2);
	}
	case 0: { //logout
		system("cls");
		ShowLogoutMenu();
	}
	default: {
		system("cls");
		cout << "Your choice must be 0-9!!\n";
		LectMenu(usr, type);
	}
	}
}

void ShowLogoutMenu()
{
	int choice;
	cout << "WELCOME\n1. Login\n0. Exit\nYour choice: "; cin >> choice;
	system("cls");
	if (choice != 0)
	{
		string usr;
		int type;
		Login(type, usr);
		LoggedinMenu(type, usr);
	}
	else exit(0);
}

void LoggedinMenu(int& type, string& usr)
{
	switch (type)
	{
	case 0: {
		while (type == 0) Login(type, usr); //Login fail: Login again
	}
	case 1: {
		StaffMenu(usr, type); //user is 1-staff: Show staff menu
		break;
	}
	case 2: {
		LectMenu(usr, type); //user is 2-lecturer: Show lecturer menu
		break;
	}
	case 3: {
		StuMenu(usr, type); //user is 3-student: Show student menu
		break;
	}
	}
}
