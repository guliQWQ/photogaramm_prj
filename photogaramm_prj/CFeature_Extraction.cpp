#include "stdio.h"
#include "CFeature_Extraction.h"
#include<opencv2/opencv.hpp>
#include "omp.h"
//using namespace cv;
using namespace std;
int thread_num = omp_get_max_threads();
int CFeature_Extraction::create_empty_prj_file_for_feat_extraction(const char* txt_path)
{
	FILE* fp = fopen(txt_path, "w");
	fprintf(fp, "img_path=\n");
	fprintf(fp, "feat_file_path=\n");
	fclose(fp); fp = NULL;

	return 1;
}

int CFeature_Extraction::feat_extraction_with_Moravec(const char* prj_txt_path)
{
	cv::Mat im = cv::imread(prj_txt_path,0);
	cv::Mat im1;
	int w;
	cout << "请输入窗口大小" << endl;
	cin >> w;		
	int d = int((w - 1) / 2);
	
	copyMakeBorder(im, im1, d, d, d, d, cv::BORDER_REFLECT);//考虑长方形影像
	cv::Mat im2,im3;
	im2.create(im.size(), CV_32FC1);
	im3.create(im.size(), CV_32FC1);

//#pragma omp parallel for num_threads(thread_num)
	for (int y = 0; y < im.rows; y++) {
		for (int x = 0; x < im.cols; x++) {
			double H = 0, V = 0, D = 0, A = 0;
				for (int i = -d; i < d; i++) {
					H += pow(im1.at<uchar>(y + d, x + d + i) - im1.at<uchar>(y + d, x + d + i + 1), 2);//data0[(y + d) * im.cols * im.channels() + (x + d + i + 1) * im.channels() ]), 2);
					V += pow(im1.at<uchar>(y + d + i, x + d) - im1.at<uchar>(y + d + i + 1, x + d), 2);//(data0[(y + d + i) * im.cols * im.channels() + (x + d) * im.channels() ] - data0[(y + d + i + 1) * im.cols * im.channels() + (x + d) * im.channels() ]), 2);
					D += pow(im1.at<uchar>(y + d + i, x + d + i) - im1.at<uchar>(y + d + i + 1, x + d + i + 1), 2);//(data0[(y + d + i) * im.cols * im.channels() + (x + d + i) * im.channels() ] - data0[(y + d + i + 1) * im.cols * im.channels() + (x + d + i + 1) * im.channels() ]), 2);
					A += pow(im1.at<uchar>(y + d - i, x + d + i) - im1.at<uchar>(y + d - i - 1, x + d + i + 1), 2);//(data0[(y + d - i) * im.cols * im.channels() + (x + d + i) * im.channels() ] - data0[(y + d - i - 1) * im.cols * im.channels() + (x + d + i + 1) * im.channels() ]), 2);
				}				
					float IV= min({ H, V, D, A });					
					im2.at<float>(y,x) = IV;					
		}
	}
	int w2 = 5,d2=(w2-1)/2,nmax=0;
//#pragma omp parallel for num_threads(thread_num)
	for (int y = d2;y < im2.rows-d2;y++) {
		for (int x = d2;x < im2.cols-d2;x++) {
			if (im2.at<float>(y, x) >3000) {
				for (int p = -d2;p < d2;p++) {
					for (int q = -d2;q < d2;q++) {
						if (im2.at<float>(x, y) > nmax){
							nmax = im2.at<float>(x, y);
						}
					}
				}
				if (im2.at<float>(x, y) == nmax) {
					circle(im, cv::Point(y, x), 3, cv::Scalar(0, 0, 255),-1);
					im3.at<float>(y, x) = im2.at<float>(y, x);
				}
			}
		}
	}

	imshow("feature points", im);
	cv::waitKey(0);
	cv::destroyAllWindows();
	return 1;
}

cv::Mat CFeature_Extraction::feat_matching_Moravec(cv::Mat im, int w,int key) {
	cv::Mat im1;	
	int d = int((w - 1) / 2),field= 29000;
	if (key == 1)
		field = 5000;
	copyMakeBorder(im, im1, d, d, d, d, cv::BORDER_REFLECT);//考虑长方形影像
	cv::Mat im2, im3;
	im2.create(im.size(), CV_32FC1);
	im3.create(im.size(), CV_32FC1);
	uchar* data0 = im1.data;
    //#pragma omp parallel for num threads(thread_num)
	for (int y = 0; y < im.rows; y++) {
		for (int x = 0; x < im.cols; x++) {
			double H = 0, V = 0, D = 0, A = 0;
			for (int i = -d; i < d; i++) {
				H += pow(im1.at<uchar>(y + d, x + d + i) - im1.at<uchar>(y + d, x + d + i + 1), 2);
				V += pow(im1.at<uchar>(y + d + i, x + d) - im1.at<uchar>(y + d + i + 1, x + d), 2);
				D += pow(im1.at<uchar>(y + d + i, x + d + i) - im1.at<uchar>(y + d + i + 1, x + d + i + 1), 2); 
				A += pow(im1.at<uchar>(y + d - i, x + d + i) - im1.at<uchar>(y + d - i - 1, x + d + i + 1), 2);
			}
			float IV = min({ H, V, D, A });
			im2.at<float>(y, x) = IV;
		}
	}

	int w2 = 5, d2 = (w2 - 1) / 2, nmax = 0;
    //#pragma omp parallel for num threads(thread_num)
	for (int y0 = d2;y0 < im2.rows -1- d2;y0++) {
		for (int x0 = d2;x0 < im2.cols-1 - d2;x0++) {
			if (im2.at<float>(y0, x0) >field) {//选取大于阈值的点存储 save points bigger than threshold
				im3.at<float>(y0, x0) = im2.at<float>(y0, x0);//此时为先行后列 row is the first
			}
		}
	}
	return im3;
}