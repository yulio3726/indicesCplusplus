
#include "funciones.h"

int main() {

    //variables necesarios para el indexado
    int     nObjDB = 0,
            nObjQuerys = 2,
            k = 8; //k vecinos mas cercanos


    std:: vector<int> percentajes = {1},
                      nHiperPlanos = {64, 128, 192 ,256};

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

    for(int i = 0; i < nHiperPlanos.size(); i++){

        std:: cout << "CONSTRUCCION DEL INDICE :: " << i <<std::endl;
        std::vector<hiperplano> hyperplanes = selecRefs( nHiperPlanos[i], db.ndb);
        index rbbf1 = build(db, hyperplanes);

        std::cout<<"CONSULTAS ::" << std::endl;
        recalls = test(rbbf1, db, querys, answers, k, hyperplanes, percentajes);

        std::cout << "RESULTADOS ::" << std::endl;
        std::cout << "\t"<< nHiperPlanos[i] << " % " << recalls[0]/querys.ndb << std::endl;

        if(file.is_open()){
            file << nHiperPlanos[i] << " " << recalls[0]/querys.ndb << std::endl;
        } else{
            std::cout<< "error al escribir los resultados" << std::endl;
        }

        recalls.clear();
    }

    file.close();
    return 0;
}

index build( dataBase &db ,std::vector<hiperplano> hyperplanes){

    index rbbf1;
    sketch o;

    for(int i = 0; i < db.ndb; i++){
        o.reset();
        for(int dim = 0; dim < hyperplanes.size(); dim++){

            hiperplano hi;
            hi.p1 = hyperplanes[dim].p1 - 1;
            hi.p2 = hyperplanes[dim].p2 - 1;

            double d1 = eclideanDistance(db.db[i],db.db[hi.p1]);
            double d2 = eclideanDistance(db.db[i],db.db[hi.p2]);

            if(d1 <= d2)
                o.set(dim);
        }
        rbbf1.push_back(o);
    }

    return rbbf1;
}

std::vector<float> test(index &rbbf1, dataBase &db, dataBase &querys, answersQuerys &answers, int k, std::vector<hiperplano> hyperplanes , std::vector<int> percentages){

    std::vector<float> recalls (percentages.size(),0);

    std::vector<parOD> hammingDistances;

    float recall;

    std::vector<int> answer;

    //prueba para cada objeto
    for(int j = 0; j < querys.ndb; j++){

        answer = answers[j];

        /*//muestra los resultados que encuentra si utilizo la búsqueda secuencal para obtener los resultados
        //comparandolo con los resultados leidos desde el fichero
        std::vector<int> answerSec = busquedaSecuencial(db, querys.db[j], k);
        for(int a = 0; a < k; a++)
            std::cout<<"file " << answer[a] << " program " << answerSec[a] << std::endl;*/

        //prueba para cada porcentaje
        for(int i = 0; i < percentages.size(); i++){

            hammingDistances.clear();
            hammingDistances = knn(rbbf1,db, querys.db[j], hyperplanes);

            recall = calcRecall(answer, hammingDistances, percentages[i]);
            recalls[i] = recalls[i] + recall;

        }
        answer.clear();
    }

    /*std::cout<< "\t se retornan " << recalls.size() << " recalls"<< std::endl;

    for(int i = 0; i < recalls.size(); i++){
        std::cout<<"\t" << percentages[i] << " - " << recalls[i]/querys.ndb << std::endl;
    }*/

    return recalls;
}

std::vector<parOD> knn(index &rbbf1, dataBase db, std::vector<float> query, std::vector<hiperplano> hyperplanes){

    parOD   hammingO;

    std::vector<parOD> hammingDistances;

    //construccion del sketch consulta
    sketch q;
    q.reset();

    for(int dim = 0; dim < hyperplanes.size(); dim++){

        hiperplano hi;
        hi.p1 = hyperplanes[dim].p1 - 1;
        hi.p2 = hyperplanes[dim].p2 - 1;

        double d1 = eclideanDistance(query,db.db[hi.p1]);
        double d2 = eclideanDistance(query,db.db[hi.p2]);

        if(d1 <= d2)
            q.set(dim);
    }

    //búsqueda
    for(int i = 0; i < rbbf1.size(); i++){

        hammingO.obj = i; //Las respuestas van de 0 a las primeras 30
        hammingO.dist = hammingdistance( q, rbbf1[i]);

        hammingDistances.push_back(hammingO);
    }

    sort(hammingDistances.begin(), hammingDistances.end(), &compPairOD);

    return hammingDistances;
}