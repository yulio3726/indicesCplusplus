//
// Created by julio on 4/27/2017.
//

#ifndef PERMUTATIONS_STRUCTURES_H
#define PERMUTATIONS_STRUCTURES_H

typedef std::vector<std::vector<int>> answersQuerys;

typedef  std::vector<std::vector<int>> index;

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

struct tuplaInfoPermutacion{
    int u; //objeto
    double d; //distancia
    int inversa; //inversa con respecto a la permutacion
};

#endif //PERMUTATIONS_STRUCTURES_H
