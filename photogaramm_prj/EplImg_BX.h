#include "windows.h"
#ifndef EPLIMAGEDLL_H_HS_2014_10_16
#define EPLIMAGEDLL_H_HS_2014_10_16
#include "SpVZImage.h"

//该宏完成在dll项目内部使用__declspec(dllexport)导出  
//在dll项目外部使用时，用__declspec(dllimport)导入  
//宏DLL_IMPLEMENT在simpledll.cpp中定义
#ifdef DLL_IMPLEMENT  
#define DLL_API __declspec(dllexport)  
#else  
#define DLL_API __declspec(dllimport)  
#endif  

class DLL_API CEplImg_BX
{
public:
	CEplImg_BX(void);
	~CEplImg_BX(void);
		//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	/* 
	设置函数参数
	int nLOrgImgHeight, int nLOrgImgWidth, int nLOrgImgChannelNum,	//左影像高、宽、波段数
	double nLOrgImgXs, double nLOrgImgYs, double nLOrgImgZs, double nLOrgImgPhi, double nLOrgImgOmega, double nLOrgImgKappa,	//左影像外方位元素
	float nLOrgImgf, float nLOrgImgx0, float nLOrgImgy0, float nLOrgImgPixelSize,	//左影像相机参数
	double nLOrgImgk1, double nLOrgImgk2, double nLOrgImgp1, double nLOrgImgp2,	    //左影像畸变参数
	int nROrgImgHeight, int nROrgImgWidth, int nROrgImgChannelNum,					//右影像高、宽、波段数
	double nROrgImgXs, double nROrgImgYs, double nROrgImgZs, double nROrgImgPhi, double nROrgImgOmega, double nROrgImgKappa,	//右影像外方位元素
	float nROrgImgf, float nROrgImgx0, float nROrgImgy0, float nROrgImgPixelSize,	//右影像相机参数
	double nROrgImgk1, double nROrgImgk2, double nROrgImgp1, double nROrgImgp2,		//右影像畸变参数
	*/
	int SetPars(int nLOrgImgHeight, int nLOrgImgWidth, int nLOrgImgChannelNum,  
		double nLOrgImgXs, double nLOrgImgYs, double nLOrgImgZs, double nLOrgImgPhi, double nLOrgImgOmega, double nLOrgImgKappa,
		float nLOrgImgf, float nLOrgImgx0, float nLOrgImgy0, float nLOrgImgPixelSize, 
		double nLOrgImgk1, double nLOrgImgk2, double nLOrgImgp1, double nLOrgImgp2,
		int nROrgImgHeight, int nROrgImgWidth, int nROrgImgChannelNum, 
		double nROrgImgXs, double nROrgImgYs, double nROrgImgZs, double nROrgImgPhi, double nROrgImgOmega, double nROrgImgKappa,
		float nROrgImgf, float nROrgImgx0, float nROrgImgy0, float nROrgImgPixelSize, 
		double nROrgImgk1, double nROrgImgk2, double nROrgImgp1, double nROrgImgp2);

	//释放内存数据
	void ReleaseData();

// 	/* 
// 	生成灰度核线影像对 的 主函数
// 	输出的核线影像由核线影像对应的实际大小确定
// 	先确定左核线影像范围，右核线影像范围与其相对应
// 		unsigned char* pLImgBits,	//左原始影像
// 		unsigned char* pRImgBits,	//右原始影像
// 		int nLEplImgChannel,		//生成左核线影像波段数
// 		int nREplImgChannel			//生成右核线影像波段数
// 	*/
// 	int GetElpStereoImgs_MainFun(unsigned char* pLImgBits, unsigned char* pRImgBits, 
// 		int nLEplImgChannel, int nREplImgChannel);

	/* 
	生成灰度核线影像对 的 主函数
	输出的核线影像由核线影像对应的实际大小确定
	先确定左核线影像范围，右核线影像范围与其相对应
	
	unsigned char* pLImgBits,	//左原始影像
	unsigned char* pRImgBits,	//右原始影像
	int nLEplImgChannel,		//生成左核线影像波段数
	int nREplImgChannel			//生成右核线影像波段数
	*/
	int GetElpStereoImgs(unsigned char* pLImgBits, int nLRowFrom, int nLColFrom, int nLRowNum, int nLColNum, int nLEplImgChannel, 
								 unsigned char* pRImgBits, int nRRowFrom, int nRColFrom, int nRRowNum, int nRColNum, int nREplImgChannel, 
								 bool bIsLREplImgSizeSame);


