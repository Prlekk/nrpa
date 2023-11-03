#include "Student.h"

//Constructors
Student::Student() {}
Student::Student(int i, const std::string &m, const std::string &n, const std::string &bd, const std::string &e, const std::string &ci, const std::string &co, const std::string &pn) {
    id = i;
    mail = m;
    name = n;
    birthDate = bd;
    emso = e;
    city = ci;
    country = co;
    phoneNumber = pn;
}

//Destructor
Student::~Student() {}

//Setters
void Student::setId(int i) { id = i; }
void Student::setMail(const std::string &m) { mail = m; }
void Student::setName(const std::string &n) { name = n; }
void Student::setBirthDate(const std::string &b) {birthDate = b; }
void Student::setEMSO(const std::string &e) { emso = e; }
void Student::setCity(const std::string &c) { city = c; }
void Student::setCountry(const std::string &c) { country = c; }
void Student::setPhoneNumber(const std::string &p) { phoneNumber = p; }
void Student::setGrades(const std::vector<Grade>& g) { grades = g; }
void Student::setHomework(const std::vector<Homework> &h) { homework = h; }
void Student::addHomeworkToHomeworks(Homework& h) { homework.push_back(h); }
void Student::setFinishedGrades(const bool &f) { finishedGrades = f; }

//Getters
int Student::getId() { return id; }
const std::string& Student::getMail() { return mail; }
const std::string& Student::getName() { return name; }
const std::string& Student::getBirthDate() { return birthDate; }
const std::string& Student::getEMSO() { return emso; }
const std::string& Student::getCity() { return city; }
const std::string& Student::getCountry() { return country; }
const std::string& Student::getPhoneNumber() { return phoneNumber; }
std::vector<Grade> Student::getGrades() { return grades; }
std::vector<Homework> Student::getHomework() { return homework; }
bool Student::getFinishedGrades() { return finishedGrades; }

//Class Methods
