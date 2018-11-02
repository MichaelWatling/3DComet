#include "CometAuto.h"


CometAuto::CometAuto()
{

}

CometAuto::CometAuto(std::string infile, std::string outfile):CometMain(infile, outfile)
{
	FindHead();
	FindTail();
	DrawShapes();
	FindDNAH();
	FindDNAT();
	CaclDNAPer();
	SaveFile();
	ImgShow();
}

void CometAuto::DrawShapes()
{
	std::cout << "Drawing shapes..." << std::endl;

	for (int i = 0; i < myHeads.size(); i++)
	{
		circle(img, myHeads[i], CircleRadius[i], cv::Scalar(255, 255, 255),6);
		line(img, cv::Point(tails[i].x, tails[i].y + 100), cv::Point(tails[i].x, tails[i].y - 100), cv::Scalar(255, 255, 255));
	}

}



void CometAuto::FindHead()
{
	std::cout << "Finding Head..." <<std:: endl;

	uint8_t newInten;
	uint8_t grayMax = threshImg.at<uint8_t>(maxY, maxX);

	for (int i = 0; i < img.rows; i++) //Going through the height or Y axis.
	{									// The height and width are equal the image is a square
		for (int j = 0; j < img.cols; j++) //  Going through the width or X axis. 
		{
			newInten = threshImg.at<uchar>(i, j); // This uses the X and Y to find a new point

			if (newInten > LowerBounds) //Compaired to lower bounds (80% of max pixel intensity)
			{
				grayMax = newInten;
				maxX = j;
				maxY = i;
				if (myHeads.size() > 0) {
					j = CheckIfInBounds();
					//cout << j << " " << i << endl;

				}
				else
				{
					findNewHead();
				}

			}


		}

	}

}

void CometAuto::FindTail()
{
	bool rightSideFlag;

	uint8_t newInten;

	for (int i = 0; i < myHeads.size(); i++)
	{
		rightSideFlag = false;
		for (int j = myHeads[i].x + CircleRadius[i]; j < img.cols; j++)
		{
			newInten = testImg.at<uchar>(myHeads[i].y, j);

			if (!rightSideFlag)
			{
				if (newInten < TC)
				{
					tails.push_back(cv::Point(j, myHeads[i].y));
					rightSideFlag = true;
				}
			}
		}
	}
}

void CometAuto::FindHeadRadius()
{
	

	bool leftSideFlag = false;
	uint8_t newInten;

	for (int i = maxX; i > 0; i--)
	{
		newInten = threshImg.at<uchar>(maxY, i);

		if (!leftSideFlag)
		{
			if (newInten < TC)
			{
				LeftSide = { maxY, i };
				leftSideFlag = true;
			}
		}
	}

	if (!leftSideFlag)
	{
		LeftSide.y = 0;
	}

	bool testFlag = false;
	cv::Point testPoint;
	for (int i = maxX; i < img.cols; i++)
	{
		newInten = threshImg.at<uchar>(maxY, i);

		if (!testFlag)
		{
			if (newInten < TC)
			{
				testPoint = { maxY, i };
				testFlag = true;
			}
		}
	}

	if (!testFlag)
	{
		testPoint.y = img.cols;
	}

	CircleRadius.push_back(((testPoint.y - LeftSide.y) / 2)*1.5);
	maxX = (testPoint.y + LeftSide.y) / 2;
	myHeads.push_back(cv::Point(maxX, maxY));
}

void CometAuto::ImgShow()
{
	cv::namedWindow("Image", cv::WINDOW_NORMAL);

	cv::setMouseCallback("Image", CallBackFunction, this);

	while (true)
	{
		cv::imshow("Image", img);
		char c = cv::waitKey(0);
		if (c == 'q')
		{
			cv::destroyAllWindows();
			break;
		}
		else if (c == 'd')
		{
			read = false;
			deselect = true;
		}
		else if (c == 'r')
		{
			read = true;
			deselect = false;
		}
		else if (c == 'm')
		{
			create3DImage();
		}
	}
	
	



}

