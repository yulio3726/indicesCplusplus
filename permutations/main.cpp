#include "funciones.h"

int main() {

    //variables necesarios para el indexado
    int     nObjDB = 0,
            nObjQuerys = 2,
            k = 8; //k vecinos mas cercanos


    std:: vector<int> percentajes = {1},
            nPermutantes = {64, 128, 192 ,256},
            permutantes;

    //archivos
    std::string dirDatabase;
    std::string dirDatabaseQuerys;
    std::string dirAnswersQuerys;

    dirDatabase = "C:\\Users\\julio\\ClionProjects\\DBS\\uniformR20-50mil.ascii";
    dirDatabaseQuerys = "C:\\Users\\julio\\ClionProjects\\DBS\\uniformR20-50.querys";
    dirAnswersQuerys = "C:\\Users\\julio\\ClionProjects\\DBS\\resultados-uniform-r20-50mil";

    //lectura de las bases de datos
    std::cout <<"LECTURA DE LA BASE DE DATOS::"<< std::endl;
    dataBase db = loadDB(dirDatabase, nObjDB);

    std::cout << "LECTURA DE LAS CONSULTAS::" << std::endl;
    dataBase querys = loadDB(dirDatabaseQuerys, nObjQuerys);

    std::cout << "LECTURA DE LAS RESPUESTAS A LAS CONSULTAS::" << std::endl;
    answersQuerys answers = loadAnswers(dirAnswersQuerys, nObjQuerys, k);

    std::vector<float> recalls; //por se quiere revisar mas del 1 porciento

    std::ofstream file;
    file.open("uniformR20-8nn-1porciento");

    for(int i = 0; i < nPermutantes.size(); i++){

        std:: cout << "CONSTRUCCION DEL INDICE :: " << i <<std::endl;
        permutantes = selecRefs( nPermutantes[i], db.ndb);
        index pIndex = build(db, permutantes);

        std::cout<<"CONSULTAS ::" << std::endl;
        recalls = test(pIndex, db, querys, answers, k, permutantes, percentajes);

        std::cout << "RESULTADOS ::" << std::endl;
        std::cout << "\t"<< nPermutantes[i] << " -" << recalls[0]/querys.ndb << std::endl;
        std::cout << nPermutantes[i] << " " << recalls[0]/querys.ndb << std::endl;

        if(file.is_open()){
            file << nPermutantes[i] << " " << recalls[0]/querys.ndb << std::endl;
        } else{
            std::cout<< "error al escribir los resultados" << std::endl;
        }

        recalls.clear();
    }


    file.close();
    return 0;
}

index build( dataBase &db ,std::vector<int> permutantes){

    index pIndex;

    std::vector<tuplaInfoPermutacion>       permutacionI;

    std::vector<int> inversa;

    std::vector<float> u;

    for(int i = 0; i < db.ndb; i++){
        permutacionI.clear();
        inversa.clear();
        u.clear();
        u=db.db[i];
        permutacionI = calculaPermutacion(permutantes,u,db);
        inversa = permutacionInversa(permutacionI);
        pIndex.push_back(inversa);
    }

    return pIndex;
}

std::vector<float> test(index &rbbf1, dataBase &db, dataBase &querys, answersQuerys &answers, int k, std::vector<int> permtantes , std::vector<int> percentages){

    std::vector<float> recalls (percentages.size(),0);

    std::vector<parOD> ispDistances;

    float recall;

    std::vector<int> answer;

    //prueba para cada objeto
    for(int j = 0; j < querys.ndb; j++){

        answer = answers[j];

        //prueba para cada porcentaje
        for(int i = 0; i < percentages.size(); i++){

            ispDistances.clear();
            ispDistances = knn(rbbf1,db, querys.db[j], permtantes);

            recall = calcRecall(answer, ispDistances, percentages[i]);
            recalls[i] = recalls[i] + recall;
        }
        answer.clear();
    }

    return recalls;
}

std::vector<parOD> knn(index &pIndex, dataBase db, std::vector<float> query, std::vector<int> permutantes){

    parOD   ispO;

    std::vector<parOD> ispDistances;

    //construccion de la permutacion consulta
    std::vector<tuplaInfoPermutacion>       permutacionQ;

    permutacionQ = calculaPermutacion(permutantes,query,db);
    std::vector<int> inversaQ = permutacionInversa(permutacionQ);

    //búsqueda
    for(int i = 0; i < pIndex.size(); i++){

        ispO.obj = i; //Las respuestas van de 0 a las primeras 30
        ispO.dist = distanciaSP(inversaQ, pIndex[i]);
        ispDistances.push_back(ispO);
    }

    sort(ispDistances.begin(), ispDistances.end(), &compPairOD);

    return ispDistances;
}