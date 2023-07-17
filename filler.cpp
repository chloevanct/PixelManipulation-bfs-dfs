/**
 * File:        filler.cpp
 * Description: Implementation of functions in the filler namespace.
 *
 *              SUBMIT THIS FILE WITH YOUR MODIFICATIONS
 */

/**
 * Performs a flood fill using breadth first search.
 *
 * @param config FillerConfig struct to setup the fill
 * @return animation object illustrating progression of flood fill algorithm
 */
animation filler::FillBFS(FillerConfig &config)
{

	// Call the Fill function with Queue as the ordering structure
	return Fill<Queue>(config);

	// complete your implementation below
	// You should replace the following line with a
	// correct call to fill.
	// return animation(); // REPLACE THIS STUB
}

/**
 * Performs a flood fill using depth first search.
 *
 * @param  config - FillerConfig struct to setup the fill
 * @return animation object illustrating progression of flood fill algorithm
 */
animation filler::FillDFS(FillerConfig &config)
{
	// os = Stack();
	// complete your implementation below
	// You should replace the following line with a
	// correct call to fill.
	return Fill<Stack>(config); // REPLACE THIS STUB
}

/**
 * Run a flood fill on an image starting at the seed point
 *
 * @param config FillerConfig struct with data for flood fill of image
 * @return animation object illustrating progression of flood fill algorithm
 */
