#include <iostream>
#include <string>
#include <vector> //Used for list, serves as foundation of data structure to be sorted. 
#include <fstream>
#include <sstream> //Used for file path
#include <algorithm> //Used for unique() to facilitate removal of duplicates in an ordered list
#include <ShlObj.h> //Used for SHGetKnownFolderPath()

class Sorter {

public:
	int sortingMethod;
	std::string fileName;
	bool byWord;

	Sorter(std::string name, int method, bool word) {
		Sorter::fileName = name;
		Sorter::sortingMethod = method;
		Sorter::byWord = word;
	}

	//Driver
	void run() {
		char response;
		std::string newFileName = fileName + "1";
		std::cout << "Loading file... please wait." << std::endl;
		openList();

		std::cout << "Sorting file..." << std::endl;
		quickSort(&list, 0, int(list.size()) - 1);
		std::cout << "Would you like to remove duplicates? [Y / N ]" << std::endl;
		while (!(std::cin >> response) && (response != 'Y' || response != 'N')) {
			std::cin.clear();
			//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input.  Try again: ";
		}

		if (response == 'Y') {
			removeDuplicates();
		}

		std::cout << "Saving to new file..." << std::endl;
		saveList(newFileName);
		std::cout << std::endl << "Operations complete! Check your desktop for sorted file. Thank you for using Bailey's file sorter!" << std::endl;
	}
private:
	std::vector<std::string> list; //List holds each line from the textFile. 
	std::wstringstream filePath;  //Used for storing filePath to desktop, use.rdbuf() or .str() for access.

	//Opens provided file given fileName and populates list with the lines of the file. 
	void openList() {
		std::string current;
		wchar_t* desktop = 0; //Pointer of type wide char to the desktop filePath

		SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &desktop); //Retrieves desktop file path

		std::wstring wideFileName = std::wstring(fileName.begin(), fileName.end());

		filePath << desktop << "\\";
		filePath << const_cast<wchar_t*>(wideFileName.c_str());

		std::ifstream myFile;

		myFile.open(filePath.str());

		//CoTaskMemFree(static_cast<void*>(desktop)); //Prevents memory leak, frees as specified by SHGetKnownFolderPath()

		if (myFile.is_open()) {
			if (byWord) {
				while (myFile >> current) {
					if (current == "") { continue; }
					list.push_back(current);
				}
			}
			else {
				while (std::getline(myFile, current)) {
					if (current == "") { continue; }
					list.push_back(current);
				}
			}
			myFile.close();
		}
		else {
			std::cout << "File could not be found. Please ensure that the file name is correct and the file is on the desktop." << std::endl;
		}
	}

	void quickSort(std::vector<std::string>* vec, int low, int high) {
		if (low < high)
		{
			std::cout << "Yes" << std::endl; 
			int pivot = partition(&list, low, high); //The pivot is now in the right spot.

			quickSort(&list, low, pivot - 1);  // Before pi
			quickSort(&list, pivot + 1, high); // After pi
		}
	}

	void swap(std::string* a, std::string* b) {
		std::string temp = *a;
		*a = *b;
		*b = temp;
	}

	void removeDuplicates() {
		list.erase(unique(list.begin(), list.end()), list.end());
	}

	//Takes the last element as pivot and places all smaller elements to its left and all larger to its right. 
	int partition(std::vector<std::string>* vec, int low, int high) {
		std::string pivot = (*vec)[high];
		int i = low - 1;

		for (int j = low; j <= high - 1; j++) {
			int checkLength = ((*vec)[j].size() <= pivot.size()) ? int((*vec)[j].size()) : int(pivot.size());
			switch (sortingMethod) {
			case 1: //Alphabetic swap
				if ((*vec)[j].compare(pivot) <= 0) {
					i++;
					swap(&(*vec)[i], &(*vec)[j]);
				}
				break;
			case 2: //Length swap
				if ((*vec)[j].size() <= pivot.size()) {
					i++;
					swap(&(*vec)[i], &(*vec)[j]);
				}
				break;
			default:
				break;
			}
		}
		swap(&(*vec)[i + 1], &(*vec)[high]);
		return i + 1;
	}

	//Saves the final, sorted list to a text file on the user's desktop. The name of the file is "[fileName]1.txt".
	void saveList(std::string newFileName) {

		std::string current;
		int posOfExtension;
		for (int i = 0; i < filePath.str().size(); i++) {
			if (filePath.str()[i] == '.') {
				posOfExtension = i;
				break;
			}
		}

		std::wstring newFilePath = std::wstring(filePath.str()); //Remove '.txt' extension
		newFilePath.erase(newFilePath.begin() + posOfExtension, newFilePath.end());
		newFilePath.append(L"1.txt");
		std::ofstream myFile;

		myFile.open(newFilePath);
		if (myFile.is_open()) {
			for (int i = 0; i < int(list.size()); i++) {
				myFile << list[i] << std::endl;
			}
			myFile.close();
		}
		else {
			std::cout << "File could not be found. Please ensure that the file name is correct and the file is on the desktop." << std::endl;
		}
	}

	//For debugging purposes, allows ability to view elements of vector at any stage of the code. 
	void printVector(std::vector<std::string> vec) {
		for (int i = 0; i < int(vec.size()); i++) {
			std::cout << vec[i] << std::endl;
		}
	}
};