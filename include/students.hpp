//
// Created by ykvap on 27.12.2020.
//

#ifndef LAB_01_PARSER_STUDENTS_HPP
#define LAB_01_PARSER_STUDENTS_HPP
#include <any>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>
using std::any;
using std::string;
using nlohmann::json;
using std::vector;

static const string NAME = "name";
static const string GROUP = "group";
static const string AVG = "avg";
static const string DEBT = "debt";
class Students {

    any name;
    any group;
    any avg;
    any debt;

    public:

    static Students fromJson(const json& jsonStudents);
    Students() = default;
    Students(any n, any g, any a, any d);
    bool operator == (const Students& refStudent);
    string operator[](const string& valueName) const;

    static vector<Students> ParseFile(const string& jsonPath);
    friend std::ostream& operator<<(
            std::ostream& os, vector<Students> student);
};
bool operator != (const any& lvalue, const any& rvalue);
#endif //LAB_01_PARSER_STUDENTS_HPP
