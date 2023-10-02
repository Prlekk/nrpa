#include "Functions.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<Grade> allGrades;
    std::vector<Subject> subjects;
    subjects = generateSubjects(firstAvaliableId(subjects));
    std::sort(subjects.begin(), subjects.end(), [](Subject& a, Subject& b) {
        return a.getName() < b.getName();
    });
    std::vector<Student> students = getStudentsFromFile(rand() % 20 + 2);

    createSchool(subjects, students, allGrades);
    printText("Added " + std::to_string(allGrades.size()) + " grades to " + std::to_string(subjects.size()) + " subjects with " + std::to_string(students.size()) + " students.");
    mainUserInterface();

    int input = userInput(0, 3);
    int selectedSubjectId = -1;
    int selectedStudentId = -1;
    int selectedGradeId = -1;

    switch (input) {
        case 1:
            selectIdAndNameFromSubjects(subjects);
            selectedSubjectId = userInput(0, subjects.size());
            break;
        case 2:
            selectIdAndNameFromStudents(students);
            selectedStudentId = userInput(0, students.size());
            selectStudentWhereIdIsInput(selectedStudentId, students, subjects);
            break;
        case 3:
            selectIdAndNameFromGrades(allGrades, subjects, students);
            selectedGradeId = userInput(0, allGrades.size());
        default:
            break;
    }
}
