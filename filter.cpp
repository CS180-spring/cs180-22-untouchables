#include "filter.hpp"

// constructor with member initializer list
// to set reference to db so db reference does
// not have to be passed to filter class every time
Filter::Filter(Database& db): db{db}{workingClt = nullptr;}

// filter constructor function to call display
// function, set working collection, and get user input
void Filter::filterMain(){
 
    string userInput = "";
    string selectedClt = "";

    displayMenu();
    
    // Stay in filter menu until user types exit
    while(userInput != "exit"){

        // check if working collection is selected
        if(workingClt == nullptr){
            userInput = selectCollection();
        }

        // check if user input from selectCollection() is exit 
        if(userInput == "exit"){
            break;
        }

        // get user for filter options
        getline(cin,userInput);
        
        // call filter functions based off of user input
        if(userInput == "filter" || userInput == to_string(1)){
            filterDisplay();

        }
        else if(userInput == "query" || userInput == to_string(2)){
            query();
        }
        else if(userInput == "sort" || userInput == to_string(3)){
            sortDisplay();
        }
        else if(userInput == "sort"){

        }
        else if(userInput == "collections"){
            db.dbAll();
            cout << ">>> ";
        }
        else if(userInput == "mainDB"){
            workingClt = db.rtnMainDB();
            displayMenu();
        }
        else if(userInput == "change"){
            userInput = selectCollection();
        }
        else if(userInput == "menu"){
            displayMenu();
        }
    }

    // set working collection to
    // nullptr when function exits
    workingClt = nullptr;
};

// simple function to display filter menu
void Filter::displayMenu(){
    
    int width = 5;
    system("clear");

        cout << "********************************************************************************************************\n";
        cout << "*                                      Movie Database                                                  *\n";
        cout << "********************************************************************************************************\n";
        cout << "*                                                                                                      *\n";
        cout << left << setw(width) << "*" << left << setw(40) << "1.filter" << left << setw(50) << "filter menu" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "2.query" << left << setw(50) << "query menu" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "3.sort" << left << setw(50) << "sort menu" << right << setw(9) << "*" << endl; //added this to import .csv/JSON files into specified collection
        cout << left << setw(width) << "*" << left << setw(40) << "4.collections" << left << setw(50) << "display available collections" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "5.mainDB" << left << setw(50) << "select main database" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "5.change" << left << setw(50) << "change collection" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "exit" << left << setw(50) << "return to database menu" << right << setw(9) << "*" << endl;
        cout << "*                                                                                                      *" << endl;
        cout << "********************************************************************************************************" << endl;
        cout << "Selected collection: ";
        // conditional statement to display
        // working collection if selected
        if(workingClt != nullptr){
            cout << workingClt->name << endl;
            cout << "Select option\n\n";
            cout << ">>> ";

        }    
}

// function gets working collection from
// user 
string Filter::selectCollection(){

    //string tmpName = cltName;
    string userInput = "";

    cout << "\nInput collection to work on:\n\n";
    cout << ">>> ";

    getline(cin,userInput);

    // continue to get user input until working
    // collection is selected or user exit
    while(!db.collectionExists(userInput)){ 
        
        // check if user wants 
        // to work on mainDB
        if(userInput == "mainDB"){
            workingClt = db.rtnMainDB();
            displayMenu();
            return userInput;
        }
        // check if user wants to 
        // display available collections
        else if(userInput == "collections"){
            db.dbAll();
            cout << ">>> ";

            getline(cin,userInput); 
        }
        // need to check if user wants to exit menu
        else if(userInput == "exit"){
            return userInput;
        }
        // collection does not exist prompt 
        // user to enter a working collection
        else{
            cout << "Collection does not exist\n";
            cout << "input collection to work on: \n\n";

            cout << ">>> ";
            
            getline(cin,userInput); 
        }
    }
    // set working collection
    if(db.collectionExists(userInput)){
        
        workingClt = db.getCollectionByName(userInput);

        displayMenu();
        return userInput;
    }
    // need to return something but may not be used
    return userInput;
}

//string to be searched, string you are searching for
bool Filter::isSubstring(const std::string& str1, const std::string& str2) {
    size_t found = str1.find(str2);
    return (found != std::string::npos);
}


