#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"
using cs225::PNG;

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //   create a StickerSheet that contains an image and at least three stickers.
  //StickerSheet mysheet(PNGreadFromFile("alma.png"), 3);
  Image sheet;
  sheet.readFromFile("sheet.png");

  StickerSheet mysheet(sheet, 7);

  Image sheldon;
  sheldon.readFromFile("sheldon.png");
  sheldon.scale(0.6);
  mysheet.addSticker(sheldon, 10, 300);

  Image amy;
  amy.readFromFile("amy.png");
  amy.scale(0.5);
  mysheet.addSticker(amy, 150, 300);

  Image penny;
  penny.readFromFile("penny_tbbt.png");
  penny.scale(0.28);
  mysheet.addSticker(penny, 290, 300);
  // mysheet.addSticker(iword, 600, 600);
  
  Image lenord;
  lenord.readFromFile("lenord.png");
  lenord.scale(0.5);
  mysheet.addSticker(lenord, 440, 300);

  Image howard;
  howard.readFromFile("howard.png");
  howard.scale(0.5);
  mysheet.addSticker(howard, 590, 300);

  Image bernny;
  bernny.readFromFile("bernny.png");
  bernny.scale(0.5);
  mysheet.addSticker(bernny, 740, 300);

  Image raj;
  raj.readFromFile("raj.png");
  raj.scale(0.4);
  mysheet.addSticker(raj, 365, 0);

  Image output = mysheet.render();
  output.writeToFile("myImage.png");
  //(PNG::PNG readFromFile("alma.png"), 3)
  //mysheet.readFromFile("alma.png");

  /*
  png.readFromFile("alma.png");
  result = grayscale(png);
  result.writeToFile("out-grayscale.png");
  */
  return 0;
}
