//use regex for parsing

//terminal console
#include <iostream>
#include <map> //linking documents with databases
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "json.hpp"
#include "filter.cpp"
//#include "console.h"

using namespace std;
//using json = nlohmann::json;

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
struct DataBase {
    string name;
    vector <Movie_Document> storedDocuments;
    vector <Movie_Document*> movieDocs;  //documents linked with this DataBase
};

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

//NEEDS INPUT VALIDATION, TODO
void addDocumentManually(DataBase* current) {
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


void importCSV(DataBase* current_DB){
    
    int badcnt = 0;
    //temp variables to hold data for parsing
    int inQoute = 0;
    string tmpStr = "";
    
    //define your file name
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
        current_DB->movieDocs.push_back(tmpDoc);

        //clear tmp vector for more data
        tmpData.clear();
    }

    cout << ".csv data import successful\n";
}


void printEntireDB(DataBase* db){
    int cnt = 0;

    for(auto i : db->movieDocs){
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
        cnt++;
    }
    cout << "size of current data base is: " << db->movieDocs.size() << endl;
}

//helper function, takes a string, returns true if convertable to an int
bool isStringInt(string str) {
  int num;
  istringstream iss(str);
  iss >> num;
  return iss.eof() && !iss.fail();
}

//same as isStringInt but with doubles
bool isStringDouble(string str) {
  double num;
  istringstream iss(str);
  iss >> num;
  return iss.eof() && !iss.fail();
}

