#ifndef SUBJECT_H
#define SUBJECT_H

#include "Student.h"

#include <algorithm>

class Subject {
    private:
        int id;
        std::string name;
        std::string teacher;
        std::vector<Student> students;
    public:
        //Constructors
        Subject();
        Subject(int i, const std::string& n, const std::string& t);
        
        //Destructor
        ~Subject();

        //Setters
        void setId(int i);
        void setName(const std::string& n);
        void setTeacher(const std::string& t);
        void setStudents(const std::vector<Student>& s);
        
        //Getters
        int getId();
        const std::string& getName();
        const std::string& getTeacher();
        std::vector<Student> getStudents();

        //Class methods
        void addStudent(Student& student);
};

#endif