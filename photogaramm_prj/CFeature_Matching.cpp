#include "CFeature_Matching.h"
#include "CFeature_Extraction.h"
#include "stdio.h"
#include "omp.h"
#include<opencv2/opencv.hpp>
#include<sstream>
using namespace std;
//int thread_num = omp_get_max_threads();

CFeature_Matching::CFeature_Matching()
{
	sigma0 = 0.5;
	u = 0; v = 0; miu = 0; fi = 0; kappa = 0; Bs = 1;//距离角度系数 parameters of distance and angle
	sx = 1;
}
int CFeature_Matching::create_empty_prj_file_for_feat_matching(const char* txt_path)
{
	FILE* fp = fopen(txt_path, "w");
	fprintf(fp, "img_path=\n");
	fprintf(fp, "feat_file_path=\n");
	fclose(fp); fp = NULL;

	return 1;
}

int CFeature_Matching::feat_matching(int key) {
	 im10 = cv::imread(image_path1, 1);
	 im20 = cv::imread(image_path2, 1);
	 cv::Mat im1, im2;
	 cvtColor(im10, im1, cv::COLOR_BGR2GRAY);
	 cvtColor(im20, im2, cv::COLOR_BGR2GRAY);
	CFeature_Extraction fe;
	cv::Mat f1 = fe.feat_matching_Moravec(im1, 5,0);//特征提取 feature extraction
	cv::Mat f2 = fe.feat_matching_Moravec(im2, 5,0);
	cout << "feature extraction complete" << endl;
	vector<cv::Point2f>leftPoint0;//存储同名点 save identical name points
	vector<cv::Point2f>rightPoint0;
	float field = 0.95;
	if (key == 1)
		field = 0.97;
//#pragma omp parallel for num threads(thread_num)
	for (int y = 0;y < f1.cols-5;y++) {
		for (int x = 0;x < f1.rows-5;x++) {
			if (f1.at<float>(x, y) > 0) {
				float rou = -1;//相关系数 Correlation coefficient
				int pm = 0, qm = 0;
//#pragma omp parallel for num threads(thread_num)
				for (int q = 0;q < f2.cols-5;q++) {
					for (int p = 0;p < f2.rows-5;p++) {
						if (f2.at<float>(p, q) > 0) {
							if (xgxs(im1, im2, x, y, p, q) > rou){
								rou = xgxs(im1, im2, x, y, p, q);//算f1与f2所有特征点的相关系数，取最大值 get the maximum of all Correlation coefficients of points in f1 and f2
								pm = p;qm = q;//12he
							}
						}
					}
				}
				if (rou > field) {
					leftPoint0.push_back(cv::Point(y, x));//此时改为列在前 column is the first
					rightPoint0.push_back(cv::Point(qm,pm));
				}
			}
		}
	}
	
	vector<uchar>isChoose;//剔除粗差
	cv::Mat E=findFundamentalMat(leftPoint0, rightPoint0,isChoose, cv::FM_RANSAC,1);
	vector<cv::Mat> ims;
	cv::Mat match;
	ims.push_back(im10);
	ims.push_back(im20);
	hconcat(ims, match);

    //#pragma omp parallel for num threads(thread_num)
	for (int k = 0;k < isChoose.size();k++) {
		if (isChoose[k]!=0) {
			line(match, cv::Point(leftPoint0[k]), cv::Point(rightPoint0[k].x + im10.cols, rightPoint0[k].y), cv::Scalar(0, 255, 0), 3);
			leftPoint.push_back(cv::Point2f(sx*(leftPoint0[k].x-((im1.cols-1)/2)), sx * (((im1.rows - 1)/2) - leftPoint0[k].y)));//像素大小im1.rows-1-
			rightPoint.push_back(cv::Point2f(sx * (rightPoint0[k].x - ((im2.cols - 1) / 2)), sx * (((im2.rows - 1)/2 )- rightPoint0[k].y)));//原点为中心的像点坐标
		}
	}
	cv::imwrite(folder + "point_match.png", match);
	ofstream pp (folder+"point_pair.txt");
	for (int i = 0;i < leftPoint.size();i++){
	pp<<leftPoint[i]<<rightPoint[i]<< endl;
	}	
	cout << "feature matching complete"<< endl;
	pp.close();
	return 1;
}

int CFeature_Matching::calibration(const char* image_path1, const char* image_path2, const char* inner_path)
{	input(inner_path);
	feat_matching(0);
	generation();
	cout << "u=" <<  u << endl;
	cout << "v=" <<  v << endl;
	cout << "fi=" << fi << endl;
	cout << "omega=" << miu << endl;
	cout << "kappa=" << kappa << endl;
	return 1;
}

