//
// Created by julio on 4/26/2017.
//

#ifndef RBBF1_FUNCIONES_H
#define RBBF1_FUNCIONES_H

//includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include <chrono>
#include <random>
#include <algorithm>
#include <math.h>
#include "structures.h"

//funciones

dataBase loadDB(std::string fileName, int nObjDB);

answersQuerys loadAnswers(std::string fileName, int nObjDB, int k);

index build( dataBase &db ,std::vector<hiperplano> hyperplanes);

std::vector<hiperplano> selecRefs(int nHiperPlanos, int max);

double eclideanDistance(std::vector<float> x, std::vector<float> y);

std::vector<float> test(index &rbbf1, dataBase &db, dataBase &querys, answersQuerys &answers, int k, std::vector<hiperplano> hyperplanes , std::vector<int> percentages);

double hammingdistance(sketch x, sketch y);

bool compPairOD(parOD const& x, parOD const& y);

std::vector<parOD> knn(index &rbbf1, dataBase db, std::vector<float> query, std::vector<hiperplano> hyperplanes);

float calcRecall(std::vector<int> answer, std::vector<parOD> &hammingDistances, int percentage);

std::vector<int> busquedaSecuencial( dataBase &db, std::vector<float> q, int k);

#endif //RBBF1_FUNCIONES_H
