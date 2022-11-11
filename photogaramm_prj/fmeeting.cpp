#include "fmeeting.h"
#include "stdio.h"
#include "omp.h"
#include<opencv2/opencv.hpp>
#include"EplImg_BX.h"
#include"SpVZImage.h"
using namespace std;
//int thread_num = omp_get_max_threads();
bool front_meeting::nega_projection(vector<cv::Point3f>Xa, vector<cv::Point2f>Xl, vector<cv::Point2f>Xr) {
	vector<cv::Point2f>dis;
	float d1, d2;
	cv::Point2f p1, p2;
	double x1 = 0, y1 = 0;
	for (int i = 0;i <Xa.size();i++) {
		p1.x = -cf.f_1 * ((Xa[i].x - Xs1.x) ) / ((Xa[i].z - Xs1.z)) ;//+ cf.xy1.x
		p1.y = -cf.f_1 * ( (Xa[i].y - Xs1.y) ) / ((Xa[i].z - Xs1.z));//+ cf.xy1.y
		p2.x = -cf.f_2 * (B0.at<float>(0, 0) * (Xa[i].x - Xs2.x) + B0.at<float>(0, 1) * (Xa[i].y - Xs2.y) + B0.at<float>(0, 2) * (Xa[i].z - Xs2.z)) / (B0.at<float>(2, 0) * (Xa[i].x - Xs2.x) + B0.at<float>(2, 1) * (Xa[i].y - Xs2.y) + B0.at<float>(2, 2) * (Xa[i].z - Xs2.z));
		p2.y = -cf.f_2 * (B0.at<float>(1, 0) * (Xa[i].x - Xs2.x) + B0.at<float>(1, 1) * (Xa[i].y - Xs2.y) + B0.at<float>(1, 2) * (Xa[i].z - Xs2.z)) / (B0.at<float>(2, 0) * (Xa[i].x - Xs2.x) + B0.at<float>(2, 1) * (Xa[i].y - Xs2.y) + B0.at<float>(2, 2) * (Xa[i].z - Xs2.z));
		d1 = sqrt(pow(Xl[i].x - p1.x, 2) + pow(Xl[i].y - p1.y, 2));
		d2= sqrt(pow(Xr[i].x - p2.x, 2) + pow(Xr[i].y - p2.y, 2));
		x1 += d1;
		y1 += d2;
	}
	cout << "accuracy examination complete" << endl;
	cout << "left image accuracy(mm):" << x1 / Xa.size() << " right image accuracy(mm):" << y1 / Xa.size() << endl;
	return 1;
}



void front_meeting::Br() {
	Xs2.x = Xs1.x + cf.Bs;
	Xs2.y = Xs1.y + cf.Bs*cf.u;
	Xs2.z = Xs1.z+ cf.Bs*cf.v;

	B = cv::Mat::zeros(3, 4, CV_32F);
	float a1 = cos(cf.fi) * cos(cf.kappa) - sin(cf.fi) * sin(cf.miu) * sin(cf.kappa);
	float a2 = -cos(cf.fi) * sin(cf.kappa) - sin(cf.fi) * sin(cf.miu) * cos(cf.kappa);
	float a3 = -sin(cf.fi) * cos(cf.miu);
	float b1 = cos(cf.miu) * sin(cf.kappa);
	float b2 = cos(cf.miu) * cos(cf.kappa);
	float b3 = -sin(cf.miu);
	float c1 = sin(cf.fi) * cos(cf.kappa) + cos(cf.fi) * sin(cf.miu) * sin(cf.kappa);
	float c2 = -sin(cf.fi) * sin(cf.kappa) + cos(cf.fi) * sin(cf.miu) * cos(cf.kappa);
	float c3 = cos(cf.fi) * cos(cf.miu);

	B0.at<float>(0, 0) = a1;B0.at<float>(0, 1) = b1;B0.at<float>(0, 2) = c1;
	B0.at<float>(1, 0) = a2;B0.at<float>(1, 1) = b2;B0.at<float>(1, 2) = c2;
	B0.at<float>(2, 0) = a3;B0.at<float>(2, 1) = b3;B0.at<float>(2, 2) = c3;
	
	B.at<float>(0, 0) = -cf.f_1 * a1;
	B.at<float>(0, 1) = -cf.f_1 * b1;
	B.at<float>(0, 2) = -cf.f_1 * c1;

	B.at<float>(1, 0) = -cf.f_1 * a2;
	B.at<float>(1, 1) = -cf.f_1 * b2;
	B.at<float>(1, 2) = -cf.f_1 * c2;

	B.at<float>(2, 0) = a3;
	B.at<float>(2, 1) = b3;
	B.at<float>(2, 2) = c3;

	B.at<float>(0, 3) = cf.f_1 * (a1 * Xs2.x + b1 * Xs2.y + c1 * Xs2.z);
	B.at<float>(1, 3) = cf.f_1 * (a2 * Xs2.x + b2 * Xs2.y + c2 * Xs2.z);
	B.at<float>(2, 3) = -(a3 * Xs2.x + b3 * Xs2.y + c3 * Xs2.z);
}


