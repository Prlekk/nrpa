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
    date = date.substr(0,2) + date.substr(3,2) + date.substr(6, 3) + randomNumber(4);
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
    std::vector<Student> temp;
    for(int i = 0; i < size && i < 100; i++) {
        Student s(i+1, surnames[i] + "." + names[i] + "@gmail.com", surnames[i] + " " + names[i], randomDate(), "", cities[i], countries[i], randomNumber(9));
        s.setEMSO(generateEmso(s.getBirthDate()));
        temp.push_back(s);
    }
    std::random_device rd;
    std::mt19937 g(rd());
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

std::string getSubjectName(int id, std::vector<Subject> subjects) {
    for(auto i : subjects) {
        if(i.getId() == id) return i.getName();
    }
    return "";
}

void selectIdAndNameFromStudents(std::vector<Student> students){
    std::string line = "";
    printText("ID\t| Name");
    printText("-----------------------");
    for(auto i : students) {
        line = std::to_string(i.getId()) + "\t| " + i.getName();
        printText(line);
    }
}

void Student::addGrade(int num, std::vector<Grade> &allGrades) {
    int randomReason = rand() % 3;
    std::vector<std::string> reasons = extractFromFile("reasons.txt");
    Grade grade(firstAvaliableId(allGrades), id, num, rand() % 5 + 1, reasons[randomReason]);
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
}