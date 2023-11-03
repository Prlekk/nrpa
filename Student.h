#ifndef STUDENT_H
#define STUDENT_H

#include "Grade.h"

#include <iostream>
#include <vector>

class Student
{
private:
    int id;
    std::string mail;
    std::string name;
    std::string birthDate;
    std::string emso;
    std::string city;
    std::string country;
    std::string phoneNumber;
    std::vector<Grade> grades;
    std::vector<Homework> homework;
    bool finishedGrades = false;
public:
    //Constructors
    Student();
    Student(int i, const std::string& m, const std::string& n, const std::string& bd, const std::string& e, const std::string& ci, const std::string& co, const std::string& pn);
    
    //Destructor
    ~Student();

    //Setters
    void setId(int i);
    void setMail(const std::string& m);
    void setName(const std::string& n);
    void setBirthDate(const std::string& b);
    void setEMSO(const std::string& e);
    void setCity(const std::string& c);
    void setCountry(const std::string& c);
    void setPhoneNumber(const std::string& p);
    void setGrades(const std::vector<Grade>& g);
    void setHomework(const std::vector<Homework>& h);
    void addHomeworkToHomeworks(Homework& h);
    void setFinishedGrades (const bool& f);

    //Getters
    int getId();
    const std::string& getMail();
    const std::string& getName();
    const std::string& getBirthDate();
    const std::string& getEMSO();
    const std::string& getCity();
    const std::string& getCountry();
    const std::string& getPhoneNumber();
    std::vector<Grade> getGrades();
    std::vector<Homework> getHomework();
    bool getFinishedGrades();
    

    //Class Methods
    void addGrade(int num, std::vector<Grade> &allGrades);
    void addGrade(int subjectId, int studentId, int grade, std::string gradeType, std::vector<Grade>& allGrades);
};


#endif
