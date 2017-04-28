//
// Created by julio on 4/28/2017.
//

#ifndef SBEPP_FUNCIONES_H
#define SBEPP_FUNCIONES_H

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

index build( dataBase &db ,std::vector<int> permutantes, int prefijo);

std::vector<tuplaInfoPermutacion> calculaPermutacion(std::vector<int> &permutantes, std::vector<float> u, dataBase &bd);

double eclideanDistance(std::vector<float> x, std::vector<float> y);

bool comparaTuplasInfoPermutacion(tuplaInfoPermutacion const& x, tuplaInfoPermutacion const& y);

std::vector<int> permutacionInversa(std::vector<tuplaInfoPermutacion> permutacion);

std::vector<float> test(index &sbepp, dataBase &db, dataBase &querys, answersQuerys &answers, int k, std::vector<int> permtantes , int prefijo, std::vector<int> percentages);

std::vector<parOD> knn(index &rbbf1, dataBase db, std::vector<float> query, std::vector<int> permutantes, int prefijo);

double hammingdistance(sketch x, sketch y);

bool compPairOD(parOD const& x, parOD const& y);

float calcRecall(std::vector<int> answer, std::vector<parOD> &hammingDistances, int percentage);

#endif //SBEPP_FUNCIONES_H
