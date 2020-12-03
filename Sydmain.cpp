//
//  main.cpp
//  Proj3
//
//  Created by Sydney on 12/3/20.
//  Copyright © 2020 Sydney. All rights reserved.
//

#include <iostream>
#include <queue>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ctype.h>
using namespace std;

class Title
{
private:
    // These variables are the column headers in the data set from title.basics.tsv.gz (https://www.imdb.com/interfaces/)
        // the type/format of the title(e.g.movie, short, tvseries, tvepisode, video, etc)
    string titleType;
    // the more popular title / the title used by the filmmakers on promotional materials at the point of release
    string primaryTitle;
    // original title, in the original language
    string originalTitle;
    // 0: non-adult title; 1: adult title
    bool isAdult;
    // represents the release year of a title.In the case of TV Series, it is the series start year
    int startYear;
    // TV Series end year.‘\N’ for all other title types
    int endYear;
    // primary runtime of the title, in minutes
    int minutes;
    // includes up to three genres associated with the title
    string genre[]; // I'm gonna look into this one because some titles have varying number of genres... I think a string array works

public:
    Title();
    // alphanumeric unique identifier of the title
    string titleID;

    Title(string titleID, string titleType, string primaryTitle, string originalTitle,
        bool isAdult, int startYear, int endYear, int minutes, string genre[]);
};

Title::Title()
{
    // default constructor
}

Title::Title(string titleID, string titleType, string primaryTitle, string originalTitle,
    bool isAdult, int startYear, int endYear, int minutes, string genre[])
{
    // constructor
}

class Node {
    public:
        Title t;
        Node *left;
        Node *right;
        int height;
        int bf;
        Node() : t(), left(nullptr), right(nullptr), height(0) {}
        Node(Title _t) : t(_t), left(nullptr), right(nullptr) {}
        Node(Title _t, Node *left, Node *right) : t(_t), left(left), right(right) {}
        
};

int getHeight(Node* root)
{
    if(root == NULL)
    {
        return 0;
    }
    return 1+(max(getHeight(root -> right), getHeight(root->left))); // this was inspired by
    //the line above was created with help from reading this GeeksForGeeks article.
    //https://www.geeksforgeeks.org/how-to-determine-if-a-binary-tree-is-balanced/#:~:text=To%20check%20if%20a%20tree,are%20balanced%2C%20otherwise%20return%20false.
}

int getBalanceFactor(Node* node)
{
    //balance factor is left root height - right root height
    if(node == NULL)
    {
        return 0;
    }
    int bf = getHeight(node->left) - getHeight(node->right);
    return bf;
}

//Rotations

//The logic behind this was provided in Lecture 4C
Node* rotateLeft(Node *node)
{
    Node* temp;
    temp = node -> right;
    node -> right = temp -> left;
    temp->left = node;
    return temp;

}

//The logic behind this was provided in Lecture 4C
Node* rotateRight(Node *node)
{
    Node* temp;
    temp = node -> left;
    node -> left = temp -> right;
    temp -> right = node;
    return temp;

}

//The logic behind this was provided in Lecture 4C
Node* rotateLeftRight(Node *node)
{
    Node* temp = node -> left;
    node-> left = rotateLeft(temp);
    return rotateRight(node);

}

//The logic behind this was provided in Lecture 4C
Node* rotateRightLeft(Node *node)
{
    
    Node* temp = node -> right;
    node-> right = rotateRight(temp);
    return rotateLeft(node);
}

// Main functions:

//The base logic behind this was provided in Lecture 3D
Node* insert(Node* root, Title tt)
{
    // if root is null, the recursion is done and we can return
    if(root == NULL)
    {
        cout <<"successful" << endl;
        return new Node(tt);
    }
    //check if node needs to go in left subtree
    if((tt.titleID) < root->t.titleID){
        root->left = insert(root->left, tt);
          
    }
    // check if node needs to go in right subtree
    else if((tt.titleID) > root->t.titleID){
        root->right = insert(root->right, tt);
          
    }
    //check if node is already in the tree
    else if((tt.titleID) == root->t.titleID){
        cout << "unsuccessful"<< endl;
        return root;
    }
    
    int bf = getBalanceFactor(root);
    
    // The Rotation algorithm was implemented after reading GeeksForGeeks Article:
    // https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
    // the second part of the If statements specifically were inspired by this code.

    
    //Left Right Rotation
    if(bf > 1 && tt.titleID > root -> left ->t.titleID)
    {
        return rotateLeftRight(root);
    }
    //Right Right Rotation
    if(bf < -1 && tt.titleID > root -> right ->t.titleID)
    {
        return rotateLeft(root);
    }
    //Right Left Rotation
    if(bf < -1 && tt.titleID < root -> right ->t.titleID)
    {
        return rotateRightLeft(root);
    }
    //Left Left Rotation
    // if the balance factor is more than 1 and the ID needs to go in the
    if(bf > 1 && tt.titleID < root -> left ->t.titleID)
    {
        return rotateRight(root);
    }
    
    return root;
}

//i wrote this for proj 1 but i thought this could be used to find the movie we end up looking for?
void select(Node* root, string id)
{
    bool foundName = false;
    //check if root is null
    if(root == NULL)
    {
        cout << "unsuccessful" <<endl;
        foundName=true;
    }
    //check to see where in tree
    while(foundName==false)
    {
        if(root == NULL)
        {
            cout << "unsuccessful" <<endl;
            foundName=true;
        }
        if((root->t.titleID).compare(id) ==0)
        {
            cout << root->t.titleID << endl;
            foundName=true;
        }
        else if(id < root->t.titleID)
        {
            if(root->left != NULL)
            {
                root = root->left;
            }
            else{
                cout << "unsuccessful" <<endl;
                foundName=true;
            }
        }
        else if(id > root->t.titleID)
        {
            if(root->right != NULL)
            {
                root = root->right;
            }
            else{
                cout << "unsuccessful" <<endl;
                foundName=true;
            }
        }
    }
}



int main() {
    // insert code here...
    cout << "Hello, World!\n";
    
    
    return 0;
}
