#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Subject.h"

#include <fstream>
#include <random>
#include <time.h>

void pauseProgram();
bool isInt(std::string str);
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
std::string getSubjectName(int id, std::vector<Subject> subjects);
void selectIdAndNameFromStudents(std::vector<Student> students);
void selectAllGrades(Student student, std::vector<Subject> subjects);
#endif