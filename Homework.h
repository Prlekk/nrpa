#ifndef HOMEWORK_H
#define HOMEWORK_H

#include "Date.h"

class Homework {
  private:
    int id;
    int subjectId;
    std::string assignment;
    Date dueDate;
  public:
    //Constructors
    Homework();
    Homework(int i, int s, std::string a);

    //Setters
    void setId(int i);
    void setSubjectID(int s);
    void setAssignment(std::string s);
    void setDueDate(int day, int month, int year);
    void setDueDate(int day, int month);
    void setDueDate(int day);

    //Getters
    int getId();
    int getSubjectId();
    std::string getAssignment();
    int getDueDateDay();
    int getDueDateMonth();
    int getDueDateYear();
    std::string getDueDateFullDate();
};

#endif