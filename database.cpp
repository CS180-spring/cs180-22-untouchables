#include "database.hpp"
#include "nlohmann/json.hpp"

// Helper function to parse csv files
vector<Movie_Document*> parseCSV(string fname){
    
    int badcnt = 0;
    //temp variables to hold data for parsing
    int inQoute = 0;
    string tmpStr = "";

    //collection* collection = getCollectionByName(cltName);

    vector<Movie_Document *> movieData;
    
    /*
    if(collection == nullptr){
        cout << "Collection not found\n";
        return;
    }
    */
    
    //define your file name
    //string file_name = "/home/yt/Desktop/2023_Spring/CS180_Intro_Software_Engineering/Revised_Structure/cs180-22-untouchables/imdb_top_1000.csv";
    string file_name = "imdb_top_1000.csv";
    
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
                tmpData.push_back(line);
            }  
            
        }   

        //assign parsed data to newly created movie_document
        //parsed data was put into vector and is now being assigned
        //to data members of movie_document object
        tmpDoc->poster_Link = tmpData[0];
        tmpDoc->series_title = tmpData[1];
        /*
        if(tmpData[2] != "N/A"){
            cout << tmpData[2] << endl;
            tmpDoc->released_year = stoi(tmpData[2]);}
        else{tmpDoc->released_year = -1;}
        */
        if (tmpData[2] != "N/A") {
            try {
                tmpDoc->released_year = stoi(tmpData[2]);
            } catch (const std::invalid_argument& e) {
                tmpDoc->released_year = -1;
            }
        } else {
            tmpDoc->released_year = -1;
        }
        
        tmpDoc->certificate = tmpData[3];

        if (tmpData[4] != "N/A") {
            try {
                tmpDoc->runtime = stoi(tmpData[4]);
            } catch (const std::invalid_argument& e) {
                tmpDoc->runtime = -1;
            }
        } else {
            tmpDoc->runtime = -1;
        }

        tmpDoc->genre = tmpData[5];
        
        if (tmpData[6] != "N/A") {
            try {
                tmpDoc->IMDB_rating = stod(tmpData[6]);
            } catch (const std::invalid_argument& e) {
                tmpDoc->IMDB_rating = -1;
            }
        } else {
            tmpDoc->IMDB_rating = -1;
        }

        tmpDoc->overview = tmpData[7];

        if (tmpData[8] != "N/A") {
            try {
                tmpDoc->meta_score = stoi(tmpData[8]);
            } catch (const std::invalid_argument& e) {
                tmpDoc->meta_score = -1;
            }
        } else {
            tmpDoc->meta_score = -1;
        }

        tmpDoc->Director = tmpData[9];
        tmpDoc->Star1 = tmpData[10];
        tmpDoc->Star2 = tmpData[11];
        tmpDoc->Star3 = tmpData[12];
        tmpDoc->Star4 = tmpData[13];
        
        if (tmpData[14] != "N/A") {
            try {
                tmpDoc->numVotes = stoi(tmpData[14]);
            } catch (const std::invalid_argument& e) {
                tmpDoc->numVotes = -1;
            }
        } else {
            tmpDoc->numVotes = -1;
        }

        if (tmpData[15] != "0") {
            string str = tmpData[15];
            for (int i = 0, len = str.size(); i < len; i++) {
                if (ispunct(str[i])) {
                    str.erase(i--, 1);
                    len = str.size();
                }
            } try {
                tmpDoc->gross = stoi(str);
            } catch (const std::invalid_argument& e) {
                tmpDoc->gross = 0;
            }
        } else {
            tmpDoc->gross = 0;
        }
        //push new movie document to current database object
        //the entire database is pushed to the referenced db
        //movie documents are stored in "vector<Movie_Documents*> movieDocs"
        //can access data elements through pointer -> 
        movieData.push_back(tmpDoc);

        //clear tmp vector for more data
        tmpData.clear();
        tmpData[15] = '0';
    }

    return movieData;

}

Database::Database(){
    collection* defaultClt = new collection;
    mainDB = new collection;
    mainDB->name = "mainDB";
    defaultClt->name = "default";
    //currentClt = nullptr;    
    collectionDB.push_back(defaultClt);
    currentClt = defaultClt;

    // import main database
    currentClt->movieDocs = parseCSV("imdb_top_1000.csv");
    mainDB->movieDocs = parseCSV("imdb_top_1000.csv");
}

