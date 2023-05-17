#include "filter.hpp"
//using json = nlohmann::json;

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
    system("clear");

    int width = 5;
    cout << "********************************************************************************************************\n";
    cout << "*                                            Movie Database                                            *\n";
    cout << "********************************************************************************************************\n";
    cout << "*                                                                                                      *\n";
    cout << left << setw(width) << "*" << left << setw(40) << "db" << left << setw(50) << "display current collection" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "db-all" << left << setw(50) << "display all available collections" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "import -<format> <collection> <file>" << left << setw(50) << "import data file into collection" << right << setw(9) << "*" << endl; //added this to import .csv/JSON files into specified collection
    cout << left << setw(width) << "*" << left << setw(40) << "export <collection>" << left << setw(50) << "export collection" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "print -<flag> <collection>" << left << setw(50) << "print all movie documents of selected collection" << right << setw(9) << "*" << endl;        //added this to print data
    cout << left << setw(width) << "*" << left << setw(40) << "add <name>" << left << setw(50) << "add new collection" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "use <name>" << left << setw(50) << "switch to another collection" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "filter" << left << setw(50) << "filter menu" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "element <index>" << left << setw(50) << "display an element of the current collection" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "modify <movie_title>" << left << setw(50) << "change a movie's information in the curret collection" << right << setw(8) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "rm <name>" << left << setw(50) << "remove an existing collection" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "menu" << left << setw(50) << "revisit the command list" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "add -m" << left << setw(50) << "enter a movie in the current collection" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "enter" << left << setw(50) << "enter a movie in the current collection" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "view" << left << setw(50) << "show all tables in the current collection" << right << setw(9) << "*" << endl; //this could be combined with 'db', I'm keeping it separate for now 
    cout << left << setw(width) << "*" << left << setw(40) << "exit" << left << setw(50) << "exit system" << right << setw(9) << "*" << endl;
    cout << "*                                                                                                      *" << endl;
    cout << "********************************************************************************************************" << endl;
    cout << endl;
}

