#include "date.h"

s21::Date::Date(int day, int month, int year)
    : day_(day), month_(month), year_(year) {}

int s21::Date::GetDayInMonth() {
  int days = 0;
  if (month_ == 2)
    days = 28;
  else if (month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11)
    days = 30;
  else
    days = 31;
  return days;
}

void s21::Date::Add(int days, int months, int years) {
  day_ += days;
  while (day_ > GetDayInMonth()) {
    day_ -= GetDayInMonth();
    month_ += 1;
  }
  month_ += months;
  while (month_ > 12) {
    month_ -= 12;
    year_ += 1;
  }
  year_ += years;
}

bool s21::Date::operator==(const Date& o) const {
  if (this == &o) return true;

  if (year_ == o.year_ && month_ == o.month_ && day_ == o.day_)
    return true;
  else
    return false;
}

bool s21::Date::operator>(const Date& o) const {
  if (this == &o) return true;

  if (year_ > o.year_)
    return true;
  else if (year_ < o.year_)
    return false;

  if (month_ > o.month_)
    return true;
  else if (month_ < o.month_)
    return false;

  if (day_ > o.day_)
    return true;
  else
    return false;
}

bool s21::Date::operator<(const Date& o) const {
  if (this == &o) return true;

  if (year_ < o.year_)
    return true;
  else if (year_ > o.year_)
    return false;

  if (month_ < o.month_)
    return true;
  else if (month_ > o.month_)
    return false;

  if (day_ < o.day_)
    return true;
  else
    return false;
}

bool s21::Date::operator>=(const Date& o) const {
  return (*this > o || *this == o);
}
