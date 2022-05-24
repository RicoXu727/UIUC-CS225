/* Your code here! */
#include "maze.h"
#include <queue>
#include <vector>
using namespace std;
using namespace cs225;
SquareMaze::SquareMaze() {

}

void SquareMaze::makeMaze(int width, int height) {
    this->width = width;
    this->height = height;
    basicSet.addelements(width * height);
    for (int i = 0; i < width * height; i++) {
        right.push_back(true);
        down.push_back(true);
    }
    for (int i = 0; i < width * height - 1; i++) {
        vector<int> moveWards;
        //have node right and two nodes in different sets. mark 0;
        if ((i + 1) % width != 0 && basicSet.find(i) != basicSet.find(i + 1)) {
            moveWards.push_back(0);
        }
        // the node is not in the last row, and two nodes in different sets
        //(the node below it) , mark 1;
        if (i < (width * (height - 1)) && basicSet.find(i) != basicSet.find(i + width)) {
            moveWards.push_back(1);
        }
        // check if the node in the first colomn, and two nodes in different sets;
        // mark 2;
        if (i % width != 0 && basicSet.find(i) != basicSet.find(i - 1)) {
            moveWards.push_back(2);
        }
        //ckeck if the node in the first row, and two nodes in different sets;
        // mark 3;
        if (!(i < width) && basicSet.find(i) != basicSet.find(i - width)) {
            moveWards.push_back(3);
        }

    
        //find a points randomly, with the total scope.
        int moveNum = moveWards[rand() % moveWards.size()];

        if (moveNum == 0) { // can move right
            basicSet.setunion(i, i + 1); // remove rightWall
            right[i] = false; // mark right wall removed
        } else if (moveNum == 1) {
            basicSet.setunion(i, i + width);
            down[i] = false;
        } else if (moveNum == 2) {
            basicSet.setunion(i, i - 1);
            right[i - 1] = false;
        } else if (moveNum == 3) {
            basicSet.setunion(i, i - width);
            down[i - width] = false;
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (dir == 0) {
        if (x >= width - 1) {
            return false;
        } else {
            return right[y * width + x] == false;
        }
    } else if (dir == 1) {
        if (y >= height - 1) {
            return false;
        } else {
            return down[y * width + x] == false;
        }
    } else if (dir == 2) {
        if (x <= 0) {
            return false;
        } else {
            return right[y * width + x - 1] == false;
        } 
    } else if (dir == 3) {
        if (y <= 0) {
            return false;
        } else {
            return down[y * width + x - width] == false;
        }
    } else {
        return false;
    }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (dir == 0) {
        right[y * width + x] = exists;
    } else {
        down[y * width + x] = exists;
    }
}

vector<int> SquareMaze::solveMaze() {
    vector<int> pathRecord;  
    vector<int> distCount;  
    vector<bool> checkTraversal;
    //preset three vectors, same size;
    // default checkTraversal have not been traversed;
    for(int i = 0; i < width * height; i++){
      pathRecord.push_back(-1); 
      distCount.push_back(0);
      checkTraversal.push_back(false); 
    }
    //set the initial square;
    pathRecord[0] = 0;
    checkTraversal[0] = true;
    // built bfs queue;
    queue<int> helperQueue;
    int x;
    int y;
    // record the move index in movePin;
    int movePin;
    //set initial queue to make the while loop works;
    helperQueue.push(0);
    while(!helperQueue.empty()){
      movePin = helperQueue.front();
      checkTraversal[movePin] = true;
      x = movePin % width;
      y = movePin / width;
      helperQueue.pop();
        //start traversal
        //check if the player can move rightward;
      if(canTravel(x, y, 0)){ 
      int rightIdx = movePin + 1;
        //check if this square have been traversaled;
        if(!checkTraversal[rightIdx]){
          pathRecord[rightIdx] = movePin;
          //save current count;
          distCount[rightIdx] = distCount[movePin] + 1;
          // push a new movePin; bfs
          helperQueue.push(rightIdx);
          checkTraversal[rightIdx] = true;
        }
      }
      //check if the player can move downward;
      if(canTravel(x, y, 1)){
        int downIdx = movePin + width;
        if(!checkTraversal[downIdx]){
          pathRecord[downIdx] = movePin;
          distCount[downIdx] = distCount[movePin] + 1;
          helperQueue.push(downIdx);
          checkTraversal[downIdx] = true;
        }
      }
      //ckeck if the player can move left;
      if(canTravel(x, y, 2)){
        int leftIdx = movePin - 1;
        if(!checkTraversal[leftIdx]){
          pathRecord[leftIdx] = movePin;
          distCount[leftIdx] = distCount[movePin] + 1;
          helperQueue.push(leftIdx);
          checkTraversal[leftIdx] = true;
        }
      }
      //check if the player can move up;
      if(canTravel(x, y, 3)){
        int upIndex = movePin - width;
        if(!checkTraversal[upIndex]){
          pathRecord[upIndex] = movePin;
          distCount[upIndex] = distCount[movePin] + 1;
          helperQueue.push(upIndex);
          checkTraversal[upIndex] = true;
        }
      }
    }

    //find the longest path, must in the last row;
    int maxIdx = 0;
    for(int k = 0; k < width; k++){
      if(distCount[width * (height - 1) + k] > distCount[maxIdx]){
        maxIdx = width * (height - 1) + k;
      }
    }

    //set new private number here
    end = maxIdx; // or the drawfunction failed;
    vector<int> finalRecord; 
    while(maxIdx != 0){
      if(pathRecord[maxIdx] == maxIdx - 1){
        finalRecord.push_back(0);
      }
      if(pathRecord[maxIdx] == maxIdx - width){
        finalRecord.push_back(1);
      }
      if(pathRecord[maxIdx] == maxIdx + 1){
        finalRecord.push_back(2);
      }
      if(pathRecord[maxIdx] == maxIdx + width){
        finalRecord.push_back(3);
      }
      maxIdx = pathRecord[maxIdx];
    }
    // finalPath record in a back ward;
    // modified the output order;
    vector<int> output;
    for (int i = finalRecord.size() - 1; i >= 0; i--) {
        output.push_back(finalRecord[i]);
    } 
    
  return output;
}

PNG * SquareMaze::drawMaze() const {
  PNG * outputPng = new PNG(width * 10 + 1, height * 10 + 1);
    //reaversal the whole maze pixel;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            // set the left colunm to black;
            if (y == 0) { 
                for (int k = 0; k < 10; k++) {
                    if ((x * 10 + k < 1) || (x * 10 + k > 9)) {
                        HSLAPixel & pixel = outputPng->getPixel(x * 10 + k, 0);
                        pixel.l = 0;
                    }
                }
            }
            // set the first row to black;
            if (x == 0) { // the first row;
                for (int k = 0; k < 10; k++) {
                    HSLAPixel & pixel = outputPng->getPixel(0, y * 10 + k);
                    pixel.l = 0;
                }
            }
            //If the right wall exists
            //then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10.
            if (canTravel(x, y, 0) == false) {
                for (int k = 0; k <= 10; k++) {
                    HSLAPixel & pixel = outputPng->getPixel((x + 1) * 10, y * 10 + k);
                    pixel.l = 0;
                }
            }
            //If the bottom wall exists
            //then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
            if (canTravel(x, y, 1) == false) {
                for (int k = 0; k <= 10; k++) {
                    HSLAPixel & pixel = outputPng->getPixel(x * 10 + k, (y + 1) * 10);
                    pixel.l = 0;
                }
            }
        }
    }
    return outputPng;
}

