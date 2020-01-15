#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

class hash
{
    private:
        std::string in_;
        std::string fixedin_;
        std::string out_;

    public:
        std::vector<int> values = {};
        hash()
        {
            in_ = "";
            fixedin_ = "";
            out_ = "";
        }
        hash( std::string input )
        {
            in_ = input;
            fixedin_ = "";
            out_ = "";
        }

    void setIn( std::string &input ) { in_ = input; }
    void setFixedIn( std::string &fixed) { fixedin_ = fixed; }
    void setOut( std::string &output) { out_ = output; }
    std::string const getIn () { return in_; }
    std::string const getFixedIn () { return fixedin_; }
    std::string const getOut () { return out_; }
    ~hash(){};
};

void inUser( hash &key );
void inFile( hash &key, std::string &filename );
void inByLines( std::vector<hash> &diffhash, std::string &filename ); 
void makeTextLonger( hash &key );
void hashAlgorithm( hash &key );
std::string inHexa( unsigned long long int &index );
std::string hashAdd( std::string &basehash, hash &key );
void printHash ( hash &key ); 
void printHash ( std::vector<hash> &diffhash );
void generateFile1();
void generateFile2();

#endif