//HUGE DEPENDENCY, THE NEW COLLECTION MADE HERE IS MADE OF POINTERS, WHICH MEANS IF YOU DELETE STUFF FROM THE ORIGINAL COLLECTION AND TRY TO VIEW THE QUERIED COLLECTION,
//A SEGFAULT OCCURS, DON'T KNOW HOW TO FIX THIS PLS HELP, TODO
void Filter::query() {
    string user_input;
    string newName;
    cout << "What phrase would you like to search for?" << endl;
    getline(cin, user_input);
    cout << "What would you like the new queried collection to be called?" << endl;
    getline(cin, newName);
    vector <Movie_Document*> pings;
    //quite literally checks if the phrase is in any of the important string fields, if it is then movie doc pointer gets added to new collection
    for (int i = 0; i < workingClt->movieDocs.size(); i++) {
        if (isSubstring(workingClt->movieDocs[i]->Director, user_input))
            pings.push_back(workingClt->movieDocs[i]);
        else if (isSubstring(workingClt->movieDocs[i]->overview, user_input))
            pings.push_back(workingClt->movieDocs[i]);
        else if (isSubstring(workingClt->movieDocs[i]->series_title, user_input))
            pings.push_back(workingClt->movieDocs[i]);
        else if (isSubstring(workingClt->movieDocs[i]->genre, user_input))
            pings.push_back(workingClt->movieDocs[i]);
        else if (isSubstring(workingClt->movieDocs[i]->Star1, user_input))
            pings.push_back(workingClt->movieDocs[i]);
        else if (isSubstring(workingClt->movieDocs[i]->Star2, user_input))
            pings.push_back(workingClt->movieDocs[i]);
        else if (isSubstring(workingClt->movieDocs[i]->Star3, user_input))
            pings.push_back(workingClt->movieDocs[i]);
        else if (isSubstring(workingClt->movieDocs[i]->Star4, user_input))
            pings.push_back(workingClt->movieDocs[i]);
    }
    if (pings.size() > 0) {
        db.addFltCollection(newName, pings);
    }
    else {
        cout << "No matches found, queried collection could not be created" << endl;
    }
}

///////FILTER FUNCTIONS////////////
// fuction displays filter menu and gets user input
// and will call specific function specific to user input
void Filter::filterDisplay(){
    
    int width = 5;
    string userInput = "";
    
    while(userInput != "exit"){
        system("clear");

        cout << "********************************************************************************************************\n";
        cout << "*                                            Filter Menu                                               *\n";
        cout << "********************************************************************************************************\n";
        cout << "*                                                                                                      *\n";
        cout << left << setw(width) << "*" << left << setw(40) << "1.title" << left << setw(50) << "by title" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "2.release year" << left << setw(50) << "by release year" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "3.rated" << left << setw(50) << "by rating" << right << setw(9) << "*" << endl; //added this to import .csv/JSON files into specified collection
        cout << left << setw(width) << "*" << left << setw(40) << "4.runtime" << left << setw(50) << "by runtime" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "5.genre" << left << setw(50) << "by genre" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "6.IMDB rating" << left << setw(50) << "by IMDB rating" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "7.meta score" << left << setw(50) << "by meta score" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "8.director" << left << setw(50) << "by director" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "9.starring" << left << setw(50) << "by actor/actress" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "10.number of votes" << left << setw(50) << "by number of votes" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "11.Gross" << left << setw(50) << "by gross earnings" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "12.multiple filters" << left << setw(50) << "apply multiple filters" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "exit" << left << setw(50) << "exit filter menu" << right << setw(9) << "*" << endl;
        cout << "*                                                                                                      *" << endl;
        cout << "********************************************************************************************************" << endl;
        cout << "Selected collection: ";
        if(workingClt != nullptr){cout << workingClt->name << endl;}
        cout << endl;
        cout << ">>> ";

        getline(cin,userInput);
        string counter;
        if(userInput == "1" || userInput == "title"){            
            featureFilter("title");
        }
        else if(userInput == "2" || userInput == "release year"){
        
        }
        else if(userInput == "3" || userInput == "rated"){
            featureFilter("rated");                    
        }
        else if(userInput == "4" || userInput == "runtime"){
          
        }
        else if(userInput == "5" || userInput == "genre"){
            featureFilter("genre");
        }
        else if(userInput == "6" || userInput == "IMDB rating"){
          
        }
        else if(userInput == "7" || userInput == "meta score"){
         
        }
        else if(userInput == "8" || userInput == "director"){
            featureFilter("director");
        }
        else if(userInput == "9" || userInput == "starring"){
            featureFilter("star");
        }
        else if(userInput == "10" || userInput == "number of votes"){
            
        }
        else if(userInput == "11" || userInput == "gross revenue"){
        
        }
        else if(userInput == "12" || userInput == "multiple filters"){

        }
        else if(userInput == "exit"){
            displayMenu();

        }
       else{
            filterDisplay();
       }
    }
}

