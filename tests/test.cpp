// Copyright 2021 Petrova Kseniya <ksyushki5@yandex.ru>

#include <gtest/gtest.h>
#include <student.hpp>

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
