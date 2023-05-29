#include "filter.hpp"

using namespace std;
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
    cout << left << setw(width) << "*" << left << setw(40) << "access" << left << setw(50) << "check the user's accesslevel" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "db" << left << setw(50) << "display current collection" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "db-all" << left << setw(50) << "display all available collections" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "import -<format> <collection> <file>" << left << setw(50) << "import data file into collection" << right << setw(9) << "*" << endl; //added this to import .csv/JSON files into specified collection
    cout << left << setw(width) << "*" << left << setw(40) << "export <collection>" << left << setw(50) << "export collection" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "print -<flag> <collection>" << left << setw(50) << "print all movie documents of selected collection" << right << setw(9) << "*" << endl;        //added this to print data
    cout << left << setw(width) << "*" << left << setw(40) << "add <name>" << left << setw(50) << "add new collection" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "use <name>" << left << setw(50) << "switch to another collection" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "filter" << left << setw(50) << "filter menu" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "element <index>" << left << setw(50) << "display an element of the current collection" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "modify <collection> <movie_title>" << left << setw(50) << "edit movie data in current collection" << right << setw(9) << "*" << endl;
    cout << left << setw(width) << "*" << left << setw(40) << "rm <collection> <move_title>" << left << setw(50) << "remove existing collection/movie" << right << setw(9) << "*" << endl;
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
void userInstruction(Filter& filter, Database& db, vector<string>& instructions, int accesslevel){

    string instruction = instructions[0];

    if(instruction == "access"){
        if(instructions.size() != 1){
            cout << "please use proper command, recommended command: \"access\"" << endl;
            return;
        }
        string user = "";
        if (accesslevel == 0){
            user = "admin";
        }else{
            user = "developer";
        }
        cout << "current access level: " << accesslevel << ", equivalent as: " << user << endl;
    }

    if(instruction == "print"){
      if(instructions[1] == "-main"){
      db.printMainDB();
      }
    }

    //output current database
    if(instruction == "db"){
        if (instructions.size() != 1){
            cout << "please use proper command, recommended command: \"db\"" << endl;
            return;
        }
        db.printCurrentCltName();
    }
    
    //prints list of all collections
    else if(instruction == "db-all"){
        if (instructions.size() != 1){
            cout << "please use proper command, recommended command: \"db-all\"" << endl;
            return;
        }
        db.dbAll();
    }
    
    // imports data from file and takes three parameters
    else if(instruction == "import"){
        if (instructions.size() != 4){
            cout << "please use proper command, recommended command: \"import -<format> <collection> <file>\"" << endl;
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
            cout << "please use proper command, recommended command: \"export <collection>\"" << endl;
            return;
        }
        string cltName = instructions[1];

        db.exportCSV(cltName);
    }
    
    else if(instruction == "filter"){

        filter.filterMain();
        messageDisplayer();
       
    }
    
    else if(instruction == "element"){
        
    }

    // prints data and takes multiple 
    // parameters see "man" for syntax
    else if(instruction == "print"){
        if (instructions.size() < 3){
            cout << "please use proper command, recommended command: \"print -<flag> <collection>\"" << endl;
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
        if (instructions.size() <= 2) {
            cout << "please use proper command, recommanded command: \"modify <collection> <movie_title>\"" << endl;

            return;
        }
        string movTitle = "";
        for (int i = 2; i < instructions.size(); i++) {
            movTitle += instructions[i];
            if (i != instructions.size() - 1 ) { // check to see if not last in vector
                movTitle += " ";    
            }
        }

        db.updateEntry(instructions[1], movTitle);
    }

    // add collection and takes multiple
    // parameters see "man" for syntax
    else if(instruction == "add"){
        if(instructions.size() > 1){
            if(instructions[1] == "-m"){
                if (instructions.size() != 2){
                    cout << "please use proper command, recommended command: \"add -m\"" << endl;
                    return;
                }  
                db.addDocumentManually();
            }
            else if(instructions[1] != "-m"){
                if (instructions.size() != 2){
                    cout << "please use proper command, recommended command: \"add <name>\"" << endl;
                    return;
                }
                string cltName = instructions[1];
                db.addCollection(cltName);
            }
        }else{
            cout << "please use proper command, recommended command: \"add <name> or add -m\"" << endl;
            return;
        }
    }  

    // updates current collection
    // pointer for console
    else if(instruction == "use"){
        if (instructions.size() != 2){
            cout << "please use proper command, recommended command: \"use <name>\"" << endl;
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
            if(cltName == "mainDB"){
                cout << "cannot remove embedded main collection mainDB" << endl;
            }else if(db.deleteCollectionByName(cltName)){
                cout << "Collection " << cltName << " deleted.\n";
            }
            else{
                cout << "Deletion unsuccessful: can't delete current or non-existing collection.\n";
            }
        }
        else if(instructions.size() >= 3){
            string cltName = instructions[1];
            string movTitle = "";
            for (int i = 2; i < instructions.size(); i++) {
                movTitle += instructions[i];
                if (i != instructions.size() - 1 ) { // check to see if not last in vector
                    movTitle += " ";    
                }
            }
            db.deleteDocumentManual(cltName, movTitle);

        }else{
            cout << "please use proper command, recommended command: \"rm <name> or rm <name> <document_name>\"" << endl;
            return;
        }
    }    
    else if(instruction == "menu"){
        if (instructions.size() != 1){
            cout << "please use proper command, recommended command: \"man\"" << endl;
            return;
        }
        messageDisplayer();  
    }
    else if(instruction == "enter"){
        
    }
    else if(instruction == "view"){
        if (instructions.size() != 1){
            cout << "please use proper command, recommended command: \"view\"" << endl;
            return;
        }
        db.printSingleClt(db.getCurrentClt_name());      
        //db.printSingleClt("mainDB");
    }
    else if(instruction == "exit"){
        if (instructions.size() != 1){
            cout << "please use proper command, recommended command: \"exit\"" << endl;
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

//reference: https://www.geeksforgeeks.org/processing-strings-using-stdistringstream/
bool checkvalidation(const string& input_username, const string& input_password) {
    ifstream file("login.csv");
    if (file.is_open()) {
        string line;
        while(getline(file, line)) {
            istringstream ss(line);
            string file_username;
            string file_password;
            ss >> file_username >> file_password;
            if(file_username == input_username && file_password == input_password){
                return true;
            }
        }
    }
    return false;
}

int login(){
    bool loggedin = false;
    while(loggedin == 0){
        cout << "print \"log\" to login to the system, else to exit the system" << endl;
        cout << ">>> ";
        string userInput;
        getline(cin, userInput);
        if (userInput == "log"){
            cout << "please enter the username: " << endl;
            cout << ">>> ";
            string input_username;
            getline(cin, input_username);
            cout << "please enter the password: " << endl;
            cout << ">>> ";
            string input_password;
            getline(cin, input_password);
            if(checkvalidation(input_username, input_password)){
                loggedin = 1;
                if (input_username == "admin"){
                    return 0;
                }else{
                    return 1;
                }
            }else{
                cout << "invalid username or password" << endl << endl;
            }
        }else{
            cout << "you have successfully exited the system" << endl;
            exit(1);
        }
    }
    return 2;
}

int main(){

    int accesslevel;
    accesslevel = login();    
    /*
    if (accesslevel == 0){
        cout << "current accesslevel is 0, logged in as admin." << endl;
    }else if (accesslevel == 2){
        cout << "something went wrong" << endl;
    }else{
        cout << "You have successfully logged in as developer." << endl;
    }*/

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
            userInstruction(filter, db, userInstruct, accesslevel);
        }
        else if(user_input.empty()){
            
            cout << "input not valid!\n\n";
        }
    }

    return 0;
}
