// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include "students.hpp"

TEST(StudentTest, fromJson) {
    json jsonStudent;
    jsonStudent[NAME] = "Mirage";
    jsonStudent[GROUP] = "IBM2-36";
    jsonStudent[AVG] = 4.6;
    jsonStudent[DEBT] = "null";
            Students student = Students::fromJson(jsonStudent);
    EXPECT_TRUE(student == Students(string("Mirage"), string("IBM2-36"), 4.6, nullptr));
}
TEST(StudentTest, IncorectValue){
    json jsonStudent;
    EXPECT_THROW(Students::fromJson(jsonStudent), std::runtime_error);
}
TEST(StudentTest, GetString) {
    Students student(string("Rhino"), string("SM3-56"), 4, string("c++"));
    EXPECT_EQ(student[NAME], "Rhino");
    EXPECT_EQ(student[GROUP], "SM3-56");
    EXPECT_EQ(student[AVG], "4");
    EXPECT_EQ(student[DEBT], "c++");
}
TEST(StudentTest, WrongPath) {
    EXPECT_THROW(Students::ParseFile("wrongPath.json"), std::runtime_error);
}
TEST(StudentTest, ItemsIsNotArray) {
    const char wrongString[] = R"({"items" : "I am not array"})";

    std::ofstream wrongFile("wrongFile.json", std::ios::out);
    wrongFile << wrongString;
    wrongFile.close();

    EXPECT_THROW(Students::ParseFile("wrongFile.json"), std::runtime_error);
}
TEST(StudentsTest, WrongCount) {
    const char  wrongString[] = R"({
        "items" : [1,2,3],
        "_meta" :{
            "count" : 20
        }
    })";
    std::ofstream wrongFile("wrongFile.json", std::ios::out);
    wrongFile << wrongString;
    wrongFile.close();

    EXPECT_THROW(Students::ParseFile("wrongFile.json"), std::runtime_error);
}
TEST(StudentsTest, Parse){
    const char jsonString[] = R"({
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
            "name": "Pertov Nikita",
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
    std::ofstream jsonFile("jsonFile.json", std::ios::out);
    jsonFile << jsonString;
    jsonFile.close();

    std::stringstream ans;
    ans << Students::ParseFile("jsonFile.json");
    string refString = R"(| name         | group | avg | debt   |
|--------------|-------|-----|--------|
| Ivanov Petr  | 1     | 4.25| null   |
|--------------|-------|-----|--------|
| Sidorov Ivan | 31    | 4   | C++    |
|--------------|-------|-----|--------|
| Pertov Nikita| IU8-31| 3.33| 3 items|
|--------------|-------|-----|--------|
)";
    EXPECT_EQ(ans.str(), refString);
}