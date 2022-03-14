// Tromino Problem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

struct tromino {
    int xlocations[3];
    int ylocations[3];
};
/* Grid is laid out as 0,0 is bottom left*/
class trominoGame {
private:
    std::vector<tromino> pieces;
    int* board =nullptr;
    int boardLength = 0;
    int blockedLoc[2] = {0,0};
    
    void solveGameHelper(int lengthOfSide,int xStart,int xStop,int yStart, int yStop,int xBlock,int yBlock) {                   //x and y are absolute
        if (lengthOfSide == 2) {
            int counter = 0;
            tromino temp;
            for (int i = xStart; i < xStop; ++i) {
                for (int j = yStart; j < yStop; ++j) {
                    if (i != xBlock || j != yBlock) {
                       
                        temp.xlocations[counter] = i;
                        temp.ylocations[counter] = j;
                        counter++;
                       
                    }
                }
            }
            pieces.push_back(temp);
            for (int j = 0; j < 3; j++) {
                std::cout << temp.xlocations[j] << " " << temp.ylocations[j] << "   ";
            }
            std::cout << std::endl;
            return;
        }
        //find the quadrant that contains the block
        int midpoint = lengthOfSide >> 1;
        if (xBlock < midpoint+xStart && yBlock < midpoint+yStart) {       //third quadrant(bottom left) has blocked location
            tromino temp;
            temp.xlocations[0] = xStart + midpoint;
            temp.ylocations[0] = yStart + midpoint-1;

            temp.xlocations[1] = xStart + midpoint;
            temp.ylocations[1] = yStart +  midpoint;

            temp.xlocations[2] = xStart + midpoint-1;
            temp.ylocations[2] = yStart + midpoint;

            pieces.push_back(temp);
            for (int j = 0; j < 3; j++) {
                std::cout << temp.xlocations[j] << " " << temp.ylocations[j] << "   ";
            }
            std::cout << std::endl;
            solveGameHelper(midpoint, xStart, xStart+midpoint, yStart, yStart+midpoint,xBlock,yBlock);                          //third quadrant
            solveGameHelper(midpoint, xStart + midpoint, xStop, yStart, yStart + midpoint, xStart + midpoint, yStart + midpoint - 1);
            solveGameHelper(midpoint, xStart + midpoint, xStop, yStart + midpoint, yStop, xStart + midpoint, yStart + midpoint);                          //first
            solveGameHelper(midpoint, xStart, xStart + midpoint, yStart + midpoint, yStop, xStart + midpoint-1, yStart+midpoint);
            return;//second
        }
        if (xBlock < midpoint+xStart && yBlock >= midpoint+yStart) {      //second Quadrant(top left) has blocked location
            tromino temp;
            temp.xlocations[0] = midpoint + xStart;
            temp.ylocations[0] = midpoint-1 + yStart;

            temp.xlocations[1] = midpoint-1 + xStart;
            temp.ylocations[1] = midpoint -1 + yStart;

            temp.xlocations[2] = midpoint + xStart;
            temp.ylocations[2] = midpoint + yStart;

            pieces.push_back(temp);
            for (int j = 0; j < 3; j++) {
                std::cout << temp.xlocations[j] << " " << temp.ylocations[j] << "   ";
            }
            std::cout << std::endl;
            solveGameHelper(midpoint, xStart, xStart+midpoint, yStart, yStart+midpoint, xStart+midpoint-1, yStart+midpoint-1);
            solveGameHelper(midpoint, xStart + midpoint, xStop, yStart, yStart + midpoint, xStart + midpoint, yStart + midpoint - 1);
            solveGameHelper(midpoint, xStart + midpoint , xStop, yStart + midpoint, yStop, xStart + midpoint, yStart + midpoint);
            solveGameHelper(midpoint, xStart, xStart + midpoint, yStart + midpoint, yStop, xBlock, yBlock);
            return;
        }
        if (xBlock >= midpoint+xStart && yBlock < midpoint+yStart) {     //fourth quadrant(bottom right) has blocked location
            tromino temp;
            temp.xlocations[0] = midpoint-1 +xStart;
            temp.ylocations[0] = midpoint-1 +yStart;

            temp.xlocations[1] = midpoint-1 + xStart;
            temp.ylocations[1] = midpoint + yStart;

            temp.xlocations[2] = midpoint + xStart;
            temp.ylocations[2] = midpoint + yStart;

            pieces.push_back(temp);
            for (int j = 0; j < 3; j++) {
                std::cout << temp.xlocations[j] << " " << temp.ylocations[j] << "   ";
            }
            std::cout << std::endl;
            solveGameHelper(midpoint, xStart, xStart + midpoint, yStart, yStart + midpoint, xStart + midpoint - 1, yStart + midpoint - 1);
            solveGameHelper(midpoint, xStart + midpoint, xStop, yStart, yStart + midpoint, xBlock , yBlock);
            solveGameHelper(midpoint, xStart + midpoint, xStop, yStart + midpoint, yStop, xStart + midpoint, yStart + midpoint);                          //first
            solveGameHelper(midpoint, xStart, xStart + midpoint, yStart + midpoint, yStop, xStart + midpoint - 1, yStart + midpoint);
            return;
        }
        if (xBlock >= midpoint+xStart && yBlock >= midpoint+yStart) {      //first quadrant(top right) has blocked location
            tromino temp;
            temp.xlocations[0] = midpoint-1 + xStart;
            temp.ylocations[0] = midpoint + yStart;

            temp.xlocations[1] = midpoint-1 + xStart;
            temp.ylocations[1] = midpoint-1 + yStart;

            temp.xlocations[2] = midpoint + xStart;
            temp.ylocations[2] = midpoint -1 + yStart;

            pieces.push_back(temp);
            for (int j = 0; j < 3; j++) {
                std::cout << temp.xlocations[j] << " " << temp.ylocations[j] << "   ";
            }
            std::cout << std::endl;
            solveGameHelper(midpoint, xStart, xStart + midpoint, yStart, yStart + midpoint, xStart + midpoint - 1, yStart + midpoint - 1);
            solveGameHelper(midpoint, xStart + midpoint, xStop, yStart, yStart + midpoint, xStart + midpoint, yStart + midpoint - 1);
            solveGameHelper(midpoint, xStart +midpoint, xStop, yStart + midpoint, yStop, xBlock, yBlock);
            solveGameHelper(midpoint, xStart, xStart + midpoint, yStart + midpoint, yStop, xStart + midpoint - 1, yStart + midpoint);
            return;
        }
    }
public:
    void setBoardSize(int n) {
        board = new int[n*n];
        boardLength = n;
    }
    
    void setBlockedLocation(int x, int y) {
        blockedLoc[0] = x;
        blockedLoc[1] = y;
    }

    std::vector<tromino> getPieces() {
        return pieces;
    }

    void solveGame() {
        solveGameHelper(boardLength, 0, boardLength, 0, boardLength,blockedLoc[0],blockedLoc[1]);
    }
};
int main()
{
    trominoGame x;
    x.setBoardSize(16);
    x.setBlockedLocation(5, 6);
    x.solveGame();
    std::vector<tromino> temp = x.getPieces();
   /* for (int i = 0; i < temp.size(); i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << temp[i].xlocations[j] << " " << temp[i].ylocations[j] << "   ";
        }
        std::cout << std::endl;
    }*/
}

