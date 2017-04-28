//
// Created by julio on 4/26/2017.
//

#include "funciones.h"

dataBase loadDB(std::string fileName, int nObjDB){

    std::string     line;
    std::string     element;
    std::ifstream   inputFile(fileName);

    dataBase    db;

    int     u = 0;

    bool    finish = false,
            encabezado = true;

    std::vector<float> a;

    if(inputFile.is_open()){
        while(!inputFile.eof() && finish == false){

            getline(inputFile,line,'\n');
            std::istringstream iss(line);
            u++;
            a.clear();

            while (getline(iss,element,' ')){

                if(encabezado == true){
                    db.dim = stoi(element);

                    getline(iss,element,' ');
                    if(nObjDB != 0){
                        db.ndb = nObjDB;
                    }else{
                        db.ndb = stoi(element);
                    }

                    getline(iss, element, ' ');
                    db.metrica = stoi(element);

                    encabezado = false;
                    u = 0;
                }else{
                    a.push_back(stof(element));
                }
            }

            if(u != 0) db.db.push_back(a);
            if( u == db.ndb) finish = true;
        }
    }else{
        std::cout<<"\terror al abrir la base de datos" << std::endl;
    }

    std::cout<<"\t se han leido " << db.db.size() << " objetos con " << db.db[0].size() << " dimensiones" << std::endl;

    return db;
}

answersQuerys loadAnswers(std::string fileName, int nObjDB, int k){

    std::string     line;
    std::string     element;
    std::ifstream   inputFile(fileName);

    answersQuerys    answers;

    int     u = 0,
            nk = 0;

    bool    finish = false;

    std::vector<int> answer;

    if(inputFile.is_open()){
        while(!inputFile.eof() && finish == false){

            getline(inputFile,line,'\n');
            std::istringstream iss(line);
            u++;
            answer.clear();
            nk = 0;

            while (getline(iss,element,' ')){
                nk++;
                answer.push_back(stof(element));
                if (nk == k) break;
            }

            answers.push_back(answer);
            if( u == nObjDB) finish = true;
        }
    }else{
        std::cout<<"\terror al abrir la base de datos" << std::endl;
    }

    std::cout<<"\t se han leido " << answers.size() << " consultas con " << answers[0].size() << " respuestas" << std::endl;

    return answers;
}

std::vector<hiperplano> selecRefs(int nHiperPlanos, int max){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution(1,max);

    hiperplano h;
    std::vector<hiperplano> hyperplanes;

    for (int i = 0; i < nHiperPlanos; ++i){
        h.p1 = distribution(generator);
        h.p2 = distribution(generator);
        hyperplanes.push_back(h);
    }

    return hyperplanes;
}

double eclideanDistance(std::vector<float> x, std::vector<float> y){

    double d = 0;
    for(int i = 0; i < x.size(); i++){
        d = d + pow( fabs(x[i] - y[i]) ,2);
    }

    return sqrt(d);
}

double hammingdistance(sketch x, sketch y){

    return(x ^= y ).count();
}

bool compPairOD(parOD const& x, parOD const& y){
    return(x.dist < y.dist);
}

float calcRecall(std::vector<int> answer, std::vector<parOD> &hammingDistances, int percentage){

    int     workload = ceil( hammingDistances.size() * float(percentage) / 100),
            i;

    std::vector<int> workloadHamming;

    for(i = 0; i < workload; i++)
        workloadHamming.push_back(hammingDistances[i].obj);


    float intersection = 0;
    for(i = 0; i < answer.size(); i++){
        if( find(workloadHamming.begin(), workloadHamming.end(), answer[i]) != workloadHamming.end() )
            intersection++;
    }

    //std::cout<<"\t encontrados " << intersection << " revisando " << workload  << " recall " << intersection/answer.size() << std::endl;

    return intersection/answer.size();
}

std::vector<int> busquedaSecuencial( dataBase &db, std::vector<float> q, int k){

    std::vector<parOD> resultados;

    parOD       a;

    for(int j = 0; j < db.ndb; j++){

        a.obj = j;
        a.dist = eclideanDistance(q,db.db[j]);

        resultados.push_back(a);
    }

    sort(resultados.begin(), resultados.end(), &compPairOD);

    std::vector<int> kresult;
    for(int j = 0; j < k; j++)
        kresult.push_back(resultados[j].obj);

    return kresult;
}