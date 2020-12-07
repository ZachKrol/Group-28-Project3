/*
Team 28
Team Members - Elizabeth Gekhtman, Sydney Opyrchal, Zachary Krol
Project Title - Buzzfeed Quiz Knockoff: Movie Recommender
*/

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <iterator>
#include <algorithm>
#include <ctype.h>
#include <chrono>
using namespace std;
using namespace std::chrono; // for the timer

// Title is a broad term that includes movies, shorts, tv series, video etc.
struct Title
{
    // These variables are the column headers in the data set from title.basics.tsv.gz (https://www.imdb.com/interfaces/)

    // alphanumeric unique identifier of the title
    int titleID;
    // the type/format of the title(e.g.movie, short, tvseries, tvepisode, video, etc)
    string titleType;
    // the more popular title / the title used by the filmmakers on promotional materials at the point of release
    string primaryTitle;
    // original title, in the original language
    string originalTitle;
    // 0: non-adult title; 1: adult title
    int isAdult;
    // represents the release year of a title.In the case of TV Series, it is the series start year
    int startYear;
    // TV Series end year.‘\N’ for all other title types
    int endYear;
    // primary runtime of the title, in minutes
    int minutes;
    // includes up to three genres associated with the title
    string genre;

    Title();
    Title(int titleID, string titleType, string primaryTitle, string originalTitle,
        int isAdult, int startYear, int endYear, int minutes, string genre);
};

Title::Title()
{
    titleID = 0;
    titleType = "Not Initialized";
    primaryTitle = "Not Initialized";
    originalTitle = "Not Initialized";
    isAdult = 0;
    startYear = 0;
    endYear = 0;
    minutes = 0;
    genre = "";
}

Title::Title(int titleID, string titleType, string primaryTitle, string originalTitle,
    int isAdult, int startYear, int endYear, int minutes, string genre)
{
    this->titleID = titleID;
    this->titleType = titleType;
    this->primaryTitle = primaryTitle;
    this->originalTitle = originalTitle;
    this->isAdult = isAdult;
    this->startYear = startYear;
    this->endYear = endYear;
    this->minutes = minutes;
    this->genre = genre;
}

// Load Data function. returns vector of title objects
vector<Title> LoadData()
{
    ifstream data("data.tsv");

    vector<Title> titleObjects;

    if (data.is_open())
    {
        
        string line;
        int counter = 1;

        // pass over first line of headers
        getline(data, line);

        // IMPORTANT: adjust for-loop counter to determine number of rows to read
        int loopCounter = 10000;
        for (int i = 0; i < loopCounter; i++)
        {
            // percent loaded
            int singlePercent = loopCounter / 100;
            int check = i / singlePercent;
            if (check == counter)
            {
                cout << counter << "%" << endl;
                counter++;
            }

            // declare variables to capture data
            string _titleID;
            string _titleType;
            string _primaryTitle;
            string _originalTitle;
            string _isAdult;
            string _startYear;
            string _endYear;
            string _minutes;
            string _genre;

            // clear row of header
            getline(data, line);

            // create stringstream
            istringstream streamFromLine(line);

            // get title characteristics
            getline(streamFromLine, _titleID, '\t');
            getline(streamFromLine, _titleType, '\t');
            getline(streamFromLine, _primaryTitle, '\t');
            getline(streamFromLine, _originalTitle, '\t');
            getline(streamFromLine, _isAdult, '\t');
            getline(streamFromLine, _startYear, '\t');
            getline(streamFromLine, _endYear, '\t');
            getline(streamFromLine, _minutes, '\t');
            getline(streamFromLine, _genre, '\t');

            // filter out bad entries and initialize date into objects
            // also pushback valid rows of data into object vector

            // throw out adult films for this project
            if (stoi(_isAdult) == 1)
                continue;

            // throw out all garbage episode titles
            string episodeCheck = "Episode";
            if (episodeCheck.compare(_primaryTitle.substr(0, 7)) == 0)
                continue;

            // change any value of '/N' that are supposed to be numbers(start date, minutes, etc.) to integer = 0
            // if a string is '/N' we will just leave it
            string nullCheck = "\\N";

            if (_startYear.compare(nullCheck) == 0)
                _startYear = "0";
            if (_endYear.compare(nullCheck) == 0)
                _endYear = "0";
            if (_minutes.compare(nullCheck) == 0)
                _minutes = "0";

            // chop "tt" off _titleID. convert all necessary strings to ints when needed
            _titleID = _titleID.substr(2);
            int titInt = stoi(_titleID);
            int adultInt = stoi(_isAdult);
            int startInt = stoi(_startYear);
            int endInt = stoi(_endYear);
            int minuteInt = stoi(_minutes);

            // initialize title object
            Title t(titInt, _titleType, _primaryTitle, _originalTitle, adultInt, startInt, endInt, minuteInt, _genre);

            // pushback to vector of objects
            titleObjects.push_back(t);
            
        }
        return titleObjects;
    }

    // print data
    // IMPORTANT: COMMENT THIS OUT IF YOU DON'T WANT IT TO PRINT
    /*
    for (auto iter = titleObjects.begin(); iter != titleObjects.end(); ++iter)
    {
        Title temp = *iter;
        cout << temp.titleID << " " << temp.titleType << " " <<  temp.primaryTitle << " " << temp.originalTitle << " " <<
            temp.primaryTitle << " " << temp.isAdult << " " << temp.startYear << " " << temp.endYear << " " <<
            temp.minutes << " " << temp.genre << endl;
    }
    */

    data.close();
    return titleObjects;
}

