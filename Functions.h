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
int firstAvaliableId(std::vector<Subject> subjects);
int firstAvaliableId(std::vector<Student> students);
int findIndexWithId(int id, std::vector<Grade> grades);
int findIndexWithId(int id, std::vector<Subject> subjects);
int findIndexWithId(int id, std::vector<Student> students);
std::string getSubjectName(int id, std::vector<Subject> subjects);
std::string getStudentName(int id, std::vector<Student> students);
void selectStudentWhereIdIsInput(int selectedId, std::vector<Student> students, std::vector<Subject> subjects);
void selectIdAndNameFromStudents(std::vector<Student> students);
void selectIdAndNameFromSubjects(std::vector<Subject> subjects);
void selectIdAndNameFromGrades(std::vector<Grade> grades, std::vector<Subject> subjects, std::vector<Student> students);
std::vector<int> selectDistinctSubjects(std::vector<Grade> studentGrades);
void selectAllGrades(Student student, std::vector<Subject> subjects);
void createSchool(std::vector<Subject> &subjects, std::vector<Student> &students, std::vector<Grade> &grades);
void mainUserInterface();
int finishGrade(Student &student, int subjectId);
std::vector<int> selectStudentGradesFromSubject(Student student, int subjectId);
double studentSuccess(Student &student);
int userInput(int min, int max);
void selectStudentOptions();
void handleSelectedOptionForGrade(int selectedOption, int selectedId, std::vector<Student> students, std::vector<Subject> subjects);

#endif