
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map> //linking documents with databases
#include <algorithm>
#include <regex>
//#include <nlohmann/json.hpp>

using namespace std;

//chatgpt generated sample document structure to store document in database
struct Movie_Document {
    string poster_Link;
    string series_title;
    int released_year;
    string certificate;
    int runtime; //in minutes
    string genre;
    double IMDB_rating; //specific for IMDB movie data, scale 10
    string overview;
    int meta_score; //scale 100
    string Director;
    string Star1;
    string Star2;
    string Star3;
    string Star4;
    int numVotes;
    int gross;
    //vector <string> stars; //keep all stars
};

//simulating MongoDB's feature of changing database
struct collection {
    string name;
    vector<Movie_Document*> getMovieDocs(){return this->movieDocs;}
    vector <Movie_Document*> movieDocs;  //documents linked with this DataBase
};

class Database{

    public:
        Database();
        void dbAll();
        void addCollection(string cltName);
        void addFltCollection(string name, vector<Movie_Document*> movieDocs);
        bool collectionExists(string cltName);
        void useCollection(string cltName);
        void printCurrentCltName();
        string getCurrentClt_name();
        //collection* useCollection(string cltName);
        void importCSV(string cltName, string fileName);
        void importJSON(collection* db, string fileName);
        void exportCSV(string cltName);                                             //takes name of collection and exports data to csv format on file in directory 
        void exportJSON(string cltName);                                             //takes name of collection and exports data to JSON format on file in directory
        void exportData(collection* cc, Movie_Document* movDoc, string format);
        void addDocumentManually();
        void addDocManual(string cltName, Movie_Document* movDoc);
        void deleteCollections(string cltName);
        void deleteAllDocs(string cltName);
        //Movie_Document* updateEntry(string cltName);
        void deleteDocManual();
        collection* getCollectionByName(string name);
        collection* rtnMainDB();
        collection rtnCollectionByName(string name);

        bool deleteCollectionByName(string name);
        void print();
        void printMainDB();
        void printAllClt();
        void printSingleClt(string name);
        void updateEntry(string cltName);
        vector<string> getCollectionsList();
        int checklen();


    private:
        collection* currentClt;
        collection* mainDB;
        vector<collection*> collectionDB;

        //helper functions, used in updateEntry/addDocManually for input validation
        bool isStringInt(string str);
        bool isStringDouble(string str);
        bool isValidLink(const std::string& link);


};