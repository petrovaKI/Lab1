// Copyright 2021 Petrova Kseniya <ksyushki5@yandex.ru>

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <any>
#include <vector>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <iomanip>
using nlohmann::json;

struct Student
{
  std::string name;
  std::any group;
  std::any avg;
  std:: any debt;
};
class JSON {
 public:
  explicit JSON(std::string &j);
  JSON();

 private:
  json _j;
};
json collect_inform(const std::string &path);
void make_stud(const json &data, Student &st);
std::vector<Student> parse_file(json &data);
void print();
void print(const Student &student, std::ostream &os);
void print(std::vector<Student> &students, std::ostream &os);
void print_for_test(std::vector<Student> &students, std::ostream &os);
#endif // INCLUDE_STUDENT_HPP_