		/*
	左影像由核线影像坐标获得原始影像坐标
	float nEplImgX, float nEplImgY		//左核线影像坐标
	float* pOrgImgX, float* pOrgImgY	//左原始影像坐标
	*/
	double GetLImgOrgPos_From_EplPos(float nEplImgX, float nEplImgY, float* pOrgImgX, float* pOrgImgY);

	/*
	右影像由核线影像坐标获得原始影像坐标
	float nEplImgX, float nEplImgY		//右核线影像坐标
	float* pOrgImgX, float* pOrgImgY	//右原始影像坐标
	*/
	double GetRImgOrgPos_From_EplPos(float nEplImgX, float nEplImgY, float* pOrgImgX, float* pnOrgImgY);

	/* 
	左影像由原始影像坐标获得核线影像坐标
	float nOrgImgX, float nOrgImgY,			//左原始影像坐标
	float* pEplImgX, float* pEplImgY		//左核线影像坐标
	*/
	int GetLImgEplPos_From_OrgPos(float nOrgImgX, float nOrgImgY, float* pEplImgX, float* pEplImgY);

	/* 
	右影像由原始影像坐标获得核线影像坐标
	float nOrgImgX, float nOrgImgY,			//右原始影像坐标
	float* pEplImgX, float* pEplImgY		//右核线影像坐标
	*/
	int GetRImgEplPos_From_OrgPos(float nOrgImgX, float nOrgImgY, float* pEplImgX, float* pEplImgY);


	//初始化                                                                     
	void InitData();
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
protected:

	//由于原始影像范围确定其对应的最大核线影像范围
	void GetEplRange_From_OrgRange(int nOrgRowFrom, int nOrgColFrom, int nOrgRowNum, int nOrgColNum, 
								   int* nEplRowFrom, int* nEplRowTo, int* nEplColFrom, int* nEplColTo,
							 	   bool bIsLImg);

	//双线性采样，确定采样点的灰度
	void GetPixelGray(unsigned char* pOrgImgBits, int nOrgImgHeight, int nOrgImgWidth, int nOrgImgChannelNum, int nOrgImgWidthStep,
		float nImgX, float nImgY, 
		unsigned char** pptrImg, int nImgHeight, int nImgWidth, int nImgChannelNum);
	void GetPixelGray(unsigned char* pOrgImgBits, int nOrgImgRowFrom, int nOrgImgColFrom, int nOrgImgRowNum, int nOrgImgColNum, int nOrgImgChannelNum, int nOrgImgColStep,
		float nImgX, float nImgY, unsigned char** pptrImg, int nImgChannelNum);

	//计算旋转矩阵                                                                     
	void transAngleToRotateMatrix(double nImgPhi, double nImgOmega, double nImgKappa, double r[3][3]);
	void transAngleToRotateMatrix(double nImgPhi, double nImgOmega, double nImgKappa, double r[9]);
	//计算从左影像像空间坐标系到右影像像空间坐标系 的旋转矩阵   R1_R2                                                                   
	void R21Matrix(double rl[3][3], double rr[3][3], double R21[3][3]);

	//像素坐标经畸变差改正到像点坐标(mm)
	void  Distort_Photo2MM(float xp, float yp, float* pxmc, float* pymc, 
		float pixelSize, double x0, double y0, double k1, double k2, double p1, double p2);
	//像点坐标(mm)反算到像素坐标（考虑畸变差）
	int  Distort_MM2Photo(float xmc, float ymc, float* pxp, float* pyp, float pixelSize, double x0, double y0, double k1, double k2, double p1, double p2);

	/*                                                                      
	始终按人眼立体生成核线影像时，从原始影像到核线影像计算时需要进行的坐标转换(影像中心为原点时）
	
	W' = |cos(A)*W-sin(A)*H|;		H' = |sin(A)*W+cos(A)*H|

	x'		cos(A)  -sin(A)	  x-W'/2              W/2
		=					*            +                        
	y'	    sin(A)	 cos(A)	  y-H'/2		      H/2
	
	 A = ｛0, 90, 180, 270}
	
	*/
	void TransImgPos_Org_From_Epl(float nImgX, float nImgY, float* nNewImgX, float* nNewImgY);
	void TransImgPos_Org_From_Epl(float nImgX, float nImgY, int nImgWidth, int nImgHeight, float* nNewImgX, float* nNewImgY);
	

