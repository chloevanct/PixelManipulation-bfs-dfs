/**
 * @file quarterColorPicker.cpp
 * @description Implements the QuarterColorPicker constructor and () function
 *              for CPSC 221 2023S PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "quarterColorPicker.h"
#include <cmath>

QuarterColorPicker::QuarterColorPicker(PNG &inputimg)
{

    // Complete your implementation below

    // PNG scaledimg;

    referenceimg = inputimg;
    int scaled_img_height = referenceimg.height() / 2;
    int scaled_img_width = referenceimg.width() / 2;

    scaledimg = PNG(scaled_img_width, scaled_img_height);

    for (unsigned int x = 0; x < scaledimg.width(); x += 1)
    {
        for (unsigned int y = 0; y < scaledimg.height(); y += 1)
        {

            // vector<HSLAPixel> temp;

            HSLAPixel pixelTL = *referenceimg.getPixel(x * 2, y * 2);         // top left
            HSLAPixel pixelTR = *referenceimg.getPixel(x * 2 + 1, y * 2);     // top right
            HSLAPixel pixelBL = *referenceimg.getPixel(x * 2, y * 2 + 1);     // bottom left
            HSLAPixel pixelBR = *referenceimg.getPixel(x * 2 + 1, y * 2 + 1); // bottom right

            double new_hTop;
            double new_hBot;
            double new_h;

            if (abs(pixelTL.h - pixelTR.h) < 180.0)
            {
                // result.h = (result.h + temp[i].h) / 2.0;
                new_hTop = (pixelTL.h + pixelTR.h) / 2.0;
                // cout << "atributing new_h when result<180;" << endl;
            }
            else
            {
                new_hTop = fmod((((pixelTL.h + pixelTR.h) / 2.0) + 180.0), 360.0);
                // cout << "atributing new_h when result>180;" << endl;
            }

            if (abs(pixelBL.h - pixelBR.h) < 180.0)
            {
                // result.h = (result.h + temp[i].h) / 2.0;
                new_hBot = (pixelBL.h + pixelBR.h) / 2.0;
                // cout << "atributing new_h when result<180;" << endl;
            }
            else
            {
                new_hBot = fmod((((pixelBL.h + pixelBR.h) / 2.0) + 180.0), 360.0);
                // cout << "atributing new_h when result>180;" << endl;
            }

            if (abs(new_hBot - new_hTop) < 180.0)
            {
                // result.h = (result.h + temp[i].h) / 2.0;
                new_h = (new_hBot + new_hTop) / 2.0;
                // cout << "atributing new_h when result<180;" << endl;
            }
            else
            {
                new_h = fmod((((new_hBot + new_hTop) / 2.0) + 180.0), 360.0);
                // cout << "atributing new_h when result>180;" << endl;
            }

            double new_s = ((pixelTL.s + pixelTR.s) / 2.0 + (pixelBL.s + pixelBR.s) / 2.0) / 2.0;
            double new_l = ((pixelTL.l + pixelTR.l) / 2.0 + (pixelBL.l + pixelBR.l) / 2.0) / 2.0;
            double new_a = ((pixelTL.a + pixelTR.a) / 2.0 + (pixelBL.a + pixelBR.a) / 2.0) / 2.0;

            // // temp.push_back(pixelTR);
            // temp.push_back(pixelTL);
            // temp.push_back(pixelBL);
            // temp.push_back(pixelBR);

            // // HSLAPixel result = HSLAPixel(double hue, double saturation, double luminance, double alpha);
            // HSLAPixel result = pixelTR;

            // double new_h = pixelTR.h;
            // double new_s = pixelTR.s;
            // double new_l = pixelTR.l;
            // double new_a = pixelTR.a;

            // for (unsigned int i = 0; i < temp.size(); i++)

            // {

            //     if (abs(result.h - temp[i].h) < 180.0)
            //     {
            //         // result.h = (result.h + temp[i].h) / 2.0;
            //         new_h = (result.h + temp[i].h) / 2.0;
            //         // cout << "atributing new_h when result<180;" << endl;
            //     }
            //     else
            //     {
            //         new_h = fmod((((new_h + temp[i].h) / 2.0) + 180.0), 360.0);
            //         // cout << "atributing new_h when result>180;" << endl;
            //     }

            //     new_s = (new_s + temp[i].s) / 2.0;
            //     new_l = (new_l + temp[i].l) / 2.0;
            //     new_a = (new_a + temp[i].a) / 2.0;

            //     result = HSLAPixel(new_h, new_s, new_l, new_a);
            // }

            HSLAPixel newPixel = HSLAPixel(new_h, new_s, new_l, new_a);

            *scaledimg.getPixel(x, y) = newPixel;
        }
    }

    // referenceimg = scaledimg;
}

/**
 * Picks the color for pixel (x, y).
 *
 * Using the private reference image, scale each dimension by half
 * and tile the smaller image in a 2 x 2 grid over the original dimensions
 * of the image, and return the pixel at the appropriate coordinate from
 * the tiled image.
 *
 * The value of each pixel in the scaled image will be a bilinear interpolation
 * of a 2x2 pixel region from the original image, with each of the H/S/L/A channels
 * processed individually. Interpolate over the x-axis before the y-axis.
 *
 * Since interpolation will be the exact average between exactly two pixels, then
 * the Hue channel should be averaged over the shortest arc between the two values.
 * e.g. The average of H_1 = 10 and H_2 = 320 is H_avg = 345 and NOT 165.
 * In the case of two diametric hues being averaged, e.g. 10 and 190, the average will
 * have the smaller value, i.e. 100 and NOT 280.
 *
 * @pre referenceimg width and height are both even
 */
HSLAPixel QuarterColorPicker::operator()(PixelPoint p)
{

    // // Replace the line below with your implementation

    unsigned int x = p.x % scaledimg.width();
    unsigned int y = p.y % scaledimg.height();

    // return HSLAPixel();

    return *scaledimg.getPixel(x, y);
    // // Replace the line below with your implementation

    // // return result;

    //
}

/**
 * Add your private QuarterColorPicker function implementations below
 */

// static double averageHue(double h1, double h2)
// {
//     if (abs(h1 - h2) < 180.0)
//     {
//         // result.h = (result.h + temp[i].h) / 2.0;
//         return (h1 + h2) / 2.0;
//         // cout << "atributing new_h when result<180;" << endl;
//     }
//     else
//     {
//         return fmod((((h1 + h2) / 2.0) + 180.0), 360.0);
//         // cout << "atributing new_h when result>180;" << endl;
//     }
// }