void multipleFilters(vector<string> fltNames){


}

// Filters movies by feature and pushes to temp vector
// user has option to display, create new collection, or export
void Filter::featureFilter(string fltFeature){

    string userInput;

    vector<Movie_Document*> copyVec = copyMovieDocs(workingClt->name);
    vector<Movie_Document*> sortedVec;
    //Series_Title,Rated,Genre,Director,Star

    if(fltFeature == "title"){
        cout << "Enter title: \n\n";
        cout << ">>> ";

        getline(cin, userInput);

        for(auto i : copyVec){
            if(i->series_title.find(userInput) != string::npos){
                sortedVec.push_back(i);
            }
        }
    }
    else if(fltFeature == "rated"){
        cout << "Movie ratings are: 16, A, Approved, G, GP, Passed, PG, PG-13, R, TV-14, TV-MA, TV-PG, U, U/A, UA, Unrated\n";
        cout << "Enter rating: \n\n";
        cout << ">>> ";

        getline(cin, userInput);

        for(auto i : copyVec){
            if(i->certificate.find(userInput) != string::npos){
                sortedVec.push_back(i);
            }
        }
    }
    else if(fltFeature == "genre"){
        cout << "Enter genre: \n\n";
        cout << ">>> ";

        getline(cin, userInput);

        for(auto i : copyVec){
            if(i->genre.find(userInput) != string::npos){
                sortedVec.push_back(i);
            }
        }
    }
    else if(fltFeature == "director"){
        cout << "Enter director: \n\n";
        cout << ">>> ";

        getline(cin, userInput);

        for(auto i : copyVec){
            if(i->Director.find(userInput) != string::npos){
                sortedVec.push_back(i);
            }
        }
    }
    else if(fltFeature == "star"){
        cout << "Enter star name: \n\n";
        cout << ">>> ";

        getline(cin, userInput);

        for(auto i : copyVec){
            if((i->Star1.find(userInput) != string::npos) || (i->Star2.find(userInput) != string::npos) 
                || (i->Star3.find(userInput) != string::npos) || (i->Star4.find(userInput) != string::npos)){
                sortedVec.push_back(i);
            }
        }
    }
    if(!sortedVec.empty()){
        cout << "Found " << sortedVec.size() << " result(s)\n";
        cout << "Press any key to continue\n\n";
        cout << ">>> ";
        cin.get();
        fltSortResults(sortedVec);

    }
    else if(sortedVec.empty()){
        cout << "Found 0 results\n";
        cout << "Press any key to continue\n\n";
        cout << ">>> ";
        cin.get();
    }
}

