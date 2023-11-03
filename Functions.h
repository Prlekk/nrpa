#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Subject.h"

#include <fstream>
#include <random>
#include <time.h>
#include <cmath>
#include <ctime>
#include <sstream>

void pauseProgram();
bool isInt(std::string str);
int toInt(std::string str);
double roundToTwoDecimals(double value);
std::string randomDate();
std::string generateEmso(std::string date);
std::string randomNumber(int size);
std::vector<std::string> extractFromFile(std::string filename);
std::vector<Student> getStudentsFromFile(int size);
std::vector<Subject> generateSubjects(int firstId);
void selectAllFromStudents(std::vector<Student> students);
int firstAvaliableId(std::vector<Grade> grades);
int firstAvaliableId(std::vector<Student> students);
int firstAvaliableId(std::vector<Subject> subjects);
int firstAvaliableId(std::vector<Homework> homeworks);
int findIndexWithId(int id, std::vector<Grade> grades);
int findIndexWithId(int id, std::vector<Subject> subjects);
int findIndexWithId(int id, std::vector<Student> students);
std::string getSubjectName(int id, std::vector<Subject> subjects);
std::string getStudentName(int id, std::vector<Student> students);
void selectSubjectWhereIdIsInput(int selectedId, std::vector<Subject> subjects);
void selectStudentWhereIdIsInput(int selectedId, std::vector<Student> students, std::vector<Subject> subjects);
void selectIdAndNameFromStudents(std::vector<Student> students);
void selectIdAndNameFromSubjects(std::vector<Subject> subjects);
void selectIdAndNameFromGrades(std::vector<Grade> grades, std::vector<Subject> subjects, std::vector<Student> students);
void selectIdAndNameFromHomeworks(std::vector<Homework> homeworks, std::vector<Subject> subjects);
std::vector<int> selectDistinctSubjects(std::vector<Grade> studentGrades);
void selectAllGrades(Student student, std::vector<Subject> subjects);
void createSchool(std::vector<Subject> &subjects, std::vector<Student> &students, std::vector<Grade> &grades, std::ofstream &outputFile, std::string filename, char timestamp[20]);
void mainUserInterface();
int finishGrade(Student &student, int subjectId);
std::vector<int> selectStudentGradesFromSubject(Student student, int subjectId);
double studentSuccess(Student &student);
int userInput(int min, int max);
void selectStudentOptions();
void handleSelectedOptionForStudent(int selectedOption, int selectedId, std::vector<Student> &students, std::vector<Subject>& subjects, std::vector<Homework>& homeworks, std::vector<Grade> &allGrades, std::ofstream &outputFile);
void handleSelectedOptionForGrade(int selectedOption, int selectedId, std::vector<Student> &students, std::vector<Subject> subjects, std::vector<Grade> &allGrades, std::ofstream &outputFile);
void printGradeOptions();
void printStudentGrades(std::vector<int> distinctGrades, std::vector<Grade> grades, std::vector<Subject> subjects);
int binarySearch(std::vector<int> arr, int l, int r, int x);
int binarySearch(std::vector<Grade> arr, int l, int r, int x);
int binarySearch(std::vector<Subject> arr, int l, int r, int x);
void printGradeInfo(Grade grade, std::vector<Subject> subjects);
std::vector<Grade> addGradeToStudent(std::vector<Subject> subjects, Student &student, std::vector<Grade> &allGrades, std::ofstream &outputFile);
std::vector<Student> addStudentToSubject(std::vector<Student>& allStudents, std::vector<Subject>& subjects, Subject& subject, std::vector<Grade>& allGrades, std::ofstream& outputFile);
int gradeSelector();
std::string gradeTypeSelector();
bool compareSubjectsById(Subject& a, Subject& b);
void finishStudentGrades(Student &student, std::vector<Subject> subjects);
void clearScreen();
std::vector<Grade> removeGradeFromStudent(Student &student, std::ofstream &outputFile);
void selectSubjectOptions();
void printStudentInfo(Subject subject);
void printStudentUsingId(Subject subject, int studentId);
bool validateInput(std::string str);
Student createStudent(std::vector<Student>& allStudents, std::ofstream& outputFile);
std::vector<Student> removeStudentFromSubject(Subject &subject, std::ofstream &outputFile);
std::string getUserInput(const std::string& prompt);
std::vector<int> printSubjectFromStudent(Student student, std::vector<Subject> subjects);
std::vector<int> printHomeworkInfo(Subject subject, std::vector<Homework> homeworks);
std::vector<Homework> addHomeworkToSubject(std::vector<Homework>& homeworks, Subject& subject, std::ofstream& outputFile);
Date getDate();
bool checkIfDayValid(int day, Date date);
void removeHomeworkFromSubject(std::vector<Homework>& homeworks, Subject& subject, std::ofstream& outputFile);
bool isXInVector(std::vector<int> vec, int x);
std::vector<int> getSubjectStudents(std::vector<Student> students);

#endif