void Database::printMainDB(){
    
    if(!mainDB->movieDocs.empty()){
        for(auto i : mainDB->movieDocs){
            //cout << "poster-link: " << curr->poster_Link << endl;
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
        }
    }
    else{
        cout << "Main database empty\n\n";
    }
};


// Function simply returns a collection ptr to
// to referenced collection else returns nullptr
// if collection does not exist
collection* Database::getCollectionByName(string name){

    if(name == "mainDB"){
        
        return mainDB;
    }
    else{
        for(int i = 0; i < collectionDB.size(); i++){
            if(collectionDB[i]->name == name){
                
                return collectionDB[i];
            }
        }
    }
    
    return nullptr;
};

// function returns collection object 
collection Database::rtnCollectionByName(string name){

    collection rtnClt;

    for(int i = 0; i < collectionDB.size(); i++){
        if(collectionDB[i]->name == name){
            
            rtnClt = *collectionDB[i];
            break;
        }
    }

    return rtnClt;

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
        cout << "no available collections.\n\n";
    } 
    else{
        cout << "Available collections include: ";

        for(auto i : getCollectionsList()){
            cout << i << " ";
        }
        cout << endl << endl;
    }
}

// add collection to collectionDB
void Database::addCollection(string cltName){
    collection* Clt = new collection;

    Clt->name = cltName;
    collectionDB.push_back(Clt);

    cout << "New Collection \'"<< Clt->name << "\' added to database.\n";
}

// add collection from filtered results function 
// takes additional vector<Movie_Documents*> parameter
 void Database::addFltCollection(string cltName, vector<Movie_Document*> movieDocs) {

    collection* clt = new collection;

    clt->name = cltName;

    clt->movieDocs = movieDocs;

    collectionDB.push_back(clt);

 }

 collection* Database::rtnMainDB(){
    return this->mainDB;
 }

// Function simply iterates through collectionDB to check
// if collection with referenced name already exists
 bool Database::collectionExists(string cltName){
    if(cltName == "mainDB" && !mainDB->movieDocs.empty()){
        
        return 1;
    }
    
    for(auto i : collectionDB){
        if(i->name == cltName){
            
            return 1;
        }
    }
    return 0;

 }

// update currentClt ptr to passed parameter
// and use for reference in other functions
void Database::useCollection(string cltName){
    if(getCollectionByName(cltName) == nullptr){
        cout << "The collection does not exist, use add <name> to add the collection first" << endl;
    }else{
        this->currentClt = getCollectionByName(cltName);
        cout << "Switched to " << this->currentClt->name << " collection.\n";
    }   
}

// use private collection* currentClt to print current collection
void Database::printCurrentCltName(){
    if(currentClt == nullptr){
        cout << "no current collection\n\n";
    }
    else{
        cout << "current collection is: " << currentClt->name << "\n\n";
    }
}

string Database::getCurrentClt_name(){
    return currentClt->name;
}

int Database::checklen(){
    return collectionDB.size();
}

// delete collection by name and check if not current collection
// function will call deleteAllDocs to clean up memory allocation
// then it will delete memory allocated for collection and return bool
bool Database::deleteCollectionByName(string cltName){
    
    if(getCollectionByName(cltName) == nullptr){
        return false;
    }

    collection* clt = getCollectionByName(cltName);

    if(clt->name == currentClt->name){
        return false;
    }
    else{
        deleteAllDocs(cltName); 

        //cout << checklen(); 
        //chatgpt generate code to delete collection* from the vector
        auto it = std::find_if(collectionDB.begin(), collectionDB.end(),
                               [&](collection* c) { return c->name == cltName; });
        if (it != collectionDB.end()) {
            collectionDB.erase(it);
        }
        
        delete clt;
        //cout << checklen();    
        return true;
    }
}

void Database::deleteAllDocs(string cltName){

    collection* clt = getCollectionByName(cltName);

    for(auto i : clt->movieDocs){
        
        delete i;
    
    }

    cout << "All documents from " << cltName << " deleted.\n";
}

/*
collection* Database::useCollection(string cltName){
    
    return getCollectionByName(cltName);
}
*/

