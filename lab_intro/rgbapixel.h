/**
 * @file rgbapixel.h
 * Definition of the RGBAPixel class for the EasyPNG library.
 *
 * @author Chase Geigle
 * @date Spring 2012
 */

// c-style includes
#include <stdio.h>
#include <stdlib.h>

// c++ style includes
#include <string>
#include <iostream>
#include <sstream>

/**
 * Represents a single RGBA pixel.
*/
class RGBAPixel
{
    public:
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;

        /**
         * @brief Construct a new RGBAPixel object
         *
         */
        RGBAPixel();

        /**
         * @brief Construct a new RGBAPixel object with the given color values.
         *
         * @param _r
         * @param _g
         * @param _b
         */
        RGBAPixel(uint8_t _r, uint8_t _g, uint8_t _b);

};