class Node
{
public:
    Title t;
    Node* left;
    Node* right;
    int height;
    int bf;
    Node() : t(), left(nullptr), right(nullptr), height(0) {}
    Node(Title _t) : t(_t), left(nullptr), right(nullptr) {}
    Node(Title _t, Node* left, Node* right) : t(_t), left(left), right(right) {}

};

int getHeight(Node* root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + (max(getHeight(root->right), getHeight(root->left))); // this was inspired by
    //the line above was created with help from reading this GeeksForGeeks article.
    //https://www.geeksforgeeks.org/how-to-determine-if-a-binary-tree-is-balanced/#:~:text=To%20check%20if%20a%20tree,are%20balanced%2C%20otherwise%20return%20false.
}

int getBalanceFactor(Node* node)
{
    //balance factor is left root height - right root height
    if (node == NULL)
    {
        return 0;
    }
    int bf = getHeight(node->left) - getHeight(node->right);
    return bf;
}

//Rotations

//The logic behind this was provided in Lecture 4C
Node* rotateLeft(Node* node)
{
    Node* temp;
    temp = node->right;
    node->right = temp->left;
    temp->left = node;
    return temp;

}

//The logic behind this was provided in Lecture 4C
Node* rotateRight(Node* node)
{
    Node* temp;
    temp = node->left;
    node->left = temp->right;
    temp->right = node;
    return temp;

}

//The logic behind this was provided in Lecture 4C
Node* rotateLeftRight(Node* node)
{
    Node* temp = node->left;
    node->left = rotateLeft(temp);
    return rotateRight(node);

}

//The logic behind this was provided in Lecture 4C
Node* rotateRightLeft(Node* node)
{

    Node* temp = node->right;
    node->right = rotateRight(temp);
    return rotateLeft(node);
}

// Main functions:

