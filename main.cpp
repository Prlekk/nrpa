#include "Functions.h"

int main() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&currentTime);
    char timestamp[20]; // Format: YYYYMMDD_HHMMSS
    std::strftime(timestamp, sizeof(timestamp), "%d%m%Y_%H%M%S", timeInfo);
    std::string filename = "output_" + std::string(timestamp) + ".txt";
    std::ofstream outputFile(filename);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<Grade> allGrades;
    std::vector<Subject> subjects;
    std::vector<Homework> homeworks;
    Date date;
    Homework h;
    h.setId(5);
    h.setSubjectID(2);
    h.setAssignment("test");
    h.setDueDate(1, 2, 2023);
    subjects = generateSubjects(firstAvaliableId(subjects));
    std::sort(subjects.begin(), subjects.end(), [](Subject& a, Subject& b) {
        return a.getName() < b.getName();
    });
    std::vector<Student> students = getStudentsFromFile(rand() % 20 + 2);

    if(outputFile.is_open()) {
        createSchool(subjects, students, allGrades, outputFile, filename, timestamp);
    }else {
        printText("Error opening file.");
        return 0;
    }

    printText("Added " + std::to_string(allGrades.size()) + " grades to " + std::to_string(subjects.size()) + " subjects with " + std::to_string(students.size()) + " students.");
    int input;
    int selectedSubjectId = -1;
    int selectedStudentId = -1;
    int selectedGradeId = -1;
    int selectedOption = 0;

    while(1){
        mainUserInterface();
        input = userInput(0, 4);
        switch (input) {
            case 1:
                selectIdAndNameFromSubjects(subjects);
                selectedSubjectId = userInput(0, subjects.size());
                if(selectedSubjectId == 0) {
                    printText("Returning...");
                    break;
                }
                selectSubjectWhereIdIsInput(selectedSubjectId, subjects);
                selectSubjectOptions();
                selectedOption = userInput(0, 6);
                handleSelectedOptionForStudent(selectedOption, selectedSubjectId, students, subjects, homeworks, allGrades, outputFile);
                break;
            case 2:
                selectIdAndNameFromStudents(students);
                selectedStudentId = userInput(0, students.size());
                if(selectedStudentId == 0) {
                    printText("Returning...");
                    break;
                }
                selectStudentWhereIdIsInput(selectedStudentId, students, subjects);
                selectStudentOptions();
                selectedOption = userInput(0, 4);
                handleSelectedOptionForGrade(selectedOption, selectedStudentId, students, subjects, allGrades, outputFile);
                break;
            case 3:
                selectIdAndNameFromGrades(allGrades, subjects, students);
                break;
            case 4:
                selectIdAndNameFromHomeworks(homeworks, subjects);
                break;
            case 0:
                printText("Goodbye...");
                sleep(1000);
                return 0;
            default:
                break;
        }
    }
    outputFile.close();
    return 0;
}