#include "database.hpp"
//#include "filter.cpp"

Database::Database(){
    collection* defaultClt = new collection;
    defaultClt->name = "default";
    collectionDB.push_back(defaultClt);
    currentClt = defaultClt;
}

collection* Database::getCollectionByName(string name){

    for(int i = 0; i < collectionDB.size(); i++){
        if(collectionDB[i]->name == name){
            
            return collectionDB[i];
        }
    }

    return nullptr;
};

//simple function to get the List of DataBase names
vector<string>  Database::getCollectionsList(){
    vector<string>cltNameList;

    for (int i = 0; i < collectionDB.size(); ++i){
        cltNameList.push_back(collectionDB[i]->name);
    }
    return cltNameList;
}

 //display all available databases
void Database::dbAll(){
    if (collectionDB.size() == 0){
        cout << "no available collections.";
    } 
    else{
        cout << "all available collections include: ";

        for(auto i : getCollectionsList()){
            cout << i << " ";
        }
        cout << endl;
    }
}

// add collection to collectionDB
void Database::addCollection(string cltName){
    collection* Clt = new collection;

    Clt->name = cltName;
    collectionDB.push_back(Clt);

    cout << "New Collection \'"<< Clt->name << "\' added to database.\n";
}

// update currentClt ptr to passed parameter
// and use for reference in other functions
void Database::useCollection(string cltName){

    this->currentClt = getCollectionByName(cltName);
    
    cout << "Switched to " << this->currentClt->name << " collection.\n";
}

// use private collection* currentClt to print current collection
void Database::printCurrentClt(){
    cout << "current collection is: " << currentClt->name << "\n";
}

string Database::printCurrentClt_name(){
    return currentClt->name;
}

// delete collection by name and check if not current collection
// function will call deleteAllDocs to clean up memory allocation
// then it will delete memory allocated for collection and return bool
bool Database::deleteCollectionByName(string cltName){

    collection* clt = getCollectionByName(cltName);

    if(clt->name == currentClt->name){
        return false;
    }
    else{
    deleteAllDocs(cltName);
    
    delete clt;

    cout << "Collection " << cltName << " deleted.\n";
    
    return true;
    
    }
}

void Database::deleteAllDocs(string cltName){

    collection* clt = getCollectionByName(cltName);

    for(auto i : clt->movieDocs){
        
        delete i;
    
    }

    cout << "All documents from " << cltName << "deleted.\n";
}

/*
collection* Database::useCollection(string cltName){
    
    return getCollectionByName(cltName);
}
*/
            