//The base logic behind this was provided in Lecture 3D
Node* insert(Node* root, Title tt)
{
    // if root is null, the recursion is done and we can return
    if (root == NULL)
    {
        //cout << "successful" << endl;
        return new Node(tt);
    }
    //check if node needs to go in left subtree
    if ((tt.titleID) < root->t.titleID)
    {
        root->left = insert(root->left, tt);

    }
    // check if node needs to go in right subtree
    else if ((tt.titleID) > root->t.titleID)
    {
        root->right = insert(root->right, tt);

    }
    //check if node is already in the tree
    else if ((tt.titleID) == root->t.titleID)
    {
        //cout << "unsuccessful" << endl;
        return root;
    }

    int bf = getBalanceFactor(root);

    // The Rotation algorithm was implemented after reading GeeksForGeeks Article:
    // https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
    // the second part of the If statements specifically were inspired by this code.


    //Left Right Rotation
    if (bf > 1 && tt.titleID > root->left->t.titleID)
    {
        return rotateRight(root);
    }
    //Right Right Rotation
    if (bf < -1 && tt.titleID > root->right->t.titleID)
    {
        return rotateLeft(root);
    }
    //Right Left Rotation
    if (bf < -1 && tt.titleID < root->right->t.titleID)
    {
        return rotateLeft(root);
    }
    //Left Left Rotation
    // if the balance factor is more than 1 and the ID needs to go in the
    if (bf > 1 && tt.titleID < root->left->t.titleID)
    {
        return rotateRight(root);
    }

    return root;
}

//i wrote this for proj 1 but i thought this could be used to find the movie we end up looking for?
void select(Node* root, int id)
{
    bool foundName = false;
    //check if root is null
    if (root == NULL)
    {
        cout << "unsuccessful" << endl;
        foundName = true;
    }
    //check to see where in tree
    while (foundName == false)
    {
        if (root == NULL)
        {
            cout << "unsuccessful" << endl;
            foundName = true;
        }
        if (root->t.titleID == id)
        {
            cout << root->t.titleID << endl;
            foundName = true;
        }
        else if (id < root->t.titleID)
        {
            if (root->left != NULL)
            {
                root = root->left;
            }
            else
            {
                cout << "unsuccessful" << endl;
                foundName = true;
            }
        }
        else if (id > root->t.titleID)
        {
            if (root->right != NULL)
            {
                root = root->right;
            }
            else
            {
                cout << "unsuccessful" << endl;
                foundName = true;
            }
        }
    }
}
void inOrder(Node* root)
{
    if(root == NULL){
        return;
    }
    else
    {
    inOrder(root->left);
    cout << root->t.genre <<endl;
    inOrder(root->right);
    }
}

void inOrderTrav(Node* root, vector<Title>& movies, Title tt)
{
    if(root == NULL){
        return;
    }
    else
    {
    inOrderTrav(root->left, movies, tt);
    if(root->t.genre.find(tt.genre) != string::npos)
    {
        movies.push_back(root->t);
    }
    inOrderTrav(root->right, movies, tt);
    }
}


vector<Title> findMovies(Node* root, Title tt)
{
    
    vector<Title> movies;
    cout << "start movies" <<endl;
    if (root == NULL)
    {
        cout <<"this is a problem lol " <<endl;
        return movies;
    }
    while(root!=NULL)
    {
        //cout <<root->t.genre<<endl;
        cout <<"Root year: " << root->t.startYear << " T year: " << tt.startYear<<endl;
        if (root->t.genre.find(tt.genre) != string::npos)
        {
            
            
            if((tt.startYear - root->t.startYear) < 2 && (tt.startYear - root->t.startYear) > 0)
            {
                root = root->right;
                inOrderTrav(root, movies, tt);
                break;
            }
            else if((tt.startYear - root->t.startYear) > -2 && (tt.startYear - root->t.startYear) < 0)
            {
                root = root->left;
                inOrderTrav(root, movies, tt);
                break;
            }
            
            /*movies.push_back(root->t);
            if((root->t.startYear - tt.startYear) <= 0)
            {
                //cout <<"Root dif here: " << root->t.startYear << " "<< tt.startYear<<endl;
                //cout << "ROOT DIF " <<(root->t.startYear - tt.startYear) <<endl;
                root = root->right;
            }
            else if((root->t.startYear - tt.startYear) > 0)
            {
                //cout <<"Root dif here: " << root->t.startYear << " "<< tt.startYear<<endl;
                root = root->left;
                
            }*/
            
        }
        else{
            if((root->t.startYear - tt.startYear) < 0)
            {
                //cout <<"Root dif here: " << root->t.startYear << " "<< tt.startYear<<endl;
                //cout << "ROOT DIF " <<(root->t.startYear - tt.startYear) <<endl;
                root = root->right;
            }
            else if((root->t.startYear - tt.startYear) >= 0)
            {
                //cout <<"Root dif here: " << root->t.startYear << " "<< tt.startYear<<endl;
                root = root->left;
                
            }
        }
        //cout << "vagina" <<endl;
        
    }
    return movies;
    
}