void CFeature_Matching::sift(const char* sift_path) {
	
	ifstream f(sift_path);
	string s;
	string s1;
	float x1, y1, x2, y2;
	getline(f, s);
	getline(f, s);
	getline(f, s);
	int size = stoi(s);
	for (int i = 0;i < size;i++) {				
		f >> x1 >> y1 >> x2 >> y2;		
		leftPoint.push_back(cv::Point2f(sx*(x1- ((im10.cols - 1) / 2)), sx*(((im10.rows - 1) / 2)-y1)));
		rightPoint.push_back(cv::Point2f(sx*(x2 - ((im20.cols - 1) / 2)), sx*(((im20.rows - 1) / 2)-y2)));
	}}

void CFeature_Matching::setFolder(string s)
{
	folder = s;
}

void CFeature_Matching::input(const char* inner_path)
{
	ifstream inner(inner_path);
	string s;
	getline(inner,s);
	setFolder(s);
	getline(inner, s);
	image_path1 = s;
	getline(inner, s);
	image_path2 = s;
	float dx, dy;
	inner >> f_1 >> sx >> dx >> dy;
	xy1.x = (dx)*sx;//左下角为原点的像主点坐标
	xy1.y = (dy)*sx;
	xy2.x = (dx)*sx;
	xy2.y = (dy)*sx;
	f_2 = f_1;
	inner.close();
	cout << "inner parameters imput complete." << endl;
}

void CFeature_Matching::generation()
{
	initialization();
	int flag,time;
	for (time = 0;time < 100;time++) {
		 flag = 0;
		inB();
		for (int i = 0;i < 5;i++) {
			if (abs(x.at<float>(i, 0)) < 0.00001)
				flag ++;
		}
		if (flag==5)
			break;
	}
	cout <<"iteration complete after"<<time<<" times." << endl;
	cout << "u="<<u << " v=" << v << " phi=" << fi << " omega=" << miu << " kappa=" << kappa << endl;
}

void CFeature_Matching::inB()//录入矩阵与平差
{	
    //#pragma omp parallel for num threads(12)
	for (int i = 0;i < leftPoint.size();i++) {	
		#pragma omp critical
		Bx.at<float>(i, 0) = Fu_(leftPoint[i], rightPoint[i]);
		Bx.at<float>(i, 1) = Fv_(leftPoint[i], rightPoint[i]);
		Bx.at<float>(i, 2) = Ffi_(leftPoint[i], rightPoint[i]);
		Bx.at<float>(i, 3) = Fmiu_(leftPoint[i], rightPoint[i]);
		Bx.at<float>(i, 4) = Fkappa_(leftPoint[i], rightPoint[i]);
		l.at<float>(i, 0) = -F0_(leftPoint[i], rightPoint[i]);
	}
	x = (Bx.t() * P * Bx).inv() * Bx.t() * P * l;
	V = Bx * x - l;
	sigma0 = sqrt(sum(abs(V))[0]/(leftPoint.size() - 5));
	weight();
	u += x.at<float>(0, 0);
	v += x.at<float>(1, 0);
	fi+= x.at<float>(2, 0);
	miu+=x.at<float>(3, 0);
	kappa+= x.at<float>(4, 0);
}

double CFeature_Matching::F0_(cv::Point2f p1, cv::Point2f p2)//x2×旋转矩阵 
{
	cv::Mat F0 = cv::Mat::ones(3, 3, CV_32FC1);
	F0.at<float>(0, 1) = u;
	F0.at<float>(0, 2) = v;
	F0.at<float>(1, 0) = p1.x-xy1.x;
	F0.at<float>(1, 1) = p1.y - xy1.y;
	F0.at<float>(1, 2) = -f_1;

	cv::Mat x2 = cv::Mat::zeros(3, 1, CV_32FC1);
	x2=R(p2);

	F0.at<float>(2, 0) = x2.at<float>(0, 0);
	F0.at<float>(2, 1) = x2.at<float>(1, 0);
	F0.at<float>(2, 2) = x2.at<float>(2, 0);
	
	return Bs*determinant(F0);
}

cv::Mat CFeature_Matching::R(cv::Point2f p2) {
	float a1 = cos(fi) * cos(kappa) - sin(fi) * sin(miu) * sin(kappa);
	float a2 = -cos(fi) * sin(kappa) - sin(fi) * sin(miu) * cos(kappa);
	float a3 = -sin(fi) * cos(miu);
	float b1 = cos(miu) * sin(kappa);
	float b2 = cos(miu) * cos(kappa);
	float b3 = -sin(miu);
	float c1 = sin(fi) * cos(kappa) + cos(fi) * sin(miu) * sin(kappa);
	float c2 = -sin(fi)*sin(kappa)+cos(fi) * sin(miu) * cos(kappa);
	float c3 = cos(fi) * cos(miu);
	cv::Mat R = cv::Mat::zeros(3, 3, CV_32FC1);
	R.at<float>(0, 0) = a1;
	R.at<float>(0, 1) = a2;
	R.at<float>(0, 2) = a3;
	R.at<float>(1, 0) = b1;
	R.at<float>(1, 1) = b2;
	R.at<float>(1, 2) = b3;
	R.at<float>(2, 0) = c1;
	R.at<float>(2, 1) = c2;
	R.at<float>(2, 2) = c3;

	cv::Mat x2 = cv::Mat::zeros(3, 1, CV_32FC1);
	x2.at<float>(0, 0) = p2.x - xy2.x;
	x2.at<float>(1, 0) = p2.y - xy2.y;
	x2.at<float>(2, 0) = -f_2;
	return R * x2;
}

