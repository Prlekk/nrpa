#include "Functions.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<Grade> allGrades;
    std::vector<Subject> subjects;
    subjects = generateSubjects(firstAvaliableId(subjects));
    std::vector<Student> students = getStudentsFromFile(rand() % 98 + 2);
    for(int i = 0; i < subjects.size(); i++) {
        for(int j = 0; j < students.size(); j++) {
            subjects[i].addStudent(students[j]);
            for(int k = 0; k < rand() % 4 + 1; k++) {
                students[j].addGrade(subjects[i].getId(), allGrades);
            }
        }
    }
    printText("Added " + std::to_string(allGrades.size()) + " grades to " + std::to_string(subjects.size()) + " subjects with " + std::to_string(students.size()) + " students.");
    
}