Node* buildAVL(vector<Title> movies, Node* root)
{
    //Node* root = NULL;
    int loopCounter = movies.size();
    int counter = 1;
    for (int i = 0; i < loopCounter; i++)
    {
        // percent loaded
        int singlePercent = loopCounter / 100;
        int check = i / singlePercent;
        if (check == counter)
        {
            cout << counter << "%" << endl;
            counter++;
        }
        root = insert(root, movies[i]);
    }
    return root;
}

string getGenres()
{
    int happySad;
    
    
    
    cout<< "Quiz Time!! (Don't Worry This One's Fun lol)"<<endl;
    cout<<"Question #?: Do you need a good laugh or a good cry tonight?" << endl;
    cout <<"Enter 1 for laugh, 2 for cry" << endl;
    cin >> happySad;
    // here we will either work with happy or sad
    while(happySad!=1 && happySad!=2)
    {
        cout << "excuse me i said 1 or 2" <<endl;
        cin >> happySad;
    }
    if(happySad == 1)
    {
        cout <<"Which are you looking for?" << endl;
        cout << "1. Simple fun" <<endl <<"2. ADRENALINE" << endl <<"3. Mystery" << endl << "4. I said I wanted a good laugh"<< endl;
        cin>> happySad;
        while(happySad != 1 && happySad != 2 && happySad != 3 &&happySad != 4)
        {
            cout << "You're not good with directions smh. Try again pls" << endl;
            cin>> happySad;
        }
        if(happySad == 1)
        {
            return "Animation";
        }
        if(happySad == 2)
        {
            return "Action";
        }
        if(happySad == 3)
        {
            return "Fantasy";
        }
        if(happySad == 4)
        {
            return "Comedy";
        }
    }
    if(happySad == 2)
    {
        cout <<"Which are you looking for?" << endl;
        cout << "1. Love <3" <<endl <<"2. MURDER" << endl <<"3. Historical Info" << endl << "4. Surprise me"<< endl;
        cin>> happySad;
        while(happySad != 1 && happySad != 2 && happySad != 3 &&happySad != 4)
        {
            cout << "You're not good with directions smh. Try again pls" << endl;
            cin>> happySad;
        }
        if(happySad == 1)
        {
            return "Romance";
        }
        if(happySad == 2)
        {
            return "Horror";
        }
        if(happySad == 3)
        {
            return "Documentary";
        }
        if(happySad == 4)
        {
            return "Thriller";
        }
    }
    return "Comedy";
    
    
}

int getYear()
{
    int year;
    cout << "If you could travel to any 20th century decade, when would you visit?" << endl;
    cin>>year;
    return year;
}

int getRuntime()
{
    int time;
    cout << "How much time do you want to invest in this movie (Pls enter in minutes)" << endl;
    cin >> time;
    return time;
}

