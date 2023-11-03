#include "Date.h"

Date::Date() {}

void Date::setDay(int d) { day = d; }
void Date::setMonth(int m) { month = m; }
void Date::setYear(int y) { year = y; }

int Date::getDay() { return day; }
int Date::getMonth() { return month; }
int Date::getYear() { return year; }
std::string Date::getFullDate() { return std::to_string(this->getDay()) + "." + std::to_string(this->getMonth()) + "." + std::to_string(this->getYear()); }

