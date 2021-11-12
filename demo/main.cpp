#include <student.hpp>
#include "iostream"
#include "gtest/gtest.h"
int main() {
  const std::string &path = "/home/kseniya/lab-01-parser/tests/students.json";
  nlohmann::json data = collect_inform(path);
  std::vector<Student> students = parse_file(data);
  print(students, std::cout);
  return 0;
}
