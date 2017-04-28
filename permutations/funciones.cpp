//
// Created by julio on 4/27/2017.
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

std::vector<int> selecRefs(int nPermutantes, int max){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution(1,max);

    std::vector<int> permutantes;

    int a;

    for (int i = 0; i < nPermutantes; ++i){
        a = distribution(generator);
        permutantes.push_back(a);
    }

    return permutantes;
}

std::vector<tuplaInfoPermutacion> calculaPermutacion(std::vector<int> &permutantes, std::vector<float> u, dataBase &bd){

    std::vector<tuplaInfoPermutacion>       permutacion;

    tuplaInfoPermutacion       a;

    std::vector<float>    permutante;

    for(int i = 0; i < permutantes.size(); i++){

        permutante = bd.db[permutantes[i]-1];
        a.u = i;
        a.d = eclideanDistance(u,permutante);
        a.inversa = 0; //porque aun no se calcula
        permutacion.push_back(a);
    }

    sort(permutacion.begin(), permutacion.end(), &comparaTuplasInfoPermutacion);

    return permutacion;
}

double eclideanDistance(std::vector<float> x, std::vector<float> y){
    {

        double d = 0;
        for(int i = 0; i < x.size(); i++){
            d = d + pow( fabs(x[i] - y[i]) ,2);
        }

        return sqrt(d);
    }
}

bool comparaTuplasInfoPermutacion(tuplaInfoPermutacion const& x, tuplaInfoPermutacion const& y){
    return (x.d < y.d);
}

std::vector<int> permutacionInversa(std::vector<tuplaInfoPermutacion> permutacion){

    std::vector<int> inversa(permutacion.size());

    for(int i = 0; i < permutacion.size(); i++)
        inversa[permutacion[i].u] = i;

    return inversa;
}

double  distanciaSP(std::vector<int> x, std::vector<int> y){

    double  d;
    d = 0;

    for(int i = 0; i < x.size(); i++)
        d = d + pow( fabs(x[i] - y[i]) , 2 );

    return d;
}

bool compPairOD(parOD const& x, parOD const& y){
    return(x.dist < y.dist);
}

float calcRecall(std::vector<int> answer, std::vector<parOD> &ispDistances, int percentage){

    int     workload = ceil( ispDistances.size() * float(percentage) / 100),
            i;

    std::vector<int> workloadISP;

    for(i = 0; i < workload; i++)
        workloadISP.push_back(ispDistances[i].obj);


    float intersection = 0;
    for(i = 0; i < answer.size(); i++){
        if( find(workloadISP.begin(), workloadISP.end(), answer[i]) != workloadISP.end() )
            intersection++;
    }

    return intersection/answer.size();
}