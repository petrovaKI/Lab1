// Copyright 2021 Petrova Kseniya <ksyushki5@yandex.ru>

#include <gtest/gtest.h>
#include <student.hpp>

TEST(Test1, parse_file) {
  Student one = {"Ivanov Petr", (std::string)"1", (std::string) "4.25", nullptr};
  Student two = {"Sidorov Ivan", (size_t)31, (size_t)4, (std::string)"C++" };
  std::vector<std::string> debts = {"C++", "Linux", "Network"};
  Student three = {"Petrov Nikita", (std::string)"IU8-31", (double)3.33,
                   (std::vector<std::string>)debts};
  std::vector<Student> students_1 = {one, two, three};
  std::stringstream ss1;
  print_for_test(students_1, ss1);

  auto text = R"(
{
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Petrov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})";
  std::stringstream ss;
  ss << text;
  json obj2 = json::parse(ss);
  std::vector<Student> students_2 = parse_file(obj2);
  std::stringstream ss2;
  print_for_test(students_2, ss2);

  ASSERT_EQ(ss1.str(), ss2.str());

}
TEST(Test2, correct_types_1){
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
TEST(Test3, correct_types_2){
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
