#include "json_spirit/libs/json_spirit.h"
#include <string>
#include <fstream>

json_spirit::mValue value;
std::string json_str = R"({"name": "test", "count": 42, "values": [1, 2, 3]})";

bool ok = json_spirit::read_string(json_str, value);
if (!ok) {
    // ошибка парсинга
}

json_spirit::mObject& obj = value.get_obj();
std::string name = obj["name"].get_str();
int count = obj["count"].get_int();

json_spirit::mArray& arr = obj["values"].get_array();
for (auto& v : arr) {
    int x = v.get_int();
}