void Database::importCSV(string cltName, string fname){
    
    collection* collection = getCollectionByName(cltName);
    
    vector<Movie_Document*> movieData = parseCSV(fname);

    if(collection == nullptr){
        cout << "Collection not found\n";

    }
    else{
        collection->movieDocs = movieData;
        cout << ".csv data import successful\n\n";
    }
}

// Function takes collection name for parameter
// checks is collection exists, if collection exists
// exports data to file named after collection
// to local directory else prints collection does not exist
void Database::exportCSV(string cltName){

    collection* exportClt = getCollectionByName(cltName);

    if(exportClt != nullptr){
        
        // Name of collection to be exported
        // used for name of exported file 
        string fileName = exportClt->name;
    
        fileName = fileName + ".csv";

        // Output file stream
        ofstream oFile;

        // Open file
        oFile.open(fileName);

        // Check for any error
        if(!oFile){
            cout << "Error in creating export file!\n\n";
        }
        else{

            // Export header
            oFile << "Poster_Link,Series_Title,Released_Year,Certificate,Runtime,Genre,IMDB_Rating,Overview,Meta_score,Director,Star1,Star2,Star3,Star4,No_of_Votes,Gross\n";
            
            // Loop through all movieDocs of collection 
            // and export to .csv format
            for(auto i : exportClt->movieDocs){
                
                oFile << "\"" << i->poster_Link << "\"";
                oFile << "," << i->series_title;
                oFile << "," << i->released_year;
                oFile << "," << i->certificate;
                oFile << "," << i->runtime;
                oFile << "," << i->genre;
                oFile << "," << i->IMDB_rating;
                oFile << "\"";
                oFile << "," << i->overview;
                oFile << "\"";
                oFile << "," << i->meta_score;
                oFile << "," << i->Director;
                oFile << "," << i->Star1;
                oFile << "," << i->Star2;
                oFile << "," << i->Star3;
                oFile << "," << i->Star4;
                oFile << "," << i->numVotes;
                oFile << ",\"" << i->gross << "\"";
                oFile << "\n";
            }

            // Close file
            oFile.close();

            // Export successful
            cout << "Data export successful\n\n";
        }

    }
    // Collection not found
    else if(exportClt == nullptr){
        cout << "Collection not found\n\n";
    }
}
void Database::importJSON(collection* db, string fileName) {
    // Input file stream
    ifstream iFile;

    // Open file
    iFile.open(fileName);

    // Check for errors
    if (!iFile) {
        cout << "Error in opening import file!\n\n";
    }
    else {
        // Read the contents of the file into a string
        string fileContents((istreambuf_iterator<char>(iFile)), istreambuf_iterator<char>());

        // Parse the JSON string
        nlohmann::json jsonArray = nlohmann::json::parse(fileContents);

        // Iterate through the JSON array
        for (auto& movieJson : jsonArray) {
            // Create a new movie document
            Movie_Document* newMovie = new Movie_Document();

            // Populate the movie document with data from JSON
            newMovie->poster_Link = movieJson["Poster_Link"];
            newMovie->series_title = movieJson["Series_Title"];
            newMovie->released_year = movieJson["Released_Year"];
            newMovie->certificate = movieJson["Certificate"];
            newMovie->runtime = movieJson["Runtime"];
            newMovie->genre = movieJson["Genre"];
            newMovie->IMDB_rating = movieJson["IMDB_Rating"];
            newMovie->overview = movieJson["Overview"];
            newMovie->meta_score = movieJson["Meta_score"];
            newMovie->Director = movieJson["Director"];
            newMovie->Star1 = movieJson["Star1"];
            newMovie->Star2 = movieJson["Star2"];
            newMovie->Star3 = movieJson["Star3"];
            newMovie->Star4 = movieJson["Star4"];
            newMovie->numVotes = movieJson["NumVotes"];
            newMovie->gross = movieJson["Gross"];

            // Add the movie document to the collection
            db->movieDocs.push_back(newMovie);
        }

        // Close file
        iFile.close();

        // Import successful
        cout << "Data import successful\n\n";
    }
}