cv::Point3f front_meeting::r(cv::Point2f p1,cv::Point2f p2)//前方交会
{
	cv::Mat B1 = cv::Mat::zeros(4, 3, CV_32F);
	cv::Mat l1 = cv::Mat::zeros(4, 1, CV_32F);
	B1.at<float>(0, 0) = cf.f_1;//fangcheng1
	//B1.at<float>(0, 1) = B.at<float>(0, 1) - p1.x * B.at<float>(2, 1);
	B1.at<float>(0, 2) =  p1.x ;
	l1.at<float>(0,0)=p1.x*Xs1.z+cf.f_1*Xs1.x;

	//B1.at<float>(1, 0) = B.at<float>(1, 0) - p1.y * B.at<float>(2, 0);
	B1.at<float>(1, 1) = cf.f_1;
	B1.at<float>(1, 2) = p1.y;
	l1.at<float>(1, 0) = p1.y *Xs1.z+cf.f_1*Xs1.y;

	B1.at<float>(2, 0) = B.at<float>(0, 0) - p2.x * B.at<float>(2, 0);
	B1.at<float>(2, 1) = B.at<float>(0, 1) - p2.x * B.at<float>(2, 1);
	B1.at<float>(2, 2) = B.at<float>(0, 2) - p2.x * B.at<float>(2, 2);
	l1.at<float>(2, 0) = p2.x * B.at<float>(2, 3) - B.at<float>(0, 3);

	B1.at<float>(3, 0) = B.at<float>(1, 0) - p2.y * B.at<float>(2, 0);
	B1.at<float>(3, 1) = B.at<float>(1, 1) - p2.y * B.at<float>(2, 1);
	B1.at<float>(3, 2) = B.at<float>(1, 2) - p2.y * B.at<float>(2, 2);
	l1.at<float>(3, 0) = p2.y * B.at<float>(2, 3) - B.at<float>(1, 3);

	cv::Mat x = (B1.t() * B1).inv() * B1.t() * l1;

	cv::Point3f Xa;
	Xa.x = x.at<float>(0, 0);
	Xa.y = x.at<float>(1, 0);
	Xa.z = x.at<float>(2, 0);
	return Xa;
}
void front_meeting::readInner(const char* innerPath) {

	double f10, sx0;
	ifstream f1(innerPath);
	string s;
	getline(f1, s);
	getline(f1, s);
	getline(f1, s);

	f1 >> f10 >> sx0 >> dx >> dy;//读入内参（虽然只用读一次）

	//f1 >> Xs1.x >> Xs1.y >> Xs1.z >> fi1 >> omega1 >> kappa1;//读入外参
	//getline(f1, s);
	//f1 >> cf->f_2 >> cf->sx >> dx >> dy;
	//f1 >> Xs2.x >> Xs2.y >> Xs2.z >> fi2 >> omega2 >> kappa2;
	//cf->f_2 = cf->f_1;
	f1.close();
}

