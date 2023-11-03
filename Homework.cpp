#include "Homework.h"

Homework::Homework() {}
Homework::Homework(int i, int s, std::string a) {
    id = i;
    subjectId = s;
    assignment = a;
}

void Homework::setId(int i) { id = i; }
void Homework::setSubjectID(int s) { subjectId = s; }
void Homework::setAssignment(std::string s) { assignment = s; }

void Homework::setDueDate(int day, int month, int year)
{
    dueDate.setDay(day);
    dueDate.setMonth(month);
    dueDate.setYear(year);
}

void Homework::setDueDate(int day, int month) {
    Date currentDate;
    dueDate.setDay(day);
    dueDate.setMonth(month);
    dueDate.setYear(currentDate.getYear());
}

void Homework::setDueDate(int day) { 
    Date currentDate;
    dueDate.setDay(day);
    dueDate.setMonth(currentDate.getMonth());
    dueDate.setYear(currentDate.getYear());
}

int Homework::getId() { return id; }
int Homework::getSubjectId() { return subjectId; }
std::string Homework::getAssignment() { return assignment; }
int Homework::getDueDateDay() { return dueDate.getDay(); }
int Homework::getDueDateMonth() { return dueDate.getMonth(); }
int Homework::getDueDateYear() { return dueDate.getYear(); }
std::string Homework::getDueDateFullDate() { return dueDate.getFullDate(); }
