//
// Created by ykvap on 27.12.2020.
//

#include "students.hpp"
any GetValue(const json& j, const string& valueName) {
    if (j.find(valueName) == j.end()) {
        throw std::runtime_error("The value" + valueName + "is not fount");
    } else {
        if (j[valueName].is_number_integer()) {
            return j[valueName].get<int>();
        } else if (j[valueName].is_number_float()) {
            return j[valueName].get<double>();
        } else if (j[valueName].is_string()) {
            if(j[valueName].get<string>() == "null"){
                return nullptr;
            }
            return j[valueName].get<string>();
        } else if (j[valueName].is_array()) {
            return j[valueName].get<vector<string>>();
        } else {
            return nullptr;
        }
    }
}
Students Students::fromJson(const json& jsonStudent){
    Students outStudent;
    outStudent.name = GetValue(jsonStudent, NAME);
    outStudent.group = GetValue(jsonStudent, GROUP);
    outStudent.avg = GetValue(jsonStudent, AVG);
    outStudent.debt = GetValue(jsonStudent, DEBT);
    return outStudent;
}
Students::Students(any n, any g, any a, any d){
name = std::move(n);
group = std::move(g);
avg = std::move(a);
debt = std::move(d);
}
bool Students::operator == (const Students& refStudent) {
    if (name != refStudent.name){
        return false;
    } else if (group != refStudent.group){
        return false;
    } else if (avg != refStudent.avg){
        return false;
    } else if (debt != refStudent.debt) {
        return false;
    } else {
            return true;
        }
}
bool operator!=(const any& lvalue, const any& rvalue) {
    if(lvalue.type()!=rvalue.type()) {
        return true;
    }else {
        if(lvalue.type() == typeid(string)){
            return std::any_cast<string>(lvalue) != std::any_cast<string>(rvalue);
        } else if (lvalue.type() == typeid(int)) {
            return std::any_cast<int>(lvalue) != std::any_cast<int>(rvalue);
        } else if (lvalue.type() == typeid(double)) {
            return std::any_cast<double>(lvalue) != std::any_cast<double>(rvalue);
        } else if (lvalue.type() == typeid(nullptr)) {
            return false;
        } else {
            return std::any_cast<vector<string>>(lvalue)!= std::any_cast<vector<string>>(rvalue);
        }
    }
}
string getAny(const any& valueToGet){
    if (valueToGet.type() == typeid(string)){
         return std::any_cast<string>(valueToGet);
    } else if (valueToGet.type() == typeid(vector<string>)){
         return string(std::to_string(std::any_cast<vector<string>>(valueToGet).size())+" items");
    } else if (valueToGet.type() == typeid(int)){
        return std::to_string(std::any_cast<int>(valueToGet));
    } else if (valueToGet.type() == typeid(double)){
        std::stringstream ss;
        ss << std::setprecision(3) << std::any_cast<double>(valueToGet);
        return ss.str();
    } else if (valueToGet.type() == typeid(std::nullptr_t)){
          return "null";
    } else {
        return "";
    }
}
string Students::operator[](const string& valueName) const{
    if (valueName == NAME){
        return getAny(name);
    } else if (valueName == GROUP) {
    return getAny(group);
    } else if (valueName == AVG) {
        return getAny(avg);
    } else if (valueName == DEBT) {
        return getAny(debt);
    } else {
        throw std::runtime_error{"There is no value with the name " + valueName};
    }
}
vector<Students> Students::ParseFile(const string& jsonPath) {
    std::ifstream jsonFile(jsonPath);

     if(!jsonFile){
         throw std::runtime_error("File cannot be opened");
     }
     json data;
     jsonFile >> data;

     if(!data["items"].is_array()){
         throw std::runtime_error{R"("Items" field is not array)"};
     }
     if(data["items"].size() != data["_meta"]["count"]){
         throw std::runtime_error{R"("Items"" size is not equal to "_meta"->"count")"};
     }

     vector<Students> students;
     for(const auto& student : data["items"]){
         students.emplace_back(fromJson(student));
     }
    return students;
}

std::ostream& operator<<(std::ostream& os, std::vector<Students> students) {
    vector<size_t> length{4, 5, 3, 4};
    for (const auto& student : students) {
        if (student[NAME].length() > length[0]) {
            length[0] = student[NAME].length();
        }
        if (student[GROUP].length() > length[1]) {
            length[1] = student[GROUP].length();
        }
        if (student[AVG].length() > length[2]) {
            length[2] = student[AVG].length();
        }
        if (student[DEBT].length() > length[3]) {
            length[3] = student[DEBT].length();
        }
    }
    string separator;

    for (size_t i = 0; i < length.size(); ++i) {
        separator += "|-";
        for (size_t j = 0; j < length[i]; ++j) {
            separator += "-";
        }
    }
    separator += "|";

    os << "| " << std::left << std::setw(length[0]) << NAME
       << "| " << std::left << std::setw(length[1]) << GROUP
       << "| " << std::left << std::setw(length[2]) << AVG
       << "| " << std::left << std::setw(length[3]) << DEBT
       << "|\n" << separator << std::endl;

    for (const auto &student : students) {
    os << "| " << std::left << std::setw(length[0]) << student[NAME]
       << "| " << std::left << std::setw(length[1]) << student[GROUP]
       << "| " << std::left << std::setw(length[2]) << student[AVG]
       << "| " << std::left << std::setw(length[3]) << student[DEBT]
       << "|\n" << separator << std::endl;
   }
    return os;
}

