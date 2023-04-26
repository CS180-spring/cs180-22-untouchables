//terminal console
#include <iostream>
#include <map> //linking documents with databases
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>

using namespace std;

//chatgpt generated sample document structure to store document in database
struct Movie_Document {
    string series_title;
    int released_year;
    int runtime; //in minutes
    string genre;
    double IMDB_rating; //specific for IMDB movie data, scale 10
    string overview;
    int meta_score; //scale 100
    string Director;
    string Star; //star 1 only
    //vector <string> stars; //keep all stars
};

//simulating MongoDB's feature of changing database
struct DataBase {
    string name;
    vector <Movie_Document> storedDocuments; //documents linked with this DataBase
};

void messageDisplayer();

//check if user input is within input word limitation
string check_num_word(string user_input, int limit);

//simple function to get the List of DataBase names
vector<string> getNameList(vector<DataBase> existingDB);


void displayMovieDocument(const DataBase& database, unsigned int index);