float CFeature_Matching::Fu_(cv::Point2f p1, cv::Point2f p2)//对u求偏导
{
	cv::Mat X2 = cv::Mat::zeros(3, 1, CV_32FC1);
		X2= R(p2);
	
	return Bs*((X2.at<float>(0,0))*-f_1 - (p1.x - xy1.x) * X2.at<float>(2,0));
}

float CFeature_Matching::Fv_(cv::Point2f p1, cv::Point2f p2)//对v求偏导
{
	cv::Mat X2 = cv::Mat::zeros(3, 1, CV_32FC1);
		X2= R(p2);
	return Bs * ((p1.x - xy1.x)* X2.at<float>(1,0)-X2.at<float>(0,0)*(p1.y-xy1.y));
}

float CFeature_Matching::Ffi_(cv::Point2f p1, cv::Point2f p2)//对φ求偏导
{
	float a1 = -sin(fi) * cos(kappa) - cos(fi) * sin(miu) * sin(kappa);
	float a2 = sin(fi) * sin(kappa) - cos(fi) * sin(miu) * cos(kappa);
	float a3 = -cos(fi) * cos(miu);
	//float b1 = 0;
	//float b2 = 0;
	//float b3 = 0;
	float c1 = cos(fi) * cos(kappa) -sin(fi) * sin(miu) * sin(kappa);
	float c2 = -cos(fi) * sin(kappa) -sin(fi) * sin(miu) * cos(kappa);
	float c3 = -sin(fi) * cos(miu);
	cv::Mat R = cv::Mat::zeros(3, 3, CV_32FC1);
	R.at<float>(0, 0) = a1;
	R.at<float>(0, 1) = a2;
	R.at<float>(0, 2) = a3;
	//R.at<float>(1, 0) = b1;
	//R.at<float>(1, 1) = b2;
	//R.at<float>(1, 2) = b3;
	R.at<float>(2, 0) = c1;
	R.at<float>(2, 1) = c2;
	R.at<float>(2, 2) = c3;

	cv::Mat x2 = cv::Mat::zeros(3, 1, CV_32FC1);
	x2.at<float>(0, 0) = p2.x - xy2.x;
	x2.at<float>(1, 0) = p2.y - xy2.y;
	x2.at<float>(2, 0) = -f_2;	
	x2=(R * x2);

	cv::Mat F = cv::Mat::ones(3, 3, CV_32FC1);
	F.at<float>(0, 1) = u;
	F.at<float>(0, 2) = v;
	F.at<float>(1, 0) = p1.x - xy1.x;
	F.at<float>(1, 1) = p1.y - xy1.y;
	F.at<float>(1, 2) = -f_1;
	F.at<float>(2, 0) = x2.at<float>(0,0);
	F.at<float>(2, 1) = x2.at<float>(1, 0);
	F.at<float>(2, 2) = x2.at<float>(2, 0);
	return Bs * determinant(F);
}

float CFeature_Matching::Fmiu_(cv::Point2f p1, cv::Point2f p2)//对ω求偏导
{
	float a1 = - sin(fi) * cos(miu) * sin(kappa);
	float a2 = - sin(fi) * cos(miu) * cos(kappa);
	float a3 = sin(fi) * sin(miu);
	float b1 = -sin(miu) * sin(kappa);
	float b2 = -sin(miu) * cos(kappa);
	float b3 = -cos(miu);
	float c1 =  cos(fi) * cos(miu) * sin(kappa);
	float c2 =  cos(fi) * cos(miu) * cos(kappa);
	float c3 = cos(fi) * -sin(miu);
	cv::Mat R = cv::Mat::zeros(3, 3, CV_32FC1);
	R.at<float>(0, 0) = a1;
	R.at<float>(0, 1) = a2;
	R.at<float>(0, 2) = a3;
	R.at<float>(1, 0) = b1;
	R.at<float>(1, 1) = b2;
	R.at<float>(1, 2) = b3;
	R.at<float>(2, 0) = c1;
	R.at<float>(2, 1) = c2;
	R.at<float>(2, 2) = c3;

	cv::Mat x2 = cv::Mat::zeros(3, 1, CV_32FC1);
	x2.at<float>(0, 0) = p2.x - xy2.x;
	x2.at<float>(1, 0) = p2.y - xy2.y;
	x2.at<float>(2, 0) = -f_2;
	x2 = (R * x2);

	cv::Mat F = cv::Mat::ones(3, 3, CV_32FC1);
	F.at<float>(0, 1) = u;
	F.at<float>(0, 2) = v;
	F.at<float>(1, 0) = p1.x - xy1.x;
	F.at<float>(1, 1) = p1.y - xy1.y;
	F.at<float>(1, 2) = -f_1;
	F.at<float>(2, 0) = x2.at<float>(0, 0);
	F.at<float>(2, 1) = x2.at<float>(1, 0);
	F.at<float>(2, 2) = x2.at<float>(2, 0);
	return Bs * determinant(F);
}

