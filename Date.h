#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <string>

class Date {
  public:
    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    int day = local_time->tm_mday;
    int month = 1 + local_time->tm_mon;
    int year = 1900 + local_time->tm_year;

    //Constructors
    Date();

    //Setters
    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);

    //Getters
    int getDay();
    int getMonth();
    int getYear();
    std::string getFullDate();
};

#endif