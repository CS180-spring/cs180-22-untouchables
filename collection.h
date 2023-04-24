#include <iostream>

using namespace std;

//chatgpt generated sample document structure to store document in database
struct Movie_Doc {
    string series_title;
    int released_year;
    int runtime; //in minutes
    string genre;
    double IMDB_rating; //specific for IMDB movie data, scale 10
    string overview;
    int meta_score; //scale 100
    string Director;
    string Star; //star 1 only
    //vector <string> stars; //keep all stars
};

class Collection
{
private:
    /* data */
public:
    Collection(/* args */);
    ~Collection();
    
    void count();           //return number of documents in a collection
    void deleteOne();       //deletes a single document in a collection
    void deleteMany();      //deletes multiple documents in a collection
    void drop();            //removes specific collection from database
    void insertOne();       //inserts a new document into a collection
    void insert();          //
    void insertMany();      //inserts multiple documents into a collection
    void remove();          //deletes documents from a collection
    void updateOne();       //updates a single document in a collection
    void updateMany();      //updates multiple documents in a collection

    void totalSize();       //report total size of collection and includes size of all documents and indexes

    

};

Collection::Collection(/* args */)
{
}

Collection::~Collection()
{
}

