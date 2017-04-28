//
// Created by julio on 4/25/2017.
//

#include "funciones.h"


dataBase loadDB(std::string fileName, int nLinesToRead){

    std::string     line;
    std::string     element;
    std::ifstream   inputFile(fileName);

    bool    encabezado =  true,
            finish = false;

    std::vector<float>  a;

    int     u,
            ndb;

    dataBase    db;

    u = 0;
    if(inputFile.is_open()){

       while(!inputFile.eof() && finish == false){

           getline(inputFile,line,'\n');
           std::istringstream iss(line);
           a.clear();
           u++;
           while( getline(iss,element,' ') ){


               if(encabezado == true){

                   int dim = stoi(element);//dim

                   getline(iss,element,' '); // nbd
                   if(nLinesToRead!=0){
                       ndb = nLinesToRead;
                   }else{
                       ndb = stoi(element);
                   }

                   getline(iss,element,' '); // metrica
                   int metrica = stoi(element);
                   encabezado = false;
                   u=0;

               }else{
                   a.push_back(std::stof(element));
               }
           }
           if(u!=0){
               db.insert( {u,a} ); //guardo el elemento //http://en.cppreference.com/w/cpp/container/unordered_map/insert
           }

           if (u == ndb)
               finish = true;
       }
        inputFile.close();
    }else{
        std::cout << "Error al abrir la base de datos" << std::endl;
    }

    std::cout << "\t Se han leido " << db.size() << " objetos con " << db[1].size() << " dimensiones"<<std::endl;

    return db;
}

void printDataBAse(dataBase &db){

    for(auto& x:db){
        std::cout << " " << x.first << ":" ;
        for(std::vector<float>::iterator y = x.second.begin(); y != x.second.end(); ++y)
            std::cout << ' ' << *y;
        std::cout << std::endl;
    }

}

//http://www.cplusplus.com/reference/random/uniform_int_distribution/operator()/
std::vector<int> selecPermutants(int n,int max){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution(1,max);

    std::vector<int> permutants;

    for (int i = 0; i < n; ++i)
        permutants.push_back(distribution(generator));

    return permutants;
}