PNG * SquareMaze::drawMazeWithSolution() {
    PNG * mazeWithSolution = drawMaze();
    vector<int> path = solveMaze();
    int startX = 5;
    int startY = 5;
    // start traversal here
    for (unsigned i = 0; i < path.size(); i++) {
        if (path[i] == 0) {
            for (int k = 0; k < 11; k++) {
                HSLAPixel & pixel = mazeWithSolution->getPixel(startX + k, startY);
                //(Red is 0,1,0.5,1 in HSLA)
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            startX = startX + 10; // change X to move;
        } else if (path[i] == 1) {
            for (int k = 0; k < 11; k++) {
                HSLAPixel & pixel = mazeWithSolution->getPixel(startX, startY + k);
                //(Red is 0,1,0.5,1 in HSLA)
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            startY = startY + 10;
        } else if (path[i] == 2) {
            for (int k = 0; k < 11; k++) {
                HSLAPixel & pixel = mazeWithSolution->getPixel(startX - k, startY);
                //(Red is 0,1,0.5,1 in HSLA)
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            startX = startX - 10;
        } else if (path[i] == 3) {
            for (int k = 0; k < 11; k++) {
                HSLAPixel & pixel = mazeWithSolution->getPixel(startX, startY - k);
                //(Red is 0,1,0.5,1 in HSLA)
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            startY = startY - 10;
        }
    }
    //call the destination maze coordinates (x,y)
    //whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
    int endX = end % width;
    int endY = end / height;
    for (int k = 1; k < 10; k++) {
        HSLAPixel & pixel = mazeWithSolution->getPixel(endX * 10 + k, (endY + 1) * 10);
        pixel.l = 1;
    }
    return mazeWithSolution;
}