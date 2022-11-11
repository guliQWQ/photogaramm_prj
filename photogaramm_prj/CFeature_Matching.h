#pragma once
#include<opencv2/opencv.hpp>
#include<vector>
#include<sstream>
#include "omp.h"
class CFeature_Matching
{
	friend class front_meeting;
public:
	CFeature_Matching();
	int create_empty_prj_file_for_feat_matching(const char* txt_path);
	float xgxs(cv::Mat im1, cv::Mat im2, int x1, int y1, int x2, int y2);
	int feat_matching(int key);
	int calibration(const char* image_path1, const char* image_path2, const char* inner_path);
	void input(const char* inner_path);
	void generation();
	void inB();
	double F0_(cv::Point2f p1, cv::Point2f p2);
	cv::Mat R(cv::Point2f p2);
	float Fu_(cv::Point2f p1, cv::Point2f p2);
	float Fv_(cv::Point2f p1, cv::Point2f p2);
	float Ffi_(cv::Point2f p1, cv::Point2f p2);
	float Fmiu_(cv::Point2f p1, cv::Point2f p2);
	float Fkappa_(cv::Point2f p1, cv::Point2f p2);
	void weight();
	void initialization();
	void sift(const char* sift_path);
	void setFolder(std::string s);

private:
	float f_1;
	float f_2;
	std::vector<cv::Point2f>leftPoint;
	std::vector<cv::Point2f>rightPoint;
	cv::Mat Bx;
	cv::Mat P ;
	cv::Mat l;
	cv::Mat x;
	cv::Mat V;
	double sigma0;
	double u , v , miu , fi , kappa ,Bs;//距离角度系数 
	cv::Point2f xy1, xy2 ;//像主点
	float sx;
	cv::Mat im10, im20;
	std::string folder,image_path1,image_path2;
	
};

