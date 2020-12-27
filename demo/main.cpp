#include <iostream>
#include <students.hpp>
int main(){
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

        std::cout << Students::ParseFile("jsonFile.json");
}
