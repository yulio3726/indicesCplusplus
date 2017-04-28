
#include "funciones.h"

int main() {

    std::string dirDataBase;
    std::string dirDatabaBaseQuerys;
    std::string dirAnswersQuerys;

    dataBase db, querys;

    std::vector<int> nPermutants = {64,128,192,256};

    //tiempo de ejecucion
    std::chrono::time_point<std::chrono::high_resolution_clock>    start,
            end;

    //nombres de las archivos;
    dirDataBase = "C:\\Users\\julio\\ClionProjects\\DBS\\nasa.ascii";
    dirDatabaBaseQuerys = "C:\\Users\\julio\\ClionProjects\\DBS\\consultas.20.1000.ascii";
    dirAnswersQuerys = "C:\\Users\\julio\\ClionProjects\\DBS\\300resultados-nasa-r20-1m";

    //lectura de los archivos
    std::cout << "Se lee la base de datos ::" << std::endl;
    db = loadDB(dirDataBase,0);

    std::cout << "Se lee las consultas ::" << std::endl;
    querys = loadDB(dirDatabaBaseQuerys,0);

    //generan numeros aleatorios
    std::vector<int> permutants;
    permutants = selecPermutants(5,db.size());

    //contruccion del indice
    index PI; //permutants index

    return 0;
}