// Menu to implement displaying, creating new 
// collection, or exporting from filter/sorted data
void Filter::fltSortResults(vector<Movie_Document*> fsData){

    int width = 5;
    string userInput = "";

    if(!fsData.empty()){
        
        system("clear");

        cout << "********************************************************************************************************\n";
        cout << "*                                            Results Menu                                              *\n";
        cout << "********************************************************************************************************\n";
        cout << "*                                                                                                      *\n";
        cout << left << setw(width) << "*" << left << setw(40) << "1.display" << left << setw(50) << "print results" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "4.create" << left << setw(50) << "create new collection" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "5.export" << left << setw(50) << "export movie data" << right << setw(9) << "*" << endl;
        cout << "*                                                                                                      *" << endl;
        cout << "********************************************************************************************************" << endl;
        cout << "Selected collection: ";
        if(workingClt != nullptr){cout << workingClt->name << endl;}
        cout << endl;
        cout << ">>> ";

        getline(cin, userInput);

        if(userInput == "1" || userInput == "Display"){

            printData(fsData);
        }
        else if(userInput == "3" || userInput == "create"){
            cout << "name of new collection: \n\n";
            cout << ">>> ";

            getline(cin,userInput);

            db.addFltCollection(userInput, fsData);
            cout << "new collection " << userInput << " added to database\n";
            cout << "hit enter to continue\n\n";
            cout << ">>> ";
            cin.get();
        }
        else if(userInput == "5" || userInput == "export"){
            cout << "name of file: \n\n";
            cout << ">>> ";
            getline(cin, userInput);

            db.fltExportCSV(fsData, userInput);
            cout << "hit enter to continue\n";
            cin.get();
            //need to change up export to take new parameters
        }
    }
  
}

/// SORTING FUNCTIONS ///
void Filter::sortDisplay(){
    
    int width = 5;
    
    string feature = "";
    string order = "";
    string userInput = "";

    while(userInput != "exit"){
        system("clear");

        cout << "********************************************************************************************************\n";
        cout << "*                                            Sort Menu                                                 *\n";
        cout << "********************************************************************************************************\n";
        cout << "*                                                                                                      *\n";
        cout << left << setw(width) << "*" << left << setw(40) << "1.title" << left << setw(50) << "by title" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "2.date" << left << setw(50) << "by release year" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "3.rated" << left << setw(50) << "by rating" << right << setw(9) << "*" << endl; //added this to import .csv/JSON files into specified collection
        cout << left << setw(width) << "*" << left << setw(40) << "4.runtime" << left << setw(50) << "by runtime" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "5.genre" << left << setw(50) << "by genre" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "6.rating" << left << setw(50) << "by IMDB rating" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "7.meta" << left << setw(50) << "by meta score" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "8.director" << left << setw(50) << "by director" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "9.star" << left << setw(50) << "by actor/actress" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "10.votes" << left << setw(50) << "by number of votes" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "11.gross" << left << setw(50) << "by gross earnings" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "exit" << left << setw(50) << "exit sort menu" << right << setw(9) << "*" << endl;
        cout << "*                                                                                                      *" << endl;
        cout << "********************************************************************************************************" << endl;
        cout << "Selected collection: ";
        if(workingClt != nullptr){cout << workingClt->name << endl;}
        cout << endl;
        cout << "Enter feature to sort by:\n\n";
        cout << ">>> ";

        getline(cin, userInput);
        
        if(userInput != "exit"){
           
           feature = userInput;

            cout << "Enter 0 to sort ascending:\n";
            cout << "Enter 1 to sort descending:\n\n";
            cout << ">>> ";

            getline(cin, order);

            sorter(feature, order); 
        }
        else if(userInput == "exit"){
            displayMenu();
        }
    }    
}

// sorts by series title right now 
void Filter::sorter(string feature, string order){

    // gets movie data copied over
    vector<Movie_Document*> copyVec = copyMovieDocs(workingClt->name); // can change this to a passed string variable passed to alphasort()
   
    if(feature == "1" || feature == "title"){
        titleSort(copyVec, order);
    }
    else if(feature == "2" || feature == "date"){
        releaseDateSort(copyVec, order);
    }
    else if(feature == "3" || feature == "rated"){
        ratedSort(copyVec, order);
    }
    else if(feature == "4" || feature == "runtime"){
        runtimeSort(copyVec, order);
    }
    else if(feature == "5" || feature == "genre"){
        genreSort(copyVec, order);
    }
    else if(feature == "6" || feature == "rating"){
        ratingSort(copyVec, order);
    }
    else if(feature == "7" || feature == "meta"){
        metaScoreSort(copyVec, order);
    }
    else if(feature == "8" || feature == "director"){
        directorSort(copyVec, order);
    }
    else if(feature == "9" || feature == "star"){
        starSort(copyVec, order);
    }
    else if(feature == "10" || feature == "votes"){
        numVotesSort(copyVec, order);
    }
    else if(feature == "11" || feature == "gross"){
        grossEarningsSort(copyVec, order);
    }
}