//helper function to call db functions based off of parsed user input
void userInstruction(Filter& filter, Database& db, vector<string>& instructions){

    string instruction = instructions[0];

    if(instruction == "print"){
      if(instructions[1] == "-main"){
      db.printMainDB();
      }
    }

    //output current database
    if(instruction == "db"){
        if (instructions.size() != 1){
            cout << "please use proper command, recommanded command: \"db\"" << endl;
            return;
        }
        db.printCurrentCltName();
    }
    
    //prints list of all collections
    else if(instruction == "db-all"){
        if (instructions.size() != 1){
            cout << "please use proper command, recommanded command: \"db-all\"" << endl;
            return;
        }
        db.dbAll();
    }
    
    // imports data from file and takes three parameters
    else if(instruction == "import"){
        if (instructions.size() != 4){
            cout << "please use proper command, recommanded command: \"import -<format> <collection> <file>\"" << endl;
            return;
        }
        if(instructions[1] == "-csv"){
            string cltName = "", fileName = "";

            cltName = instructions[2];
            fileName = instructions[3];

            // does actual import and takes 
            // two parameters <collection> <filename>
            db.importCSV(cltName, fileName);            
        }
    }

    else if(instruction == "export"){
        if (instructions.size() != 2){
            cout << "please use proper command, recommanded command: \"export <collection>\"" << endl;
            return;
        }
        string cltName = instructions[1];

        db.exportCSV(cltName);
    }
    
    else if(instruction == "filter"){

        filter.filterMain();
        messageDisplayer();
        /*
        if(instructions[1] == "-a"){
            string cltName = instructions[2];
            string feature = instructions[3];
            filter.alphabetSort(cltName, feature);
        }
        else if(instructions[1] == "-g"){
            string cltName = instructions[2];
            string genre = instructions[3];
            filter.genreSort(cltName, genre);
        }
        */
       
    }
    
    else if(instruction == "element"){
        
    }

    // prints data and takes multiple 
    // parameters see "man" for syntax
    else if(instruction == "print"){
        if (instructions.size() < 3){
            cout << "please use proper command, recommanded command: \"print -<flag> <collection>\"" << endl;
            return;
        }
        string tmp = instructions[1];
        if(tmp == "-a"){
            string tmpClt = instructions[2];

            db.printSingleClt(tmpClt);
        }        
        else if(tmp == "-d"){           
            //need to define print function to handle multiple parameters
            for (int i = 2; i < instructions.size(); ++i){
                cout << "===================================================================================" <<endl;
                cout << "printing collection " << instructions[i] << ":" << endl;
                db.printSingleClt(instructions[i]);
            }
        }
    }

    else if(instruction == "modify"){
        if (instructions.size() <= 1){
            cout << "please use proper command, recommanded command: \"modify <movie_title>\"" << endl;
            return;
        }
        string movTitle = "";
        for (int i = 1; i < instructions.size(); i++) {
            movTitle += instructions[i];
            if (i != instructions.size() - 1 ) { // check to see if not last in vector
                movTitle += " ";    
            }
        }
        db.updateEntry(movTitle);
    }

    // add collection and takes multiple
    // parameters see "man" for syntax
    else if(instruction == "add"){
        if(instructions.size() > 1){
            if(instructions[1] == "-m"){
                if (instructions.size() != 2){
                    cout << "please use proper command, recommanded command: \"add -m\"" << endl;
                    return;
                }  
                db.addDocumentManually();
            }
            else if(instructions[1] != "-m"){
                if (instructions.size() != 2){
                    cout << "please use proper command, recommanded command: \"add <name>\"" << endl;
                    return;
                }
                string cltName = instructions[1];
                db.addCollection(cltName);
            }
        }else{
            cout << "please use proper command, recommanded command: \"add <name> or add -m\"" << endl;
            return;
        }
    }  

    // updates current collection
    // pointer for console
    else if(instruction == "use"){
        if (instructions.size() != 2){
            cout << "please use proper command, recommanded command: \"use <name>\"" << endl;
            return;
        }
        string cltName = instructions[1];   

        //update current collection pointer
        db.useCollection(cltName);
    }

    // delete data and takes multiple parameters
    // for collections and docs, see "man"
    else if(instruction == "rm"){
        if(instructions.size() < 3){
            string cltName = instructions[1];
            if(db.deleteCollectionByName(cltName)){
                cout << "Collection " << cltName << " deleted.\n";
            }
            else{
                cout << "Deletion unsuccessful: can't delete current collection.\n";
            }
        }
        else if(instructions.size() == 3){
            string cltName = instructions[1];
            string docName = instructions[2];
            //db.deleteDocManual(string cltName, string docName);
        }else{
            cout << "please use proper command, recommanded command: \"rm <name> or rm <name> <document_name>\"" << endl;
            return;
        }
    }    
    else if(instruction == "menu"){
        if (instructions.size() != 1){
            cout << "please use proper command, recommanded command: \"man\"" << endl;
            return;
        }
        messageDisplayer();  
    }
    else if(instruction == "enter"){
        
    }
    else if(instruction == "view"){
        if (instructions.size() != 1){
            cout << "please use proper command, recommanded command: \"view\"" << endl;
            return;
        }
        db.printSingleClt(db.getCurrentClt_name());        
    }
    else if(instruction == "exit"){
        if (instructions.size() != 1){
            cout << "please use proper command, recommanded command: \"exit\"" << endl;
            return;
        }
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
    Filter filter(db);
    
    string user_input;
    vector<string> userInstruct;
    
    
    messageDisplayer();

    

    while(1){

        //consoleDisplay();

        // added this to imitate terminal input
        cout << ">>> ";
        getline(cin,user_input);

        // parse user input and return in vector or strings
        if(!user_input.empty()){
            
            userInstruct = parseUserInput(user_input);
        
            // pass parsed vector to helper 
            // function to call db functions
            userInstruction(filter, db, userInstruct);
        }
        else if(user_input.empty()){
            
            cout << "input not valid!\n\n";
        }

        

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