	/*                                                                      
	始终按人眼立体生成核线影像时，从原始影像到核线影像计算时需要进行的坐标转换(影像中心为原点时）

	x'		cos(A)  sin(A)	  x-W/2     |cos(A)|  |sin(A)|    W/2
		=					*        +                     *
	y'	   -sin(A)	cos(A)	  y-H/2		|-sin(A)| |cos(A)|    H/2
	
	 A = ｛0, 90, 180, 270}
	
	*/
	void TransImgPos_Epl_From_Org(float nImgX, float nImgY, int nImgWidth, int nImgHeight, float* nNewImgX, float* nNewImgY);
	/*                                                                      
	始终按人眼立体生成核线影像时，从原始影像到核线影像计算时需要进行的坐标转换(左下角为原点时）

	x'		cos(A)  sin(A)	  x-W/2     |cos(A)|  |sin(A)|    W/2
		=					*        +                     *
	y'	   -sin(A)	cos(A)	  y-H/2		|-sin(A)| |cos(A)|    H/2
	
	 A = ｛0, 90, 180, 270}
	
	*/
	void TransImgPos_Epl_From_Org(float nImgX, float nImgY, float* nNewImgX, float* nNewImgY);
protected:
	//变量
	bool m_bIsSetPars;								//是否设置类参数
	double m_nLImgRM[3][3];											//左影像旋转矩阵

	double m_nRImgRM[3][3];											//右影像旋转矩阵

	double m_nBX, m_nBY, m_nBZ;										//摄影测量坐标系下基线坐标
	double usl, vsl, wsl;											//左影像外方位元素为基准（0，0，0，0，0，0）下的基线坐标
	double usr, vsr, wsr;											//右影像外方位元素为基准（0，0，0，0，0，0）下的基线坐标
	double m_R1_R2[3][3];												//右影像相对左影像的旋转矩阵

	float m_nLImgHeight_2, m_nLImgWidth_2;							//左影像高宽一半
	float m_nRImgHeight_2, m_nRImgWidth_2;							//右影像高宽一半
	
	bool m_bIsRImgRotate;											//左右影像的重叠关系是否不一致（如左影像确定是左右重叠，而右影像外确定是上下重叠）
																	//若是不一致，则右影像需要旋转
	int m_nRImgRotateAngle;											//需要旋转的角度（-90或+90度）
public:
	
	//原始影像信息
	int m_nLImgHeight, m_nLImgWidth, m_nLImgChannelNum;	//左影像高、宽、波段数
	double m_nLImgXs, m_nLImgYs, m_nLImgZs, m_nLImgPhi, m_nLImgOmega, m_nLImgKappa;//左影像外方位元素
	float m_nLImgf, m_nLImgx0, m_nLImgy0, m_nLImgPixelSize;			//左影像相机参数
	double m_nLImgk1, m_nLImgk2, m_nLImgp1, m_nLImgp2;				//左影像畸变参数

	int m_nRImgHeight, m_nRImgWidth, m_nRImgChannelNum;			//右影像高、宽、波段数
	double m_nRImgXs, m_nRImgYs, m_nRImgZs, m_nRImgPhi, m_nRImgOmega, m_nRImgKappa;		//右影像外方位元素
	float m_nRImgf, m_nRImgx0, m_nRImgy0, m_nRImgPixelSize;			//右影像相机参数
	double m_nRImgk1, m_nRImgk2, m_nRImgp1, m_nRImgp2;				//右影像畸变参数


	//核线信息
	int m_nLEntireEplImgFromX, m_nLEntireEplImgFromY;				//左影像核线影像全部区域
	int m_nLEntireEplImgToX, m_nLEntireEplImgToY;
	int m_nLEntireEplImgHeight, m_nLEntireEplImgWidth;	
	int m_nREntireEplImgFromX, m_nREntireEplImgFromY, m_nREntireEplImgToX, m_nREntireEplImgToY;	//右影像核线影像全部区域
	int m_nREntireEplImgHeight, m_nREntireEplImgWidth;	
	
