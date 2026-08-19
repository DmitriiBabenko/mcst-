//
// Created by Dmitrii B. on 19.08.2026
//
#pragma once
#include <vector>
#include "Graph.h"

//Pred: graph - валидный граф. args.regs > 0
//Post: валидный граф, для любых двух узлов a и b, f - порядок в топологической сортировке графа
//                              где f(a) < f(b) ==> f(b) > f(c_i), где c_i все узлы вычисляемые из a
//  в случае если args.regs будет недостаточно для выполнения pred условия функция ничего не возвращает;
const Graph assignComponent(const Graph & graph, std::mt19937 & gen, const unsigned & regs);