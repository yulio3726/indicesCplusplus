//
// Created by julio on 4/25/2017.
//


#ifndef INDICE_INVERTIDOPRUEBA_FUNCIONES_H
#define INDICE_INVERTIDOPRUEBA_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <sstream>      // std::istringstream
#include <unordered_map>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include "structures.h"

typedef std::unordered_map<std::string,std::string> stringmap;

dataBase loadDB(std::string fileName, int delta);

void printDataBAse(dataBase &db);

std::vector<int> selecPermutants(int n,int max);

#endif //INDICE_INVERTIDOPRUEBA_FUNCIONES_H
