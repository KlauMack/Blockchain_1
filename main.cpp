#include "hash.h"


int main()
{

	generateFile1();
	generateFile2();

    std::string tempor = "";

	std::cout << "To input your own text type 0, to read from file type 1: \n";
	std::cin >> tempor;

	while (tempor != "0" && tempor != "1")
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Please type 0 to input your own text or type 1 to read from file: \n";
		std::cin >> tempor;
	}

    if(tempor == "0")
    {
		hash key;
        inUser( key );
		makeTextLonger( key );

		auto start = std::chrono::high_resolution_clock::now();

		hashAlgorithm( key );

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		std::cout << "Algorithm took " << std::fixed << std::setprecision(10) << diff.count() << " second(s) to complete.\n";
		printHash( key );
    }
    else
    {
        std::string filename;
		std::cout << "To hash the whole file type 0, to hash each file line type 1 \n";
		std::cin >> tempor;
		if( tempor == "0" )
        {
			std::cout << "Type the file name. Example: file1.txt\n";
			std::cin >> filename;
			hash key;

        	try
            {
           		inFile( key, filename);   
        	}
        	catch (std::exception &e)
			{
				std::cout << "Unable to open file. \n";
				return 0;
			}

			makeTextLonger( key );

			auto start = std::chrono::high_resolution_clock::now();

			hashAlgorithm( key );

			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff = end - start;
			std::cout << "Algorithm took " << std::fixed << std::setprecision(10) << diff.count() << " second(s) to complete.\n";
			printHash( key );

		}
		else
        {
			std::cout << "Type the file name. Example: file1.txt\n";
			std::cin >> filename;
			std::vector<hash> diffhash = {};

        	try
            {
           		inByLines( diffhash, filename );
        	}
        	catch (std::exception &e)
			{
				std::cout << "Unable to open file. \n";
				return 0;
			}

			std::chrono::duration<double> tsum;
			for(unsigned int i = 0; i < diffhash.size(); i++)
            {
				makeTextLonger( diffhash[i] );
				auto start = std::chrono::high_resolution_clock::now();

				hashAlgorithm( diffhash[i] );

				auto end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> diff = end - start;
				tsum = tsum + diff;
			}
			printHash( diffhash );
			std::cout << "Algorithm took " << std::fixed << std::setprecision(10) << tsum.count() << " second(s) to complete.\n";
		}
    }

	return 0;
}