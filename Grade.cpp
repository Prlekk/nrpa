#include "Grade.h"

//Constructors
Grade::Grade() {}
Grade::Grade(int i, int stid, int suid, int g, const std::string& gt) {
    id = i;
    studentId = stid;
    subjectId = suid;
    grade = g;
    gradeType = gt;
}

//Destructors
Grade::~Grade() {}

//Setters
void Grade::setId(int i) { id = i; }
void Grade::setStudentId(int i) { studentId = i; }
void Grade::setSubjectId(int i) { subjectId = i; }
void Grade::setGrade(int g) { grade = g; }
void Grade::setGradeType(const std::string& g) { gradeType = g; }

//Getters
int Grade::getId() { return id; }
int Grade::getStudentId() { return studentId; }
int Grade::getSubjectId() { return subjectId; }
int Grade::getGrade() { return grade; }
const std::string& Grade::getGradeType() { return gradeType; }

//Class methods

void sleep(int time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

void printText(std::string str) {
    for (int i = 0; i < str.length(); i++) {
        std::cout << str[i] << std::flush;
        sleep(20);
    }
    std::cout << std::endl;
}
