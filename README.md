# Depth First Search and Breadth First Search Image Filling Algorithms with Pixel Manipulation

#### Utilized a queue data structure to store elements for breadth-first-search filling algorithm, and a stack data structure for a depht-first-search filling algorithm. Several functors below to determine image fill behaviour.

## ImageTileColorPicker:
#### Determines the HSLAPixel to be used given an x and y coordinate and tiling one image over the dimensions of the target image, aligned to (0, 0).

### ImageTile Picker - Breadth First Search Output
![](https://github.com/chloevanct/PixelManipulation-bfs-dfs/blob/main/images-soln/ex-bfsimagetile.gif)

### ImageTile Picker - Depth First Search Output
![](https://github.com/chloevanct/PixelManipulation-bfs-dfs/blob/main/images-soln/ex-dfsimagetile.gif)

## NegativeBorderColorPicker: 
#### Picks the color for pixel (x,y); leaves pixel unchanged if it is not on the border of a fill region; if a pixel is on the border of a fill region, change it to the "negative" of the original colour value in the Hue and Luminance channels. The border of the image is considered to be a border of the fill region.

### NegativeBorder Picker - Breadth First Search Output
![](https://github.com/chloevanct/PixelManipulation-bfs-dfs/blob/main/images-soln/ex-bfsnegativeborder.gif)

### NegativeBorder Picker - Depth First Search Output
![](https://github.com/chloevanct/PixelManipulation-bfs-dfs/blob/main/images-soln/ex-dfsnegativeborder.gif)

## QuarterFill Picker: 
#### Determines the color that should be used given an x and y coordinate using a quartered image pattern. That is, using a private reference image, scaled each dimension by half and tile the smaller image in a 2 x 2 grid over the original dimensions of the image, and returned the pixel at the appropriate coordinate from the tiled image. The value of each pixel in the scaled image will be a bilinear interpolatiom of a 2x2 pixel region from the original image, with each of the H/S/L/A channels processed individually. 

### QuarterFill - Breadth First Search Output
![](https://github.com/chloevanct/PixelManipulation-bfs-dfs/blob/main/images-soln/ex-bfsquarter.gif)

### QuarterFill - Depth First Search Output
![](https://github.com/chloevanct/PixelManipulation-bfs-dfs/blob/main/images-soln/ex-dfsquarter.gif)