void Database::importCSV(string cltName, string fname){
    
    int badcnt = 0;
    //temp variables to hold data for parsing
    int inQoute = 0;
    string tmpStr = "";

    collection* collection = getCollectionByName(cltName);
    
    //define your file name
    string file_name = fname; //"imdb_top_1000.csv";

    //attach an input stream to the wanted file
    ifstream input_File(file_name);

    //check stream status
    if (!input_File){printf("Can't open input file!");}

    // file contents
    vector<string> tmpData;

    // one line
    string iString = "";
    string line = "";

    //burn header file line in csv document
    getline(input_File, iString);

    //get entire line of csv file with getline
    //increment through entire file with while loop
    while(getline(input_File, iString)){
        //create movie_document via new and assign to movie_document pointer
        Movie_Document* tmpDoc = new Movie_Document();
        
        //send current 
        stringstream sstream(iString);

        //check if end of file is reached
        while(!sstream.eof()){

            //handle quotes
            if(sstream.peek() == '\"'){
                getline(sstream, line, '\"');
                getline(sstream, line, '\"');
                if(sstream.peek() == '\"'){
                    string tmp = "";
                    tmp = sstream.get();
                    line = line + tmp;
                    getline(sstream, tmpStr, '\"');
                    
                    tmp = sstream.get();

                    line = line + tmpStr + tmp;
                    
                    getline(sstream, tmpStr,'\"');
                    line = line + tmpStr;
                }
                //push quoted data
                //cout << line << endl;
                tmpData.push_back(line);
                getline(sstream, line, ',');
            }
            else{     
                //check if end of line is reached
                if(sstream.rdbuf()->in_avail() == 0){
                    break;
                }
                //get line up to ','
                getline(sstream, line,',');
                if(line.empty()){
                    line = "N/A";
                }
                //push data to temp vector container
                //cout << line << endl;
                tmpData.push_back(line);
            }  
            
        }   

        //assign parsed data to newly created movie_document
        //parsed data was put into vector and is now being assigned
        //to data members of movie_document object
        tmpDoc->poster_Link = tmpData[0];
        tmpDoc->series_title = tmpData[1];
        
        if(tmpData[2] != "N/A"){
            tmpDoc->released_year = stoi(tmpData[2]);}
        else{tmpDoc->released_year = -1;}
        
        tmpDoc->certificate = tmpData[3];

        if(tmpData[4] != "N/A"){
            tmpDoc->runtime = stoi(tmpData[4]);}
        else{tmpDoc->runtime = -1;}
        
        tmpDoc->genre = tmpData[5];
        
        if(tmpData[6] != "N/A"){
            tmpDoc->IMDB_rating = stod(tmpData[6]);}
        else{tmpDoc->IMDB_rating = -1;}
      
        tmpDoc->overview = tmpData[7];

        if(tmpData[8] != "N/A"){
            tmpDoc->meta_score = stoi(tmpData[8]);}
        else{tmpDoc->meta_score = -1;};

        tmpDoc->Director = tmpData[9];
        tmpDoc->Star1 = tmpData[10];
        tmpDoc->Star2 = tmpData[11];
        tmpDoc->Star3 = tmpData[12];
        tmpDoc->Star4 = tmpData[13];
        
        if(tmpData[14] != "N/A"){
            tmpDoc->numVotes = stoi(tmpData[14]);}
        else{tmpDoc->numVotes = -1;};
        
        if(tmpData[15] != "N/A"){
            tmpDoc->gross = stoi(tmpData[15]);}
        else{tmpDoc->gross = -1;};

        //push new movie document to current database object
        //the entire database is pushed to the referenced db
        //movie documents are stored in "vector<Movie_Documents*> movieDocs"
        //can access data elements through pointer -> 
        collection->movieDocs.push_back(tmpDoc);

        //clear tmp vector for more data
        tmpData.clear();
    }

    cout << ".csv data import successful\n";
}

