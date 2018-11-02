#include "CometManual.h"


CometManual::CometManual()
{

}

CometManual::CometManual(std::string infile, std::string outfile):CometMain(infile, outfile)
{
	ImgShow();
}

void CometManual::CallBackFunction(int evt, int x, int y, int flags, void* param)
{
	if (evt == cv::EVENT_LBUTTONDOWN)
	{
		CometManual* settings = reinterpret_cast<CometManual*>(param);
		if (settings->add)
		{
			settings->checkMouseAdd(evt, x, y);
		}
		else if(settings->read)
		{
			settings->checkMouseRead(evt, x, y);
		}
		else if (settings->deselect)
		{
			settings->checkMouseDeselect(evt, x, y);
		}
		else if (settings->addTail)
		{
			settings->checkMouseAddTail(evt, x, y);
		}

	}

}

void CometManual::checkMouseAdd(int evt, int x, int y)
{
	maxX = x;
	maxY = y;
	bool flag = false;
	for (int i = 0; i < myHeads.size(); i++)
	{
		if ((x >= (myHeads[i].x - CircleRadius[i])) && (x <= (myHeads[i].x + CircleRadius[i])) && (y >= (myHeads[i].y - CircleRadius[i])) && (y <= (myHeads[i].y + CircleRadius[i])))
		{
			flag = true;
			std::cout << "There was a comet aready found at this poistion" << std::endl;

		}
	}
	if (flag == false)
	{
		FindHeadRadius();
	}
	

}


void CometManual::checkMouseRead(int evt, int x, int y)
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

void CometManual::checkMouseDeselect(int evt, int x, int y)
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

void CometManual::checkMouseAddTail(int evt, int x, int y)
{
	std::cout << "Adding tail between: " << y + 100 << " and " << y - 100 << std::endl;
	line(img, cv::Point(x, y + 100), cv::Point(x, y - 100), cv::Scalar(255, 255, 255));
	tails.push_back(cv::Point(x, y));
	FindDNAH();
	FindDNAT();
	CaclDNAPer();
	SaveFile();
}

void CometManual::create3DImage()
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
					largestY[i] = j;
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
		std::string output = coordOut + "coord" + test + ".txt";
		outFile.open("Output\\" + output);
		for (int j = myHeads[i].y - CircleRadius[i]; j < myHeads[i].y + CircleRadius[i]; j += 10) //Going through the height or Y axis.
		{									// The height and width are equal the image is a square
			for (int k = myHeads[i].x - CircleRadius[i]; k < myHeads[i].x + CircleRadius[i]; k += 10) //  Going through the width or X axis. 
			{
				for (float l = -5; l < 5; l += 1)
				{
					outFile << (k - midX[i]) << "\n" << (j - midY[i]) << "\n" << l << "\n";
				}
			}
		}

		for (int m = myHeads[i].y - CircleRadius[i]; m < myHeads[i].y + CircleRadius[i]; m += 10) //Going through the height or Y axis.
		{									// The height and width are equal the image is a square
			for (int n = myHeads[i].x + CircleRadius[i]; n < tails[i].y; n += 1) //  Going through the width or X axis. 
			{
				newInten = testImg.at<uchar>(m, n);

				if (newInten >(IBKG))
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
}

void CometManual::FindHeadRadius()
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

	circle(img, cv::Point(maxX, maxY), (((testPoint.y - LeftSide.y) / 2)*1.5), cv::Scalar(255, 255, 255));
	CircleRadius.push_back(((testPoint.y - LeftSide.y) / 2)*1.5);
	rad = (((testPoint.y - LeftSide.y) / 2)*1.5);
	myHeads.push_back(cv::Point(maxX, maxY));
}

void CometManual::FindTail()
{

	bool rightSideFlag = false;

	uint8_t newInten;
	for (int j = maxX + rad; j < img.cols; j++)
	{
		newInten = testImg.at<uchar>(maxY, j);

		if (!rightSideFlag)
		{
			if (newInten < TC)
			{
				line(img, cv::Point(j, maxY + 100), cv::Point(j, maxY - 100), cv::Scalar(255, 255, 255));
				tails.push_back(cv::Point(j, maxY));
				rightSideFlag = true;
			}
		}
	}

}


void CometManual::ImgShow()
{
	cv::namedWindow("Image", cv::WINDOW_NORMAL);
	


	cv::setMouseCallback("Image", CallBackFunction, this);



	while (true)
	{
		imshow("Image", img);
	
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
			add = false;
			addTail = false;
			
		}
		else if (c == 'r')
		{
			read = true;
			deselect = false;
			add = false;
			addTail = false;
			
		}
		else if (c == 'a')
		{
			read = false;
			deselect = false;
			add = true;
			addTail = false;
			
		}
		else if (c == 't')
		{
			read = false;
			deselect = false;
			add = false;
			addTail = true;
			
		}
		else if (c == 'm')
		{
			create3DImage();
		}
	}

}
