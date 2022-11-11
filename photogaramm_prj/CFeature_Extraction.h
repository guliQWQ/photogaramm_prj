#pragma once
#include<opencv2/opencv.hpp>
class CFeature_Extraction
{
public:
	int create_empty_prj_file_for_feat_extraction(const char* txt_path);
	int feat_extraction_with_Moravec(const char* prj_txt_path);
	cv::Mat feat_matching_Moravec(cv::Mat im,int w,int key);
	
};

