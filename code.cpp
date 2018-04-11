#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <sstream>
#include <utility>

std::vector<std::string> explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}

void printLine(){
    std::cout << "\n----------------------------\n";
}

int main()
{
    std::string inputFileName = "Data.txt";
    std::ifstream file(inputFileName);
    std::string str;
    std::string fileContents;
    std::vector<std::string> fileLines;
    std::vector<std::string> rules;
    const char bacteriaDelimeter = ' ';
    const char sizeDelimeter = 'x';

    int index = 0;
    int bacteriaDefinitionIndex = 0;
    int rulesIndexStart = 0;
    int rulesIndexEnd = 0;
    int sizeDefinitonIndex = 0;
    int positionDefinitionStart = 0;

    std::cout << "Bacteria Simulation Started\n";
    std::cout << "Reading and parsing " + inputFileName + "\n";


    while (std::getline(file, str))
    {
      fileLines.push_back(str);

      if(str == "bacteria:"){
        bacteriaDefinitionIndex = index +1;
      }

      if(str == "rules:"){
        rulesIndexStart = index + 1;
      }

      if(str == "size:"){
        rulesIndexEnd = index - 1;
        sizeDefinitonIndex = index + 1;
      }

      if(str == "start:"){
        positionDefinitionStart = index + 1;
      }

      index++;
    }

    std::string bacteriaDefinitionLine = fileLines[bacteriaDefinitionIndex];

    std::cout << "Bacterias: " + bacteriaDefinitionLine + "\n";

    std::vector<std::string> bacterias = explode(bacteriaDefinitionLine, bacteriaDelimeter);

    std::cout << "Rules\n";
    for(int i = rulesIndexStart; i <= rulesIndexEnd; i++){
        //std::cout << fileLines[i] + "\n";
        rules.push_back(fileLines[i]);
    }

    char rulesParsed[rules.size()][2];


    for(int i = 0; i < rules.size(); i++){
        rulesParsed[i][0] = rules[i][0];
        rulesParsed[i][1] = rules[i][rules[1].size() - 1];
        printf("%c => %c\n", rulesParsed[i][0], rulesParsed[i][1]);
    }


    std::string boardSizeDefinition = fileLines[sizeDefinitonIndex];

    std::cout << "Board Size: " + boardSizeDefinition + "\n";

    std::vector<std::string> boardSize = explode(boardSizeDefinition, sizeDelimeter);

    int boardWidth = std::stoi(boardSize[0]);
    int boardHeight = std::stoi(boardSize[1]);

    printf("Board width: %d Board height: %d \n", boardWidth, boardHeight);

    char board[boardWidth][boardHeight];

    for (int i = 0; i < boardWidth; i++)
    {
        for (int j = 0; j < boardHeight; j++){
            board[i][j] = ' ';
        }

    }

    std::cout << "Start Positions\n";
    for(int i = positionDefinitionStart; i < index; i++){
        std::cout << fileLines[i] + "\n";
        std::vector<std::string> bacteriaPositionInfo = explode(fileLines[i], bacteriaDelimeter);
        board[stoi(bacteriaPositionInfo[1])][stoi(bacteriaPositionInfo[2])] = bacteriaPositionInfo[0][0];
    }

    printLine();

    for (int i = 0; i < boardWidth; i++)
    {
        for (int j = 0; j < boardHeight; j++){

            printf("%c ", board[i][j]);
        }
        printf("\n");
    }

    std::cout << "Please enter turn number:";
    int turnNumber;
    std::cin >> turnNumber;

    printf("Turn number is %d\n", turnNumber);

    for(int turn = 1; turn <= turnNumber; turn++){

        char newPositions[bacterias.size()][boardWidth][boardHeight];


        for(int bacteriaIndex = 0; bacteriaIndex < bacterias.size(); bacteriaIndex++){
            for (int row = 0; row < boardWidth; row++)
            {
                for (int col = 0; col < boardHeight; col++){
                    newPositions[bacteriaIndex][row][col] = ' ';
                }
            }
        }

        printLine();
        printf("\nTurn %d :", turn);

        for(int bacteriaIndex = 0; bacteriaIndex < bacterias.size(); bacteriaIndex++){

            std::string currentBacteria = bacterias[bacteriaIndex];

            for (int row = 0; row < boardWidth; row++)
            {
                for (int col = 0; col < boardHeight; col++){
                    if(board[row][col] == currentBacteria[0]){

                        if((row + 1) >= 0 && (row + 1) <= boardWidth-1){
                            newPositions[bacteriaIndex][row+1][col] = currentBacteria[0];
                        }

                        if((row - 1) >= 0 && (row - 1) <= boardWidth-1){
                           newPositions[bacteriaIndex][row-1][col] = currentBacteria[0];
                        }

                        if((col + 1) >= 0 && (col + 1) <= boardHeight-1){
                            newPositions[bacteriaIndex][row][col+1] = currentBacteria[0];
                        }

                        if((col - 1) >= 0 && (col - 1) <= boardHeight-1){
                           newPositions[bacteriaIndex][row][col-1] = currentBacteria[0];
                        }
                    }
                }
            }

            for (int row = 0; row < boardWidth; row++)
            {
                for (int col = 0; col < boardHeight; col++)
                {
                    if(newPositions[bacteriaIndex][row][col] == currentBacteria[0]){
                        //Değişim burada gerçekleşiyor

                        if(board[row][col] != ' '){

                            char bacteriaInCell = board[row][col];

                            for(int i = 0; i < rules.size(); i++){
                                if(rulesParsed[i][0] == currentBacteria[0] && rulesParsed[i][1] == bacteriaInCell){
                                    board[row][col] = currentBacteria[0];
                                }
                            }

                        }else{
                            board[row][col] = currentBacteria[0];
                        }
                    }

                }
            }
        }
        printLine();
        for (int i = 0; i < boardWidth; i++)
        {
            for (int j = 0; j < boardHeight; j++){

                printf("%c ", board[i][j]);
            }
            printf("\n");
        }
    }
}