#include "database.hpp"

//using json = nlohmann::json;

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

//helper function to parse user input from terminal
vector<string> parseUserInput(string userInput){

    string syntax = "";

    vector<string> parsedInput;

    stringstream ss(userInput);

    while(ss >> syntax){
        parsedInput.push_back(syntax);
    }

    return parsedInput;
}

//terminal console commands
void messageDisplayer() {
    cout << "input command to interact with the system:" << endl;
    cout << "enter 'db' to display current collection" << endl;
    cout << "enter 'db-all' to display all available collections" << endl;
    cout << "enter 'import -<format> <collection> <file>' to import data file into collection\n";           //added this to import .csv/JSON files into specified collection
    cout << "enter 'print -<flag> <collection>' to print all movie documents of current database\n";        //added this to print data
    cout << "enter 'add <name>' to add a new database" << endl;
    cout << "enter 'use <name>' to switch to another database" << endl;
    cout << "enter 'filter' to filter by categories in the current database" << endl;
    cout << "enter 'element <index>' to display an element of the current database" << endl;
    cout << "enter 'modify' to change a movie's information in the curret database" << endl;
    cout << "enter 'rm <name>' to remove an existing database" << endl;
    cout << "enter 'menu' to revisit the command list" << endl;
    cout << "enter 'addm' to enter a movie in the current database" << endl;
    cout << "enter 'enter' to enter a movie in the current database" << endl;
    cout << "enter 'view' to show all tables in the current database" << endl; //this could be combined with 'db', I'm keeping it separate for now 
    cout << "enter 'exit' to exit from the system" << endl;
}

//helper function to call db functions based off of parsed user input
void userInstruction(Database& db, vector<string>& instructions){

    string instruction = instructions[0];

    //output current database
    if(instruction == "db"){
       
        db.printCurrentClt();
        
    }
    
    //prints list of all collections
    else if(instruction == "db-all"){                   
     
        db.dbAll();
       
    }
    
    // imports data from file and takes three parameters
    else if(instruction == "import"){                   
        if(instructions[1] == "-csv"){
            string cltName = "", fileName = "";

            cltName = instructions[2];
            fileName = instructions[3];

            // does actual import and takes 
            // two parameters <collection> <filename>
            db.importCSV(cltName, fileName);            
        }
    }
    
    else if(instruction == "filter"){
        //filter();
    
    }
    
    else if(instruction == "element"){
        
    }

    // prints data and takes multiple 
    // parameters see "man" for syntax
    else if(instruction == "print"){
        string tmp = instructions[1];
        if(tmp == "-a"){
            string tmpClt = instructions[2];

            db.printSingleClt(tmpClt);
        }        
        else{
            //need to define print function to handle multiple parameters
        }
    }

    else if(instruction == "modify"){
        string movTitle = "";
        movTitle = instructions[1]; 
        //db.updateEntry(movTitle);
    }

    // add collection and takes multiple
    // parameters see "man" for syntax
    else if(instruction == "add"){
        if(instructions[1] == "-m"){
            //db.addDocumentManually();
        }
        else if(instructions[1] != "-m"){
            string cltName = instructions[1];
            db.addCollection(cltName);
        }
        
    }  

    // updates current collection
    // pointer for console
    else if(instruction == "use"){
        string cltName = instructions[1];   

        //update current collection pointer
        db.useCollection(cltName);
    }

    // delete data and takes multiple parameters
    // for collections and docs, see "man"
    else if(instruction == "rm"){
        string cltName = instructions[1];
        string docName = instructions[2];
        
        // if parsed data < 3 then delete entire collection
        // else get additional parsed data for movie docs
        if(instructions.size() < 3){
            if(db.deleteCollectionByName(cltName)){
                cout << "Collection " << cltName << " deleted.\n";
            }
            else{
                cout << "Deletion unsuccessful: can't delete current collection.\n";
            }
        }
        else if(instructions.size() == 3){
            //db.deleteDocManual(string cltName, string docName);

        }
    }    
    else if(instruction == "menu"){
        messageDisplayer();    
    }
    else if(instruction == "enter"){
        
    }
    else if(instruction == "view"){
        
    }
    else if(instruction == "exit"){
        //exit the database system
        if (instruction == "exit"){
            exit(1);
        }
    }
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

int main(){

    Database db;
    
    string user_input;
    vector<string> userInput;
    vector<string> userInstruct;
  
    //DataBase pointer, always points to the current database
    //collection* currentClt = db.getCollectionByName("default");
    
    messageDisplayer();

    while(1){
        // added this to imitate terminal input
        cout << ">>> ";
        getline(cin,user_input);

        // parse user input and return in vector or strings
        userInstruct = parseUserInput(user_input);
        
        // pass parsed vector to helper 
        // function to call db functions
        userInstruction(db, userInstruct);

        
      
        /*
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

    */
     
    }

    return 0;
}
