#include "Date.h"
#include <sstream>
Date::Date(): year_(0), month_(0), day_(0), hour_(0), minute_(0) {}

Date::Date(int y, int m, int d, int h, int mi): year_(y), month_(m), day_(d),
    hour_(h), minute_(mi) {
    //  check valid point;
    // if unvalid date = 0;
  //  if ( !isValid(*this) ) year_ = month_ = day_ = hour_ = minute_ = 0;
}

int Date::getYear(void) const {
  return year_;
}

void Date::setYear(int year) {
  year_ = year;
  //  if ( !isValid(*this) ) year_ = month_ = day_ = hour_ = minute_ = 0;
}

int Date::getMonth(void) const {
  return month_;
}

void Date::setMonth(int month) {
  month_ = month;
  // if ( !isValid(*this) ) year_ = month_ = day_ = hour_ = minute_ = 0;
}

int Date::getDay(void) const {
  return day_;
}

void Date::setDay(int day) {
  day_ = day;
  // if ( !isValid(*this) ) year_ = month_ = day_ = hour_ = minute_ = 0;
}

int Date::getHour(void) const {
  return hour_;
}

void Date::setHour(int hour) {
  hour_ = hour;
  //  if ( !isValid(*this) ) year_ = month_ = day_ = hour_ = minute_ = 0;
}

int Date::getMinute(void) const {
  return minute_;
}

void Date::setMinute(int minute) {
  minute_ = minute;
  //  if ( !isValid(*this) ) year_ = month_ = day_ = hour_ = minute_ = 0;
}

bool Date::isValid(Date date) {
  if (date.year_ < 1000|| date.year_ > 9999) return false;
  if (date.hour_ < 0 || date.hour_ > 23) return false;
  if (date.minute_ < 0 || date.minute_ > 59) return false;
  if (date.month_ < 1 || date.month_ > 12) return false;
  if (date.day_ > 31||date.day_ < 1) return false;
  if (date.day_ == 31) {
    if (date.month_ == 2 || date.month_ == 4 || date.month_ == 6 ||
    date.month_ == 9 || date.month_ == 11) return false;
  }
  if (date.month_ == 2) {
    if (date.day_ > 29) return false;
    if (date.day_ == 29) {
      if (!((date.year_ % 4 == 0&&date.year_ % 100 != 0) ||
            (date.year_ % 400 == 0)) )
        return false;
    }
  }
  return true;
}
Date Date::stringToDate(std::string dateString) {
  if (dateString.size() != 16) return Date(0,0,0,0,0);
  std::stringstream s1; s1 << dateString.substr(0, 4);
  int year, month, day, hour, minute;
  s1 >> year;

  std::stringstream s2; s2 << dateString.substr(5, 2);
  s2 >> month;

  std::stringstream s3; s3 << dateString.substr(8, 2);
  s3 >> day;

  std::stringstream s4; s4 << dateString.substr(11, 2);
  s4 >> hour;

  std::stringstream s5; s5 << dateString.substr(14, 2);
  s5 >> minute;

  return Date(year, month, day, hour, minute);
}

std::string Date::dateToString(Date date) {
  std::string temp, s;
  std::stringstream s1; s1 << date.year_;
  s1 >> temp; s += temp;
  s += '-';

  if (date.month_ < 10) s += '0';
  std::stringstream s2; s2 << date.month_;
  s2 >> temp; s += temp;
  s += '-';

  if (date.day_ < 10) s += '0';
  std::stringstream s3; s3 << date.day_;
  s3 >> temp; s += temp;
  s += '/';

  if (date.hour_ < 10) s+= '0';
  std::stringstream s4; s4 << date.hour_;
  s4 >> temp; s += temp;
  s += ':';

  if (date.minute_ < 10) s += '0';
  std::stringstream s5; s5 << date.minute_;
  s5 >> temp; s += temp;

  return s;
}

Date & Date::operator=(const Date& date) {
  year_ = date.year_; month_ = date.month_; day_ = date.day_;
  hour_ = date.hour_; minute_ = date.minute_;
  //  if ( !isValid(*this) ) year_ = month_ = day_ = hour_ = minute_ = 0;
  return *this;
}

bool Date::operator==(const Date& date) const {
  if (year_ == date.year_ && month_ == date.month_ && day_ == date.day_
    && hour_ == date.hour_ && minute_ == date.minute_) {
     return true;
  } else {
    return false;
  }
}

bool Date::operator>(const Date& date) const {
  // 1999 > 1555
  if (year_ != date.year_) return year_ > date.year_;
  if (month_ != date.month_) return month_ > date.month_;
  if (day_ != date.day_) return day_ > date.day_;
  if (hour_ != date.hour_) return hour_ > date.hour_;
  return minute_ > date.minute_;
}

bool Date::operator<(const Date& date) const {
  if (*this == date || *this > date) {
    return false;
  } else {
    return true;
  }
}

bool Date::operator>=(const Date& date) const {
  if (*this > date || *this == date) {
     return true;
  } else {
    return false;
  }
}

bool Date::operator<=(const Date& date) const {
  if (*this > date) {
    return false;
  } else {
    return true;
  }
}

