// Copyright 2021 Petrova Kseniya <ksyushki5@yandex.ru>

#include <student.hpp>

json collect_inform(const std::string &path) {
  std::ifstream jf(path);
  json data;
  jf >> data;

  if (path.empty()) throw std::runtime_error{"The file path cannot be empty!"};
  if (!jf)
    throw std::runtime_error{"There is no such file on your computer: " + path};
  if (!data.at("items").is_array())
    throw std::runtime_error{"The items in the file must be an array!"};
  if (data.at("items").size() != data.at("_meta").at("count").get<size_t>())
    throw std::runtime_error{"Value in _meta corresponds to the length of the array item"};

  return data;
}
auto get_name(const json &data) -> std::string {
  return data.get<std::string>();
}

auto get_group(const json &data) -> std::any {
  if (data.is_string()) return data.get<std::string>();
  else return data.get<std::size_t>();
}
auto get_avg(const json &data) -> std::any {
  if (data.is_null())
    return nullptr;
  else if (data.is_string())
    return data.get<std::string>();
  else if (data.is_number_float())
    return data.get<double>();
  else
    return data.get<size_t>();
}
auto get_debt(const json &data) -> std::any {
  if (data.is_null())
    return nullptr;
  else if (data.is_string())
    return data.get<std::string>();
  else
    return data.get <std::vector<std::string>>();
}

void make_stud(const json &data, Student &st) {
  st.name = get_name(data.at("name"));
  st.group = get_group(data.at("group"));
  st.avg = get_avg(data.at("avg"));
  st.debt = get_debt(data.at("debt"));
}
std::vector<Student> parse_file(json &data) {
  std::vector<Student> students;
  for (auto const &item : data.at("items")) {
    Student student;
    make_stud(item, student);
    students.push_back(student);
  }
  return students;
}

void print() {
  std::cout << "+" << std::setfill('-') << std::setw(25) << "+" << std::setw(10)
            << "+" << std::setw(10) << "+" << std::setw(10) << "+" << std::endl;
  std::cout << "|" << std::setfill(' ') << std::setw(24) << std::left << "name"
            << "|" << std::setw(9) << std::left << "group"
            << "|" << std::setw(9) << std::left << "avg"
            << "|" << std::setw(9) << std::left << "debt" << "|"<< std::endl;
  std::cout << "+" << std::setfill('-') << std::setw(25) << std::right << "+" << std::setw(10)
            << "+" << std::setw(10) << "+" << std::setw(10) << std::right << "+" << std::endl;
}
void print(const Student &student, std::ostream &os) {
  os << "|" << std::setfill(' ') << std::setw(24) << std::left << std::any_cast<std::string>(student.name) << std::right << "|";

  if(student.group.type() == typeid(std::string))
    os << std::setw(9) << std::left << std::any_cast<std::string>(student.group)<< std::right << "|";
  else os << std::setw(9) << std::left <<  std::any_cast<size_t>(student.group) << "|";

  if(student.avg.type() == typeid(std::string))
    os << std::setw(9) << std::left << std::any_cast<std::string>(student.avg) << "|";
  else if(student.avg.type() == typeid(double))
    os << std::setw(9) << std::left << std::any_cast<double>(student.avg) << "|";
  else if(student.avg.type() == typeid(std::size_t))
    os << std::setw(9) << std:: left << std::any_cast<size_t>(student.avg) << "|";

  if(student.debt.type() == typeid(std::nullptr_t))
    os << std::setw(9) << std::left << "null" << "|" << std::endl;
  else if(student.debt.type() == typeid(std::string))
    os << std::setw(9) << std::left << std::any_cast<std::string>(student.debt) << "|" << std::endl;
  else  os << std::setw(1) << std::left << std::any_cast<std::vector<std::string>>(student.debt).size()
           <<std::setw(8) << std::left << " items" << std::right << "|" << std::endl;

  os << "+" << std::setfill('-') << std::setw(25) << std::right << "+" << std::setw(10)
     << "+" << std::setw(10) << "+" << std::setw(10) << "+" << std::endl;
}
void print(std::vector<Student> &students, std::ostream &os) {
  print();
  for(Student &student : students)
    print(student, os);
}
void print_for_test(std::vector<Student> &students, std::ostream &os){
  for(Student &student : students)
    print(student, os);
}