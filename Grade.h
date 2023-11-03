#ifndef GRADE_H
#define GRADE_H

#include "Homework.h"

#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

class Grade {
  private:
    int id;
    int studentId;
    int subjectId;
    int grade;
    std::string gradeType;
  public:
    //Constructors
    Grade();
    Grade(int i, int stid, int suid, int g, const std::string& gt);
    
    //Destructor
    ~Grade();

    //Setters
    void setId(int i);
    void setStudentId(int i);
    void setSubjectId(int i);
    void setGrade(int g);
    void setGradeType(const std::string& g);

    //Getters
    int getId();
    int getStudentId();
    int getSubjectId();
    int getGrade();
    const std::string& getGradeType();

    //Class methods
};
void sleep(int time);
void printText(std::string str);

#endif