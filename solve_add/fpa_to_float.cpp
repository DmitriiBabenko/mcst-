#include "../fpa_to_float.h"
#include <cmath>
float exp_to_float(const std::vector<char>& exp, const int base) {
    const std::string s(exp.begin(), exp.end());
    return std::stoi(s, nullptr, base);
}

float mantissa_to_float(const std::vector<char>& mantissa) {
    float result = 1.0f;
    for (size_t i = 0; i < mantissa.size(); ++i) {
        if (mantissa[i] == '1')
            result += std::pow(2.0f, -static_cast<int>(i + 1));
    }
    return result;
}

float fpa_to_float(const z3::expr& val) {
    std::string strVal = val.to_string();

    const size_t sign_pos = strVal.find("#b");
    if (sign_pos == std::string::npos) return 0.0f;

    const char sign_bit = strVal[sign_pos + 2];

    const size_t exp_pos = strVal.find("#x", sign_pos);
    if (exp_pos == std::string::npos) {return 0.0f;}

    std::vector<char> exp;
    for (size_t i = exp_pos + 2; i < strVal.size() && strVal[i] != ' '; ++i) {
        exp.push_back(strVal[i]);
    }

    size_t mant_pos = strVal.find("#b", exp_pos);
    if (mant_pos == std::string::npos) return 0.0f;

    std::vector<char> mantissa;
    for (size_t i = mant_pos + 2; i < strVal.size() && strVal[i] != ')'; ++i) {
        mantissa.push_back(strVal[i]);
    }

    const float sign = (sign_bit == '0') ? 1.0f : -1.0f;
    const float exponent = exp_to_float(exp, 16) - 127.0f; // IEEE 754 bias
    const float mantissa_val = mantissa_to_float(mantissa);

    return sign * std::pow(2.0f, exponent) * mantissa_val;
}