	unsigned char* m_pLEplImgBits;							//需要计算左核线影像
	int m_nLEplImgHeight, m_nLEplImgWidth, m_nLEplImgChannelNum;  //需要计算左核线影像高、宽、波段数
	int m_nLEplImgFromX, m_nLEplImgFromY;						//需要计算左核线影像起始行列号（原点位置不变）
	int m_nLEplImgToX, m_nLEplImgToY;							//需要计算左核线影像终止行列号（原点位置不变）

	unsigned char* m_pREplImgBits;							//需要计算右核线影像
	int m_nREplImgHeight, m_nREplImgWidth, m_nREplImgChannelNum;	//需要计算右影像高、宽、波段数
	int m_nREplImgFromX, m_nREplImgFromY;						//需要计算右核线影像起始行列号（原点位置不变）
	int m_nREplImgToX, m_nREplImgToY;							//需要计算右核线影像终止行列号（原点位置不变）
	int m_nOverlapFlag;									//重叠类型（参数由基线方向确定）， 1:左右重叠；2：下上重叠；3：右左重叠；4：上下重叠

#if 0
	
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	/* 
	设置函数参数
	int nLOrgImgHeight, int nLOrgImgWidth, int nLOrgImgChannelNum,	//左影像高、宽、波段数
	double nLOrgImgXs, double nLOrgImgYs, double nLOrgImgZs, double nLOrgImgPhi, double nLOrgImgOmega, double nLOrgImgKappa,	//左影像外方位元素
	float nLOrgImgf, float nLOrgImgx0, float nLOrgImgy0, float nLOrgImgPixelSize,	//左影像相机参数
	double nLOrgImgk1, double nLOrgImgk2, double nLOrgImgp1, double nLOrgImgp2,	    //左影像畸变参数
	int nROrgImgHeight, int nROrgImgWidth, int nROrgImgChannelNum,					//右影像高、宽、波段数
	double nROrgImgXs, double nROrgImgYs, double nROrgImgZs, double nROrgImgPhi, double nROrgImgOmega, double nROrgImgKappa,	//右影像外方位元素
	float nROrgImgf, float nROrgImgx0, float nROrgImgy0, float nROrgImgPixelSize,	//右影像相机参数
	double nROrgImgk1, double nROrgImgk2, double nROrgImgp1, double nROrgImgp2,		//右影像畸变参数
	*/
	int SetPars(int nLOrgImgHeight, int nLOrgImgWidth, int nLOrgImgChannelNum,  
		double nLOrgImgXs, double nLOrgImgYs, double nLOrgImgZs, double nLOrgImgPhi, double nLOrgImgOmega, double nLOrgImgKappa,
		float nLOrgImgf, float nLOrgImgx0, float nLOrgImgy0, float nLOrgImgPixelSize, 
		double nLOrgImgk1, double nLOrgImgk2, double nLOrgImgp1, double nLOrgImgp2,
		int nROrgImgHeight, int nROrgImgWidth, int nROrgImgChannelNum, 
		double nROrgImgXs, double nROrgImgYs, double nROrgImgZs, double nROrgImgPhi, double nROrgImgOmega, double nROrgImgKappa,
		float nROrgImgf, float nROrgImgx0, float nROrgImgy0, float nROrgImgPixelSize, 
		double nROrgImgk1, double nROrgImgk2, double nROrgImgp1, double nROrgImgp2);

	//释放内存数据
	void ReleaseData();

	/* 
	生成灰度核线影像对 的 主函数
	输出的核线影像由核线影像对应的实际大小确定
	先确定左核线影像范围，右核线影像范围与其相对应
	
	unsigned char* pLImgBits,	//左原始影像
	unsigned char* pRImgBits,	//右原始影像
	int nLEplImgChannel,		//生成左核线影像波段数
	int nREplImgChannel			//生成右核线影像波段数
	*/
	int GetElpStereoImgs(unsigned char* pLImgBits, int nLRowFrom, int nLColFrom, int nLRowNum, int nLColNum, int nLEplImgChannel, 
								 unsigned char* pRImgBits, int nRRowFrom, int nRColFrom, int nRRowNum, int nRColNum, int nREplImgChannel, 
								 bool bIsLREplImgSizeSame);


		/*
	左影像由核线影像坐标获得原始影像坐标
	float nEplImgX, float nEplImgY		//左核线影像坐标
	float* pOrgImgX, float* pOrgImgY	//左原始影像坐标
	*/
	double GetLImgOrgPos_From_EplPos(float nEplImgX, float nEplImgY, float* pOrgImgX, float* pOrgImgY);

