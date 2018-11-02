#pragma once
#pragma managed
#include "opencv2/highgui/highgui.hpp"
#include<opencv2/opencv.hpp>
#include<iostream>
#include <cliext\vector>
#include <ostream>


class CometMain
{
public:
	CometMain();
	CometMain(std::string infile, std::string outfile);
	void SaveFile();
	void FindDNAH();
	void FindDNAT();
	void CaclDNAPer();
protected:
	double IBKG;
	double IMAX; 
	double TC;
	double LowerBounds;// IBKG is Image Background Level Intensity, IMAX is Maximum Image Intensity, TC is comet theshold
	std::string OutFile;
	std::string coordOut;
#pragma region Points
	cv::Point IBKG_LOC;
	cv::Point IMAX_LOC;
	cv::Point LeftSide; //Holds the left side of the head
	cv::Point tailRightSide; //Holds the right side of the tail
#pragma endregion

#pragma region Mats
	cv::Mat img; //Main Colour Image. To be shown
	cv::Mat grayImg; // Gray version of Img, to be converted
	cv::Mat threshImg; // Shows only the heads found in the pictures, not to be shown
	cv::Mat testImg;	// Shows the tail including the head, not to be shown
	cv::Mat topImg;
	cv::Mat sideImg;
	cv::Mat frontImg;
#pragma endregion
	int maxX, maxY; // Always changing X and Y coordinated on the screen, stored to jump between functions
	std::vector<int> CircleRadius; // Vector of the radius of the heads
	std::vector<double> DNAH;
	std::vector<double> DNAT;
	std::vector<double> pDNAH;
	std::vector<double> pDNAT;
	std::vector<cv::Point> myHeads;
	std::vector<cv::Point> tails; // Vector that stores the middle of the head and end of the tail
	std::vector <cv::Point> xy;
};

