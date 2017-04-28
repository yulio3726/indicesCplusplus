//
// Created by julio on 4/26/2017.
//

#ifndef RBBF1_STRUCTURES_H
#define RBBF1_STRUCTURES_H

//variables

typedef std::bitset<256> sketch;

typedef  std::vector<sketch> index;

typedef std::vector<std::vector<int>> answersQuerys;

struct parOD{
    int obj;
    double dist;
};

struct dataBase{
    std::vector<std::vector<float>> db; //vector de vectores
    int dim;
    int metrica;
    int ndb;
};

struct hiperplano{
    int p1;
    int p2;
};

#endif //RBBF1_STRUCTURES_H
