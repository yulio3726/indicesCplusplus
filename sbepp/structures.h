//
// Created by julio on 4/28/2017.
//

#ifndef SBEPP_STRUCTURES_H
#define SBEPP_STRUCTURES_H

typedef std::bitset<256> sketch;

typedef  std::vector<sketch> index;

typedef std::vector<std::vector<int>> answersQuerys;

struct dataBase{
    std::vector<std::vector<float>> db; //vector de vectores
    int dim;
    int metrica;
    int ndb;
};

struct tuplaInfoPermutacion{
    int u; //objeto
    double d; //distancia
    int inversa; //inversa con respecto a la permutacion
};

struct parOD{
    int obj;
    double dist;
};

#endif //SBEPP_STRUCTURES_H