void Database::printSingleClt(string cltName){
    collection* tmpClt = getCollectionByName(cltName);
    if (tmpClt == nullptr){
        cout << "Collection not found.\n";
    }else{
        vector<Movie_Document*> tmpDocs = tmpClt->getMovieDocs();
        if(tmpDocs.empty()){
            cout << "Collection has a empty document.\n";
        }else{  
            string temp_input;    
            int impl = 0;
            /*
            int higher_bound = 0;
            if (5 + impl*5 > tmpDocs.size()){
                higher_bound = 5 + impl*5;
            }else{
                higher_bound = tmpDocs.size();
            }*/
            for (int i = 0 + impl*5; i < 5 + impl*5; ++i){
                Movie_Document* curr = tmpDocs[i];
                if(curr != nullptr){
                    printf("Document %d\n",i);
                    cout << "poster-link: " << curr->poster_Link << endl;
                    cout << "series-title: " << curr->series_title << endl;
                    cout << "released-year: " << curr->released_year << endl;
                    cout << "certificate: " << curr->certificate << endl;
                    cout << "runtime: " << curr->runtime << endl;
                    cout << "genre: " << curr->genre<< endl;
                    cout << "IMDB-rating: " << curr->IMDB_rating << endl;
                    cout << "overview: " << curr->overview << endl;
                    cout << "meta-score: " << curr->meta_score << endl;
                    cout << "director: " << curr->Director << endl;
                    cout << "Stars: " << curr->Star1 << ", " << curr->Star2 << ", " << curr->Star3 << ", " << curr->Star4 << endl;
                    cout << "number-votes: " << curr->numVotes << endl;
                    cout << "gross: " << curr->gross << endl << endl;
                }
            }
            cout << "type \"next\" to view next 5 movie documents, type \"previous\" to view the previous 5 movie documents" << endl;
            cout << "type \"exit\" to return to main manual" << endl;
            while(temp_input != "exit"){
                cout << ">>> ";
                getline(cin,temp_input);
                if (temp_input == "next"){
                    cout << "===================================================================================" << endl;
                    impl = impl + 1;
                    if(tmpDocs[0+impl*5] == nullptr){
                        cout << "you are already at the end of the documents" << endl;
                    }else{
                        for (int i = 0 + impl*5; i < 5 + impl*5; ++i){
                            Movie_Document* curr = tmpDocs[i];
                            if(curr != nullptr){
                                printf("Document %d\n",i);
                                cout << "poster-link: " << curr->poster_Link << endl;
                                cout << "series-title: " << curr->series_title << endl;
                                cout << "released-year: " << curr->released_year << endl;
                                cout << "certificate: " << curr->certificate << endl;
                                cout << "runtime: " << curr->runtime << endl;
                                cout << "genre: " << curr->genre<< endl;
                                cout << "IMDB-rating: " << curr->IMDB_rating << endl;
                                cout << "overview: " << curr->overview << endl;
                                cout << "meta-score: " << curr->meta_score << endl;
                                cout << "director: " << curr->Director << endl;
                                cout << "Stars: " << curr->Star1 << ", " << curr->Star2 << ", " << curr->Star3 << ", " << curr->Star4 << endl;
                                cout << "number-votes: " << curr->numVotes << endl;
                                cout << "gross: " << curr->gross << endl << endl;
                            }
                        }
                    }
                } else if (temp_input == "previous"){
                    if (impl == 0){
                        cout << "you are already at the start of the documents" << endl;
                    }else{
                        cout << "===================================================================================" << endl;
                        impl = impl - 1;
                        for (int i = 0 + impl*5; i < 5 + impl*5; ++i){
                            Movie_Document* curr = tmpDocs[i];
                            if(curr != nullptr){
                                printf("Document %d\n",i);
                                cout << "poster-link: " << curr->poster_Link << endl;
                                cout << "series-title: " << curr->series_title << endl;
                                cout << "released-year: " << curr->released_year << endl;
                                cout << "certificate: " << curr->certificate << endl;
                                cout << "runtime: " << curr->runtime << endl;
                                cout << "genre: " << curr->genre<< endl;
                                cout << "IMDB-rating: " << curr->IMDB_rating << endl;
                                cout << "overview: " << curr->overview << endl;
                                cout << "meta-score: " << curr->meta_score << endl;
                                cout << "director: " << curr->Director << endl;
                                cout << "Stars: " << curr->Star1 << ", " << curr->Star2 << ", " << curr->Star3 << ", " << curr->Star4 << endl;
                                cout << "number-votes: " << curr->numVotes << endl;
                                cout << "gross: " << curr->gross << endl << endl;
                            }
                        }
                    }
                }
            }
            cout << "you have successfully exit the movie document viewer" << endl;
            cout << ">>> ";cout << "size of current data base is: " << tmpClt->movieDocs.size() << endl;
        }
    }
}

//NEEDS INPUT VALIDATION, TODO
void Database::addDocumentManually(collection* current) {
    Movie_Document* addMe = new Movie_Document();
    string user_input;
    cout << "Input the series title: " << endl;
    getline(cin,addMe->series_title);
    cout << "Input the release year: " << endl;
    cin >> addMe->released_year;
    cout << "Input the runtime (int): " << endl;
    cin >> addMe->runtime;
    cout << "Input the genre: " << endl; 
    cin.ignore();
    getline(cin, addMe->genre);
    cout << "Input the IMDB_rating (double): " << endl;
    cin >> addMe->IMDB_rating;
    cout << "Input the description: " << endl;
    cin.ignore();
    getline(cin, addMe->overview);
    cout << "Input the meta_score: " << endl;
    cin >> addMe->meta_score;
    cout << "Input the Director's name: " << endl;
    cin.ignore();
    getline(cin, addMe->Director);
    cout << "Input the star: " << endl; //also this is just the wrong format, TODO
    cin >> addMe->Star1;
    current->movieDocs.push_back(addMe);
    cout << "Movie added successfully" << endl;
}