void front_meeting::frontmeet( const char* innerPath)
{
	string image3 = "10040083_ds.tif";
	string image2= "10040082_ds.tif";
	cf.input(innerPath);
	if ((cf.image_path1.find(image3) < cf.image_path1.length()) && (cf.image_path2.find(image2) < cf.image_path2.length())) {
		cf.feat_matching(1);
	}
	else
		cf.feat_matching(0);	
	cf.generation();
	Br();//输入旋转矩阵	rotation matrix
	CEplImg_BX cbx;

	//输入参数
	int re0=cbx.SetPars(cf.im10.rows, cf.im10.cols, cf.im10.channels(),
		0, 0, 0, 0, 0, 0, cf.f_1, 0, 0, cf.sx, 0, 0, 0, 0,
		cf.im20.rows, cf.im20.cols, cf.im20.channels(), 
		cf.Bs, cf.Bs * cf.u, cf.Bs * cf.v, cf.fi, cf.miu, cf.kappa, cf.f_2, 0, 0, cf.sx, 0, 0, 0, 0);

	//生产核线影像
	BYTE* pLImgBits, * pRImgBits;
	int r1 = cf.im10.rows, c1 = cf.im10.cols, cha = cf.im10.channels();
	pLImgBits = new BYTE[r1 * c1 * 3];
	pRImgBits = new BYTE[r1* c1 * 3];
	ReadImgDat((cf.image_path1).c_str(), pLImgBits, 0, 0, c1, r1, 3);
	ReadImgDat((cf.image_path2).c_str(), pRImgBits, 0, 0, c1, r1, 3);
	cbx.GetElpStereoImgs(pLImgBits, 0, 0, r1, c1, cha,pRImgBits, 0,0,r1,c1, cha,false);
	string le = cf.folder + "left_epi.tif";
	string re = cf.folder + "right_epi.tif";
	if (!SaveImg(le.c_str(), cbx.m_pLEplImgBits, cbx.m_nLEplImgWidth, cbx.m_nLEplImgHeight, cbx.m_nLEplImgChannelNum)
		|| !SaveImg(re.c_str(), cbx.m_pREplImgBits, cbx.m_nREplImgWidth, cbx.m_nREplImgHeight, cbx.m_nREplImgChannelNum))
	{
		std::cout << "error" << endl;
	}

	//free memory
	delete[]pRImgBits; pRImgBits = NULL;
	delete[]pLImgBits; pLImgBits = NULL;

	//生产视差图
	string lp = cf.folder+"left_epi.tif ";
	string rp = cf.folder+"right_epi.tif ";
	string exe = "..\\64位\\epi_dense_matching\\epi_dense_matching.exe ";
	string res = cf.folder+"epi.tif";
	string s0 = exe + lp + rp +"200 "+"400 "+ res;
	const char* s1 =(s0).c_str();
	std::system(s1);

	//密集匹配 dense matching
	dep=cv::imread(res,2);
	std::cout << "disparity graph complete" << endl;
	cv::Point3f X3d;
	cv::Point2f Xl, Xr;
	vector<cv::Point3f>Xa;
	vector<cv::Point2f>Xol,Xor;
	float olx, oly, orx, ory,elx,ely,erx;
	ofstream f3(cf.folder+"point_cloud.txt");
	cv::Mat elf = cv::imread(lp, 1);
//#pragma omp parallel for num_threads(thread_num)
	for (int i = 0;i < cf.im10.cols;i++) {
	//#pragma omp parallel for num_threads(thread_num)
		for (int j = 0;j < cf.im10.rows;j++) {
			if(!isnan(dep.at<float>(j, i))){
			elx =i;ely = r1-1-j;
			erx = i - dep.at<float>(j, i);//深度图的单位:像素
			
			cbx.GetLImgOrgPos_From_EplPos(elx, ely, &olx, &oly);
			cbx.GetLImgOrgPos_From_EplPos(erx, ely, &orx, &ory);
			Xl = round(cv::Point2f(olx, oly));
			Xr = round(cv::Point2f(orx,ory));
			Xol.push_back(Xl);Xor.push_back(Xr);
			X3d = r(Xl, Xr);
			Xa.push_back(X3d);
			if(elx>=0&&ely>=0)
			f3 << X3d.x<< " " << X3d.y << " " << X3d.z << " " <<int(elf.at<cv::Vec3b>(r1-1-int(ely),int(elx))[2] )<<" " << int(elf.at<cv::Vec3b>(r1 - 1 - int(ely ), int(elx))[1])<<" " << int(elf.at<cv::Vec3b>(r1 - 1 - int(ely), int(elx))[0]) << endl;//bgr				
			}
		}
	}
	std::cout<<"dense matching complete" << endl;
	f3.close();	
	nega_projection(Xa,Xol,Xor);
	
}

cv::Point2f front_meeting::round(cv::Point2f p)//转到中心
{
	p.x = cf.sx * (p.x - (cf.im10.cols - 1) / 2);
	p.y = cf.sx * ( p.y-(cf.im10.rows - 1) / 2 );
	return p;
}







