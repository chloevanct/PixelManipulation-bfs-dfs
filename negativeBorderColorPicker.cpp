/**
 * @file negativeBorderColorPicker.cpp
 * @description Implements the NegativeBorderColorPicker constructor and () function
 *              for CPSC 221 2023S PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "negativeBorderColorPicker.h"
#include <math.h>

// 1.) compare the current pixel with the source pixel
// 2.) if the colors are within tolerance then its eligible to be changed to negative
// 3.) if the colors are in tolerance, then compare with's surrounding pixels
// 4.) if surrounding pixel's colors are over tolerance than you changed your current pixel to be negative
// 5.)

NegativeBorderColorPicker::NegativeBorderColorPicker(PNG &inputimg, PixelPoint src_px, unsigned int width, double tol)
{
    // Complete your implementation below

    referenceimg = inputimg;
    source_px = src_px;
    borderwidth = width;
    tolerance = tol;

    // unsigned int start_x = source_px.x;
    // unsigned int start_y = source_px.y;

    // for (unsigned int i = 0; i<referenceimg.width(); i++) {

    //     for (unsigned int j = 0; j<referenceimg.height(); j++) {

    //         HSLAPixel *current_pixel = referenceimg.getPixel(i,j);

    //         if (i == 0 || j == 0 || i < borderwidth || j < borderwidth) {

    //             if (current_pixel->h < 180.0)
    //                 {
    //                     current_pixel->h = current_pixel->h + 180.0;
    //                 }
    //                 else
    //                 {
    //                     current_pixel->h = current_pixel->h - 180.0;
    //                 }

    //                 current_pixel->l = abs(1.0 - current_pixel->l);

    //         }

    //         else {

    //             // HSLAPixel above_pixel = *referenceimg.getPixel(i,j-1);
    //             // HSLAPixel left_pixel = *referenceimg.getPixel(i-1,j);

    //             // unsigned int euc_dist_above = sqrt(pow(current_pixel->h - above_pixel.h, 2) + pow(current_pixel->s - above_pixel.s, 2) + pow(current_pixel->l - above_pixel.l, 2) + pow(current_pixel->a - above_pixel.a, 2));
    //             // unsigned int euc_dist_left = sqrt(pow(current_pixel->h - left_pixel.h, 2) + pow(current_pixel->s - left_pixel.s, 2) + pow(current_pixel->l - left_pixel.l, 2) + pow(current_pixel->a - left_pixel.a, 2));

    //             // if ((i - start_x < borderwidth || j - start_y < borderwidth) && ((euc_dist_above > tolerance) || (euc_dist_left > tolerance)) ) {
    //             //     if (current_pixel->h < 180.0)
    //             //     {
    //             //         current_pixel->h = current_pixel->h + 180.0;
    //             //     }
    //             //     else
    //             //     {
    //             //         current_pixel->h = current_pixel->h - 180.0;
    //             //     }

    //             //     current_pixel->l = abs(1.0 - current_pixel->l);
    //             // }
    //         }

    //     }
    // }
}

/**
 * Picks the color for pixel (x, y).
 *
 * Leaves a pixel unchanged if it is not on the border of a fill region
 *
 * If a pixel is on the border of a fill region, change it to the "negative"
 * of the original colour value in the Hue and Luminance channels.
 * Saturation and Alpha should remain unchanged.
 * Based on your understanding of HSL colour space from Lab_intro,
 * think about what would be an appropriate "negative" transformation for the
 * Hue and Luminance channels.
 *
 * Hint: a pixel is on the border of a fill region, if it is within "width"
 * pixels of a pixel which is NOT in the fill region!
 *
 * Also: the border of the image is considered to be a border of the fill region.
 */
