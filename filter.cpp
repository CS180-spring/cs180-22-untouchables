#include "filter.hpp"

// constructor with member initializer list
// to set reference to db so db reference does
// not have to be passed to filter class every time
Filter::Filter(Database& db): db{db}{}

//void Filter::messageDisplayer();

// Helper function for sorting
bool alphaSortHelper( Movie_Document* x, Movie_Document* y){

    return x->series_title < y->series_title;
}

vector<Movie_Document*> Filter::copyMovieDocs(string cltName){
    
    // use db function to get collection by name
    // pointer to collection is returned
    collection* clt = db.getCollectionByName("default");

    // set variable to size of vector to be copied
    int size = clt->movieDocs.size();

    // vector to hold copied movie data
    vector<Movie_Document*> copyVec(size);

    // copy takes beginning iterator, end iterator, and beginning iterator of new vector to copy to
    copy(clt->movieDocs.begin(),clt->movieDocs.begin() + size, copyVec.begin());

    return copyVec;

}

// sorts by series title right now 
void Filter::alphabetSort(){

    // gets movie data copied over
    vector<Movie_Document*> copyVec = copyMovieDocs("default"); // can change this to a passed string variable passed to alphasort()
    
    // sorts with a helper function
    sort(copyVec.begin(), copyVec.end(), alphaSortHelper);

    // add new collection
    // the parameters can be changed within your class so you can let user
    // pick name of new collection for example.
    db.addFltCollection("alphaSort", copyVec);

}

void Filter::genreSort(string cltName, string genre){
    vector<Movie_Document*> copyVec = copyMovieDocs(cltName);
    vector<Movie_Document*> sortedVec;

    for(auto i : copyVec){
        
        if(i->genre.find(genre) != string::npos){
            sortedVec.push_back(i);
        }
    }

    if(!db.collectionExists(genre)){
        db.addFltCollection(genre, sortedVec);
    }
    else if(db.collectionExists(genre)){
        cout << "Collection with name \"" << genre << "\"" << " already exists\nn";
    }
    // Else notify user
}

void Filter::numberSort(){
}

void Filter::output(){
}

