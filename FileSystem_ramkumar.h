//Contains File and FileManager declarations

#define FILESYSTEM_RAMKUMAR_H

//Import both linked list and queue header files
#include "LinkedList_ramkumar.hpp"
#include "Queue_ramkumar.hpp"
#include <string>
#include <vector>

//File class declaration
class File {
	//Declarations
private:
	std::string filename;
	LinkedList<int> blks; //To store block indexes

public:
	File(std::string filename); //Constructor to initialize file object with file name
	std::string getFileName(); //Get the file name of the file object
	void addBlock(int blkindex){blks.addNode(blkindex); }; //Add a block index to the file
	int fileSize() {return blks.getSize();}; //Obtain the size of the file
	std::vector<int> getFileBlocks();
};

//File manager class declarations
class FileManager {
	//Declarations
private:
    char* hardDrive; //Hard drive array
    Queue<int> blocksAvailable; //Track the available block indexes
    LinkedList<File> files; //Store file objects

public:
    FileManager(int driveSize); //Initialize FileManager class with drivesize
    ~FileManager(); //Destructor. Releases dynamic memory allocation

    void addFile(std::string name, std::string contents);
    void deleteFile(std::string name);
    std::string readFile(std::string name);
    std::vector<std::string> getFileNames();
    File* findFileByName(std::string name);
};