void CometAuto::findNewHead()
{
	uint8_t newInten;
	cv::Point findBottom;

	for (int i = maxY; i < img.rows; i++)
	{
		newInten = threshImg.at<uchar>(i, maxX);

		if (newInten < TC)
		{
			findBottom = { i, maxX };
			i = img.rows;
		}
	}
	maxY = (maxY + findBottom.x) / 2;
	FindHeadRadius();
}

int CometAuto::CheckIfInBounds()
{
	int tbr = maxX;
	for (int i = 0; i < myHeads.size(); i++)
	{
		if ((maxX >= (myHeads[i].x - CircleRadius[i])) && (maxX <= (myHeads[i].x + CircleRadius[i])) && (maxY >= (myHeads[i].y - CircleRadius[i])) && (maxY <= (myHeads[i].y + CircleRadius[i])))
		{
			//cout << maxX << " " << (myHeads[i].x - CircleRadius[i]) << " " << (myHeads[i].x + CircleRadius[i]) << " " << maxY << " " << (myHeads[i].y - CircleRadius[i]) << " " << (myHeads[i].y + CircleRadius[i]) << endl;
			tbr = (myHeads[i].x + CircleRadius[i]);
			return tbr;
		}
	}

	findNewHead();
	return tbr;
}

void CometAuto::CallBackFunction(int evt, int x, int y, int flags, void* param)
{
	if (evt == cv::EVENT_LBUTTONDOWN)
	{
		CometAuto* settings = reinterpret_cast<CometAuto*>(param);
		if (settings->read)
		{
			settings->checkMouseRead(evt, x, y);
		}
		else if (settings->deselect)
		{
			settings->checkMouseDeselect(evt, x, y);
		}
		
	}

}

void CometAuto::checkMouseRead(int evt, int x, int y)
{
	bool flag = false;

	for (int i = 0; i < myHeads.size(); i++)
	{
		if ((x >= (myHeads[i].x - CircleRadius[i])) && (x <= (myHeads[i].x + CircleRadius[i])) && (y >= (myHeads[i].y - CircleRadius[i])) && (y <= (myHeads[i].y + CircleRadius[i])))
		{
			flag = true;
			std::cout << "DNAH: " << DNAH[i] << " DNAT: " << DNAT[i] << " pDNAH: " << pDNAH[i] << " pDNAH: " << pDNAT[i] << std::endl;

		}
	}
	if (flag == false)
	{
		std::cout << "No comet found at co-ordinates: " << x << " " << y << std::endl;
	}
}

void CometAuto::checkMouseDeselect(int evt, int x, int y)
{
	bool flag = false;

	for (int i = 0; i < myHeads.size(); i++)
	{
		if ((x >= (myHeads[i].x - CircleRadius[i])) && (x <= (myHeads[i].x + CircleRadius[i])) && (y >= (myHeads[i].y - CircleRadius[i])) && (y <= (myHeads[i].y + CircleRadius[i])))
		{
			flag = true;
			std::cout << "Deleting Comet" << std::endl;
			myHeads.erase(myHeads.begin() + i);
			tails.erase(tails.begin() + i);
			CircleRadius.erase(CircleRadius.begin() + i);
			DNAH.erase(DNAH.begin() + i);
			DNAT.erase(DNAT.begin() + i);
			pDNAH.erase(pDNAH.begin() + i);
			pDNAT.erase(pDNAT.begin() + i);
			SaveFile();
		}
	}
	if (flag == false)
	{
		std::cout << "No comet found at co-ordinates: " << x << " " << y << std::endl;
	}
}