void updateEntry(DataBase* db){
    int cnt = 0;
    cout << "Please enter name of movie you want to update" << endl;
    string user_input;
    getline(cin, user_input);
    bool flag = true;
    for(auto i : db->movieDocs){
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

void messageDisplayer() {
    cout << "input command to interact with the system:" << endl;
    cout << "enter 'db' to display current database" << endl;
    cout << "enter 'import csv' to import data file into database\n";        //added this to import .csv/JSON files
    cout << "enter 'filter' to filter by categories in the current database" << endl;
    cout << "enter 'element <index>' to display an element of the current database" << endl;
    cout << "enter 'db-all' to display all available database" << endl;
    cout << "enter 'print -a' to print all movie documents of current database" << endl;
    cout << "enter 'modify' to change a movie's information in the curret database" << endl;
    cout << "enter 'add <name>' to add a new database" << endl;
    cout << "enter 'use <name>' to switch to another database" << endl;
    cout << "enter 'rm <name>' to remove an existing database" << endl;
    cout << "enter 'man' to revisit the command list" << endl;
    cout << "enter 'addm' to enter a movie in the current database" << endl;
    cout << "enter 'rmm' to enter a movie in the current database" << endl;
    cout << "enter 'view' to show all tables in the current database" << endl; //this could be combined with 'db', I'm keeping it separate for now 
    cout << "enter 'exit' to exit from the system" << endl;
}

//check if user input is within input word limitation
string check_num_word(string user_input, int limit){
    //stringstream code generated from chatgpt
    stringstream ss(user_input);
    string word;
    int word_count = 0;
    vector<string>list;

    while (ss >> word) {
        list.push_back(word);
        word_count++;
    }

    if (word_count != limit){
        return "false";
    }else{
        return list[limit-1];
    }
}

//simple function to get the List of DataBase names
vector<string> getNameList(vector<DataBase> existingDB){
    vector<string>NameList;
    for (unsigned int i = 0; i < existingDB.size(); ++i){
        NameList.push_back((existingDB.at(i)).name);
    }
    return NameList;
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

int main(){

    DataBase db = {"default"};
  
    //Document doc1 = {"doc1", "content1", "random", time(nullptr)};

    //DataBase pointer, always points to the current database
    DataBase* currentDataBase;

    //used to store existing Database entries
    vector<DataBase> existingDB;
    existingDB.push_back(db);
    currentDataBase = &(existingDB.at(0)); //default

    //initial import of csv file
    //importCSV(currentDataBase);
    
    string user_input;
    messageDisplayer();

    while(1){
        //added this to imitate terminal input
        cout << ">>> ";
        getline(cin,user_input);

        //output current database
        if (user_input == "db"){
            cout << "current database is: " << currentDataBase->name << endl;
        }
        
        //added this to import .csv file into current database
        if(user_input == "import csv"){
            importCSV(currentDataBase);
        }

        //added this to print all documents of referenced db.
        if(user_input == "print -a"){
            printEntireDB(currentDataBase);
        }

        if (user_input == "filter"){
        filter();
        }

        //display all available databases
        if (user_input == "db-all"){
            if (existingDB.size() == 0){
                cout << "no available database.";
            } else {
                cout << "all available database include: ";
                for (unsigned int i = 0; i < existingDB.size(); ++i){
                    cout << (existingDB.at(i)).name << " ";
                }
            }
            cout << endl;
        }

        if (user_input == "modify") {
            updateEntry(currentDataBase);
        }

        if (user_input.substr(0, user_input.find(" ")) == "addm") {
            addDocumentManually(currentDataBase);
        }
        
        if (user_input.substr(0, user_input.find(" ")) == "rmm") {
            deleteDocumentManually(*currentDataBase);
        }
        
        if (user_input.substr(0, user_input.find(" ")) == "view") {
            cout << "type \"all\" to print all documents in the existing database, else will print 5 at a time" <<endl;
            cout << "type \"exit\" to return to main manual" << endl;
            string temp_input;
            cout << ">>> ";
            int impl = 0;
            getline(cin,temp_input);
            
            if(temp_input == "exit"){
                cout << "you have successfully exited the movie document viewer" << endl;
            } else if(temp_input == "all"){
                printAllTables(*currentDataBase);
            }else{
                for (int i = 0 + impl*5; i < 5 + impl*5; ++i){
                    displayMovieDocument(*currentDataBase, i);
                    cout << endl;
                }
                cout << "type \"next\" to view next 5 movie documents, type \"previous\" to view the previous 5 movie documents" << endl;
                while(temp_input != "exit"){
                    cout << ">>> ";
                    getline(cin,temp_input);
                    if (temp_input == "next"){
                        cout << "===================================================================================" << endl;
                        impl = impl + 1;
                        for (int i = 0 + impl*5; i < 5 + impl*5; ++i){
                            displayMovieDocument(*currentDataBase, i);
                            cout << endl;
                        }
                    } else if (temp_input == "previous"){
                        if (impl == 0){
                            cout << "you are already at the start of the documents" << endl;
                        }else{
                            cout << "===================================================================================" << endl;
                            impl = impl - 1;
                            for (int i = 0 + impl*5; i < 5 + impl*5; ++i){
                                displayMovieDocument(*currentDataBase, i);
                                cout << endl;
                            }
                        }
                    }
                }
                cout << "you have successfully exited the movie document viewer" << endl;
            }
        }
        
        //add a new database, if the database does not already exist, name of database have to be one word
        if (user_input.substr(0, user_input.find(" ")) == "add"){
            if (check_num_word(user_input, 2) == "false"){
                cout << "enter one word name for the new database" << endl;
            } else {
                string new_name = check_num_word(user_input, 2);
                vector<string> NameList = getNameList(existingDB);
                if (find(NameList.begin(), NameList.end(), new_name) != NameList.end()){
                    cout << new_name << " already exists" << endl;
                }else{
                    DataBase db_new = {new_name};
                    existingDB.push_back(db_new);
                    currentDataBase = &(existingDB.at(0)); //?
                    cout << "new database: " << new_name << " has been successfully added" << endl;
                }
            }       
        }

        if (user_input.substr(0, user_input.find(" ")) == "element"){
            if (check_num_word(user_input, 2) == "false"){
                cout << "only enter one element index to print" << endl;
            } else {
                DataBase currDB = *currentDataBase;
                int pos = user_input.find(' ');
                string numStr = user_input.substr(pos + 1);
                int index = stoi(numStr);
                displayMovieDocument(currDB, index);
            }       
        }

        //switch to another database, if the database does not already exist, ask if user want to create a new database
        if (user_input.substr(0, user_input.find(" ")) == "use"){
            if (check_num_word(user_input, 2) == "false"){
                cout << "enter one word name for the target database" << endl;
            } else {
                string database_name = check_num_word(user_input, 2);
                vector<string> NameList = getNameList(existingDB);
                //chatgpt generated auto search, check if there is existing database matching input name
                auto db_iter = find_if(existingDB.begin(), existingDB.end(),
                       [&](const DataBase& db_search){ return db_search.name == database_name; });
                if (db_iter != existingDB.end()){ //chatgpt generated code to switch database by name
                    currentDataBase = &(*db_iter); //chatgpt generated code to switch database by name
                    cout << "current database has been switched to: " << database_name << endl;
                }else{
                    cout << "database does not exist, enter 'yes' to add, anything else to deny" << endl;
                    string new_user_input;
                    getline(cin, new_user_input);
                    if(new_user_input == "yes"){
                        DataBase db_new = {database_name};
                        existingDB.push_back(db_new);
                        cout << "new database: " << database_name << " has been successfully added" << endl;
                        currentDataBase = &existingDB.at(existingDB.size()-1); //last in the existingDB
                        cout << "current database has been switched to: " << database_name << endl;
                    } else {
                        cout << "'use' operation cancelled" << endl;
                        messageDisplayer();
                    }
                }
            }       
        }

        //delete an existing database entry, cannot remove the default database or the currently using database
        if (user_input.substr(0, user_input.find(" ")) == "rm"){
            if (check_num_word(user_input, 2) == "false"){
                cout << "enter one word name for the database to be removed" << endl;
            } else {
                string target_name = check_num_word(user_input, 2);
                vector<string> NameList = getNameList(existingDB);
                if (target_name == "default"){
                    cout << "command failed, cannot remove the default database" << endl;
                } else if (target_name == currentDataBase->name) {
                    //chatgpt generated code to remove an element from database vector by its name
                    currentDataBase = &existingDB.at(0);
                    existingDB.erase(std::remove_if(existingDB.begin(), existingDB.end(),
                    [&](const DataBase& db) { return db.name == target_name; }), existingDB.end());
                    cout << "removed current database and switched to default" << endl;
                } else if (find(NameList.begin(), NameList.end(), target_name) != NameList.end()){
                    //chatgpt generated code to remove an element from database vector by its name
                    existingDB.erase(std::remove_if(existingDB.begin(), existingDB.end(),
                    [&](const DataBase& db) { return db.name == target_name; }), existingDB.end());
                    cout << "removed database: " << target_name << endl;
                }else{
                    cout << "command failed, target database does not exist" << endl;
                }
            }       
        }

        if (user_input == "man"){
            messageDisplayer();
        }

        //exit the database system
        if (user_input == "exit"){
            exit(1);
            return 0;
        }
    }

    return 0;
}
