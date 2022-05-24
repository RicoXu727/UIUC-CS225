
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG icecream;
  icecream.readFromFile("icecream.png");

  FloodFilledImage image(icecream);

  BFS bfs1(icecream, Point(80, 60), 0.2);
  BFS bfs2(icecream, Point(80, 120), 0.2);
  BFS bfs3(icecream, Point(80, 180), 0.2);
  //BFS bfs4(icecream, Point(80, 240), 0.2);
  DFS dfs(icecream, Point(0, 0), 0.2);

  MyColorPicker mycolor(100, 0.7, 0.7);
  RainbowColorPicker rainbow(10);
  GridColorPicker grid1(HSLAPixel(270, 0.5, 0.5), HSLAPixel(180, 0.5, 0.5), 5);
  GridColorPicker grid2(HSLAPixel(178, 0.8, 0.9), HSLAPixel(178, 0.8, 0.9), 5);

  image.addFloodFill(bfs1, mycolor);
  image.addFloodFill(bfs2, rainbow);
  image.addFloodFill(bfs3, grid1);
  image.addFloodFill(dfs, grid2);
  //image.addFloodFill(bfs4, grid2);
  

  Animation animation = image.animate(1000);
  
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  
  return 0;
}