template <template <class T> class OrderingStructure>
animation filler::Fill(FillerConfig &config)
{

	/**
	 * You need to implement this function!
	 *
	 * This is the basic description of a flood-fill algorithm: Every fill
	 * algorithm requires an ordering structure, which is passed to this
	 * function via its template parameter. For a breadth-first-search
	 * fill, that structure is a Queue, for a depth-first-search, that
	 * structure is a Stack. To begin the algorithm, you simply place the
	 * given point in the ordering structure, marking it processed
	 * (the way you mark it is a design decision you'll make yourself).
	 * We have a choice to either change the color, if appropriate, when we
	 * add the point to the OS, or when we take it off. In our test cases,
	 * we have assumed that you will change the color when a point is removed
	 * from the structure.
	 * Until the structure is empty, you do the following:
	 *
	 * 1.     Remove a point from the ordering structure, and then...
	 *
	 *        1.    add its unprocessed neighbors (up/down/left/right) whose color values are
	 *              within (or equal to) tolerance distance from the seed point,
	 *              to the ordering structure, and
	 *              mark them as processed.
	 *        2.    if it is an appropriate frame, send the current PNG to the
	 *              animation (as described below).
	 *
	 * 2.     When implementing your breadth-first-search and
	 *        depth-first-search fills, you will need to explore neighboring
	 *        pixels (up/down/left/right) in some order.
	 *
	 *        While the order in which you examine neighbors does not matter
	 *        for a proper fill, you must use the same order as we do for
	 *        your animations to come out like ours! The order you should put
	 *        neighboring pixels **ONTO** the queue or stack is as follows:
	 *        1. western neighbour (left)
	 *        2. northern neighbour (up)
	 *        3. eastern neighbour (right)
	 *        4. southern neighbour (down)
	 *
	 *        If you process the neighbours in a different order, your fill may
	 *        still work correctly, but your animations will be different
	 *        from the grading scripts!
	 *
	 * 3.     For every k pixels filled, **starting at the kth pixel**, you
	 *        must add a frame to the animation, where k = frameFreq.
	 *
	 *        For example, if frameFreq is 4, then after the 4th pixel has
	 *        been filled you should add a frame to the animation, then again
	 *        after the 8th pixel, etc.  You must only add frames for the
	 *        number of pixels that have been filled, not the number that
	 *        have been checked. So if frameFreq is set to 1, a pixel should
	 *        be filled every frame.
	 *
	 * 4.     Finally, as you leave the function, send one last frame to the
	 *        animation. This frame will be the final result of the fill, and
	 *        it will be the one we test against.
	 *
	 */

	int framecount = 0;
	animation anim;
	OrderingStructure<PixelPoint> os;

	vector<vector<bool>> processed(config.img.width(), vector<bool>(config.img.height(), false));

	os.Add(config.seedpoint);
	processed[config.seedpoint.x][config.seedpoint.y] = true;

	while (!os.IsEmpty())
	{
		PixelPoint current = os.Remove();
		current.color = (*config.picker)(current);
		*config.img.getPixel(current.x, current.y) = current.color;

		if (framecount % config.frameFreq == 0)
		{
			anim.addFrame(config.img);
		}

		framecount++;

		vector<PixelPoint> neighbors;

		if (current.x > 0 && !processed[current.x - 1][current.y])
		{
			PixelPoint neighborW(current.x - 1, current.y, *config.img.getPixel(current.x - 1, current.y)); // left
			neighbors.push_back(neighborW);
			processed[current.x - 1][current.y] = true;
		}

		if (current.y > 0 && !processed[current.x][current.y - 1])
		{
			PixelPoint neighborN(current.x, current.y - 1, *config.img.getPixel(current.x, current.y - 1)); // up
			neighbors.push_back(neighborN);
			processed[current.x][current.y - 1] = true;
		}

		if (current.x < config.img.width() - 1 && !processed[current.x + 1][current.y])
		{
			PixelPoint neighborE(current.x + 1, current.y, *config.img.getPixel(current.x + 1, current.y)); // right
			neighbors.push_back(neighborE);
			processed[current.x + 1][current.y] = true;
		}

		if (current.y < config.img.height() - 1 && !processed[current.x][current.y + 1])
		{
			PixelPoint neighborS(current.x, current.y + 1, *config.img.getPixel(current.x, current.y + 1)); // down
			neighbors.push_back(neighborS);
			processed[current.x][current.y + 1] = true;
		}

		for (auto &neighbor : neighbors)
		{
			if (neighbor.color.distanceTo(config.seedpoint.color) <= config.tolerance)
			{
				os.Add(neighbor);
			}
		}
	}

	anim.addFrame(config.img); // Add the final result frame

	return anim;

	// int os_size = 0;
	// int framecount = 0; // increment after processing one pixel; used for producing animation frames (step 3 above)
	// animation anim;
	// OrderingStructure<PixelPoint> os;

	// // complete your implementation below
	// // HINT: you will likely want to declare some kind of structure to track
	// //       which pixels have already been visited

	// // To begin the algorithm, you simply place the
	// // 	 * given point in the ordering structure, marking it processed
	// // 	 * (the way you mark it is a design decision you'll make yourself).
	// // 	 * We have a choice to either change the color, if appropriate, when we
	// // 	 * add the point to the OS, or when we take it off. In our test cases,
	// // 	 * we have assumed that you will change the color when a point is removed
	// // 	 * from the structure.

	// vector<vector<bool>> processed(config.img.width(), vector<bool>(config.img.height(), false));

	// os.Add(config.seedpoint); // place given point in the ordering structure
	// processed[config.seedpoint.x][config.seedpoint.y] = true;
	// // BEG
	// // vector<PixelPoint> processed;

	// PNG result_img = config.img;

	// os_size++;
	// // unsigned int frame_it = 0;

	// while (!os.IsEmpty())
	// {
	// 	// cout << "starting iteration " << framecount << endl;

	// 	PixelPoint current = os.Remove();
	// 	os_size--;
	// 	// cout << "os size:  " << os_size << endl;
	// 	current.color = (*config.picker)(current); // takes current pixel and passes it to its color picker

	// 	*result_img.getPixel(current.x, current.y) = current.color;

	// 	if (framecount % config.frameFreq == 0)
	// 	{
	// 		anim.addFrame(result_img);
	// 		// cout << "added animation" << endl;
	// 	}

	// 	framecount++;

	// 	// processed.push_back(current);
	// 	// processed[current.x][current.y] = true;

	// 	// check if pixels we're retrieving are out of bounds

	// 	vector<PixelPoint> temp;

	// 	if (current.x > 0)
	// 	{
	// 		PixelPoint neighborW(current.x - 1, current.y, *config.img.getPixel(current.x - 1, current.y)); // left
	// 		temp.push_back(neighborW);
	// 		processed[neighborW.x][neighborW.y] = true;
	// 	}

	// 	if (current.y > 0)
	// 	{
	// 		PixelPoint neighborN(current.x, current.y - 1, *config.img.getPixel(current.x, current.y - 1)); // up
	// 		temp.push_back(neighborN);
	// 		processed[neighborN.x][neighborN.y] = true;
	// 	}

	// 	if (current.x < config.img.width() - 1)
	// 	{
	// 		PixelPoint neighborE(current.x + 1, current.y, *config.img.getPixel(current.x + 1, current.y)); // right
	// 		temp.push_back(neighborE);
	// 		processed[neighborE.x][neighborE.y] = true;
	// 	}

	// 	if (current.y < config.img.height() - 1)
	// 	{
	// 		PixelPoint neighborS(current.x, current.y + 1, *config.img.getPixel(current.x, current.y + 1)); // down
	// 		temp.push_back(neighborS);
	// 		processed[neighborY.x][neighborY.y] = true;
	// 	}

	// 	// check if neighbour pixels are already in array

	// 	for (unsigned int i = 0; i < temp.size(); i++)
	// 	{
	// 		// bool isThere = false;

	// 		if (!processed[temp[i].x][temp[i].y] && temp[i].color.distanceTo(config.seedpoint.color) <= config.tolerance)
	// 		{
	// 			os.Add(temp[i]);
	// 			os.size();
	// 		}
	// 		// for (unsigned int j = 0; j < processed.size(); j++)
	// 		// {

	// 		// 	if ((temp[i].x == processed[j].x) && (temp[i].y == processed[j].y))
	// 		// 	{
	// 		// 		isThere = true;
	// 		// 		break;
	// 		// 		// cout << "the current pixel is in the processed array? (1 if true): " << isThere << endl;
	// 		// 	}
	// 		// }

	// 		// check if neighbour pixels are within tolerance, if over tolerance add to os.
	// 		// whose color values are
	// 		// within (or equal to) tolerance distance from the seed point,
	// 		// to the ordering structure, and
	// 		// mark them as processed.

	// 		// if (p.color.distanceTo(border_pixel) >= tolerance)

	// 		// cout << "is the current pixel in processed array?" << isThere << endl;
	// 		// cout << "distance to seedpoint is" << temp[i].color.distanceTo(config.seedpoint.color) << endl;
	// 		// cout << "tolerance is" << config.tolerance << endl;

	// 		// if (!isThere && temp[i].color.distanceTo(config.seedpoint.color) <= config.tolerance)
	// 		// {
	// 		// 	// cout << "adding to the orderin structure" << endl;
	// 		// 	os.Add(temp[i]);
	// 		// 	os_size++;
	// 		// 	cout << "os size:  " << os_size << endl;
	// 		// 	cout << "processed size  " << processed.size() << endl;
	// 		// 	cout << "added x:  " << temp[i].x << "and added y:  " << temp[i].y << endl;
	// 		// 	cout << "the current pixel is in the processed array? (1 if true): " << isThere << endl;
	// 		// }
	// 	}

	// 	// END
	// }
	// return anim;
}