void CometAuto::create3DImage()
{
	std::vector<float> smallestY;
	std::vector<float> smallestX;;
	std::vector<float> largestY;
	std::vector<float> largestX;

	uint8_t newInten;

	for (int i = 0; i < myHeads.size(); i++)
	{
		smallestY.push_back(img.rows);
		smallestX.push_back(img.cols);
		largestY.push_back(0);
		largestX.push_back(0);
		for (int j = myHeads[i].y - CircleRadius[i]; j < myHeads[i].y + CircleRadius[i]; j++) //Going through the height or Y axis.
		{									// The height and width are equal the image is a square
			for (int k = myHeads[i].x - CircleRadius[i]; k < myHeads[i].x + CircleRadius[i]; k++) //  Going through the width or X axis. 
			{
				if (j < smallestY[i])
				{
					smallestY[i] = j;
				}
				else if (k < smallestX[i])
				{
					smallestX[i] = k;
				}
				else if (j> largestY[i])
				{
					largestY[i] =j;
				}
				else if (k > largestX[i])
				{
					largestX[i] = k;
				}

			}
		}
	}


	for (int i = 0; i < myHeads.size(); i++)
	{

		for (int j = myHeads[i].y - CircleRadius[i]; j < myHeads[i].y + CircleRadius[i]; j++) //Going through the height or Y axis.
		{									// The height and width are equal the image is a square
			for (int k = myHeads[i].x + CircleRadius[i]; k < tails[i].y; k++) //  Going through the width or X axis. 
			{

				if (j < smallestY[i])
				{
					smallestY[i] = j;
				}
				else if (k < smallestX[i])
				{
					smallestX[i] = k;
				}
				else if (j> largestY[i])
				{
					largestY[i] = j;
				}
				else if (k > largestX[i])
				{
					largestX[i] = k;
				}

			}
		}
	}
	std::vector<float> midY;
	std::vector<float> midX;

	for (int i = 0; i < largestY.size(); i++)
	{
		midY.push_back((largestY[i] + smallestY[i]) / 2);
		midX.push_back((largestX[i] + smallestX[i]) / 2);
	}
	

	std::ofstream outFile;
	

	for (int i = 0; i < myHeads.size(); i++)
	{
		std::string test = std::to_string(i);
		std::string output = coordOut +"coord"+ test + ".txt";
		outFile.open("Output\\"+output);
		for (int j = myHeads[i].y - CircleRadius[i]; j < myHeads[i].y + CircleRadius[i]; j+=10) //Going through the height or Y axis.
		{									// The height and width are equal the image is a square
			for (int k = myHeads[i].x - CircleRadius[i]; k < myHeads[i].x + CircleRadius[i]; k+=10) //  Going through the width or X axis. 
			{
				for (float l = -5; l < 5; l += 1)
				{
					outFile << (k - midX[i]) << "\n" << (j - midY[i]) << "\n" << l << "\n";
				}
			}
		}

		for (int m = myHeads[i].y - CircleRadius[i]; m < myHeads[i].y + CircleRadius[i]; m+=10) //Going through the height or Y axis.
		{									// The height and width are equal the image is a square
			for (int n = myHeads[i].x + CircleRadius[i]; n < tails[i].y; n+=1) //  Going through the width or X axis. 
			{
				newInten = testImg.at<uchar>(m, n);

				if (newInten > (IBKG))
				{
					for (float o = -5; o < 5; o += 1)
					{
						outFile << (n - midX[i]) << "\n" << (m - midY[i]) << "\n" << o << "\n";
					}
				}
				

			}
		}
		outFile.close();
	}

	
	std::cout << "Saved File" << std::endl;

	/*uint8_t newInten;

	


	for (int i = 0; i < xy.size(); i++)
	{
		cv::circle(topImg, cv::Point(xy[i].x, xy[i].y), 1, cv::Scalar(255, 255, 255));
		for (int j = 0; j < 100; j = j + 10)
		{
			cv::circle(sideImg, cv::Point(xy[i].x, xy[i].y + j), 1, cv::Scalar(255, 255, 255));
			cv::circle(frontImg, cv::Point(xy[0].x + j, xy[i].y), 1, cv::Scalar(255, 255, 255));
		}


	}
	cv::namedWindow("Top Test", cv::WINDOW_NORMAL);
	cv::namedWindow("Side Test", cv::WINDOW_NORMAL);
	cv::namedWindow("Front Test", cv::WINDOW_NORMAL);

	cv::imshow("Top Test", topImg);
	cv::imshow("Side Test", sideImg);
	cv::imshow("Front Test", frontImg);*/


}