void Database::exportJSON(string cltName) {

    collection* exportClt = getCollectionByName(cltName);

    if (exportClt != nullptr) {

        // Name of collection to be exported
        // used for name of exported file 
        string fileName = exportClt->name;

        fileName = fileName + ".json";

        // Output file stream
        ofstream oFile;

        // Open file
        oFile.open(fileName);

        // Check for any error
        if (!oFile) {
            cout << "Error in creating export file!\n\n";
        }
        else {
            // modified based on chatgpt sample json export code
            // Create a JSON array
            nlohmann::json jsonArray;

            // Loop through all movieDocs of collection 
            // and add to .json array
            for (auto i : exportClt->movieDocs) {
                // Create a JSON object for each movie document
                nlohmann::json movieJson;
                movieJson["Poster_Link"] = i->poster_Link;
                movieJson["Series_Title"] = i->series_title;
                movieJson["Released_Year"] = i->released_year;
                movieJson["Certificate"] = i->certificate;
                movieJson["Runtime"] = i->runtime;
                movieJson["Genre"] = i->genre;
                movieJson["IMDB_Rating"] = i->IMDB_rating;
                movieJson["Overview"] = i->overview;
                movieJson["Meta_score"] = i->meta_score;
                movieJson["Director"] = i->Director;
                movieJson["Star1"] = i->Star1;
                movieJson["Star2"] = i->Star2;
                movieJson["Star3"] = i->Star3;
                movieJson["Star4"] = i->Star4;
                movieJson["NumVotes"] = i->numVotes;
                movieJson["Gross"] = i->gross;

                // Add the movie JSON object to the array
                jsonArray.push_back(movieJson);
            }

            // Write the JSON array to the file
            oFile << jsonArray.dump(4); //dump used for better data representation

            // Close file
            oFile.close();

            // Export successful
            cout << "Data export successful\n\n";
        }
    }
    // Collection not found
    else if (exportClt == nullptr) {
        cout << "Collection not found\n\n";
    }
}

// function to export filtered movie data to .csv format
void Database::fltExportCSV(vector<Movie_Document*> fltMovies, string fileName){

    // check if filtered movie data is empty
    if(!fltMovies.empty()){
        
        fileName = fileName + ".csv";

        // Output file stream
        ofstream oFile;

        // Open file
        oFile.open(fileName);

        // Check for any error
        if(!oFile){
            cout << "Error in creating export file!\n\n";
        }
        else{

            // Export header
            oFile << "Poster_Link,Series_Title,Released_Year,Certificate,Runtime,Genre,IMDB_Rating,Overview,Meta_score,Director,Star1,Star2,Star3,Star4,No_of_Votes,Gross\n";
            
            // Loop through all movieDocs of collection 
            // and export to .csv format
            for(auto i : fltMovies){
                
                oFile << "\"" << i->poster_Link << "\"";
                oFile << "," << i->series_title;
                oFile << "," << i->released_year;
                oFile << "," << i->certificate;
                oFile << "," << i->runtime;
                oFile << "," << i->genre;
                oFile << "," << i->IMDB_rating;
                oFile << "\"";
                oFile << "," << i->overview;
                oFile << "\"";
                oFile << "," << i->meta_score;
                oFile << "," << i->Director;
                oFile << "," << i->Star1;
                oFile << "," << i->Star2;
                oFile << "," << i->Star3;
                oFile << "," << i->Star4;
                oFile << "," << i->numVotes;
                oFile << ",\"" << i->gross << "\"";
                oFile << "\n";
            }

            // Close file
            oFile.close();

            // Export successful
            cout << "Data export successful\n\n";
        }

    }
    // Collection not found
    else if(fltMovies.empty()){
        cout << "Nothing to export\n\n";
    }
}