/*
void add_movie_to_database(const string& filename, DataBase& database) {
  // Load the JSON file
  ifstream input(filename);
  json json_data;
  input >> json_data;

  // Extract the fields from the JSON object
  string posterLink = json_data["Poster Link"];
  string seriesTitle = json_data["Series Title"];
  int releasedYear = json_data["Release Year"];
  string certificate = json_data["Certificate"];
  int runtime = json_data["Runtime"];
  string genre = json_data["Genre"];
  double imdbRating = json_data["IMDB_Rating"];
  string overview = json_data["Overview"];
  int metaScore = json_data["Meta_score"];
  string director = json_data["Director"];
  string star1 = json_data["Star1"];
  string star2 = json_data["Star2"];
  string star3 = json_data["Star3"];
  string star4 = json_data["Star4"];
  int numVotes = json_data["No_of_Votes"];
  int gross = json_data["Gross"];

  // Create a new Movie_Document object
  Movie_Document new_movie = {
    posterLink,
    seriesTitle,
    releasedYear,
    certificate,
    runtime,
    genre,
    imdbRating,
    overview,
    metaScore,
    director,
    star1,
    star2,
    star3,
    star4,
    numVotes,
    gross
  };

  // Add the new Movie_Document to the database
  database.storedDocuments.push_back(new_movie);
  database.movieDocs.push_back(&database.storedDocuments.back());
} 


void deleteDocumentManually(DataBase& current){
    cout << "input the name of the movie to be removed" << endl;
    string user_input;
    getline(cin, user_input);
    //if the Document exists in the storedDocument array
    for (auto i = current.storedDocuments.begin(); i != current.storedDocuments.end(); ++i) {
        if (i->series_title == user_input) {
            current.storedDocuments.erase(i);
            cout << "Document " << user_input << " has been successfully deleted." << endl;
            return;
        }
    }
    //if the Document does not exist
    cout << "Document does not exist in the current Database" << endl;
}

void displayMovieDocument(const DataBase& database, unsigned int index) {
    if (index < 0 || index >= database.storedDocuments.size()) {
        cout << "Invalid index\n";
        return;
    }
    const Movie_Document& doc = database.storedDocuments[index];
    cout << "Series Title: " << doc.series_title << "\n";
    cout << "Released Year: " << doc.released_year << "\n";
    cout << "Runtime (in minutes): " << doc.runtime << "\n";
    cout << "Genre: " << doc.genre << "\n";
    cout << "IMDB Rating: " << doc.IMDB_rating << "\n";
    cout << "Overview: " << doc.overview << "\n";
    cout << "Meta Score: " << doc.meta_score << "\n";
    cout << "Director: " << doc.Director << "\n";
    cout << "Star: " << doc.Star1 << "\n";
}



*/
/*
void Database::updateEntry(string cltName){
    int cnt = 0;
    collection* collection = getCollectionByName(cltName);
    cout << "Please enter name of movie you want to update" << endl;
    string user_input;
    getline(cin, user_input);
    bool flag = true;
    for(auto i : ){
        if (i. == user_input) {
            flag = false;
            printf("Document %d\n",cnt);
            cout << "poster-link: " << i->poster_Link << endl;
            cout << "series-title: " << i->series_title << endl;
            cout << "released-year: " << i->released_year << endl;
            cout << "certificate: " << i->certificate << endl;
            cout << "runtime: " << i->runtime << endl;
            cout << "genre: " << i->genre<< endl;
            cout << "IMDB-rating: " << i->IMDB_rating << endl;
            cout << "overview: " << i->overview << endl;
            cout << "meta-score: " << i->meta_score << endl;
            cout << "director: " << i->Director << endl;
            cout << "Stars: " << i->Star1 << ", " << i->Star2 << ", " << i->Star3 << ", " << i->Star4 << endl;
            cout << "number-votes: " << i->numVotes << endl;
            cout << "gross: " << i->gross << endl << endl;
            cout << "What value would you like to modify? Type in the name (ex. series-title)" << endl;
            getline(cin, user_input);
            bool flag1 = false; //use this to check if entry has been modified correctly
            if (user_input == "poster-link") {
                cout << "What would you like to change it to?" << endl;
                getline(cin, user_input);
                i->poster_Link = user_input;
                flag1 = true;
            }
            else if (user_input == "series-title") {
                cout << "What would you like to change it to?" << endl;
                getline(cin, user_input);
                i->series_title = user_input;
                flag1 = true;
            }
            else if (user_input == "released-year") {
                cout << "What would you like to change it to? Enter a year " << endl;
                getline(cin, user_input);
                if (isStringInt(user_input)) {
                    if (stoi(user_input) >  1890 && stoi(user_input) < 2050) {
                        i->released_year = stoi(user_input);
                        flag1 = true;
                    }
                }
            }
            else if (user_input == "certificate") {
                cout << "What would you like to change it to?" << endl;
                getline(cin, user_input);
                i->certificate = user_input;
                flag1 = true;
            }
            else if (user_input == "runtime") {
                cout << "What would you like to change it to? Enter the number of minutes as an integer" << endl;
                getline(cin, user_input);
                if (isStringInt(user_input)) {
                    if (stoi(user_input) > 0) {
                        i->runtime = stoi(user_input);
                        flag1 = true;
                    }
                }
            }
            else if (user_input == "genre") {
                cout << "What would you like to change it to?" << endl;
                getline(cin, user_input);
                i->genre = user_input;
                flag1 = true;
            }
            else if (user_input == "IMDB-rating") {
                cout << "What would you like to change it to? Enter a number" << endl;
                getline(cin, user_input);
                if (isStringDouble(user_input)) {
                    if (stod(user_input) > 0) {
                        i->IMDB_rating = stoi(user_input);
                        flag1 = true;
                    }
                }
            }
            else if (user_input == "overview") {
                cout << "What would you like to change it to?" << endl;
                getline(cin, user_input);
                i->overview = user_input;
                flag1 = true;
            }
            else if (user_input == "meta-score") {
                cout << "What would you like to change it to? Enter an integer" << endl;
                getline(cin, user_input);
                if (isStringInt(user_input)) {
                    if (stoi(user_input) > 0) {
                        i->meta_score = stoi(user_input);
                        flag1 = true;
                    }
                }
            }
            else if (user_input == "director") {
                cout << "What would you like to change it to?" << endl;
                getline(cin, user_input);
                i->Director = user_input;
                flag1 = true;
            }
            //I'm leaving out stars for now, TODO
            else if (user_input == "number-votes") {
                cout << "What would you like to change it to? Enter an integer" << endl;
                getline(cin, user_input);
                 if (isStringInt(user_input)) {
                    if (stoi(user_input) > 0) {
                        i->numVotes = stoi(user_input);
                        flag1 = true;
                    }
                }
            }
            else if (user_input == "gross") {
                cout << "What would you like to change it to? Enter an integer" << endl;
                getline(cin, user_input);
                 if (isStringInt(user_input)) {
                    if (stoi(user_input) > 0) {
                        i->gross = stoi(user_input);
                        flag1 = true;
                    }
                }
            }
            if (flag1) {
                cout << "Document updated successfully" << endl; //this could create issues if we had 2 entries with same name
            } else {cout << "Document could not be updated due to invalid input, try again" << endl;}
        }   
        cnt++;
    }
    if (flag)
        cout << "Movie does not exist in the current Database" << endl;
}


/*
void printAllTables(DataBase& current) {
    for (int i = 0; i < current.storedDocuments.size(); i++) {
        cout << "Movie title: " << current.storedDocuments.at(i).series_title << endl;
        cout << "Description: " << current.storedDocuments.at(i).overview << endl;
        cout << "Director: " << current.storedDocuments.at(i).Director << endl; 
        cout << "Release Year: " << current.storedDocuments.at(i).released_year << endl;
        cout << "Genre: " << current.storedDocuments.at(i).genre << endl;
        cout << "Runtime: " << current.storedDocuments.at(i).runtime << endl;
        cout << "IMBD Rating: " << current.storedDocuments.at(i).IMDB_rating << endl;
        cout << "Meta Score: " << current.storedDocuments.at(i).meta_score << endl;
        cout << "Star rating: " << current.storedDocuments.at(i).Star1 << endl << endl;
    }
}
*/
