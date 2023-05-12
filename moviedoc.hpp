#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map> //linking documents with databases
#include <algorithm>

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