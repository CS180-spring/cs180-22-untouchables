#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map> //linking documents with databases
#include <algorithm>

struct collection {
    string name;
    vector<Movie_Document*> getMovieDocs(){return this->movieDocs;}
    vector <Movie_Document*> movieDocs;  //documents linked with this DataBase
};