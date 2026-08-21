//
// created by Dmitrii B. on 19.08.2026
//
#pragma once
#include <string>
#include "Graph.h"
/*
Реализует возможность кешировать состояние набора графов (ops/ways/incWays/values/regs) на диск
и загружать его обратно - это позволяет начинать/заканчивать выполнение конвейера (этапы 1-5)
на произвольном этапе (см. --cache-path-download/--cache-path-upload в sequence_generator.cpp).
pred: graph - набор валидных графов, path - валидный путь к директории
post: создаёт json содержащий std::vector<Graph> в директории по указанному пути 
*/
void saveCache(const std::vector<Graph> & graph, const std::string & path);
/*
pred: path - валидный путь к json файлу; example name.json; в файле по заданному пути - набор валидных графов
post: набор валидных графов, эквивалентных содержащимся по заданному пути 
*/
const std::vector<Graph> loadCache(const std::string & path);