//
//  main.cpp
//  AlgoIIWeek4
//
//  Created by Chris Welhoelter on 4/21/15.
//  Copyright (c) 2015 Chris Welhoelter. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main(int argc, const char * argv[]) {
    
    std::string fileName;
    std::fstream fsIn;
    
    std::cout << "enter the file name: ";
    std::cin >> fileName;
    fsIn.open(fileName);
    if (!fsIn.is_open()){
        std::cout << "could not open " << fileName << std::endl;
        exit(EXIT_FAILURE);
    }
    
    int vertexCount;
    int edgeCount;
    
    fsIn >> vertexCount;
    fsIn >> edgeCount;
    
    std::vector<std::vector<int>> curTable(vertexCount + 1, std::vector<int>(vertexCount + 1, INT_MAX));
    std::vector<std::vector<int>> prevTable(vertexCount + 1, std::vector<int>(vertexCount +1, INT_MAX));
    
    for (size_t i = 1; i <= vertexCount; i++){
        prevTable[i][i] = 0;
    }
    
    for (size_t i = 0; i < edgeCount; i++){
        int tail;
        int head;
        int length;
        
        fsIn >> tail;
        fsIn >> head;
        fsIn >> length;
        
        prevTable[head][tail] = length;
    }
    
    for (size_t k = 1; k <= vertexCount; k++){
        for (size_t i = 1; i <= vertexCount; i++){
            for (size_t j = 1; j <= vertexCount; j++){
                
                if (prevTable[i][k] == INT_MAX || prevTable[k][j] == INT_MAX){
                    curTable[i][j] = prevTable[i][j];
                }
                
                else if (prevTable[i][j] <= prevTable[i][k] + prevTable[k][j]){
                    curTable[i][j] = prevTable[i][j];
                }
                
                else {
                    curTable[i][j] = prevTable[i][k] + prevTable[k][j];
                }
                
                if (i == j && curTable[i][j] != 0){
                    std::cout << "*** NEGATIVE CYCLE ***" << std::endl;
                    std::cout << "curTable[" << i << "][" << j << "] = " << curTable[i][j] << std::endl;
                    exit(EXIT_FAILURE);
                }
                
            }
        }
        prevTable = curTable;
    }
    
    // final check for negative cycles
    for (size_t i = 1; i <= vertexCount; i++){
        if (curTable[i][i] != 0){
            std::cout << "*** NEGATIVE CYCLE ***" << std::endl;
            std::cout << "curTable[" << i << "][" << i << "] = " << curTable[i][i] << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    
    int shortestShortestPath = INT_MAX;
    
    for (size_t i = 1; i <= vertexCount; i++){
        for (size_t j = 1; j <= vertexCount; j++){
            if (curTable[i][j] < shortestShortestPath){
                shortestShortestPath = curTable[i][j];
            }
        }
    }
    
    std::cout << "shortestShortestPath = " << shortestShortestPath << std::endl;
    
    return 0;
}
