#include "Functions.h"
#include "Student.h"

void pauseProgram() {
    char input;
        std::cout << "Press ENTER to continue...";
        std::cin.get(input);
        if(input != ' ') {
            input = ' ';
    }
}

bool isInt(std::string str) {
    int i = 0;
    if(str.empty()) return false;
    if(str[0] == '-' || str[0] == '+') i = 1;
    for(; i < str.length(); i++) {
        if(str[i] < 48 || str[i] > 57) {
            return false;
        }
    }
    return true;
}

int toInt(std::string str) {
    int num = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] < '0' || str[i] > '9') return -1;
        num = num * 10;
        num = num + (str[i] - '0');
    }
    return num;
}

double roundToTwoDecimals(double value) {
    return std::round(value * 100.0) / 100.0;
}

std::string toLowerCase(std::string str) {
    if(str.empty()) return "";
    for(int i = 0; i < str.length(); i++) {
        if(str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
    return str;
}

std::string randomDate() {
    int d = rand() % 31 + 1;
    int m = rand() % 12 + 1;
    int y = rand() % 8 + 2001;
    
    std::string day = "";
    std::string month = "";
    std::string year = std::to_string(y);
    if(d < 10) {
        day = "0" + std::to_string(d);
    }else {
        day = std::to_string(d);
    }
    if(m < 10) {
        month = "0" + std::to_string(m);
    }else {
        month = std::to_string(m);
    }
    std::string date = day + "-" + month + "-" + year;
    //std::string emso = day + month + year.substr(1, year.length()-1);
    return date;
}

std::string generateEmso(std::string date) {
    int num = rand() % 2 * 5;
    date = date.substr(0,2) + date.substr(3,2) + date.substr(7, 3) + "50" + std::to_string(num) + randomNumber(3);
    return date;
}

std::string randomNumber(int size) {
    std::string num = "";
    for(int i = 0; i < size; i++) {
        num = num + std::to_string(rand() % 10);
    }
    return num;
}

std::vector<std::string> extractFromFile(std::string filename) {
    std::fstream file(filename);
    std::string line;
    std::vector<std::string> temp;
    if(!file.is_open()) {
        printText("Error opening file.");
        return temp;
    }
    while(getline(file, line)) {
        temp.push_back(line);
    }
    file.close();
    return temp;
}

std::vector<Student> getStudentsFromFile(int size) {
    std::vector<std::string> names = extractFromFile("names.txt");
    std::vector<std::string> surnames = extractFromFile("surnames.txt");
    std::vector<std::string> cities = extractFromFile("cities.txt");
    std::vector<std::string> countries = extractFromFile("countries.txt");

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(names.begin(), names.end(), g);
    std::shuffle(surnames.begin(), surnames.end(), g);
    std::shuffle(cities.begin(), cities.end(), g);
    std::shuffle(countries.begin(), countries.end(), g);

    std::vector<Student> temp;
    for(int i = 0; i < size && i < 100; i++) {
        Student s(i+1, toLowerCase(surnames[i]) + "." + toLowerCase(names[i]) + "@gmail.com", surnames[i] + " " + names[i], randomDate(), "", cities[i], countries[i], randomNumber(9));
        s.setEMSO(generateEmso(s.getBirthDate()));
        temp.push_back(s);
    }
    std::shuffle(temp.begin(), temp.end(), g);
    return temp;
}

std::vector<Subject> generateSubjects(int firstId) {
    std::vector<std::string> names = extractFromFile("subjects.txt");
    std::vector<std::string> teachers = extractFromFile("teachers.txt");
    std::vector<Subject> temp;
    for(int i = 0; i < names.size() && i < teachers.size(); i++) {
        Subject s(firstId + i, names[i], teachers[i]);
        temp.push_back(s);
    }
    return temp;
}

void selectAllFromStudents(std::vector<Student> students) {
    std::string line = "";
    printText("----------------------------------------------------------------------------------------------------------");
    printText("| ID\t| Name\t\t| Mail\t\t\t| Birth Date | EMSO\t\t| City | Country | Phone Number |");
    printText("----------------------------------------------------------------------------------------------------------");
    for(auto i : students) {
        line = "| " + std::to_string(i.getId()) + "\t| " + i.getName() + "\t| " + i.getMail() + "\t| " + i.getBirthDate() + "   | " + i.getEMSO() + "\t| " + i.getCity() + i.getCountry() + i.getPhoneNumber() + " |";
        printText(line);
    }
}

int firstAvaliableId(std::vector<Grade> grades) {
    if(grades.empty()) return 1;
    std::sort(grades.begin(), grades.end(), [](Grade& g1, Grade& g2) {
        return g1.getId() < g2.getId();
    });
    return grades.back().getId() + 1;
}

int firstAvaliableId(std::vector<Subject> subjects) {
    if(subjects.empty()) return 1;
    std::sort(subjects.begin(), subjects.end(), [](Subject& s1, Subject& s2) {
        return s1.getId() < s2.getId();
    });
    return subjects.back().getId() + 1;
}

int firstAvaliableId(std::vector<Homework> homeworks) {
    if(homeworks.empty()) return 1;
    std::sort(homeworks.begin(), homeworks.end(), [](Homework& h1, Homework& h2) {
        return h1.getId() < h2.getId();
    });
    return homeworks.back().getId() + 1;
}

int firstAvaliableId(std::vector<Student> students) {
    if (students.empty()) return 1;
    std::sort(students.begin(), students.end(), [](Student& s1, Student& s2) {
        return s1.getId() < s2.getId();
    });
    return students.back().getId() + 1;
}

int findIndexWithId(int id, std::vector<Student> students) {
    for(int i = 0; i < students.size(); i++) {
        if(students[i].getId() == id) return i;
    }
    return -1;
}

int findIndexWithId(int id, std::vector<Subject> subjects) {
    for(int i = 0; i < subjects.size(); i++) {
        if(subjects[i].getId() == id) return i;
    }
    return -1;
}

int findIndexWithId(int id, std::vector<Grade> grades) {
    for(int i = 0; i < grades.size(); i++) {
        if(grades[i].getId() == id) return i;
    }
    return -1;
}

std::string getSubjectName(int id, std::vector<Subject> subjects)
{
    for(auto i : subjects) {
        if(i.getId() == id) return i.getName();
    }
    return "";
}

std::string getStudentName(int id, std::vector<Student> students) {
    for(auto i : students) {
        if(i.getId() == id) return i.getName();
    }
    return "";
}

void selectSubjectWhereIdIsInput(int selectedId, std::vector<Subject> subjects) {
    int index = findIndexWithId(selectedId, subjects);
    std::vector<Student> students = subjects[index].getStudents();
    printText("-----------------------");
    printText("ID: " + std::to_string(subjects[index].getId()));
    printText("Name: " + subjects[index].getName());
    printText("Teacher: " + subjects[index].getTeacher());
    printText("");
    printText("Students:");
    for(auto i : subjects[index].getStudents()) {
        printText("\t" + i.getName());
    }
}

void selectStudentWhereIdIsInput(int selectedId, std::vector<Student> students, std::vector<Subject> subjects) {
    int index = findIndexWithId(selectedId, students);
    std::vector<Grade> grades = students[index].getGrades();
    std::vector<int> distinctGrades = selectDistinctSubjects(grades);
    printText("-----------------------");
    printText("ID: " + std::to_string(students[index].getId()));
    printText("Name: " + students[index].getName());
    printText("Mail: " + students[index].getMail());
    printText("Birth Date: " + students[index].getBirthDate());
    printText("EMSO: " + students[index].getEMSO());
    printText("City: " + students[index].getCity());
    printText("Country: " + students[index].getCountry());
    printText("Phone Number: " + students[index].getPhoneNumber());
    printText("");
    printText("Grades:");
    if(students[index].getFinishedGrades()) {
        printGradeOptions();
        int option = userInput(1, 2);
        switch (option)
        {
        case 1:
            finishStudentGrades(students[index], subjects);
            break;
        case 2:
            printStudentGrades(distinctGrades, grades, subjects);
        default:
            break;
        }
    }else {
        printStudentGrades(distinctGrades, grades, subjects);
    }
    printText("");
    printText("Homework:");
    if(students[index].getHomework().empty()) {
        printText("\t" + students[index].getName() + " does not have any homework.");
    }else {
        for(auto i : students[index].getHomework()) {
            printText("\t" + getSubjectName(i.getSubjectId(), subjects) + "\t" + i.getAssignment() + " due to: " + i.getDueDateFullDate());
        }
    }
}

void printGradeOptions() {
    printText("-----------------------");
    printText("Choose and option:");
    printText("1\tPrint Finished Grades");
    printText("2\tPrint All Grades");
}

void printStudentGrades(std::vector<int> distinctGrades, std::vector<Grade> grades, std::vector<Subject> subjects) {
    for(auto i : distinctGrades) {
        std::string line = "\t";
        double average = 0;
        double size = 0;
        for(int j = 0; j < grades.size(); j++) {
            if(grades[j].getSubjectId() == i) {
                line = line + std::to_string(grades[j].getGrade()) + " ";
                average += grades[j].getGrade();
                size++;
            }
        }
        printText("\t" + getSubjectName(i, subjects) + ": " + line);
    }
}

void selectIdAndNameFromStudents(std::vector<Student> students){
    std::string line = "";
    printText("ID\t| Name");
    printText("-----------------------");
    for(auto i : students) {
        line = std::to_string(i.getId()) + "\t| " + i.getName();
        printText(line);
    }
    printText("");
    printText("0\tExit program");
    printText("-------------------------");
}

void selectIdAndNameFromSubjects(std::vector<Subject> subjects) {
    std::string line = "";
    printText("-----------------------");
    printText("ID\t| Name");
    printText("-----------------------");
    for(auto i : subjects) {
        line = std::to_string(i.getId()) + "\t| " + i.getName();
        printText(line);
    }
    printText("");
    printText("0\tExit program");
    printText("-----------------------");
}

void selectIdAndNameFromGrades(std::vector<Grade> grades, std::vector<Subject> subjects, std::vector<Student> students) {
    std::string line = "";
    bool printed = false;
    printText("-----------------------------------------------");
    printText("ID\t| Student\t| Subject\t| Grade");
    printText("-----------------------------------------------");
    for(auto i : grades) {
        std::string subject = getSubjectName(i.getSubjectId(), subjects);
        std::string student = getStudentName(i.getStudentId(), students);
        line = std::to_string(i.getId()) + "\t| " + student + "\t| " + subject + "\t\t| " + std::to_string(i.getGrade());
        std::cout << line << std::endl;
        printed = true;
    }
    if(!printed) printText("There are no grades in grades list.");
}

void selectIdAndNameFromHomeworks(std::vector<Homework> homeworks, std::vector<Subject> subjects) {
    std::string line = "";
    bool printed = false;
    printText("-----------------------------------------------");
    printText("ID\t| Subject\t| Assingment\t| Due Date");
    printText("-----------------------------------------------");
    for(auto i : homeworks) {
        std::string subjectName = getSubjectName(i.getSubjectId(), subjects);
        line = std::to_string(i.getId()) + "\t| " + subjectName + "\t\t| " + i.getAssignment() + "\t| " + i.getDueDateFullDate();
        printText(line);
        printed = true;
    }
    if(!printed) printText("There are no assingments in homeworks list.");
}

std::vector<int> selectDistinctSubjects(std::vector<Grade> studentGrades) {
    std::vector<int> temp;
    for (Grade grade : studentGrades) {
        int subjectId = grade.getSubjectId();
        if (std::find(temp.begin(), temp.end(), subjectId) == temp.end()) {
            temp.push_back(subjectId);
        }
    }
    return temp;
}


void Student::addGrade(int num, std::vector<Grade> &allGrades) {
    int randomReason = rand() % 3;
    std::vector<std::string> reasons = extractFromFile("reasons.txt");
    Grade grade(firstAvaliableId(allGrades), id, num, rand() % 5 + 1, reasons[randomReason]);
    grades.push_back(grade);
    allGrades.push_back(grade);
}

void Student::addGrade(int subjectId, int studentId, int gradeNum, std::string gradeType, std::vector<Grade>& allGrades) {
    Grade grade;
    grade.setId(firstAvaliableId(allGrades));
    grade.setStudentId(studentId);
    grade.setSubjectId(subjectId);
    grade.setGrade(gradeNum);
    grade.setGradeType(gradeType);
    grades.push_back(grade);
    allGrades.push_back(grade);
}

void selectAllGrades(Student student, std::vector<Subject> subjects) {
    std::string line = "";
    printText("ID\t| Subject | Grade");
    printText("-------------------------");
    for(auto i : student.getGrades()) {
        line = std::to_string(i.getId()) + "\t| " + getSubjectName(i.getSubjectId(), subjects) + "\t  | " + std::to_string(i.getGrade());
        printText(line);
    }
    printText("");
    printText("0\tExit program");
    printText("-------------------------");
}

void createSchool(std::vector<Subject> &subjects, std::vector<Student> &students, std::vector<Grade> &grades, std::ofstream& outputFile, std::string filename, char timestamp[20]) {
    outputFile << "File created on " << timestamp << std::endl;

    for (int i = 0; i < subjects.size(); i++) {
        for (int j = 0; j < students.size(); j++) {
            outputFile << "Added " << students[j].getName() << " to " << subjects[i].getName() << "." << std::endl;
            for (int k = 0; k < rand() % 6 + 4; k++) {
                students[j].addGrade(subjects[i].getId(), grades);
                outputFile << "Added grade ID " << students[j].getGrades().back().getId() << " to " << students[j].getName() << "." << std::endl;
            }
        }
        subjects[i].setStudents(students);
    }

}

void mainUserInterface() {
    printText("----------------------------");
    printText("Choose an option:");
    printText("1\tSubjects");
    printText("2\tStudents");
    printText("3\tGrades");
    printText("4\tHomeworks");
    printText("");
    printText("0\tExit program");
    printText("----------------------------");
}


std::vector<int> selectStudentGradesFromSubject(Student student, int subjectId) {
    std::vector<int> grades;
    if(student.getGrades().empty()) return grades;
    for(int i = 0; i < student.getGrades().size(); i++) {
        if(student.getGrades()[i].getSubjectId() == subjectId) {
            grades.push_back(student.getGrades()[i].getGrade());
        }
    }
    return grades;
}

double studentSuccess(Student &student) {
    std::vector<int> lastGrades;
    std::vector<int> subjects = selectDistinctSubjects(student.getGrades());
    if(subjects.empty()) return 0.0;
    int sum = 0;
    int finnishedGrades = 0;
    for(int i = 0; i < subjects.size(); i++) {
        if(finishGrade(student, subjects[i]) != 0) {
            sum += finishGrade(student, subjects[i]);
            finnishedGrades++;
        }
    }
    return sum / finnishedGrades;
}

int finishGrade(Student &student, int subjectId) {
    std::vector<int> grades = selectStudentGradesFromSubject(student, subjectId);
    if(grades.size() < 4) return 0;
    double sum = 0;
    for(int i = 0; i < grades.size(); i++) {
        sum += grades[i];
    }
    sum = sum / grades.size();
    return round(sum);
}

int userInput(int min, int max)
{
    std::string input = "";
    do{
        std::cout << "Input: ";
        getline(std::cin, input);
        if(toInt(input) < min || toInt(input) > max) {
            printText("Invalid input. Try againn.");
        }
    }while(toInt(input) < min || toInt(input) > max);
    return toInt(input);
}

void selectSubjectOptions() {
    printText("----------------------------");
    printText("Choose an option:");
    printText("1\tSelect Student");
    printText("2\tAdd Student");
    printText("3\tRemove Student");
    printText("");
    printText("4\tShow All Homeworks");
    printText("5\tAdd Homework");
    printText("6\tRemove Homework");
    printText("");
    printText("0\tExit program");
    printText("----------------------------");
}

void selectStudentOptions() {
    printText("----------------------------");
    printText("Choose an option:");
    printText("1\tSelect Grade");
    printText("2\tAdd Grade");
    printText("3\tRemove Grade");
    printText("4\tFinish Grades");
    printText("");
    printText("0\tExit program");
    printText("----------------------------");
}

void handleSelectedOptionForStudent(int selectedOption, int selectedId, std::vector<Student> &students, std::vector<Subject>& subjects, std::vector<Homework>& homeworks, std::vector<Grade> &allGrades, std::ofstream &outputFile) {
    int index = findIndexWithId(selectedId, subjects);
    std::vector<Student> subjectStudents = subjects[index].getStudents();
    std::vector<int> homeworkIds;
    std::string line = "";
    int option = -1;
    switch (selectedOption)
    {
    case 0:
        break;
    case 1:
        printStudentInfo(subjects[index]);
        do{
            option = userInput(0, firstAvaliableId(subjects[index].getStudents()) - 1);
            if(findIndexWithId(option, subjects[index].getStudents()) == -1) {
                printText(subjects[index].getName() + " does not possess a student with ID " + std::to_string(option));
            }
        }while(findIndexWithId(option, subjects[index].getStudents()) == -1);
        if(option == 0) break;
        printStudentUsingId(subjects[index], option);
        break;
    case 2:
        subjects[index].setStudents(addStudentToSubject(students, subjects, subjects[index], allGrades, outputFile));
        break;
    case 3:
        subjects[index].setStudents(removeStudentFromSubject(subjects[index], outputFile));
        break;
    case 4:
        printHomeworkInfo(subjects[index], homeworks);
        break;
    case 5:

        // std::vector<Student> temp = subjects[0].getStudents();
        // temp[0].addHomeworkToHomeworks(h);
        // subjects[0].setStudents(temp);
        // printText(subjects[0].getStudents()[0].getHomework().back().getAssignment());

        homeworks = addHomeworkToSubject(homeworks, subjects[index], outputFile);
        subjectStudents = subjects[index].getStudents();
        for(auto& i : subjectStudents) {
            i.addHomeworkToHomeworks(homeworks.back());
        }
        subjects[index].setStudents(subjectStudents);
        for(auto& i : students) {
            if(isXInVector(getSubjectStudents(subjectStudents), i.getId())) {
                i.addHomeworkToHomeworks(homeworks.back());
            }
        }
        printText(subjects[index].getStudents()[0].getHomework().back().getAssignment());
        printText(students[0].getHomework().back().getAssignment());
        break;
    case 6:
        removeHomeworkFromSubject(homeworks, subjects[index], outputFile);
        break;
    default:
        break;
    }
}

bool isXInVector(std::vector<int> vec, int x) {
    return std::find(vec.begin(), vec.end(), x) != vec.end();
}

std::vector<int> getSubjectStudents(std::vector<Student> students) {
    std::vector<int> temp;
    for(auto i : students) {
        temp.push_back(i.getId());
    }
    return temp;
}

void printStudentInfo(Subject subject) {
    std::string line = "";
    printText("----------------------------");
    printText("ID\t| Name");
    printText("----------------------------");
    for(auto i : subject.getStudents()) {
        line = std::to_string(i.getId()) + "\t| " + i.getName();
        printText(line);
    }
}

void printStudentUsingId(Subject subject, int studentId) {
    std::string line = "";
    printText("----------------------------");
    printText("| ID\t| Name\t\t| Mail\t\t\t| Birth Date | EMSO\t\t| City\t| Country | Phone Number |");
    for(auto i : subject.getStudents()) {
        if(i.getId() == studentId) {
            line = "| " + std::to_string(i.getId()) + "\t| " + i.getName() + "\t| " + i.getMail() + "\t| " + i.getBirthDate() + " | " + i.getEMSO() + "\t| " + i.getCity() + "\t| " + i.getCountry() + " | " + i.getPhoneNumber() + "\t|";
            printText(line);
        }
    }
}

std::vector<int> printHomeworkInfo(Subject subject, std::vector<Homework> homeworks) {
    std::vector<int> subjectHomeworkIds;
    std::string line = "";
    if(homeworks.empty()) {
        printText("There are no homework assingments.");
    }else {
        bool printed = false;
        printText("----------------------------");
        printText("ID\t| Assignment\t| Due Date");
        printText("----------------------------");
        for(auto i : homeworks) {
            if(i.getSubjectId() == subject.getId()) {
                if(i.getDueDateYear() == 0) {
                    line = std::to_string(i.getId()) + "\t| " + i.getAssignment() + "\t| " + "No Due Date Set";
                } else {
                    line = std::to_string(i.getId()) + "\t| " + i.getAssignment() + "\t| " + i.getDueDateFullDate();
                }
                printText(line);
                printed = true;
                subjectHomeworkIds.push_back(i.getId());
            }
        }
        if(!printed) {
            printText(subject.getName() + " does not possess any homework assingments.");
        }
    }
    return subjectHomeworkIds;
}

std::vector<Homework> addHomeworkToSubject(std::vector<Homework>& homeworks, Subject& subject, std::ofstream& outputFile) {
    std::vector<Homework> temp = homeworks;
    std::vector<std::string> assignments = extractFromFile("assignments.txt");
    Date dueDate = getDate();
    Homework h(firstAvaliableId(temp), subject.getId(), assignments[rand() % assignments.size() - 1]);
    h.setDueDate(dueDate.getDay(), dueDate.getMonth(), dueDate.getYear());
    outputFile << "Added " + h.getAssignment() + " to " + subject.getName() << std::endl;
    printText("Added " + h.getAssignment() + " to " + subject.getName());
    temp.push_back(h);
    return temp;
}

Date getDate() {
    Date date;
    int option;
    printText("----------------------------");
    printText("Do you want to enter the month?");
    printText("1\tYes");
    printText("2\tNo");
    option = userInput(1, 2);
    if(option == 1){
        printText("Enter month...");
        option = userInput(1, 12);
        date.setMonth(option);
    }
    printText("----------------------------");
    printText("Do you want to enter the day?");
    printText("1\tYes");
    printText("2\tNo");
    option = userInput(1, 2);
    if(option == 1){
        printText("Enter day...");
        do{
            option = userInput(1, 31);
            if(!checkIfDayValid(option, date)) {
                printText("Invalid input. Try again.");
            }
        }while(!checkIfDayValid(option, date));
        date.setDay(option);
    }
    printText("----------------------------");
    printText("Do you want to enter the year?");
    printText("1\tYes");
    printText("2\tNo");
    option = userInput(1, 2);
    if(option == 1) {
        printText("Enter year...");
        option = userInput(date.getYear(), 9999);
        date.setYear(option);
    }
    printText("----------------------------");
    return date;
}

bool checkIfDayValid(int day, Date date) {
    int month = date.getMonth();
    int year = date.getYear();
    if((month == 2 && year%4==0) && day > 29) return false;
    else if((month == 2 && year%4!=0) && day > 28) return false;
    if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
    return true;
}

void removeHomeworkFromSubject(std::vector<Homework>& homeworks, Subject& subject, std::ofstream& outputFile) {
    printText("Choose an option:");
    std::vector<int> homeworkIds = printHomeworkInfo(subject, homeworks);
    int option;
    do{
        option = userInput(0, homeworks.size());
        if(binarySearch(homeworkIds, 0, homeworkIds.size() - 1, option) == -1) {
            printText(subject.getName() + " does not possess an assingment with ID " + std::to_string(option));
        }
    }while(binarySearch(homeworkIds, 0, homeworkIds.size() - 1, option) == -1);
    bool found = false;
    for(int i = 0; i < homeworks.size(); i++) {
        if(homeworks[i].getId() == option) {
            found = true;
            outputFile << "Homework ID " + std::to_string(homeworks[i].getId()) + " was removed from " + subject.getName() + "'s list successfully." << std::endl;
            printText("Homework ID " + std::to_string(homeworks[i].getId()) + " was removed from " + subject.getName() + "'s list successfully.");
            homeworks.erase(homeworks.begin() + i);
            break;
        }
    }
}

void handleSelectedOptionForGrade(int selectedOption, int selectedId, std::vector<Student> &students, std::vector<Subject> subjects, std::vector<Grade> &allGrades, std::ofstream &outputFile) {
    int index = findIndexWithId(selectedId, students);
    std::vector<Grade> grades = students[index].getGrades();
    std::vector<int> distinctGrades = selectDistinctSubjects(grades);
    std::string line = "";
    int option = -1;
    Grade selectedGrade;
    switch (selectedOption) {
        case 0:
            break;
        case 1:
            printText("-------------------------");
            printText("ID\t| Subject | Grade");
            printText("-------------------------");
            for(auto i : students[index].getGrades()) {
                line = std::to_string(i.getId()) + "\t| " + getSubjectName(i.getSubjectId(), subjects) + "\t  | " + std::to_string(i.getGrade());
                printText(line);
            }
            printText("");
            printText("0\tExit program");
            printText("-------------------------");
            do{
                option = userInput(1, firstAvaliableId(students[index].getGrades())-1);
                if(option == 0) {
                    break;
                }
                if(binarySearch(students[index].getGrades(), 0, students[index].getGrades().size()-1, option) == -1) {
                    printText(students[index].getName() + " does not posses grade with ID of " + std::to_string(option));
                }
            }while(binarySearch(students[index].getGrades(), 0, students[index].getGrades().size()-1, option) == -1);
            printText("-------------------------");
            if(option == 0) {
                break;
            }else {
                selectedGrade = students[index].getGrades()[findIndexWithId(option, students[index].getGrades())];
                printGradeInfo(selectedGrade, subjects);
            }
            break;
        case 2:
            if(!students[index].getFinishedGrades()){
                students[index].setGrades(addGradeToStudent(subjects, students[index], allGrades, outputFile));
            } else {
                printText(students[index].getName() + "'s grades are already finished.");
            }
            break;
        case 3:
            if(!students[index].getFinishedGrades()){
                students[index].setGrades(removeGradeFromStudent(students[index], outputFile));
            } else {
                printText(students[index].getName() + "'s grades are already finished.");
            } 
            break;
        case 4:
            if(!students[index].getFinishedGrades()){
                finishStudentGrades(students[index], subjects);
            } else {
                printText(students[index].getName() + "'s grades are already finished.");
            } 
            break;
        default:
            break;
    }
}

int binarySearch(std::vector<int> arr, int l, int r, int x) {
    while (l <= r) {
        int m = l + (r - l) / 2;
 
        if (arr[m] == x)
            return arr[m];
 
        if (arr[m] < x)
            l = m + 1;
 
        else
            r = m - 1;
    }
    return -1;
}

int binarySearch(std::vector<Grade> arr, int l, int r, int x) {
    while(l <= r) {
        int m = l + (r - l) / 2;
 
        if (arr[m].getId() == x)
            return arr[m].getId();
 
        if (arr[m].getId() < x)
            l = m + 1;
 
        else
            r = m - 1;
    }
    return -1;
}

int binarySearch(std::vector<Subject> arr, int l, int r, int x) {
    while(l <= r) {
        int m = l + (r - l) / 2;
 
        if (arr[m].getId() == x)
            return arr[m].getId();
 
        if (arr[m].getId() < x)
            l = m + 1;
 
        else
            r = m - 1;
    }
    return -1;
}

void printGradeInfo(Grade grade, std::vector<Subject> subjects) {
    std::string line = "";
    printText("ID\t| Subject | Grade | Grade Type");
    printText("-------------------------");
    line = std::to_string(grade.getId()) + "\t| " + getSubjectName(grade.getSubjectId(), subjects) + "\t  | " + std::to_string(grade.getGrade()) + "\t  | " + grade.getGradeType();
    printText(line);
    printText("-------------------------");
}

bool compareSubjectsById(Subject& a, Subject& b) {
    return a.getId() < b.getId();
}

void finishStudentGrades(Student &student, std::vector<Subject> subjects) {
    double sum = 0;
    int subjectId = 0;
    int count = 0;
    printText("Finished grades: ");
    for(int i = 0; i < student.getGrades().size(); i++) {
        subjectId = student.getGrades()[i].getSubjectId();
        while(student.getGrades()[i].getSubjectId() == subjectId) {
            sum += student.getGrades()[i].getGrade();
            i++;
            count++;
        }
        printText("\t" + getSubjectName(subjectId, subjects) + ":\t" +  std::to_string((int)round(sum/count)) );
        sum = 0;
        count = 0;
    }
    student.setFinishedGrades(1);
    
}

std::vector<Student> addStudentToSubject(std::vector<Student>& allStudents, std::vector<Subject>& subjects, Subject& subject, std::vector<Grade>& allGrades, std::ofstream& outputFile) {
    std::vector<Student> studentVector = subject.getStudents();
    studentVector.push_back(createStudent(allStudents, outputFile));
    return studentVector;
}

Student createStudent(std::vector<Student>& allStudents, std::ofstream& outputFile) {
    std::vector<std::string> names = extractFromFile("names.txt");
    std::vector<std::string> surnames = extractFromFile("surnames.txt");
    std::vector<std::string> cities = extractFromFile("cities.txt");
    std::vector<std::string> countries = extractFromFile("countries.txt");

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(names.begin(), names.end(), g);
    std::shuffle(surnames.begin(), surnames.end(), g);
    std::shuffle(cities.begin(), cities.end(), g);
    std::shuffle(countries.begin(), countries.end(), g);
    
    int id = firstAvaliableId(allStudents);
    int index = surnames.size() - 1;

    Student s(id, toLowerCase(surnames[index]) + "." + toLowerCase(names[index]) + "@gmail.com", surnames[index] + " " + names[index], randomDate(), "", cities[index], countries[index], randomNumber(9));
    s.setEMSO(generateEmso(s.getBirthDate()));

    printText("Adding a student...");
    allStudents.push_back(s);

    return s;
}

std::string getUserInput(const std::string& prompt) {
    std::string input = "";
    do {
        std::cout << prompt;
        getline(std::cin, input);
        if (!validateInput(input)) {
            printText("Invalid input. Try again");
        }
    } while (!validateInput(input));
    return input;
}


bool validateInput(std::string str) {
    if(str.length() <= 0) return false;
    else return true;
}

std::vector<int> printSubjectFromStudent(Student student, std::vector<Subject> subjects) {
    std::vector<int> subjectIds;
    bool count = false;
    for(auto i : subjects) {
        for(auto j : i.getStudents()) {
            if(j.getId() == student.getId()) {
                printText(std::to_string(i.getId()) + "\t| " + i.getName());
                count = true;
                subjectIds.push_back(i.getId());
            }
        }
    }
    if(!count) printText(student.getName() + " is not attending any classes.");
    return subjectIds;
}

std::vector<Grade> addGradeToStudent(std::vector<Subject> subjects, Student &student, std::vector<Grade> &allGrades, std::ofstream &outputFile) {
    std::vector<Subject> temp = subjects;
    std::vector<Grade> gradeVector = student.getGrades();
    std::sort(temp.begin(), temp.end(), compareSubjectsById);
    int option = -1;
    int id = -1;
    int subjectId = -1;
    int studentId = -1;
    int gradeNum = -1;
    std::string gradeType = "";
    printText("-------------------------");
    printText("Choose a subject to which you want to add a grade:");
    std::vector<int> avaliableSubjects = printSubjectFromStudent(student, subjects);
    std::sort(avaliableSubjects.begin(), avaliableSubjects.end());
    if(avaliableSubjects.size() == 0) {
        printText("Returning...");
    }else {
        do{
            option = userInput(1, firstAvaliableId(temp)-1);
            if(option == 0) {
                break;
            }
            if(binarySearch(avaliableSubjects, 0, avaliableSubjects.size()-1, option) == -1) {
                printText("Subject with ID " + std::to_string(option) + " does not exist.");
            }
        }while(binarySearch(avaliableSubjects, 0, avaliableSubjects.size()-1, option) == -1);
        if (option != 0) {
            printText("You have chosen " + getSubjectName(option, temp));
            printText("-------------------------");
            id = firstAvaliableId(allGrades);
            subjectId = option;
            studentId = student.getId();
            printText("Choose a grade: ");
            gradeNum = userInput(1, 5);
            printText("Choose a grade type:");
            printText("1\t| Ustno");
            printText("2\t| Pisno");
            printText("3\t| Sprotno delo");
            gradeType = gradeTypeSelector();

            Grade grade(id, studentId, subjectId, gradeNum, gradeType);
            gradeVector.push_back(grade);
            allGrades.push_back(grade);
            printText("Grade in " + getSubjectName(grade.getSubjectId(), temp) + " added to " + student.getName() + " successfully!");
            outputFile << "Added grade ID " + std::to_string(grade.getId()) + " to student " + student.getName() + "." << std::endl;
        }
    }
    
    return gradeVector;
}

int gradeSelector() {
    int option = userInput(1, 5);
    return option;
}

std::string gradeTypeSelector() {
    int option = userInput(1, 3);
    switch (option)
    {
    case 1:
        return "Ustno";
        break;
    case 2:
        return "Pisno";
    case 3:
        return "Sprotno delo";
    default:
        break;
    }
    return "";
}

void clearScreen() {
    for(int i = 0; i < 255; i++) {
        printText("");
    }
}

std::vector<Student> removeStudentFromSubject(Subject &subject, std::ofstream &outputFile) {
    int studentId;
    bool found = false;
    std::vector<Student> temp = subject.getStudents();
    do{
        studentId = userInput(0, std::numeric_limits<int>::max());

        int index = -1;
        for(int i = 0; i < temp.size(); i++) {
            if(temp[i].getId() == studentId) {
                found = true;
                index = i;
                outputFile << temp[i].getName() + " with ID " + std::to_string(studentId) + " removed from " + subject.getName() + "'s students list." << std::endl;
                printText(temp[i].getName() + " with ID " + std::to_string(studentId) + " was removed from " + subject.getName() + "'s students list.");
                temp.erase(temp.begin() + index);
                break;
            }
        }
        if (!found) {
            printText(subject.getName() + " does not possess a student with ID " + std::to_string(studentId));
        }
    }while(!found);
    return temp;
} 

std::vector<Grade> removeGradeFromStudent(Student &student, std::ofstream &outputFile) {
    int gradeId;
    bool found = false;
    std::vector<Grade> temp = student.getGrades();
    do{
        gradeId = userInput(0, std::numeric_limits<int>::max());

        int index = -1;
        for (int i = 0; i < temp.size(); i++) {
            if (temp[i].getId() == gradeId) {
                printText(std::to_string(temp[i].getId()));
                found = true;
                index = i;
                temp.erase(temp.begin() + index);
                outputFile << "Grade with ID " + std::to_string(gradeId) + " removed from " + student.getName() + "'s grades." << std::endl;
                printText("Grade with ID " + std::to_string(gradeId) + " removed from " + student.getName() + "'s grades.");
                break;
            }
        }
        if (!found) {
            printText(student.getName() + " does not possess a grade with ID " + std::to_string(gradeId));
        }
    } while (!found);
    return temp;
}