void Database::analysis(string cltName){
    collection* tmpClt = getCollectionByName(cltName);
    if (tmpClt == nullptr){
        cout << "Collection not found.\n";
    }else{
        vector<Movie_Document*> tmpDocs = tmpClt->getMovieDocs();
        if(tmpDocs.empty()){
            cout << "Collection has a empty document.\n";
        }else{
            //year 
            int earliest_released_year = INT_MAX;
            string earliest_released_year_movie;
            int latest_released_year = INT_MIN;
            string latest_released_year_movie;
            //certificate
            vector<string> cert = {"A", "UA", "PG-13", "R", "PG", "Passed", "TV-14", "G", "A", "U", "Approved"};
            vector<int> cert_num = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            //runtime
            int shortest_runtime = INT_MAX;
            string shortest_runtime_movie;
            int longest_runtime = INT_MIN;
            string longest_runtime_movie;
            //genre
            vector<string> genres = {"Drama", "Crime", "Action", "Adventure", "Biography", "Sci-Fi", "Romance", "Western", "Fantasy", "Thriller", "Comedy", "Family", "War", "Mystery", "Music", "Sport"};
            vector<int> genres_num = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            //IMDB_rating
            double lowest_IMDB_rating = INT_MAX;
            string lowest_IMDB_rating_movie;
            double highest_IMDB_rating = INT_MIN;
            string highest_IMDB_rating_movie;
            //meta_score
            int lowest_meta_score = INT_MAX;
            string lowest_meta_score_movie;
            int highest_meta_score = INT_MIN;
            string highest_meta_score_movie;
            //numVotes
            int lowest_numVotes = INT_MAX;
            string lowest_numVotes_movie;
            int highest_numVotes = INT_MIN;
            string highest_numVotes_movie;
            //gross
            int lowest_gross = INT_MAX;
            string lowest_gross_movie;
            int highest_gross = INT_MIN;
            string highest_gross_movie;

            for (int i = 0; i < tmpClt->movieDocs.size(); ++i){
                Movie_Document* curr = tmpDocs[i];
                if(curr != nullptr && curr->released_year != -1){
                    if (curr->released_year > latest_released_year){
                        latest_released_year = curr->released_year;
                        latest_released_year_movie = curr->series_title;
                    }else if (curr->released_year < earliest_released_year){
                        earliest_released_year = curr->released_year;
                        earliest_released_year_movie = curr->series_title;
                    }
                }
                if(curr != nullptr && curr->certificate != ""){
                    for(int j = 0; j < cert.size(); j++){
                        if(curr->certificate == cert[j]){
                            cert_num[j] ++;
                        }
                    }
                }
                if(curr != nullptr && curr->runtime != -1){
                    if (curr->runtime < shortest_runtime){
                        shortest_runtime = curr->runtime;
                        shortest_runtime_movie = curr->series_title;
                    }else if (curr->runtime > longest_runtime){
                        longest_runtime = curr->runtime;
                        longest_runtime_movie = curr->series_title;
                    }
                }
                if(curr != nullptr && curr->genre != ""){
                    for(int k = 0; k < genres.size(); k++){
                        if (curr->genre.find(genres[k]) != std::string::npos) {
                            genres_num[k]++;
                        }
                    }
                }
                if(curr != nullptr && curr->IMDB_rating != -1){
                    if (curr->IMDB_rating < lowest_IMDB_rating){
                        lowest_IMDB_rating = curr->IMDB_rating;
                        lowest_IMDB_rating_movie = curr->series_title;
                    }else if (curr->IMDB_rating > highest_IMDB_rating){
                        highest_IMDB_rating = curr->IMDB_rating;
                        highest_IMDB_rating_movie = curr->series_title;
                    }
                }
                if(curr != nullptr && curr->meta_score != -1){
                    if (curr->meta_score < lowest_meta_score){
                        lowest_meta_score = curr->meta_score;
                        lowest_meta_score_movie = curr->series_title;
                    }else if (curr->meta_score > highest_meta_score){
                        highest_meta_score = curr->meta_score;
                        highest_meta_score_movie = curr->series_title;
                    }
                }
                if(curr != nullptr && curr->numVotes != -1){
                    if (curr->numVotes < lowest_numVotes){
                        lowest_numVotes = curr->numVotes;
                        lowest_numVotes_movie = curr->series_title;
                    }else if (curr->numVotes > highest_numVotes){
                        highest_numVotes = curr->numVotes;
                        highest_numVotes_movie = curr->series_title;
                    }
                }
                if(curr != nullptr && curr->gross != -1){
                    if (curr->gross < lowest_gross){
                        lowest_gross = curr->gross;
                        lowest_gross_movie = curr->series_title;
                    }else if (curr->gross > highest_gross){
                        highest_gross = curr->gross;
                        highest_gross_movie = curr->series_title;
                    }
                }
            }
            cout << "size of current data base (" << cltName << ") is: " << tmpClt->movieDocs.size() << endl;
            cout << ">>> released year:" << endl;
            cout << "earliest released movie is: " << earliest_released_year_movie << " in "<< earliest_released_year << endl;
            cout << "latest released movie is: " << latest_released_year_movie << " in "<< latest_released_year << endl;
            cout << ">>> certificate:" << endl;
            cout << "among the movie documents, there are";
            for(int i = 0; i < cert.size(); ++i){
                cout << " " << cert_num[i] << " \"" << cert[i] << "\" type of movie";
            }
            cout << endl;
            cout << ">>> runtime:" << endl;
            cout << "shortest runtime movie is: " << shortest_runtime_movie << " which lasts "<< shortest_runtime << " minutes" << endl;
            cout << "longest runtime movie is: " << longest_runtime_movie << " which lasts "<< longest_runtime << " minutes" << endl;
            cout << ">>> genre:" << endl;
            cout << "among the movie documents, there are";
            for(int i = 0; i < genres.size(); ++i){
                cout << " " << genres_num[i] << " \"" << genres[i] << "\" type of movie";
            }
            cout << endl;
            cout << ">>> IMDB rating:" << endl;
            cout << "lowest IMDB rating movie is: " << lowest_IMDB_rating_movie << " with score: "<< lowest_IMDB_rating << endl;
            cout << "highest IMDB rating movie is: " << highest_IMDB_rating_movie << " with score: "<< highest_IMDB_rating << endl;
            cout << ">>> meta score:" << endl;
            cout << "lowest meta score movie is: " << lowest_meta_score_movie << " with score: "<< lowest_meta_score << endl;
            cout << "highest meta score movie is: " << highest_meta_score_movie << " with score: "<< highest_meta_score << endl;
            cout << ">>> numVotes:" << endl;
            cout << "lowest voted movie is: " << lowest_numVotes_movie << " with number of votes: "<< lowest_numVotes << endl;
            cout << "highest voted movie is: " << highest_numVotes_movie << " with number of votes: "<< highest_numVotes << endl;
            cout << ">>> gross:" << endl;
            cout << "lowest gross movie is: " << lowest_gross_movie << " with gross: "<< lowest_gross << endl;
            cout << "highest gross movie is: " << highest_gross_movie << " with gross: "<< highest_gross << endl;
        }
    }
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
            int higher_bound = 0;
            if (5 + impl*5 < tmpDocs.size()){
                higher_bound = 5 + impl*5;
            }else{
                higher_bound = tmpDocs.size();
            }
            for (int i = 0 + impl*5; i < higher_bound; ++i){
                Movie_Document* curr = tmpDocs[i];
                if(curr != nullptr){
                    printf("Document %d\n",i+1);
                    //cout << "poster-link: " << curr->poster_Link << endl;
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
            cout << "type \"view\" to view current 5 movie documents again, type \"exit\" to return to main manual" << endl;
            while(temp_input != "exit"){
                cout << ">>> ";
                getline(cin,temp_input);
                if (temp_input == "next"){
                    cout << "===================================================================================" << endl;
                    impl = impl + 1;
                    double div = 5;
                    if((tmpDocs.size()/div) <= impl){
                        cout << "you are already at the end of the documents" << endl;
                        impl = impl - 1;
                    }else{
                        int higher_bound = 0;
                        if (5 + impl*5 < tmpDocs.size()){
                            higher_bound = 5 + impl*5;
                        }else{
                            higher_bound = tmpDocs.size();
                        }
                        for (int i = 0 + impl*5; i < higher_bound; ++i){
                            Movie_Document* curr = tmpDocs[i];
                            if(curr != nullptr){
                                printf("Document %d\n",i+1);
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
                        int higher_bound = 0;
                        if (5 + impl*5 < tmpDocs.size()){
                            higher_bound = 5 + impl*5;
                        }else{
                            higher_bound = tmpDocs.size();
                        }
                        for (int i = 0 + impl*5; i < higher_bound; ++i){
                            Movie_Document* curr = tmpDocs[i];
                            if(curr != nullptr){
                                printf("Document %d\n",i+1);
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
                }else if (temp_input == "view"){
                    cout << "===================================================================================" << endl;
                    int higher_bound = 0;
                    if (5 + impl*5 < tmpDocs.size()){
                        higher_bound = 5 + impl*5;
                    }else{
                        higher_bound = tmpDocs.size();
                    }
                    for (int i = 0 + impl*5; i < higher_bound; ++i){
                        Movie_Document* curr = tmpDocs[i];
                        if(curr != nullptr){
                            printf("Document %d\n",i+1);
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
            cout << "you have successfully exit the movie document viewer" << endl;
            cout << ">>> ";cout << "size of current data base is: " << tmpClt->movieDocs.size() << endl;
        }
    }

}
void Database::addDocumentManually() {
    Movie_Document* addMe = new Movie_Document();
    string checkPosterLink;
    cout << "Input the poster link: " << endl;
    getline(cin, checkPosterLink);
    if (isValidLink(checkPosterLink)) {
        addMe->poster_Link = checkPosterLink;
    }
    else {
        cout << "Error, invalid input" << endl;
        delete addMe;
        return;
    }
    string checkTitle;
    cout << "Input the series title: " << endl;
    getline(cin,checkTitle);
    if (checkTitle != "") {
        addMe->series_title = checkTitle;
    }
    else {
        cout << "Error, invalid input" << endl;
        delete addMe;
        return;
    }
    string checkReleaseYear;
    cout << "Input the release year: " << endl;
    cin >> checkReleaseYear;
    if (isStringInt(checkReleaseYear) && stoi(checkReleaseYear) > 1887 && stoi(checkReleaseYear) <= 2050)
        addMe->released_year = stoi(checkReleaseYear);
    else {
        cout << "Error, invalid input" << endl;
        delete addMe;
        cin.ignore();
        return;
    }
    string checkRuntime;
    cout << "Input the runtime (int): " << endl;
    cin >> checkRuntime;
    if (isStringInt(checkRuntime) && stoi(checkRuntime) > 0)
        addMe->runtime = stoi(checkRuntime);
    else {
        cout << "Error, invalid input" << endl;
        delete addMe;
        cin.ignore();
        return;
    }
    cout << "Input the genre: " << endl; 
    cin.ignore();
    getline(cin, addMe->genre);
    string checkIMDB;
    cout << "Input the IMDB_rating (double): " << endl;
    cin >> checkIMDB;
    if (isStringDouble(checkIMDB) && stod(checkIMDB) >= 0 && stod(checkIMDB) <= 10) 
        addMe->IMDB_rating = stod(checkIMDB);
    else {
        cout << "Error, invalid input" << endl;
        delete addMe;
        cin.ignore();
        return;
    }
    cout << "Input the description: " << endl;
    cin.ignore();
    getline(cin, addMe->overview);

    string checkMeta;
    cout << "Input the meta_score: " << endl;
    cin >> checkMeta;
    if (isStringInt(checkMeta) && stoi(checkMeta) >= 0 && stoi(checkMeta) <= 100)
        addMe->meta_score = stoi(checkMeta);
    else {
        cout << "Error, invalid input" << endl;
        delete addMe;
        cin.ignore();
        return;
    }
    string checkDirector;
    cout << "Input the Director's name: " << endl;
    cin.ignore();
    getline(cin,checkDirector);
    if (checkDirector != "") {
        addMe->Director = checkDirector;
    }
    else {
        cout << "Error, invalid input" << endl;
        delete addMe;
        return;
    }
    string checkStar1;
    cout << "Input the first star's name: " << endl; 
    getline(cin,checkStar1);
    if (checkStar1 != "") {
        addMe->Star1 = checkStar1;
    }
    else {
        cout << "Error, invalid input" << endl;
        delete addMe;
        return;
    }

    string checkStar2;
    cout << "Input the second star's name: " << endl; 
    getline(cin,checkStar2);
    if (checkStar2 != "") {
        addMe->Star2 = checkStar2;
    }
    else {
        cout << "Error, invalid input" << endl;
        delete addMe;
        return;
    }

    string checkStar3;
    cout << "Input the third star's name: " << endl; 
    getline(cin,checkStar3);
    if (checkStar3 != "") {
        addMe->Star3 = checkStar3;
    }
    else {
        cout << "Error, invalid input" << endl;
        delete addMe;
        return;
    }

    string checkStar4;
    cout << "Input the fourth star's name: " << endl; 
    getline(cin,checkStar4);
    if (checkStar4 != "") {
        addMe->Star4 = checkStar4;
    }
    else {
        cout << "Error, invalid input" << endl;
        delete addMe;
        return;
    }
    string checkNumVotes;
    cout << "Input the number of votes: " << endl;
    cin >> checkNumVotes;
    if (isStringInt(checkNumVotes) && stoi(checkNumVotes) > 0)
        addMe->numVotes = stoi(checkNumVotes);
    else {
        cout << "Error, invalid input" << endl;
        delete addMe;
        cin.ignore();
        return;
    }
    string checkGross;
    cout << "Input the gross revenue: " << endl;
    cin >> checkGross;
     if (isStringInt(checkGross) && stoi(checkGross) > 0)
        addMe->gross = stoi(checkGross);
    else {
        cout << "Error, invalid input" << endl;
        delete addMe;
        cin.ignore();
        return;
    }
    currentClt->movieDocs.push_back(addMe);
    cout << "Movie added successfully" << endl;
    cin.ignore();
}

void Database::deleteDocumentManual(string cltName, string docName){
    collection* deleteFromMe = getCollectionByName(cltName);
    if (deleteFromMe == nullptr) {
        cout << "Error, that collection cannnot be found" << endl;
        return;
    }

    for (int i = 0; i < deleteFromMe->movieDocs.size(); ++i) {
        if (deleteFromMe->movieDocs[i]->series_title == docName) {
            delete deleteFromMe->movieDocs[i];
            deleteFromMe->movieDocs.erase(deleteFromMe->movieDocs.begin() + i);
            cout << "Document " << docName << " has been successfully deleted." << endl;
            return;
        }
    }
    //if the Document does not exist
    cout << "Document does not exist in the current collection" << endl;
}

void Database::updateEntry(string cltName, string user_input){
    int cnt = 0;
    bool flag = true;
    collection* cltToBeUpdated = getCollectionByName(cltName);
    if (cltToBeUpdated == nullptr) {
        cout << "ERROR: Collection not found" << endl;
        return;
    }
    for(auto i : cltToBeUpdated->movieDocs){
        if (i->series_title == user_input) {
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
                if (isValidLink(user_input)) {
                    i->poster_Link = user_input;
                    flag1 = true;
                }
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
                    if (stoi(user_input) >  1887 && stoi(user_input) < 2050) {
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
                        i->IMDB_rating = stod(user_input);
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
            else if (user_input == "Star1") {
                cout << "What would you like to change it to?" << endl;
                getline(cin, user_input);
                i->Star1 = user_input;
                flag1 = true;
            }
            else if (user_input == "Star2") {
                cout << "What would you like to change it to?" << endl;
                getline(cin, user_input);
                i->Star2 = user_input;
                flag1 = true;
            }
            else if (user_input == "Star3") {
                cout << "What would you like to change it to?" << endl;
                getline(cin, user_input);
                i->Star3 = user_input;
                flag1 = true;
            }
            else if (user_input == "Star4") {
                cout << "What would you like to change it to?" << endl;
                getline(cin, user_input);
                i->Star4 = user_input;
                flag1 = true;
            }
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
                cout << "Document updated successfully" << endl; //this could create issues if we had 2 entries with same name, ADD A NAME CHECK PLEASE FUTURE ME
            } else {cout << "Document could not be updated due to invalid input, try again" << endl;}
        }   
        cnt++;
    }
    if (flag)
        cout << "Movie does not exist in the current Database" << endl;
}

//helper function, takes a string, returns true if convertable to an int
bool Database::isStringInt(string str) {
  int num;
  istringstream iss(str);
  iss >> num;
  return iss.eof() && !iss.fail();
}

//same as isStringInt but with doubles
bool Database::isStringDouble(string str) {
  double num;
  istringstream iss(str);
  iss >> num;
  return iss.eof() && !iss.fail();
}
// I LIKE THIS!!!
bool Database::isValidLink(const std::string& link) { 
  regex linkPattern(
      R"(^(https?|ftp)://[^\s/$.?#].[^\s]*$)", std::regex::icase);

  return regex_match(link, linkPattern);
}
