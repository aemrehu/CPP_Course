#include "RGB/png.h"
#include "RGB/rgbapixel.h"

#include <string>
#include <cmath>

void rotate(std::string inputFile, std::string outputFile) {
	PNG pic(inputFile);
	// Your code here

	for (size_t y = 0; y < pic.height()/2; y++)
	{
		for (size_t x = 0; x < pic.width(); x++)
		{
			RGBAPixel * curr = pic(x,y);
			RGBAPixel * temp = pic(pic.width()-1-x, pic.height()-1-y);
			RGBAPixel temp2 = *curr;
			*curr = *temp;
			*temp = temp2;
		}
	}
	
	pic.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
	PNG png(width, height);
	// Your code here
	// An image with a twirl at each corner
	// and all with slightly different color gradients
	int m = 1;
	for (size_t y = 0; y < png.height(); y++)
	{
		for (size_t x = 0; x < png.width(); x++)
		{
			RGBAPixel * curr = png(x,y);
			int alpha = 255;
			bool flip = true;
			if (alpha <= 5)
				flip = true;
			if (alpha >= 250)
				flip = false;
			if (flip)
				alpha += 5;
			else
				alpha -= 5;

			int distance = (m/png.width()/2) * sqrt((x - png.width()/2)*(x - png.width()/2) + (y - png.height()/2)*(y - png.height()/2));
			curr->red = (int)(128.0 + 120.0 * cos(distance / 10.0));
			curr->green = (int)(128.0 + 110.0 * sin(distance / 10.0));
			curr->blue = (int)(128.0 + 127.0 * sin(distance / 10.0 + 2 * M_PI / 3));
			curr->alpha = alpha;
			m++;
		}
	}
	return png;
}