void Filter::titleSort(vector<Movie_Document*> copyVec, string order){
    
    int size = copyVec.size();
    bool isUnsorted;

     if(order == "0"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->series_title > copyVec[i + 1]->series_title) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->series_title > copyVec[i + 1]->series_title) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    else if(order == "1"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->series_title < copyVec[i + 1]->series_title) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->series_title < copyVec[i + 1]->series_title) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    cout << "Sorting complete hit enter\n\n";
    cout << ">>> ";
    cin.get();
    fltSortResults(copyVec);
}

void Filter::releaseDateSort(vector<Movie_Document*> copyVec, string order){

    int size = copyVec.size();
    bool isUnsorted;

     if(order == "0"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->released_year > copyVec[i + 1]->released_year) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->released_year > copyVec[i + 1]->released_year) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    else if(order == "1"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->released_year < copyVec[i + 1]->released_year) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->released_year < copyVec[i + 1]->released_year) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    cout << "Sorting complete hit enter\n\n";    
    cout << ">>> ";
    cin.get();
    fltSortResults(copyVec);
}
void Filter::ratedSort(vector<Movie_Document*> copyVec, string order){
    int size = copyVec.size();
    bool isUnsorted;

     if(order == "0"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->certificate > copyVec[i + 1]->certificate) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->certificate > copyVec[i + 1]->certificate) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    else if(order == "1"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->certificate < copyVec[i + 1]->certificate) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->certificate < copyVec[i + 1]->certificate) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    cout << "Sorting complete hit enter\n\n";
    cout << ">>> ";
    cin.get();
    fltSortResults(copyVec);
}

void Filter::runtimeSort(vector<Movie_Document*> copyVec, string order){

    int size = copyVec.size();
    bool isUnsorted;

     if(order == "0"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->runtime > copyVec[i + 1]->runtime) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->runtime > copyVec[i + 1]->runtime) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    else if(order == "1"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->runtime < copyVec[i + 1]->runtime) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->runtime < copyVec[i + 1]->runtime) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    cout << "Sorting complete hit enter\n\n";
    cout << ">>> ";
    cin.get();
    fltSortResults(copyVec);
}

void Filter::genreSort(vector<Movie_Document*> copyVec, string order){

    int size = copyVec.size();
    bool isUnsorted;

     if(order == "0"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->genre > copyVec[i + 1]->genre) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->genre > copyVec[i + 1]->genre) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    else if(order == "1"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->genre < copyVec[i + 1]->genre) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->genre < copyVec[i + 1]->genre) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    cout << "Sorting complete hit enter\n\n";
    cout << ">>> ";
    cin.get();
    fltSortResults(copyVec);
}

void Filter::ratingSort(vector<Movie_Document*> copyVec, string order){

    int size = copyVec.size();
    bool isUnsorted;

     if(order == "0"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->IMDB_rating > copyVec[i + 1]->IMDB_rating) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->IMDB_rating > copyVec[i + 1]->IMDB_rating) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    else if(order == "1"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->IMDB_rating < copyVec[i + 1]->IMDB_rating) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->IMDB_rating < copyVec[i + 1]->IMDB_rating) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    cout << "Sorting complete hit enter\n\n";
    cout << ">>> ";
    cin.get();
    fltSortResults(copyVec);
}
void Filter::metaScoreSort(vector<Movie_Document*> copyVec, string order){

    int size = copyVec.size();
    bool isUnsorted;

     if(order == "0"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->meta_score > copyVec[i + 1]->meta_score) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->meta_score > copyVec[i + 1]->meta_score) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    else if(order == "1"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->meta_score < copyVec[i + 1]->meta_score) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->meta_score < copyVec[i + 1]->meta_score) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    cout << "Sorting complete hit enter\n\n";
    cout << ">>> ";
    cin.get();
    fltSortResults(copyVec);
}
void Filter::directorSort(vector<Movie_Document*> copyVec, string order){

    int size = copyVec.size();
    bool isUnsorted;

     if(order == "0"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->Director > copyVec[i + 1]->Director) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->Director > copyVec[i + 1]->Director) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    else if(order == "1"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->Director < copyVec[i + 1]->Director) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->Director < copyVec[i + 1]->Director) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    cout << "Sorting complete hit enter\n\n";
    cout << ">>> ";
    cin.get();
    fltSortResults(copyVec);
}