/*
void titleView(){
cout << "A = View all" << endl;
cout << "T = Just titles" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
titleView();
}
}


void titleSort(){
getline(cin, userinput);
if (userinput == "0"){
alphabetSort();
cout << "Would you like to view all information or just the title?" << endl;
titleView();
}
else if(userinput == "1"){
alphabetSort();
cout << "Would you like to view all information or just the title?" << endl;
titleView();
}
else if (userinput == "2"){
}
else{
cout << "Please give a valid input:" << endl;
titleSort();
}
}

void titleFilter(){
cout << "Input:" << endl;
cout << "0 for A-Z" << endl;
cout << "1 for Z-A" << endl;
cout << "2 for no alphabetization" << endl;
titleSort();
}

void yearView(){
cout << "A = View all" << endl;
cout << "T = Just titles and years" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
yearView();
}
}


void yearSort(){
getline(cin, userinput);
if (userinput == "0"){
numberSort();
yearView();
}
else if(userinput == "1"){
numberSort();
yearView();
}
else if (userinput == "2"){
yearView();
}
else{
cout << "Please give a valid input:" << endl;
yearSort();
}
}

void yearFilter(){
cout << "Input:" << endl;
cout << "0 for oldest to newest" << endl;
cout << "1 for newest to oldest" << endl;
cout << "2 for no numerical sort" << endl;
yearSort();
}

void certificateView(){
cout << "A = View all" << endl;
cout << "T = Just titles and certificates" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
certificateView();
}
}


void certificateSort(){
getline(cin, userinput);
if (userinput == "0"){
certificateView();
}
else if(userinput == "1"){
certificateView();
}
else if (userinput == "2"){
certificateView();
}
else if(userinput == "3"){
certificateView();
}
else if(userinput == "4"){
certificateView();
}
else if (userinput == "5"){
certificateView();
}
else if(userinput == "6"){
certificateView();
}
else if(userinput == "7"){
certificateView();
}
else if (userinput == "8"){
certificateView();
}
else if(userinput == "9"){
certificateView();
}
else if(userinput == "a"){
certificateView();
}
else if (userinput == "b"){
certificateView();
}
else{
cout << "Please give a valid input:" << endl;
certificateView();
}
}

void certificateFilter(){
cout << "Input:" << endl;
cout << "0 for A film certification" << endl;
cout << "1 for U film certification" << endl;
cout << "2 for G film certification" << endl;
cout << "3 for R film certification" << endl;
cout << "4 for PG film certification" << endl;
cout << "5 for PG-13 film certification" << endl;
cout << "6 for UA and U/A film certification" << endl;
cout << "7 for TV-14 certification" << endl;
cout << "8 for TV-PG certification" << endl;
cout << "9 for TV-MA certification" << endl;
cout << "a for Passed certification" << endl;
cout << "b for Approved certification" << endl;
certificateSort();
}

void runtimeView(){
cout << "A = View all" << endl;
cout << "T = Just titles and runtimes" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
runtimeView();
}
}


void runtimeSort(){
getline(cin, userinput);
if (userinput == "0"){
numberSort();
runtimeView();
}
else if(userinput == "1"){
numberSort();
runtimeView();
}
else if (userinput == "2"){
runtimeView();
}
else{
cout << "Please give a valid input:" << endl;
runtimeView();
}
}

void runtimeFilter(){
cout << "Input:" << endl;
cout << "0 for shortest to longest" << endl;
cout << "1 for longest to shortest" << endl;
cout << "2 for no numerical sort" << endl;
runtimeSort();
}

void genreView(){
cout << "A = View all" << endl;
cout << "T = Just titles and genres" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
genreView();
}
}

void genreSort(){
getline(cin, userinput);
if (userinput == "0"){
alphabetSort();
genreView();
}
else if(userinput == "1"){
alphabetSort();
genreView();
}
else if (userinput == "2"){
genreView();
}
else{
cout << "Please give a valid input:" << endl;
genreSort();
}
}

void genreFilter(){
cout << "Input:" << endl;
cout << "0 for oldest to newest" << endl;
cout << "1 for newest to oldest" << endl;
cout << "2 for no numerical sort" << endl;
genreSort();
}

void imdbRatingView(){
cout << "A = View all" << endl;
cout << "T = Just titles and IMDB ratings" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
imdbRatingView();
}
}


void imdbRatingSort(){
getline(cin, userinput);
if (userinput == "0"){
numberSort();
imdbRatingView();
}
else if(userinput == "1"){
numberSort();
imdbRatingView();
}
else if (userinput == "2"){
imdbRatingView();
}
else{
cout << "Please give a valid input:" << endl;
imdbRatingSort();
}
}

void imdbRatingFilter(){
cout << "Input:" << endl;
cout << "0 for oldest to newest" << endl;
cout << "1 for newest to oldest" << endl;
cout << "2 for no numerical sort" << endl;
imdbRatingSort();
}

void overviewView(){
cout << "A = View all" << endl;
cout << "T = Just titles and overviews" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
overviewView();
}
}

void overviewSort(){ //Have to do query
overviewView();
}

void overviewFilter(){
cout << "Would you like to filter overviews that include all keywords or at least one keyword?" << endl;
cout << "a for all keywords" << endl;
cout << "o for at least one keyword" << endl;
getline(cin, userinput);
cout << "Input all desired keywords, each separated by a space and when finished press enter" << endl;
getline(cin, userinput);
overviewSort();
}

void metaScoreView(){
cout << "A = View all" << endl;
cout << "T = Just titles and meta scores" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
metaScoreView();
}
}

void metaScoreSort(){
getline(cin, userinput);
if (userinput == "0"){
numberSort();
metaScoreView();
}
else if(userinput == "1"){
numberSort();
metaScoreView();
}
else if (userinput == "2"){
metaScoreView();
}
else{
cout << "Please give a valid input:" << endl;
metaScoreSort();
}
}

void metaScoreFilter(){
cout << "Input:" << endl;
cout << "0 for lowest to highest" << endl;
cout << "1 for highest to lowest" << endl;
cout << "2 for no numerical sort" << endl;
metaScoreSort();
}

void directorView(){
cout << "A = View all" << endl;
cout << "T = Just titles and directors" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
directorView();
}
}


void directorSort(){
getline(cin, userinput);
if (userinput == "0"){
alphabetSort();
directorView();
}
else if(userinput == "1"){
alphabetSort();
directorView();
}
else if (userinput == "2"){
directorView();
}cout << "Input:" << endl;
cout << "0 for oldest to newest" << endl;
cout << "1 for newest to oldest" << endl;
cout << "2 for no numerical sort" << endl;
yearSort();
}
}
}

void directorFilter(){
cout << "Input:" << endl;
cout << "0 for A-Z" << endl;
cout << "1 for Z-A" << endl;
cout << "2 for no alphabetization" << endl;
directorSort();
}

void starsView(){
cout << "A = View all" << endl;
cout << "T = Just titles and stars" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
starsView();
}
}


void starsSort(){
getline(cin, userinput);
if (userinput == "0"){
alphabetSort();
starsView();
}
else if(userinput == "1"){
alphabetSort();
starsView();
}
else if (userinput == "2"){
starsView();
}
else{
cout << "Please give a valid input:" << endl;
starsSort();
}
}

void starsFilter(){
cout << "Input:" << endl;
cout << "0 for A-Z" << endl;
cout << "1 for Z-A" << endl;
cout << "2 for no alphabetization" << endl;
starsSort();
}

void noOfVotesView(){
cout << "A = View all" << endl;
cout << "T = Just titles and number of votes" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
noOfVotesView();
}
}


void noOfVotesSort(){
getline(cin, userinput);
if (userinput == "0"){
numberSort();
noOfVotesView();
}
else if(userinput == "1"){
numberSort();
noOfVotesView();
}
else if (userinput == "2"){
noOfVotesView();
}
else{
cout << "Please give a valid input:" << endl;
noOfVotesSort();
}
}

void noOfVotesFilter(){
cout << "Input:" << endl;
cout << "0 for lowest to highest" << endl;
cout << "1 for highest to lowest" << endl;
cout << "2 for no numerical sort" << endl;
noOfVotesSort();
}

void grossRevenueView(){
cout << "A = View all" << endl;
cout << "T = Just titles and gross revenues" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
grossRevenueView();
}
}


void grossRevenueSort(){
getline(cin, userinput);
if (userinput == "0"){
numberSort();
grossRevenueView();
}
else if(userinput == "1"){
numberSort();
grossRevenueView();
}
else if (userinput == "2"){
grossRevenueView();
}
else{
cout << "Please give a valid input:" << endl;
grossRevenueSort();
}
}

void grossRevenueFilter(){
cout << "Input:" << endl;
cout << "0 for lowest to highest" << endl;
cout << "1 for highest to lowest" << endl;
cout << "2 for no numerical sort" << endl;
grossRevenueSort();
}

void filter(){
cout << "Filter by inputting the respective character(s):" << endl;
cout << "T = Series_Title" << endl;
cout << "Y = Released_Year" << endl;
cout << "C = Certificate" << endl;
cout << "R = Runtime" << endl;
cout << "G = Genre" << endl;
cout << "I = IMDB_Rating" << endl;
cout << "O = Overview" << endl;
cout << "M = Meta_score" << endl;
cout << "D = Director" << endl;
cout << "S = Stars" << endl;
cout << "N = No_of_Votes" << endl;
cout << "GR = Gross Revenue" << endl;
cout << "B to go back" << endl;
string userinput;
getline(cin, userinput);
if(userinput == "T"){
titleFilter();
}
else if(userinput == "Y"){
yearFilter();
}
else if(userinput == "C"){
certificateFilter();
}
else if(userinput == "R"){
runtimeFilter();
}
else if(userinput == "G"){
genreFilter();
}
else if(userinput == "I"){
imdbRatingFilter();
}
else if(userinput == "O"){
overviewFilter();
}
else if(userinput == "M"){
metaScoreFilter();
}
else if(userinput == "D"){
directorFilter();
}
else if(userinput == "S"){
starsFilter();
}
else if(userinput == "N"){
noOfVotesFilter();
}
else if(userinput == "GR"){
grossRevenueFilter();
}
else if(userinput == "B"){
messageDisplayer();
}
else{
cout << "Please give a valid input" << endl;
filter();
}
}
*/
