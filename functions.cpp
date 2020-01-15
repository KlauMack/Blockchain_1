#include "hash.h"

// User input function
void inUser( hash &key )
{
    std::cout << "Text: \n";
    std::string text ="";
    std::cin >> text;

    key.setIn(text);
}

// Reading from file function
void inFile( hash &key, std::string &filename )
{
    std::ifstream infile(filename);

    if(infile.fail())
    {
        throw std::exception();
    }

    std::string text((std::istreambuf_iterator<char>(infile) ), (std::istreambuf_iterator<char>()));
    key.setIn(text);
    infile.close();
}

// Reading each line from file function
void inByLines( std::vector<hash> &diffhash, std::string &filename )
{
    std::ifstream infile(filename);
    std::string tempor;

    if(infile.fail())
    {
        throw std::exception();
    }

    while(!infile.eof())
    {
        std::getline(infile,tempor);
        diffhash.push_back(tempor);
    }

    diffhash.shrink_to_fit();
    infile.close();
}

// To make text longer (for 64 fixed size hash) function
void makeTextLonger( hash &key )
{
    if(key.getIn().length() < 60)
    {
        std::string filler (60, '!');
        std::string copy = key.getIn();
        filler.replace(0, copy.length(), copy);
        key.setFixedIn(filler);
    }
    else
    {
        std::string copy = key.getIn();
        key.setFixedIn(copy);
    }
}

// Hash algorithm function
void hashAlgorithm( hash &key )
{   
    std::string copy = key.getFixedIn();
    std::wstring_convert<std::codecvt_utf8_utf16<char32_t>,char32_t> converter;
    std::u32string input32 = converter.from_bytes(copy);

    unsigned long long int sum[5] = {1};
    int part = 1;
    int index = 1;
    for(char32_t &character : input32)
    {
        if(part == 1)
        {
            sum[0] = (index + index) * sum[0] + character;
        }

        if(part == 2)
        {
            sum[1] = (index + index) * sum[1] + character;
        }

        if(part == 3)
        {
            sum[2] = (index + index) * sum[2] + character;
        }

        if(part == 4)
        {
            sum[3] = (index + index) * sum[3] + character;
            part = 0;
        }

        part++;
        index++;
    }

    std::string hexa[5] = {""};

    for(int i = 0; i < 4; i++)
    {
        hexa[i] = inHexa(sum[i]);

        while(hexa[i].length() < 16)
        {
            hexa[i] += "0";
        }
    }

    std::string basehash = hexa[0] + hexa[1] + hexa[2] + hexa[3];
    std::string hashshuffle = hashShuffle(basehash, key);
    key.setOut(hashshuffle);
}

// To turn text into hexadecimal function
std::string inHexa( unsigned long long int &index )
{
    std::stringstream stream;
    stream << std::hex << index;
    std::string output(stream.str());
    return output;
}

// To make hash more random function
std::string hashShuffle( std::string &basehash, hash &key )
{
    std::string copy = key.getIn();
    std::wstring_convert<std::codecvt_utf8_utf16<char32_t>,char32_t> converter;
    std::u32string input32 = converter.from_bytes(copy);

    int i = 1;
    int sum = 0;

    for(char32_t &character : input32)
    {
        sum = sum + character * i;
        i++;
    }

    unsigned seed = sum;

    std::shuffle(basehash.begin(), basehash.end(),std::default_random_engine(seed));
    return basehash;
}

// To print hash function
void printHash ( hash &key )
{
    std::cout << key.getOut() << "\n";
}

// To print vector of hashs function
void printHash ( std::vector<hash> &diffhash )
{
    std::ofstream outfile ("result.txt");

    for(unsigned int i = 0; i < diffhash.size(); i++)
    {
        outfile << diffhash[i].getOut() << "\n";
    }

    outfile.close();
}

// To generate file with different text function
void generateFile1()
{
    std::ofstream outfile ("test6.txt");
    std::string alphabet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
    std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, 51);

    for(int i = 0; i < 1000000; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            outfile << alphabet[uni(rng)];
        }
        outfile << "\r\n";
    }
    outfile.close();
}

// To generate file so only 1 letter is different between pairs of lines function
void generateFile2()
{
    std::ofstream outfile ("test7.txt");
    std::string alphabet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
    std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, 51);
    std::uniform_int_distribution<int> uni1(0, 4);

    std::string tempor = "";

    for(int i = 0; i < 500000; i++)
    {
        tempor = "";

        for(int j = 0; j < 5; j++)
        {
            tempor += alphabet[uni(rng)];
        }

        outfile << tempor;
        outfile << "\r\n";
        tempor[uni1(rng)] = '!';
        outfile << tempor;
        outfile << "\r\n";
    }

    outfile.close();
}