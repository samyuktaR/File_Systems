/*
Author: Samyukta Ramkumar

Date: 02/18/2024

Description: This is the main file of the stupid.os project. This project is designed to manage a file system.
			 It is a prototype that demonstrates how to link together file chunks to store files on the hard drive
			 It uses linked lists, queues and arrays to perform arious tasks as requested by the user.
			 The user has the option of adding, deleting, reading, displaying, or findind a file by its name.
			 The program taks in the file name and the file contents as input and follows the above functions depending on the user's needs.
*/

//This is where your main() and major interface logic should be
//Main File

#include <iostream>
#include <cstring> //C string manipulation library
#include <string>
#include <fstream> //File stream library
#include <sstream>
#include <limits>
#include <iomanip> //Input output manipulator library
#include "FileSystem_ramkumar.h"

int main(int argc, char* argv[]) {
    int driveSize = -1; //Initialize drive size
    std::string filename = ""; //Initialize file name
    int width = 30; //Output formatting width
    int width2 = 57;

    //Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-s") == 0) { //Check if argument if for drive size
            if (i + 1 < argc) {
                driveSize = std::stoi(argv[i + 1]); //Get drive size from command line
            } else {
                std::cout << "Invalid command line arguments." << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-f") == 0) { //Check if argument is for file name
            if (i + 1 < argc) {
                filename = argv[i + 1]; //Get file name from command line
            } else {
                std::cout << "Invalid command line arguments." << std::endl;
                return 1;
            }
        }
    }

    if (driveSize == -1) { //If drive size is not provided as command line argument
        std::cout << "Please provide the size of the simulated hard drive: " << std::endl;
        std::cin >> driveSize; //Take in drive size as user input
    }

    //Create a FileManager object with the specified hard drive size
    FileManager fileManager(driveSize);

    //Load initial state of the hard drive from file, if provided
    if (!filename.empty()) { //If file name is provided
    	std::string filename;
        std::ifstream inputFile(filename); //Open file
        if (!inputFile) { //Check whether opening the file failed
            return 1;
        }

        std::string line;
        while (std::getline(inputFile, line)) { //Read each line in the file
            size_t pos = line.find(":"); //Find the position of ":" delimiter
            if (pos != std::string::npos) { //Check whether delimiter was found
                std::string name = line.substr(0, pos); //Extract file name
                std::string contents = line.substr(pos + 1); //Extract file contents
                fileManager.addFile(name, contents);
            }
        }
    }

    //Main menu loop
    int choice;
    std::string inputFilename, inputContents;
    do {
        //Display menu options
        std::cout << "Menu:\n"
                  << "1 - Show files on hard drive\n"
                  << "2 - Add a file\n"
                  << "3 - Delete a file\n"
                  << "4 - Output a file\n"
                  << "0 - Exit simulation\n";
        std::cin >> choice; //Take in user's choice input

        switch (choice) {
            case 1: {
                //Display files on hard drive
                std::vector<std::string> filenames = fileManager.getFileNames();
                std::cout << "Filename                                          size\n";
                for (const auto& filename : filenames) {
                	int filenameLength = filename.length();
                	int sizeWidth = 7;
                	int totalWidth = filenameLength + sizeWidth;
                	int spacing = width2 - totalWidth;
                	std::cout << filename << std::right << std::setw(spacing) << fileManager.readFile(filename).size() << " blk" << std::endl;
                }
                break;
            }
            case 2: {
            	//Add a file
            	std::cout << "Enter filename: ";
            	std::cin >> inputFilename;
            	std::cout << "Enter content string: ";
            	std::cin >> inputContents; //Clear the input buffer
            	fileManager.addFile(inputFilename, inputContents);
            	break;
            }


            case 3: {
                //Delete a file
                std::cout << "Enter filename: ";
                std::cin >> inputFilename;
                fileManager.deleteFile(inputFilename);
                break;
            }
            case 4: {
                //Output a file
                std::cout << "Enter filename: ";
                std::cin >> inputFilename;
                std::string contents = fileManager.readFile(inputFilename);
                if(!contents.empty()) {
                	std::cout << "Filename                      Contents\n";
                	std::cout << std::setw(width) << std::left << inputFilename << contents << std::endl;
                } else {
                	std::cout << "File Not Found." << std::endl;
                }
                break;
            }
            case 0:
                //Exit the simulation
                break;
            default:
                std::cout << "\nInvalid choice. Please try again." << std::endl;
        }

    } while (choice != 0);

    return 0;
}
