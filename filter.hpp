#ifndef _FILTER_H_
#define _FILTER_H_
#include "database.hpp"

#include <iostream>
#include <map> //linking documents with databases
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

class Filter{

    public:
        // constructor
        Filter(Database& db);
        
        string selectCollection();
        void displayMenu();                                                    // display main menu for filter class
        
        // filter function
        void filterMain();                                                     // main function to call display menu functions, set working collection, and get user input
        void filterDisplay();                                                  // display filter menu and get user input
        void genreFilter(string genre);                                        // filters working collection by genre
        void featureFilter(string feature);                                    // takes feature to filter from user input and filters features with string data
        void titleFilter(string titleName);                                    // filters working collection by title
        void fltSortResults(vector<Movie_Document*> fsData);                    // give user methods to perform on filtered movie data
        void multipleFilters(vector<string> fltNames);
        
        // sorting functions
        void sortMain();
        void sortDisplay();
        void sorter(string feature, string order);                              // takes user input for feature and order of sorting and calls sorting function based from feature input
        void titleSort(vector<Movie_Document*> copyVec, string order);          // sorts title feature in specified order
        void releaseDateSort(vector<Movie_Document*> copyVec, string order);    // sorts release date feature in specified order
        void ratedSort(vector<Movie_Document*> copyVec, string order);          // sorts rated feature in specified order
        void runtimeSort(vector<Movie_Document*> copyVec, string order);        // sorts runtime feature in specified order
        void genreSort(vector<Movie_Document*> copyVec, string order);          // sorts genre feature in specified order
        void ratingSort(vector<Movie_Document*> copyVec, string order);         // sorts rating feature in specified order
        void metaScoreSort(vector<Movie_Document*> copyVec, string order);      // sorts meta score feature in specified order
        void directorSort(vector<Movie_Document*> copyVec, string order);       // sorts director feature in specified order
        void starSort(vector<Movie_Document*> copyVec, string order);           // sorts star feature in specified order
        void numVotesSort(vector<Movie_Document*> copyVec, string order);       // sorts number of votes feature in specified order
        void grossEarningsSort(vector<Movie_Document*> copyVec, string order);  // sorts gross earnings feature in specified order

        // query/search function
        void query();

        void printData(vector<Movie_Document*> movieData);                      // print filtered/sorted movie data    
        vector<Movie_Document*> copyMovieDocs(string cltName);                  // copy actual data from collection vector<movie_document*> and not just pointer

    private:
        Database& db;
        collection* workingClt;
        vector <Movie_Document*> workingData;
        vector <Movie_Document*> sortedData;

        //helper functions
        bool isSubstring(const std::string& str1, const std::string& str2);

};
#endif
