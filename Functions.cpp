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
    return grades[grades.size()-1].getId() + 1;
}

int firstAvaliableId(std::vector<Subject> subjects) {
    if(subjects.empty()) return 1;
    return subjects[subjects.size()-1].getId() + 1;
}

int firstAvaliableId(std::vector<Student> students) {
    if(students.empty()) return 1;
    return students[students.size()-1].getId() + 1;
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
    printText("-----------------------------------------------");
    printText("ID\t| Student\t| Subject\t| Grade");
    printText("-----------------------------------------------");
    for(auto i : grades) {
        std::string subject = getSubjectName(i.getSubjectId(), subjects);
        std::string student = getStudentName(i.getStudentId(), students);
        line = std::to_string(i.getId()) + "\t| " + student + "\t| " + subject + "\t\t| " + std::to_string(i.getGrade());
        std::cout << line << std::endl;

    }
    printText("-----------------------------------------------");
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

void createSchool(std::vector<Subject> &subjects, std::vector<Student> &students, std::vector<Grade> &grades) {
    std::time_t currentTime = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&currentTime);
    char timestamp[20]; // Format: YYYYMMDD_HHMMSS
    std::strftime(timestamp, sizeof(timestamp), "%d%m%Y_%H%M%S", timeInfo);
    std::string filename = "output_" + std::string(timestamp) + ".txt";
    std::ofstream outputFile(filename);
    
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
    }else {
        outputFile << "File created on " << timestamp << std::endl;
        for(int i = 0; i < subjects.size(); i++) {
            for(int j = 0; j < students.size(); j++) {
                subjects[i].addStudent(students[j]);
                outputFile << "Added " + students[j].getName() + " to " + subjects[i].getName() + "." << std::endl;
                for(int k = 0; k < rand() % 6 + 4; k++) {
                    students[j].addGrade(subjects[i].getId(), grades);
                    outputFile << "Added grade ID " << students[j].getGrades()[students[j].getGrades().size()-1].getId() << " to " + students[j].getName() + "." << std::endl;
                }
            }
        }
    }
    outputFile.close();
}

void mainUserInterface() {
    printText("----------------------------");
    printText("Choose an option:");
    printText("1\tSubjects");
    printText("2\tStudents");
    printText("3\tGrades");
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

void handleSelectedOptionForGrade(int selectedOption, int selectedId, std::vector<Student> students, std::vector<Subject> subjects, std::vector<Grade> &allGrades) {
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
            addGrade(subjects, students[index], allGrades);
            break;
        case 3:
            break;
        case 4:
            finishStudentGrades(students[index], subjects);
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
}

void addGrade(std::vector<Subject> subjects, Student &student, std::vector<Grade> &allGrades) {
    std::vector<Subject> temp = subjects;
    std::sort(temp.begin(), temp.end(), compareSubjectsById);
    int option = -1;
    int id = -1;
    int subjectId = -1;
    int studentId = -1;
    int gradeNum = -1;
    std::string gradeType = "";
    printText("-------------------------");
    printText("Choose a subject to which you want to add a grade:");
    selectIdAndNameFromSubjects(subjects);
    do{
        option = userInput(1, firstAvaliableId(temp)-1);
        if(option == 0) {
            break;
        }
        if(binarySearch(temp, 0, temp.size()-1, option) == -1) {
            printText("Subject with ID " + std::to_string(option) + " does not exist.");
        }
    }while(binarySearch(temp, 0, temp.size()-1, option) == -1);
    if (option != 0) {
        printText("You have chosen " + getSubjectName(option, temp));
        printText("-------------------------");
        id = firstAvaliableId(allGrades);
        subjectId = option;
        studentId = student.getId();
        printText("Choose a grade: ");
        gradeNum = userInput(1, 5);
        printText("Choose a grade type:");
        gradeType = gradeTypeSelector();

        Grade grade(id, studentId, subjectId, gradeNum, gradeType);
        student.getGrades().push_back(grade);
        //student.getGrades().push_back(grade);
        allGrades.push_back(grade);
        printText("Grade added successfully");
    }

    printText("-------------------------");
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