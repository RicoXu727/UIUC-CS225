#include "StickerSheet.h"
#include "Image.h"
//#include "HSLAPixel.h"
//#include "RGB_HSL.h"
#include "cs225/HSLAPixel.h"
//#include <vector>
//using cs225::HSLAPixel;


StickerSheet::StickerSheet() {

}

/*
StickerSheet constructor
deep copy of the base picture
the ability to hold a max number of stickers (Images) 
with indices 0 through max - 1.
*/
StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    stickers.reserve(max);
    x_.reserve(max);
    y_.reserve(max);
    //Image * copybase = new Image(picture.width(), picture.height());
    copybase = new Image(picture);
    max_stickers = max;
}

/*
StickerSheet destructor
Frees all space that was dynamically allocated by this StickerSheet.
*/
StickerSheet::~StickerSheet() {
    _destroy();
}

/*
StickerSheet copy constructor
*/
StickerSheet::StickerSheet(const StickerSheet & other) {
    _copy(other);
}

/*
helper function to copy constructor
*/
void StickerSheet::_copy(const StickerSheet & other) {
    max_stickers = other.max_stickers;
    //copybase = new Image(other.copybase->width(), other.copybase->height());
    copybase = new Image(*other.copybase);
    stickers = other.stickers;
    x_ = other.x_;
    y_ = other.y_;
}

/*
overload operater=
*/
//const StickerSheet &StickerSheet::operator=(const StickerSheet &other)
const StickerSheet &StickerSheet::operator=(const StickerSheet &other) {
    if (this != &other) {
        _destroy();
        _copy(other);
    }
    return *this;
}

/*
helper function to destroy;
*/
void StickerSheet::_destroy() {
    // delete max_stickers;
    // if (copybase != NULL) {
        
    // }
    delete copybase;
    copybase = NULL;

    for (unsigned i = 0; i < stickers.size(); i++) {
        if (stickers[i] != NULL) {
            // delete stickers[i];
            // stickers[i] = nullptr;
        }
    }

    // std::vector< int >::iterator it = x.begin();
    // for ( ;it != x.end(); it++) {
    //     delete x[it];
    // }
    // auto it = stickers.rbegin();
    // while (it != stickers.rend())
    // {
    //     delete *it;
    //     // *it = NULL;
    //     // it++;
    // }
    
    // stickers.clear();
    // x_.clear();
    // y_.clear();
    //max_stickers = 0;
}



void StickerSheet::changeMaxStickers(unsigned max) {
    stickers.reserve(max);
    x_.reserve(max);
    y_.reserve(max);
    if (stickers.size() > max) {
        stickers.erase(stickers.begin() + max, stickers.begin() + stickers.size());
        x_.erase(x_.begin() + max, x_.begin() + stickers.size());
        y_.erase(y_.begin() + max, y_.begin() + stickers.size());
    }
    
    max_stickers = max;
}

/*
Adds a sticker to the StickerSheet
so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.
*/
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    //stickers.reserve(sticker.max_stickers);
    if (stickers.capacity() > stickers.size()) {
        stickers.push_back(&sticker);
        x_.push_back(x);
        y_.push_back(y);
        max_stickers++;
        return stickers.size() - 1;
    }
    return -1;
}


/*
If the layer is invalid or does not contain a stickerthis function must return false.
true if the translate was successful; otherwise false.
*/
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index >= max_stickers || index >= stickers.size()) {
        return false;
    }
    x_[index] = x;
    y_[index] = y;
    return true;
}

/*
Removes the sticker at the given zero-based layer index.
Make sure that the other stickers don't change order.
”index“ The layer in which to delete the png
*/
void StickerSheet::removeSticker(unsigned index) {
    /*
    stickers.erase(index);
    x_.erase(index);
    y_.erase(index);
    */

    stickers.erase(stickers.begin() + index);
    x_.erase(x_.begin() + index);
    y_.erase(y_.begin() + index);
}

/*
Returns a pointer to the sticker at the specified index, not a copy of it.
That way, the user can modify the Image.
If the index is invalid, return NULL.
"index"The layer in which to get the sticker.
return : A pointer to a specific Image in the StickerSheet
*/
Image * StickerSheet:: getSticker(unsigned index) {
    /*
    if (index > max_stickers - 1 || index > stickers.size() -1) {
        return NULL;
    } else {
        return stickers[index];
    }
    */
    if (index >= max_stickers || index >= stickers.size()) {
        return NULL;
    } else {
        return stickers[index];
    }
}

/*
Renders: the whole StickerSheet on one Image and returns that Image.
The base picture is drawn first and then each sticker is drawn in order starting with 
layer zero (0) then layer one (1), and so on.

If a pixel's alpha channel in a sticker is zero (0)
no pixel is drawn for that sticker at that pixel.

If the alpha channel is non-zero, a pixel is drawn. 
(Alpha blending is awesome, but not required.) 

The returned Image always includes the full contents of the picture and all stickers.

This means that the size of the result image may be larger than the base picture 
if some stickers go beyond the edge of the picture.
*/
Image StickerSheet::render() const {
    Image output(*copybase);

    for (unsigned i = 0; i < stickers.size(); i++) {
        //resize image
        unsigned currentwidth = stickers[i]->width();
        unsigned currentheight = stickers[i]->height();
        if ((currentwidth + x_[i]) > output.width()) {
            output.resize(currentwidth + x_[i], output.height());
        }
        if ((currentheight + y_[i]) > output.height()) {
            output.resize(output.width(), currentheight + y_[i]);
        }
        // getpixel
        for (unsigned x = 0; x < currentwidth; x++) {
            for (unsigned y = 0; y < currentheight; y++) {
                cs225::HSLAPixel & currentpixel = output.getPixel(x + x_[i], y + y_[i]);
                cs225::HSLAPixel & originpixel = stickers[i]->getPixel(x, y);
                if (originpixel.a != 0) {
                    currentpixel = originpixel;
                }
            }
        }
    }
    return output;
    // auto it = stickers.rbegin();
    // while (it != stickers.rbegin())
    // {
    //     unsigned currentwidth = (*it).getWidth();
    //     unsigned currentheight = (*it).gstHeight();
    //     if ((currentwidth + x_[it]))
    // }
    // for (std::vector<Image*>::iterator it = stickers.begin(); it != stickers.end() ; it++) {}
}