int main()
{
    // load file title.basics.tsv.gz
    // pushback these objects to a vector
        // IMPORTANT: This is the vector that will be passed by reference into functions that create the Map and AVL structures

    cout << "Loading Movie Data from IMDB Database..." << endl;
    vector<Title> titleObjects = LoadData();
    cout << "Done Loading!" << endl << endl;
    // debugging
    cout << "Lib size " << titleObjects.size() << endl;

    // welcome screen
    cout << "---------------------------------------------------------------------------------------------" << endl << endl;
    cout << "Welcome to our Movie Recommending Quiz!" << endl << endl;
    cout << "We gathered titles (movies, tv-shows, videos, etc.) from the IMDB Database and " << endl;
    cout << "we want to recommend a title selection for you after answering a simple set of questions!" << endl << endl;
    cout << "Press ENTER to begin. . ." << endl;

    cin.ignore();

    // QUIZ LOOP
    int selection = 1;
    while (selection == 1)
    {
        cout << "---------------------------------------------------------------------------------------------" << endl << endl;
        
        cout << "*QUIZ QUESTIONS AND STORING THE ANSWERS WILL GO HERE*" << endl << endl;
            // maybe storing answers in an array(index is question # and value is answer)
            // or map (key is question number, value is answer)
        string genre = getGenres();
        int year = getYear();
        int runTime = getRuntime();

        // choose data structure to use
        cout << "Which data structure do you want to use to store and search for titles?" << endl;
        cout << "1. Map" << endl;
        cout << "2. AVL Tree" << endl;

        int dataChoice;
        while (true)
        {
            // this code prevents infinite loop on invalid char input.
            // inspired from https://stackoverflow.com/questions/21844160/why-does-my-program-have-an-infinite-loop-when-i-enter-in-a-character
            if (!(cin >> dataChoice))
            {
                cin.clear(); // clears the error state
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove the bad input from the buffer
                cout << "Invalid input. Try Again." << endl;
                continue;
            }
            else
            {
                if (dataChoice == 1)
                {
                    // Start Timer (Zach)
                    auto startTime = high_resolution_clock::now();

                    // Map Initialize Function (Elizabeth) <------------------------------------------

                    // Map *Search* Function (Elizabeth) <------------------------------------------
                    
                    // End Timer (Zach)
                    auto stopTime = high_resolution_clock::now();
                    auto timeDuration = duration_cast<seconds>(stopTime - startTime);
                    cout << "Time it took to store and search data using Map: " << timeDuration.count() << " seconds" << endl << endl;

                    break;
                }
                else if (dataChoice == 2)
                {
                    // Start Timer (Zach)
                    auto startTime = high_resolution_clock::now();

                    // AVL Tree Initialize Function (Sydney)
                    Node* root = NULL;
                    cout <<"Excellent choice! " <<endl;
                    root= buildAVL(titleObjects, root);
                    

                    // AVL Tree *Search* Function (Sydney) <------------------------------------------
                    Title t;
                    t.genre = genre;
                    t.minutes = runTime;
                    t.startYear = year;
                    cout << "OG ROOT : " << root->t.titleID<<endl;
                    //inOrder(root);
                    vector<Title> res = findMovies(root, t);
                    cout <<"Number of options: " << res.size() << endl;
                    //debugging stuff
                    cout << "Library size " << titleObjects.size() << endl;
                    
                    // End Timer (Zach)
                    auto stopTime = high_resolution_clock::now();
                    auto timeDuration = duration_cast<seconds>(stopTime - startTime);
                    cout << "Time it took to store and search data using Map: " << timeDuration.count() << " seconds" << endl << endl;
                    

                    break;
                }
                else
                {
                    cout << "Invalid input. Try Again." << endl;
                    continue;
                }
            }
        }

        // output search result
        cout << endl << "The title we have recommended for you is: " << "*REPLACE THIS WITH SEARCH RESULT*" << endl << endl;


        // ask if they want to take quiz again
        cout << "Enter \"1\" to take the quiz again" << endl;
        cin >> selection;
        cout << endl;
    }

    cout << "Enjoy your viewing experience!" << endl;

    return 0;
}
