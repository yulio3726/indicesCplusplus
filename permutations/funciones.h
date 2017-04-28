//
// Created by julio on 4/27/2017.
//

#ifndef PERMUTATIONS_FUNCIONES_H
#define PERMUTATIONS_FUNCIONES_H

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

dataBase loadDB(std::string fileName, int nObjDB);

answersQuerys loadAnswers(std::string fileName, int nObjDB, int k);

std::vector<int> selecRefs(int nPermutantes, int max);

index build( dataBase &db ,std::vector<int> hyperplanes);

std::vector<tuplaInfoPermutacion> calculaPermutacion(std::vector<int> &permutantes, std::vector<float> u, dataBase &bd);

double eclideanDistance(std::vector<float> x, std::vector<float> y);

bool comparaTuplasInfoPermutacion(tuplaInfoPermutacion const& x, tuplaInfoPermutacion const& y);

std::vector<int> permutacionInversa(std::vector<tuplaInfoPermutacion> permutacion);

std::vector<float> test(index &rbbf1, dataBase &db, dataBase &querys, answersQuerys &answers, int k, std::vector<int> permtantes , std::vector<int> percentages);

std::vector<parOD> knn(index &pIndex, dataBase db, std::vector<float> query, std::vector<int> permutantes);

double  distanciaSP(std::vector<int> x, std::vector<int> y);

bool compPairOD(parOD const& x, parOD const& y);

float calcRecall(std::vector<int> answer, std::vector<parOD> &ispDistances, int percentage);

#endif //PERMUTATIONS_FUNCIONES_H
