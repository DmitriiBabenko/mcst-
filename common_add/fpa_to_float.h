#ifndef FPA_TO_FLOAT_H
#define FPA_TO_FLOAT_H

#include <vector>
#include "z3++.h"

int exp_to_float(const std::vector<char>& exp, int base);
float mantissa_to_float(const std::vector<char>& mantissa);
float fpa_to_float(const z3::expr& val);

#endif