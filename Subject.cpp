#include "Subject.h"

//Constructors
Subject::Subject() {}
Subject::Subject(int i, const std::string& n, const std::string& t) {
    id = i;
    name = n;
    teacher = t;
}

//Destructor
Subject::~Subject() {}

//Setters
void Subject::setId(int i) { id = i; }
void Subject::setName(const std::string& n) { name = n; }
void Subject::setTeacher(const std::string& t) { teacher = t; }
void Subject::setStudents(const std::vector<Student>& s){ students = s; }

//Getters
int Subject::getId() { return id; }
const std::string& Subject::getName() { return name; }
const std::string& Subject::getTeacher() { return teacher; }
std::vector<Student> Subject::getStudents() { return students; }

//Class methods
void Subject::addStudent(Student& student) {
    students.push_back(student);
}
