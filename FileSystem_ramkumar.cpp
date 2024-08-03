//Contains File and FileManager definitions
#include <iostream>
#include <sstream> //string stream library
#include <string>
#include <vector>
#include "FileSystem_ramkumar.h"
#include "LinkedList_ramkumar.hpp"
#include "Queue_ramkumar.hpp"

File::File(std::string filename) : filename(filename) {} //Constructor to take a file name as parameter for the file class

//Get the file name
std::string File::getFileName() {
	return filename;
}

//Get the blocks that the file has taken up as a vector of int values
std::vector<int> File::getFileBlocks() {
	std::vector<int> fileBlocks; //Initialize a vector to store the file blocks
	Node<int>* current = blks.getHead(); //Head of block list
	while(current != nullptr){ //Iterate through the block list
		fileBlocks.push_back(current->data);
		current = current->next; //Move on to next node
	}
	return fileBlocks;
}

//Taking drive size as parameter for file manager class
FileManager::FileManager(int driveSize) {
	hardDrive = new char[driveSize]; //Memory allocation for hard drive
	for (int i = 0; i < driveSize; ++i) {
		hardDrive[i] = ' '; //Initialize the hard drive with empty spaces
		blocksAvailable.enqueue(i); //Enqueue each block index to indicate the number of available blocks
	}
}

FileManager::~FileManager(){
	delete[] hardDrive; //Memory deallocation
}

//Take file name and file contents as parameter and add a file to the file manager
void FileManager::addFile(std::string name, std::string contents){

	//Check whether a file of the given name already exists
	if (findFileByName(name) != nullptr) {
		std::cout << "File with name '" << name << "' already exists." << std::endl;
		return;
	}

	File newFile(name); //New file object for name given
	for (size_t i = 0; i < contents.size(); ++i) {
		//Check block availability to store file contents
		if (!blocksAvailable.isEmpty()) {
			int blockIndex = blocksAvailable.front(); //Get next available block index
			blocksAvailable.dequeue(); //Dequeue block index
			hardDrive[blockIndex] = contents[i]; //Store file contents in the hard drive
			newFile.addBlock(blockIndex); //Add the block index to the file's block list
		} else {
			std::cout << "Not enough space on the hard drive to store the file '" << name << "'" << std::endl;
			return;
		}
	}
	files.addNode(newFile); //New file added to file manager
}

//Take file name as parameter and delete the file from file manager
void FileManager::deleteFile(std::string name) {
	Node<File>* current = files.getHead();
	while (current != nullptr) {
		//Check if current file has the given name
		if (current->data.getFileName() == name) {
			std::vector<int> fileBlocks = current->data.getFileBlocks(); //Get blocks occupied by the file
			for (int blockIndex : fileBlocks) {
				blocksAvailable.enqueue(blockIndex); //To indicate availability
				hardDrive[blockIndex] = ' '; //Clear the block on the hard drive
			}
			files.removeNode(current);
			return;
		}
		current = current->next; //Move on to the next file
	}
	std::cout << "File '" << name << "' not found." << std::endl;
}

//Take the file name as a parameter and read the contents of the file
std::string FileManager::readFile(std::string name) {
	Node<File>* current = files.getHead();
	while (current != nullptr) {
		if (current->data.getFileName() == name) {
			std::string contents;
			std::vector<int> fileBlocks = current->data.getFileBlocks();
			for (int blockIndex : fileBlocks) {
				if (blockIndex >= 0 && blockIndex < blocksAvailable.size()) {
					contents += hardDrive[blockIndex]; //Append the block contents to the content string
				} else {
					break;
				}
			}
			return contents;
		}
		current = current->next;
	}
	return "File '" + name + "' not found.";
}

//Get the names of all the files stored in the file manager
std::vector<std::string> FileManager::getFileNames() {
	std::vector<std::string> filenames; //Vector initialized to store file names
	Node<File>* current = files.getHead();
	while (current != nullptr) {
		filenames.push_back(current->data.getFileName()); //Add file name to the vector
		current = current->next;
	}
	return filenames;
}

//Take file name as a parameter and find a file by its name
File* FileManager::findFileByName(std::string name) {
	Node<File>* current = files.getHead();
	while (current != nullptr) {
		if (current->data.getFileName() == name) {
			return &(current->data); //Return pointer to the file object
		}
		current = current->next;
	}
	return nullptr; //If the file is not found
}