	/*
	右影像由核线影像坐标获得原始影像坐标
	float nEplImgX, float nEplImgY		//右核线影像坐标
	float* pOrgImgX, float* pOrgImgY	//右原始影像坐标
	*/
	double GetRImgOrgPos_From_EplPos(float nEplImgX, float nEplImgY, float* pOrgImgX, float* pnOrgImgY);

	/* 
	左影像由原始影像坐标获得核线影像坐标
	float nOrgImgX, float nOrgImgY,			//左原始影像坐标
	float* pEplImgX, float* pEplImgY		//左核线影像坐标
	*/
	int GetLImgEplPos_From_OrgPos(float nOrgImgX, float nOrgImgY, float* pEplImgX, float* pEplImgY);

	/* 
	右影像由原始影像坐标获得核线影像坐标
	float nOrgImgX, float nOrgImgY,			//右原始影像坐标
	float* pEplImgX, float* pEplImgY		//右核线影像坐标
	*/
	int GetRImgEplPos_From_OrgPos(float nOrgImgX, float nOrgImgY, float* pEplImgX, float* pEplImgY);


	//初始化                                                                     
	void InitData();
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
protected:

	//由于原始影像范围确定其对应的最大核线影像范围
	void GetEplRange_From_OrgRange(int nOrgRowFrom, int nOrgColFrom, int nOrgRowNum, int nOrgColNum, 
								   int* nEplRowFrom, int* nEplRowTo, int* nEplColFrom, int* nEplColTo,
							 	   bool bIsLImg);

	//双线性采样，确定采样点的灰度
	void GetPixelGray(unsigned char* pOrgImgBits, int nOrgImgHeight, int nOrgImgWidth, int nOrgImgChannelNum, int nOrgImgWidthStep,
		float nImgX, float nImgY, 
		unsigned char** pptrImg, int nImgHeight, int nImgWidth, int nImgChannelNum);
	void GetPixelGray(unsigned char* pOrgImgBits, int nOrgImgRowFrom, int nOrgImgColFrom, int nOrgImgRowNum, int nOrgImgColNum, int nOrgImgChannelNum, int nOrgImgColStep,
		float nImgX, float nImgY, unsigned char** pptrImg, int nImgChannelNum);

	//计算旋转矩阵                                                                     
	void transAngleToRotateMatrix(double nImgPhi, double nImgOmega, double nImgKappa, double r[3][3]);
	void transAngleToRotateMatrix(double nImgPhi, double nImgOmega, double nImgKappa, double r[9]);
	//计算从左影像像空间坐标系到右影像像空间坐标系 的旋转矩阵   R1_R2                                                                   
	void R21Matrix(double rl[3][3], double rr[3][3], double R21[3][3]);

	//像素坐标经畸变差改正到像点坐标(mm)
	void  Distort_Photo2MM(float xp, float yp, float* pxmc, float* pymc, 
		float pixelSize, double x0, double y0, double k1, double k2, double p1, double p2);
	//像点坐标(mm)反算到像素坐标（考虑畸变差）
	int  Distort_MM2Photo(float xmc, float ymc, float* pxp, float* pyp, float pixelSize, double x0, double y0, double k1, double k2, double p1, double p2);

	/*                                                                      
	始终按人眼立体生成核线影像时，从原始影像到核线影像计算时需要进行的坐标转换(影像中心为原点时）
	
	W' = |cos(A)*W-sin(A)*H|;		H' = |sin(A)*W+cos(A)*H|

	x'		cos(A)  -sin(A)	  x-W'/2              W/2
		=					*            +                        
	y'	    sin(A)	 cos(A)	  y-H'/2		      H/2
	
	 A = ｛0, 90, 180, 270}
	
	*/
	void TransImgPos_Org_From_Epl(float nImgX, float nImgY, float* nNewImgX, float* nNewImgY);
	void TransImgPos_Org_From_Epl(float nImgX, float nImgY, int nImgWidth, int nImgHeight, float* nNewImgX, float* nNewImgY);
	

