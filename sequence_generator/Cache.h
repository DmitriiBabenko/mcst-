//
// created by Dmitrii B. on 19.08.2026
//
#pragma once
#include <string>
#include "Graph.h"
//pred: graph - набор валидных графов, path - валидный путь к директории
//post: создаёт json содержащий std::vector<Graph> в директории по указанному пути
void saveCache(const std::vector<Graph> & graph, const std::string & path);
//pred: path - валидный путь к json файлу; example name.json; в файле по заданному пути - набор валидных графов
//post: набор валидных графов, эквивалентных содержащимся в файле по заданному пути
const std::vector<Graph> loadCache(const std::string & path);