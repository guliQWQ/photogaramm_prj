#pragma once
#include "stdio.h"
#include "CFeature_Matching.h"
#include<opencv2/opencv.hpp>
using namespace std;
class front_meeting
{   public:
	CFeature_Matching cf;
	bool nega_projection(vector<cv::Point3f>Xa,vector<cv::Point2f>Xl, vector<cv::Point2f>Xr);
	void Br();
	cv::Point3f r(cv::Point2f p1,cv::Point2f p2);
	void readInner(const char* innerPath);
	void frontmeet( const char* innerPath);
	cv::Point2f round(cv::Point2f p);
private:
	cv::Point3f Xs1=cv::Point3f(0,0,0);
	cv::Point3f Xs2;
	double u1 = 0, v1 = 0, omega1 = 0, fi1 = 0, kappa1 = 0;
	double u2 = 0, v2 = 0, omega2 = 0, fi2 = 0, kappa2 = 0;
	float dx, dy;
cv::Mat B;
cv::Mat B0 = cv::Mat::zeros(3,3, CV_32F);
cv::Mat dep;// ”≤ÓÕº
};

