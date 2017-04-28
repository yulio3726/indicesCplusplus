#include "funciones.h"

int main() {

    //variables necesarios para el indexado
    int     nObjDB = 0,
            nObjQuerys = 2,
            k = 8; //k vecinos mas cercanos


    std:: vector<int> percentajes = {1},
            nPermutantes = {64,128, 192, 256}, //{64, 384, 576 , 768}, //192
            prefijos = {64,128, 192, 256},
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

    //for(int i = 0; i < nPermutantes.size(); i++){

        std:: cout << "CONSTRUCCION DEL INDICE :: " << 0 <<std::endl;
        permutantes = selecRefs( nPermutantes[0], db.ndb);
        index sbepp = build(db, permutantes, prefijos[0]);

        std::cout<<"CONSULTAS ::" << std::endl;
        recalls = test(sbepp, db, querys, answers, k, permutantes, prefijos[0], percentajes);

        std::cout << "RESULTADOS ::" << std::endl;
        std::cout << "\t"<< nPermutantes[0] << " - " << recalls[0]/querys.ndb << std::endl;

        if(file.is_open()){
            file << nPermutantes[0] << " " << recalls[0]/querys.ndb << std::endl;
        } else{
            std::cout<< "error al escribir los resultados" << std::endl;
        }

    //    recalls.clear();
    //}

    file.close();
    return 0;
}

index build( dataBase &db ,std::vector<int> permutantes, int prefijo){

    index sbepp;

    std::vector<tuplaInfoPermutacion>       permutacionI;

    std::vector<int> inversa;

    std::vector<float> u;

    int parametroNpermutantes = permutantes.size();

    sketch      a;

    for(int i = 0; i < db.ndb; i++){
        permutacionI.clear();
        inversa.clear();
        u.clear();
        u=db.db[i];
        permutacionI = calculaPermutacion(permutantes,u,db);
        inversa = permutacionInversa(permutacionI);
        for(int j = 0; j < prefijo; j++){

            if( permutacionI[j].inversa <= parametroNpermutantes/2 )
                a.set(j);
        }
        sbepp.push_back(a);
        a.reset();
    }

    return sbepp;
}

std::vector<float> test(index &sbepp, dataBase &db, dataBase &querys, answersQuerys &answers, int k, std::vector<int> permtantes , int prefijo, std::vector<int> percentages){

    std::vector<float> recalls (percentages.size(),0);

    std::vector<parOD> hammingDistances;

    float recall;

    std::vector<int> answer;


    for(int j = 0; j < querys.ndb; j++){

        answer = answers[j];
        std::cout << "\tconsulta " << j <<std::endl;

        //prueba para cada porcentaje
        for(int i = 0; i < percentages.size(); i++){

            hammingDistances.clear();
            std::cout << "\t knn" << std::endl;
            hammingDistances = knn(sbepp,db, querys.db[j], permtantes, prefijo);
            std::cout<< "\t calcula recall" << std::endl;
            recall = calcRecall(answer, hammingDistances, percentages[i]);
            std::cout<<"\t Recall " << recall << std::endl;
            recalls[i] = recalls[i] + recall;

        }
        answer.clear();
    }


    return recalls;
}

std::vector<parOD> knn(index &sbepp, dataBase db, std::vector<float> query, std::vector<int> permutantes, int prefijo){

    parOD   hammingO;

    std::vector<parOD> hammingDistances;

    //construccion del sketch consulta
    std::vector<tuplaInfoPermutacion>       permutacionI;

    std::vector<int> inversa;

    int parametroNpermutantes = permutantes.size();

    sketch q;
    q.reset();

    permutacionI = calculaPermutacion(permutantes,query,db);
    inversa = permutacionInversa(permutacionI);

    std::cout<<"\t sketch consulta " << std::endl;
    for(int j = 0; j < prefijo; j++){

        if( permutacionI[j].inversa <= parametroNpermutantes/2 )
            q.set(j);
    }

    //búsqueda
    std::cout << "\t busqueda" << std::endl;
    for(int i = 0; i < sbepp.size(); i++){

        hammingO.obj = i; //Las respuestas van de 0 a las primeras 30
        hammingO.dist = hammingdistance( q, sbepp[i]);

        hammingDistances.push_back(hammingO);
    }

    std::cout <<"\t ordenamiento" << std::endl;
    sort(hammingDistances.begin(), hammingDistances.end(), &compPairOD);

    return hammingDistances;
}