HSLAPixel NegativeBorderColorPicker::operator()(PixelPoint p)
{

    HSLAPixel cur_pixel = *referenceimg.getPixel(p.x, p.y);

    // check if pixel is on the image border, if so change it to it's negative pixel color
    // if (p.x < borderwidth || p.y < borderwidth || p.x >= referenceimg.width() - borderwidth || p.y >= referenceimg.height() - borderwidth)     // if its on the border of the whole image
    if (p.x < borderwidth || p.y < borderwidth || p.x >= referenceimg.width() - borderwidth || p.y >= referenceimg.height() - borderwidth) // if its on the border of the whole image
    {
        if (cur_pixel.h < 180.0)
        {
            cur_pixel.h = cur_pixel.h + 180.0;
        }
        else
        {
            cur_pixel.h = cur_pixel.h - 180.0;
        }
        cur_pixel.l = abs(1.0 - cur_pixel.l);

        return cur_pixel;
    }

    // unsigned int cur_x = p.x;
    // unsigned int cur_y = p.y;

    // Replace the line below with your implementation'
    // check whether the current pixel matches to the colour of the source pixel
    // check if the pixel is on the border (meaning, if the pixel in its drect surrounding is over tolernace than the source pixel)

    unsigned int upper_x = p.x + borderwidth;
    unsigned int lower_x = p.x - borderwidth;

    unsigned int upper_y = p.y + borderwidth;
    unsigned int lower_y = p.y - borderwidth;

    // if (cur_x >= source_px.x && cur_y >= source_px.y)

    // if (source_px.color.distanceTo(cur_pixel) <= tolerance) // we only traverse the pixels that are within tolerance of source pixel
    // {
    for (unsigned int x = lower_x; x <= upper_x; x++)
    {
        for (unsigned int y = lower_y; y <= upper_y; y++)
        {

            HSLAPixel border_pixel = *referenceimg.getPixel(x, y);

            // unsigned int euc_dist = sqrt(pow(p.color.h - border_pixel.h, 2) + pow(p.color.s - border_pixel.s, 2) + pow(p.color.l - border_pixel.l, 2) + pow(p.color.a - border_pixel.a, 2));

            if (sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y)) <= borderwidth)
            {

                if (source_px.color.distanceTo(border_pixel) > tolerance)
                {
                    if (cur_pixel.h < 180.0)
                    {
                        cur_pixel.h = cur_pixel.h + 180.0;
                    }
                    else
                    {
                        cur_pixel.h = cur_pixel.h - 180.0;
                    }

                    cur_pixel.l = abs(1.0 - cur_pixel.l);

                    return cur_pixel;
                }
            }
        }
    }
    // }

    // }

    return cur_pixel;
}

// unsigned int cur_x = p.x;
// unsigned int cur_y = p.y;

// unsigned int upper_x = p.x + borderwidth;
// unsigned int lower_x = p.x - borderwidth;

// unsigned int upper_y = p.y + borderwidth;
// unsigned int lower_y = p.y - borderwidth;

// if (cur_x >= source_px.x && cur_y >= source_px.y)
// {
//     for (unsigned int x = lower_x; x <= upper_x; x++)
//     {
//         for (unsigned int y = lower_y; y <= upper_y; y++)
//         {
//             if (x < 0 || y < 0 || x >= referenceimg.width() || y >= referenceimg.height())
//             {
//                 return p.color;
//             }

//             HSLAPixel border_pixel = *referenceimg.getPixel(x, y);
//             unsigned int euc_dist = sqrt(pow(p.color.h - border_pixel.h, 2) + pow(p.color.s - border_pixel.s, 2) + pow(p.color.l - border_pixel.l, 2) + pow(p.color.a - border_pixel.a, 2));

//             if (euc_dist > tolerance)
//             {
//                 if (p.color.h < 180.0)
//                 {
//                     p.color.h = p.color.h + 180.0;
//                 }
//                 else
//                 {
//                     p.color.h = p.color.h - 180.0;
//                 }

//                 p.color.l = abs(1.0 - p.color.l);

//                 return p.color;
//             }
//             // else
//             // {
//             //     return p.color;
//             // }
//         }
//     }
// }

// return p.color;
