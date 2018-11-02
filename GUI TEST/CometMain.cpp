#include "CometMain.h"



CometMain::CometMain()
{
}

CometMain::CometMain(std::string infile, std::string outfile)
{
	
	img = cv::imread("Images\\"+infile);
	if (outfile == "")
	{
		OutFile = "NoFileNameGiven.csv";
		coordOut = "NoFileNameGiven";
	}
	else
	{
		OutFile = outfile + ".csv";
		coordOut = outfile;
	}
	
	if (!img.data)
	{
		std::cout << "This has failed" << std::endl;
		exit(1);
	}
	cvtColor(img, grayImg, CV_RGB2GRAY);
	minMaxLoc(grayImg, &IBKG, &IMAX, &IBKG_LOC, &IMAX_LOC);
	
	TC = (IBKG + IMAX) / 2;
	LowerBounds = IMAX * 0.8;
	blur(grayImg, threshImg, cv::Size(11, 11), cv::Point(-1, -1));
	threshold(threshImg, threshImg, TC, 255, cv::THRESH_BINARY);
	threshold(grayImg, testImg, (TC / 4), 255, cv::THRESH_BINARY);
	threshold(grayImg, topImg, 0, 0, cv::THRESH_BINARY);
	threshold(grayImg, frontImg, 0, 0, cv::THRESH_BINARY);
	threshold(grayImg, sideImg, 0, 0, cv::THRESH_BINARY);
	maxX = 0;
	maxY = 0;
}

void CometMain::SaveFile()
{
	std::ofstream outFile;
	outFile.open("Output\\"+OutFile);
	outFile << "DNA Head Intensity" << "," << "DNA Tail Intensity" << "," << "DNA Head Percentage" << "," << "DNA Tail Percentage" << std::endl;
	for (int i = 0; i < myHeads.size(); i++)
	{
		outFile << DNAH[i] << "," << DNAT[i] << "," << pDNAH[i] << "," << pDNAT[i] << std::endl;
	}

	outFile.close();
}

//CAN BE CHANGED OUT FOR NEW ALGORITHIMS
void CometMain::FindDNAH()
{
	uint8_t newInten;
	for (int i = 0; i < myHeads.size(); i++)
	{
		DNAH.push_back(0);
		for (int j = myHeads[i].y - CircleRadius[i]; j < myHeads[i].y + CircleRadius[i]; j++) //Going through the height or Y axis.
		{									// The height and width are equal the image is a square
			for (int k = myHeads[i].x - CircleRadius[i]; k < myHeads[i].x + CircleRadius[i]; k++) //  Going through the width or X axis. 
			{
				newInten = grayImg.at<uchar>(j, k); // This uses the X and Y to find a new point

				DNAH[i] = DNAH[i] + newInten;
			}
		}
	}
}
//CAN BE CHANGED OUT FOR NEW ALGORITHIMS
void CometMain::FindDNAT()
{
	
	uint8_t newInten;


	for (int i = 0; i < myHeads.size(); i++)
	{
		DNAT.push_back(0);
		for (int j = myHeads[i].y - CircleRadius[i]; j < myHeads[i].y + CircleRadius[i]; j++) //Going through the height or Y axis.
		{									// The height and width are equal the image is a square
			for (int k = myHeads[i].x + CircleRadius[i]; k < tails[i].y; k++) //  Going through the width or X axis. 
			{
				newInten = grayImg.at<uchar>(j, k); // This uses the X and Y to find a new point

				DNAT[i] = DNAT[i] + newInten;
			}
		}
		}
}
//CAN BE CHANGED OUT FOR NEW ALGORITHIMS
void CometMain::CaclDNAPer()
{
	for (int i = 0; i < myHeads.size(); i++)
	{
		pDNAT.push_back(DNAT[i] / (DNAH[i] + DNAT[i] * 100));
		pDNAH.push_back(100 - pDNAT[i]);
	}
}


