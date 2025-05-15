//
// Created by libin on 2025/1/3.
//

#ifndef KNOWLEDGETEST_FILEOPERATE_H
#define KNOWLEDGETEST_FILEOPERATE_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <direct.h>

//class fileOperate {
//};

/* get current work direct */
void CurrentWorkDirectory() {
    char cwd[1024];
    if (_getcwd(cwd, sizeof(cwd)) != NULL)
        std::cout << "current work directory: " << cwd << std::endl;
    else
        std::cout << "获取工作路径失败" << std::endl;
}


/* read content from the file */
int readFromFile() {
    // open the file
    std::ifstream inputStrm("../Resource/example.txt");

    if(!inputStrm) {
        std::cerr << "Can not open the file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputStrm, line)) {     // get content by line
        std::cout << line << std::endl;               // print content to control center
    }

    // close the file
    inputStrm.close();
    return 0;
}

/* put the client's inputting content into file */
int outputToFile() {
    std::ofstream outputFile("../Resource/example.txt", std::ofstream::app);
    if (!outputFile) {
        std::cerr << "Can not open the file." << std::endl;
        return 1;
    }

    std::string userInput;
    std::cout << "Please input some text: " << std::endl;
    std::getline(std::cin, userInput);      // get the input

    outputFile << userInput << std::endl;       // write into file

    outputFile.close();
    return 0;
}

/* read from the file and counting */
int countWords() {
    std::ifstream inputFile("../Resource/example.txt");
    if (!inputFile) {
        std::cerr << "Can not open the file." << std::endl;
        return 1;
    }

    int wordCount = 0;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream lineStrm(line);
        std::string word;
        while (lineStrm >> word) {  // 按空格分词
            ++wordCount;
        }
    }

    std::ofstream outputFile("../Resource/example.txt", std::fstream::app);
    outputFile << "There are " << wordCount << " words in this file." << std::endl;

    inputFile.close();
    outputFile.close();
    return 0;
}

/* copy contents from one file to the other file. */
int copyFileContent() {
    std::ifstream inputStrm("../Resource/example.txt", std::fstream::binary);
    if(!inputStrm) {
        std::cerr << "Can not open the example.txt" << std::endl;
        return 1;
    }

    std::ofstream outputStrm("../Resource/destination.txt", std::fstream::binary);
    if(!outputStrm) {
        std::cerr << "Can not open the destination.txt" << std::endl;
        return 1;
    }

    outputStrm << inputStrm.rdbuf();

    inputStrm.close();
    outputStrm.close();
    return 0;
}

/* read a file and modify its contents */
int modifyContents() {
    std::ifstream inputStrm("../Resource/example.txt");
    if (!inputStrm.is_open()) {
        std::cerr << "Can not open the Resource/example.txt " << std::endl;
        return 1;
    }
//    for (int i = 0; i < 10; ++i) {
//        for (int j = 0; j < 20; ++j) {
//            inputStrm << "old " << std::endl;
//        }
//        inputStrm << "\n" << std::endl;
//    }


    std::ofstream outputStrm("../Resource/modified.txt");
    if (!outputStrm) {
        std::cerr << "Can not open the Resource/modified.txt" << std::endl;
    }

    std::string line;
    while (std::getline(inputStrm, line)) {
        // 替换每行中的 old 为 new
        size_t pos = 0;
        while ((pos = line.find("old", pos)) != std::string::npos) {
            line.replace(pos, 3, "new");
            pos += 3;
        }
        outputStrm << line << std::endl;
    }

    inputStrm.close();
    outputStrm.close();
    std::cout << "Contents are modified." << std::endl;

    return 0;
}

void readFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Can not open the file:" + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}

/* handling errors and exception */
int handleException(){
    try {
        readFile("../Resource/example.txt");
    } catch (const std::exception& exception) {
        std::cerr << "error: " << exception.what() << std::endl;
    }
    return 0;
}

#endif //KNOWLEDGETEST_FILEOPERATE_H