float CFeature_Matching::Fkappa_(cv::Point2f p1, cv::Point2f p2)//对κ求偏导
{
	float a1 = cos(fi) * -sin(kappa) - sin(fi) * sin(miu) * cos(kappa);
	float a2 = -cos(fi) * cos(kappa) + sin(fi) * sin(miu) * sin(kappa);
	
	float b1 = cos(miu) * cos(kappa);
	float b2 = cos(miu) * -sin(kappa);
	
	float c1 = sin(fi) * -sin(kappa) + cos(fi) * sin(miu) * cos(kappa);
	float c2 = -sin(fi) * cos(kappa) - cos(fi) * sin(miu) * sin(kappa);
	
	cv::Mat R = cv::Mat::zeros(3, 3, CV_32FC1);
	R.at<float>(0, 0) = a1;
	R.at<float>(0, 1) = a2;
	
	R.at<float>(1, 0) = b1;
	R.at<float>(1, 1) = b2;
	
	R.at<float>(2, 0) = c1;
	R.at<float>(2, 1) = c2;

	cv::Mat x2 = cv::Mat::zeros(3, 1, CV_32FC1);
	x2.at<float>(0, 0) = p2.x - xy2.x;
	x2.at<float>(1, 0) = p2.y - xy2.y;
	x2.at<float>(2, 0) = -f_2;
	x2 = (R * x2);

	cv::Mat F = cv::Mat::ones(3, 3, CV_32FC1);
	F.at<float>(0, 1) = u;
	F.at<float>(0, 2) = v;
	F.at<float>(1, 0) = p1.x - xy1.x;
	F.at<float>(1, 1) = p1.y - xy1.y;
	F.at<float>(1, 2) = -f_1;
	F.at<float>(2, 0) = x2.at<float>(0, 0);
	F.at<float>(2, 1) = x2.at<float>(1, 0);
	F.at<float>(2, 2) = x2.at<float>(2, 0);
	return Bs * determinant(F);

}

void CFeature_Matching::weight()//迭代中定权 weight during iteration
{
//#pragma omp parallel for num_threads(thread_num)
	for (int i = 0;i < leftPoint.size();i++) {
		if (V.at<float>(i, 0) < 3 * sigma0)
			P.at<float>(i, i) = 100.0;
		else
			P.at<float>(i, i) = 0.5;
	}
}

void CFeature_Matching::initialization()
{
	Bx = cv::Mat::zeros(leftPoint.size(), 5, CV_32FC1);
	P = cv::Mat::eye(leftPoint.size(), leftPoint.size(), CV_32FC1);
	l = cv::Mat::zeros(leftPoint.size(), 1, CV_32FC1);
	x = cv::Mat::zeros(5, 1, CV_32FC1);
	V= cv::Mat::zeros(leftPoint.size(), 1, CV_32FC1);
	cout << "initialization complete" << endl;
}

float CFeature_Matching::xgxs(cv::Mat im1, cv::Mat im2, int x1, int y1, int x2, int y2) {
	int m = 5, n = 5;
	float g1 = 0, g2 = 0, fenzi = 0, fenmux = 0,fenmuy=0, rou = 0;

	for (int i = 0;i < m;i++) {
		for (int j = 0;j < n;j++) {
			g1 += im1.at<uchar>(x1 + i, y1 + j);
			g2 += im2.at<uchar>(x2 + i, y2 + j);
		}
	}
	g1 = g1 / (m * n);
	g2 = g2 / (m * n);

	for (int i = 0;i < m;i++) {
		for (int j = 0;j < n;j++) {
			fenzi += im1.at<uchar>(x1 + i, y1 + j) * im2.at<uchar>(x2 + i, y2 + j)-(g1*g2);
			fenmux += pow((im1.at<uchar>(x1 + i, y1 + j) - g1) , 2);
			fenmuy += pow((im2.at<uchar>(x2 + i, y2 + j) - g2), 2);
		}
	}
	rou = fenzi * pow((fenmux*fenmuy), -0.5);
	return rou;
}