	/*                                                                      
	始终按人眼立体生成核线影像时，从原始影像到核线影像计算时需要进行的坐标转换(影像中心为原点时）

	x'		cos(A)  sin(A)	  x-W/2     |cos(A)|  |sin(A)|    W/2
		=					*        +                     *
	y'	   -sin(A)	cos(A)	  y-H/2		|-sin(A)| |cos(A)|    H/2
	
	 A = ｛0, 90, 180, 270}
	
	*/
	void TransImgPos_Epl_From_Org(float nImgX, float nImgY, int nImgWidth, int nImgHeight, float* nNewImgX, float* nNewImgY);
	/*                                                                      
	始终按人眼立体生成核线影像时，从原始影像到核线影像计算时需要进行的坐标转换(左下角为原点时）

	x'		cos(A)  sin(A)	  x-W/2     |cos(A)|  |sin(A)|    W/2
		=					*        +                     *
	y'	   -sin(A)	cos(A)	  y-H/2		|-sin(A)| |cos(A)|    H/2
	
	 A = ｛0, 90, 180, 270}
	
	*/
	void TransImgPos_Epl_From_Org(float nImgX, float nImgY, float* nNewImgX, float* nNewImgY);
protected:
	//变量
	bool m_bIsSetPars;								//是否设置类参数
	double m_nLImgRM[3][3];											//左影像旋转矩阵

	double m_nRImgRM[3][3];											//右影像旋转矩阵

	double m_nBX, m_nBY, m_nBZ;										//摄影测量坐标系下基线坐标
	double usl, vsl, wsl;											//左影像外方位元素为基准（0，0，0，0，0，0）下的基线坐标
	double usr, vsr, wsr;											//右影像外方位元素为基准（0，0，0，0，0，0）下的基线坐标
	double m_R1_R2[3][3];												//右影像相对左影像的旋转矩阵

	float m_nLImgHeight_2, m_nLImgWidth_2;							//左影像高宽一半
	float m_nRImgHeight_2, m_nRImgWidth_2;							//右影像高宽一半
	
	
public:
	
	//原始影像信息
	int m_nLImgHeight, m_nLImgWidth, m_nLImgChannelNum;	//左影像高、宽、波段数
	double m_nLImgXs, m_nLImgYs, m_nLImgZs, m_nLImgPhi, m_nLImgOmega, m_nLImgKappa;//左影像外方位元素
	float m_nLImgf, m_nLImgx0, m_nLImgy0, m_nLImgPixelSize;			//左影像相机参数
	double m_nLImgk1, m_nLImgk2, m_nLImgp1, m_nLImgp2;				//左影像畸变参数

	int m_nRImgHeight, m_nRImgWidth, m_nRImgChannelNum;			//右影像高、宽、波段数
	double m_nRImgXs, m_nRImgYs, m_nRImgZs, m_nRImgPhi, m_nRImgOmega, m_nRImgKappa;		//右影像外方位元素
	float m_nRImgf, m_nRImgx0, m_nRImgy0, m_nRImgPixelSize;			//右影像相机参数
	double m_nRImgk1, m_nRImgk2, m_nRImgp1, m_nRImgp2;				//右影像畸变参数


	//核线信息
	int m_nLEntireEplImgFromX, m_nLEntireEplImgFromY;				//左影像核线影像全部区域
	int m_nLEntireEplImgToX, m_nLEntireEplImgToY;
	int m_nLEntireEplImgHeight, m_nLEntireEplImgWidth;	
	int m_nREntireEplImgFromX, m_nREntireEplImgFromY, m_nREntireEplImgToX, m_nREntireEplImgToY;	//右影像核线影像全部区域
	int m_nREntireEplImgHeight, m_nREntireEplImgWidth;	
	
	unsigned char* m_pLEplImgBits;							//需要计算左核线影像
	int m_nLEplImgHeight, m_nLEplImgWidth, m_nLEplImgChannelNum;  //需要计算左核线影像高、宽、波段数
	int m_nLEplImgFromX, m_nLEplImgFromY;						//需要计算左核线影像起始行列号（原点位置不变）
	int m_nLEplImgToX, m_nLEplImgToY;							//需要计算左核线影像终止行列号（原点位置不变）

	unsigned char* m_pREplImgBits;							//需要计算右核线影像
	int m_nREplImgHeight, m_nREplImgWidth, m_nREplImgChannelNum;	//需要计算右影像高、宽、波段数
	int m_nREplImgFromX, m_nREplImgFromY;						//需要计算右核线影像起始行列号（原点位置不变）
	int m_nREplImgToX, m_nREplImgToY;							//需要计算右核线影像终止行列号（原点位置不变）
	int m_nOverlapFlag;	

#endif
};

#endif