void Filter::starSort(vector<Movie_Document*> copyVec, string order){

    int size = copyVec.size();
    bool isUnsorted;

     if(order == "0"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->Star1 > copyVec[i + 1]->Star1) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->Star1 > copyVec[i + 1]->Star1) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    else if(order == "1"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->Star1 < copyVec[i + 1]->Star1) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->Star1 < copyVec[i + 1]->Star1) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    cout << "Sorting complete hit enter\n\n";
    cout << ">>> ";
    cin.get();
    fltSortResults(copyVec);
}

void Filter::numVotesSort(vector<Movie_Document*> copyVec, string order){

    int size = copyVec.size();
    bool isUnsorted;

     if(order == "0"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->numVotes > copyVec[i + 1]->numVotes) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->numVotes > copyVec[i + 1]->numVotes) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    else if(order == "1"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->numVotes < copyVec[i + 1]->numVotes) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->numVotes < copyVec[i + 1]->numVotes) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    cout << "Sorting complete hit enter\n\n";
    cout << ">>> ";
    cin.get();
    fltSortResults(copyVec);
}
void Filter::grossEarningsSort(vector<Movie_Document*> copyVec, string order){

    int size = copyVec.size();
    bool isUnsorted;

     if(order == "0"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->gross > copyVec[i + 1]->gross) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->gross > copyVec[i + 1]->gross) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    else if(order == "1"){
        do {
            isUnsorted = false;
            for (int i = 0; i < (size - 1); i++) {
                if (copyVec[i]->gross < copyVec[i + 1]->gross) {
                    isUnsorted = true;
                    for (; i < (size - 1); i++) {
                        if (copyVec[i]->gross < copyVec[i + 1]->gross) {
                            swap(copyVec[i], copyVec[i + 1]);
                        }
                    }
                }
            }
        } while (isUnsorted);
    }
    cout << "Sorting complete hit enter\n\n";
    cout << ">>> ";
    cin.get();
    fltSortResults(copyVec);
}

// Simple function to print movie data in 5 document increments
void Filter::printData(vector<Movie_Document*> movieData){

    string userInput = "";

    for(int i = 0; i < movieData.size(); i++){
        cout << "series-title: " << movieData[i]->series_title << endl;
        cout << "released-year: " << movieData[i]->released_year << endl;
        cout << "certificate: " << movieData[i]->certificate << endl;
        cout << "runtime: " << movieData[i]->runtime << endl;
        cout << "genre: " << movieData[i]->genre<< endl;
        cout << "IMDB-rating: " << movieData[i]->IMDB_rating << endl;
        cout << "overview: " << movieData[i]->overview << endl;
        cout << "meta-score: " << movieData[i]->meta_score << endl;
        cout << "director: " << movieData[i]->Director << endl;
        cout << "Stars: " << movieData[i]->Star1 << ", " << movieData[i]->Star2 << ", " << movieData[i]->Star3 << ", " << movieData[i]->Star4 << endl;
        cout << "number-votes: " << movieData[i]->numVotes << endl;
        cout << "gross: " << movieData[i]->gross << endl << endl;

        if((i % 4) == 0 && (i != 0)){
            cout << "hit enter to display next 5 results\n";
            cout << "exit to exit any time\n";
            getline(cin, userInput);
            if(userInput == "exit"){
                break;
            }
        }

    }
        
}

vector<Movie_Document*> Filter::copyMovieDocs(string cltName){
    
    // use db function to get collection by name
    // pointer to collection is returned
    collection* clt = db.getCollectionByName(cltName);

    // set variable to size of vector to be copied
    int size = clt->movieDocs.size();

    // vector to hold copied movie data
    vector<Movie_Document*> copyVec(size);

    // copy takes beginning iterator, end iterator, and beginning iterator of new vector to copy to
    copy(clt->movieDocs.begin(),clt->movieDocs.begin() + size, copyVec.begin());

    return copyVec;
}