// Copyright 2021 Petrova Kseniya <ksyushki5@yandex.ru>

#include <gtest/gtest.h>
#include <student.hpp>

TEST(Test1, collect_inform){
  const std::string data_from_file = "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": \"Ivanov Petr\",\n"
      "      \"group\": \"1\",\n"
      "      \"avg\": \"4.25\",\n"
      "      \"debt\": null\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Sidorov Ivan\",\n"
      "      \"group\": 31,\n"
      "      \"avg\": 4,\n"
      "      \"debt\": \"C++\"\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Petrov Nikita\",\n"
      "      \"group\": \"IU8-31\",\n"
      "      \"avg\": 3.33,\n"
      "      \"debt\": [\n"
      "        \"C++\",\n"
      "        \"Linux\",\n"
      "        \"Network\"\n"
      "      ]\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 3\n"
      "  }\n"
      "}";
  nlohmann::json obj_1 = json::parse(data_from_file);
  const std::string &path = "/home/kseniya/lab-01-parser/tests/students.json";
  nlohmann::json obj_2 = collect_inform(path);
  ASSERT_EQ(obj_1, obj_2) << "Test passed!";
}
TEST(Test2, parse_file){
  Student one = {"Ivanov Petr", (std::string)"1", (std::string) "4.25", nullptr};
  Student two = {"Sidorov Ivan", (size_t)31, (size_t)4, (std::string)"C++" };
  std::vector<std::string> debts = {"C++", "Linux", "Network"};
  Student three = {"Petrov Nikita", (std::string)"IU8-31", (double)3.33,
                   (std::vector<std::string>)debts};
  std::vector<Student> students_1 = {one, two, three};
  std::stringstream ss1;
  print_for_test(students_1, ss1);
  std::string s1 = ss1.str();

  const std::string &path = "/home/kseniya/lab-01-parser/tests/students.json";
  nlohmann::json data = collect_inform(path);
  std::vector<Student> students_2 = parse_file(data);
  std::stringstream ss2;
  print_for_test(students_2, ss2);
  std::string s2 = ss2.str();

  ASSERT_EQ(s1, s2);
}
TEST(Test3, correct_types_1){
  const std::string data_str ="{\n"
      "      \"name\": \"Ivanov Petr\",\n"
      "      \"group\": 1,\n"
      "      \"avg\": 4.25,\n"
      "      \"debt\": [\n"
      "        \"C++\",\n"
      "        \"Linux\",\n"
      "        \"Network\"\n"
      "      ]\n"
      "    }";
  nlohmann::json data = json::parse(data_str);
  Student st;
  make_stud(data, st);
  ASSERT_TRUE(st.group.type()==typeid(std::size_t));
  ASSERT_TRUE(st.avg.type()==typeid(double));
  ASSERT_TRUE(st.debt.type()== typeid(std::vector<std::string>));
}
TEST(Test4, correct_types_2){
  const std::string data_str ="{\n"
      "      \"name\": \"Ivanov Petr\",\n"
      "      \"group\": \"IU8-31\",\n"
      "      \"avg\": 4.25,\n"
      "      \"debt\": null\n"
      "    }";
  nlohmann::json data = json::parse(data_str);
  Student st;
  make_stud(data, st);
  ASSERT_TRUE(st.group.type()==typeid(std::string));
  ASSERT_TRUE(st.debt.type()==typeid(nullptr));
}
