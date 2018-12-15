#include <iostream>
#include <fstream>
#include "sorter.cpp"

/* NOTE: THIS PROGRAM IS CURRENTLY COMPATIBLE WITH WINDOWS MACHINES RUNNING VISTA AND LATER. */

void getFileName(std::string& fileName) {
	std::cout << "What is the name of your file ?" << std::endl;
	std::cin >> fileName;
}

void pickSortingMethod(int& sortingMethod, bool& byWord) {
	std::string response;

	std::cout << "How would you like to sort this list?" << std::endl;
	std::cout << "\t 1) Alphabetically" << std::endl;
	std::cout << "\t 2) By length" << std::endl;
	while (!(std::cin >> sortingMethod) && sortingMethod < 0 || sortingMethod > 2) {
		std::cin.clear();
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input.  Try again: ";
	}

	std::cout << "Would you like to sort by word or by line? [WORD / LINE]" << std::endl;
	while (!(std::cin >> response) && response != "WORD" && response != "LINE") {
		std::cin.clear();
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input.  Try again: ";
	}
	byWord = (response == "WORD") ? true : false;
}

int main() {
	char response;
	int sortingMethod;
	bool byWord;
	std::string fileName;
	Sorter* sort;

	std::cout << "Welcome to list sorter! This program will sort a text file (using a given line break)." << std::endl;
	getFileName(fileName);

	std::cout << "Your file is named " << fileName << ", is this correct? [ Y / N ]" << std::endl;
	fileName = fileName.append(".txt");

	std::cin >> response;
	while (response != 'Y' && response != 'N') {
		std::cout << "Invalid response, please try again: ";
		std::cin >> response;
	}

	if (response == 'N') {
		getFileName(fileName);
	}

	pickSortingMethod(sortingMethod, byWord);
	sort = new Sorter(fileName, sortingMethod, byWord);
	sort->run();

	return 0;
}
