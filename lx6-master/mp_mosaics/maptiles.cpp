/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    unsigned int source_row = theSource.getRows();
    unsigned int source_column = theSource.getColumns();
    MosaicCanvas* new_canvas = new MosaicCanvas(source_row, source_column);

    map<Point<3>, unsigned int> map;
    vector<Point<3>> points_vector;
    for (unsigned int index = 0; index < theTiles.size(); index++) {
        LUVAPixel average_color = theTiles[index].getAverageColor();
        Point<3> converted_point = convertToXYZ(average_color);
        points_vector.push_back(converted_point);
        map[converted_point] = index;
    }

    KDTree<3>*kdTree = new KDTree<3>(points_vector);
    for (unsigned int i = 0; i < source_row; i++) {
        for (unsigned int j = 0; j < source_column; j++) {
            LUVAPixel origin_color = theSource.getRegionColor(i, j);
            Point<3> origin_point = convertToXYZ(origin_color);
            Point<3> map_point = kdTree->findNearestNeighbor(origin_point);
            int index = map[map_point];
            new_canvas->setTile(i, j, &theTiles[index]);
        }
    }
    return new_canvas;
}

