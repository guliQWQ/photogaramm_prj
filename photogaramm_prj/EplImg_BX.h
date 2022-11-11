#include "windows.h"
#ifndef EPLIMAGEDLL_H_HS_2014_10_16
#define EPLIMAGEDLL_H_HS_2014_10_16
#include "SpVZImage.h"

//�ú������dll��Ŀ�ڲ�ʹ��__declspec(dllexport)����  
//��dll��Ŀ�ⲿʹ��ʱ����__declspec(dllimport)����  
//��DLL_IMPLEMENT��simpledll.cpp�ж���
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
	���ú�������
	int nLOrgImgHeight, int nLOrgImgWidth, int nLOrgImgChannelNum,	//��Ӱ��ߡ���������
	double nLOrgImgXs, double nLOrgImgYs, double nLOrgImgZs, double nLOrgImgPhi, double nLOrgImgOmega, double nLOrgImgKappa,	//��Ӱ���ⷽλԪ��
	float nLOrgImgf, float nLOrgImgx0, float nLOrgImgy0, float nLOrgImgPixelSize,	//��Ӱ���������
	double nLOrgImgk1, double nLOrgImgk2, double nLOrgImgp1, double nLOrgImgp2,	    //��Ӱ��������
	int nROrgImgHeight, int nROrgImgWidth, int nROrgImgChannelNum,					//��Ӱ��ߡ���������
	double nROrgImgXs, double nROrgImgYs, double nROrgImgZs, double nROrgImgPhi, double nROrgImgOmega, double nROrgImgKappa,	//��Ӱ���ⷽλԪ��
	float nROrgImgf, float nROrgImgx0, float nROrgImgy0, float nROrgImgPixelSize,	//��Ӱ���������
	double nROrgImgk1, double nROrgImgk2, double nROrgImgp1, double nROrgImgp2,		//��Ӱ��������
	*/
	int SetPars(int nLOrgImgHeight, int nLOrgImgWidth, int nLOrgImgChannelNum,  
		double nLOrgImgXs, double nLOrgImgYs, double nLOrgImgZs, double nLOrgImgPhi, double nLOrgImgOmega, double nLOrgImgKappa,
		float nLOrgImgf, float nLOrgImgx0, float nLOrgImgy0, float nLOrgImgPixelSize, 
		double nLOrgImgk1, double nLOrgImgk2, double nLOrgImgp1, double nLOrgImgp2,
		int nROrgImgHeight, int nROrgImgWidth, int nROrgImgChannelNum, 
		double nROrgImgXs, double nROrgImgYs, double nROrgImgZs, double nROrgImgPhi, double nROrgImgOmega, double nROrgImgKappa,
		float nROrgImgf, float nROrgImgx0, float nROrgImgy0, float nROrgImgPixelSize, 
		double nROrgImgk1, double nROrgImgk2, double nROrgImgp1, double nROrgImgp2);

	//�ͷ��ڴ�����
	void ReleaseData();

// 	/* 
// 	���ɻҶȺ���Ӱ��� �� ������
// 	����ĺ���Ӱ���ɺ���Ӱ���Ӧ��ʵ�ʴ�Сȷ��
// 	��ȷ�������Ӱ��Χ���Һ���Ӱ��Χ�������Ӧ
// 		unsigned char* pLImgBits,	//��ԭʼӰ��
// 		unsigned char* pRImgBits,	//��ԭʼӰ��
// 		int nLEplImgChannel,		//���������Ӱ�񲨶���
// 		int nREplImgChannel			//�����Һ���Ӱ�񲨶���
// 	*/
// 	int GetElpStereoImgs_MainFun(unsigned char* pLImgBits, unsigned char* pRImgBits, 
// 		int nLEplImgChannel, int nREplImgChannel);

	/* 
	���ɻҶȺ���Ӱ��� �� ������
	����ĺ���Ӱ���ɺ���Ӱ���Ӧ��ʵ�ʴ�Сȷ��
	��ȷ�������Ӱ��Χ���Һ���Ӱ��Χ�������Ӧ
	
	unsigned char* pLImgBits,	//��ԭʼӰ��
	unsigned char* pRImgBits,	//��ԭʼӰ��
	int nLEplImgChannel,		//���������Ӱ�񲨶���
	int nREplImgChannel			//�����Һ���Ӱ�񲨶���
	*/
	int GetElpStereoImgs(unsigned char* pLImgBits, int nLRowFrom, int nLColFrom, int nLRowNum, int nLColNum, int nLEplImgChannel, 
								 unsigned char* pRImgBits, int nRRowFrom, int nRColFrom, int nRRowNum, int nRColNum, int nREplImgChannel, 
								 bool bIsLREplImgSizeSame);


		/*
	��Ӱ���ɺ���Ӱ��������ԭʼӰ������
	float nEplImgX, float nEplImgY		//�����Ӱ������
	float* pOrgImgX, float* pOrgImgY	//��ԭʼӰ������
	*/
	double GetLImgOrgPos_From_EplPos(float nEplImgX, float nEplImgY, float* pOrgImgX, float* pOrgImgY);

	/*
	��Ӱ���ɺ���Ӱ��������ԭʼӰ������
	float nEplImgX, float nEplImgY		//�Һ���Ӱ������
	float* pOrgImgX, float* pOrgImgY	//��ԭʼӰ������
	*/
	double GetRImgOrgPos_From_EplPos(float nEplImgX, float nEplImgY, float* pOrgImgX, float* pnOrgImgY);

	/* 
	��Ӱ����ԭʼӰ�������ú���Ӱ������
	float nOrgImgX, float nOrgImgY,			//��ԭʼӰ������
	float* pEplImgX, float* pEplImgY		//�����Ӱ������
	*/
	int GetLImgEplPos_From_OrgPos(float nOrgImgX, float nOrgImgY, float* pEplImgX, float* pEplImgY);

	/* 
	��Ӱ����ԭʼӰ�������ú���Ӱ������
	float nOrgImgX, float nOrgImgY,			//��ԭʼӰ������
	float* pEplImgX, float* pEplImgY		//�Һ���Ӱ������
	*/
	int GetRImgEplPos_From_OrgPos(float nOrgImgX, float nOrgImgY, float* pEplImgX, float* pEplImgY);


	//��ʼ��                                                                     
	void InitData();
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
protected:

	//����ԭʼӰ��Χȷ�����Ӧ��������Ӱ��Χ
	void GetEplRange_From_OrgRange(int nOrgRowFrom, int nOrgColFrom, int nOrgRowNum, int nOrgColNum, 
								   int* nEplRowFrom, int* nEplRowTo, int* nEplColFrom, int* nEplColTo,
							 	   bool bIsLImg);

	//˫���Բ�����ȷ��������ĻҶ�
	void GetPixelGray(unsigned char* pOrgImgBits, int nOrgImgHeight, int nOrgImgWidth, int nOrgImgChannelNum, int nOrgImgWidthStep,
		float nImgX, float nImgY, 
		unsigned char** pptrImg, int nImgHeight, int nImgWidth, int nImgChannelNum);
	void GetPixelGray(unsigned char* pOrgImgBits, int nOrgImgRowFrom, int nOrgImgColFrom, int nOrgImgRowNum, int nOrgImgColNum, int nOrgImgChannelNum, int nOrgImgColStep,
		float nImgX, float nImgY, unsigned char** pptrImg, int nImgChannelNum);

	//������ת����                                                                     
	void transAngleToRotateMatrix(double nImgPhi, double nImgOmega, double nImgKappa, double r[3][3]);
	void transAngleToRotateMatrix(double nImgPhi, double nImgOmega, double nImgKappa, double r[9]);
	//�������Ӱ����ռ�����ϵ����Ӱ����ռ�����ϵ ����ת����   R1_R2                                                                   
	void R21Matrix(double rl[3][3], double rr[3][3], double R21[3][3]);

	//�������꾭�����������������(mm)
	void  Distort_Photo2MM(float xp, float yp, float* pxmc, float* pymc, 
		float pixelSize, double x0, double y0, double k1, double k2, double p1, double p2);
	//�������(mm)���㵽�������꣨���ǻ���
	int  Distort_MM2Photo(float xmc, float ymc, float* pxp, float* pyp, float pixelSize, double x0, double y0, double k1, double k2, double p1, double p2);

	/*                                                                      
	ʼ�հ������������ɺ���Ӱ��ʱ����ԭʼӰ�񵽺���Ӱ�����ʱ��Ҫ���е�����ת��(Ӱ������Ϊԭ��ʱ��
	
	W' = |cos(A)*W-sin(A)*H|;		H' = |sin(A)*W+cos(A)*H|

	x'		cos(A)  -sin(A)	  x-W'/2              W/2
		=					*            +                        
	y'	    sin(A)	 cos(A)	  y-H'/2		      H/2
	
	 A = ��0, 90, 180, 270}
	
	*/
	void TransImgPos_Org_From_Epl(float nImgX, float nImgY, float* nNewImgX, float* nNewImgY);
	void TransImgPos_Org_From_Epl(float nImgX, float nImgY, int nImgWidth, int nImgHeight, float* nNewImgX, float* nNewImgY);
	

	/*                                                                      
	ʼ�հ������������ɺ���Ӱ��ʱ����ԭʼӰ�񵽺���Ӱ�����ʱ��Ҫ���е�����ת��(Ӱ������Ϊԭ��ʱ��

	x'		cos(A)  sin(A)	  x-W/2     |cos(A)|  |sin(A)|    W/2
		=					*        +                     *
	y'	   -sin(A)	cos(A)	  y-H/2		|-sin(A)| |cos(A)|    H/2
	
	 A = ��0, 90, 180, 270}
	
	*/
	void TransImgPos_Epl_From_Org(float nImgX, float nImgY, int nImgWidth, int nImgHeight, float* nNewImgX, float* nNewImgY);
	/*                                                                      
	ʼ�հ������������ɺ���Ӱ��ʱ����ԭʼӰ�񵽺���Ӱ�����ʱ��Ҫ���е�����ת��(���½�Ϊԭ��ʱ��

	x'		cos(A)  sin(A)	  x-W/2     |cos(A)|  |sin(A)|    W/2
		=					*        +                     *
	y'	   -sin(A)	cos(A)	  y-H/2		|-sin(A)| |cos(A)|    H/2
	
	 A = ��0, 90, 180, 270}
	
	*/
	void TransImgPos_Epl_From_Org(float nImgX, float nImgY, float* nNewImgX, float* nNewImgY);
protected:
	//����
	bool m_bIsSetPars;								//�Ƿ����������
	double m_nLImgRM[3][3];											//��Ӱ����ת����

	double m_nRImgRM[3][3];											//��Ӱ����ת����

	double m_nBX, m_nBY, m_nBZ;										//��Ӱ��������ϵ�»�������
	double usl, vsl, wsl;											//��Ӱ���ⷽλԪ��Ϊ��׼��0��0��0��0��0��0���µĻ�������
	double usr, vsr, wsr;											//��Ӱ���ⷽλԪ��Ϊ��׼��0��0��0��0��0��0���µĻ�������
	double m_R1_R2[3][3];												//��Ӱ�������Ӱ�����ת����

	float m_nLImgHeight_2, m_nLImgWidth_2;							//��Ӱ��߿�һ��
	float m_nRImgHeight_2, m_nRImgWidth_2;							//��Ӱ��߿�һ��
	
	bool m_bIsRImgRotate;											//����Ӱ����ص���ϵ�Ƿ�һ�£�����Ӱ��ȷ���������ص�������Ӱ����ȷ���������ص���
																	//���ǲ�һ�£�����Ӱ����Ҫ��ת
	int m_nRImgRotateAngle;											//��Ҫ��ת�ĽǶȣ�-90��+90�ȣ�
public:
	
	//ԭʼӰ����Ϣ
	int m_nLImgHeight, m_nLImgWidth, m_nLImgChannelNum;	//��Ӱ��ߡ���������
	double m_nLImgXs, m_nLImgYs, m_nLImgZs, m_nLImgPhi, m_nLImgOmega, m_nLImgKappa;//��Ӱ���ⷽλԪ��
	float m_nLImgf, m_nLImgx0, m_nLImgy0, m_nLImgPixelSize;			//��Ӱ���������
	double m_nLImgk1, m_nLImgk2, m_nLImgp1, m_nLImgp2;				//��Ӱ��������

	int m_nRImgHeight, m_nRImgWidth, m_nRImgChannelNum;			//��Ӱ��ߡ���������
	double m_nRImgXs, m_nRImgYs, m_nRImgZs, m_nRImgPhi, m_nRImgOmega, m_nRImgKappa;		//��Ӱ���ⷽλԪ��
	float m_nRImgf, m_nRImgx0, m_nRImgy0, m_nRImgPixelSize;			//��Ӱ���������
	double m_nRImgk1, m_nRImgk2, m_nRImgp1, m_nRImgp2;				//��Ӱ��������


	//������Ϣ
	int m_nLEntireEplImgFromX, m_nLEntireEplImgFromY;				//��Ӱ�����Ӱ��ȫ������
	int m_nLEntireEplImgToX, m_nLEntireEplImgToY;
	int m_nLEntireEplImgHeight, m_nLEntireEplImgWidth;	
	int m_nREntireEplImgFromX, m_nREntireEplImgFromY, m_nREntireEplImgToX, m_nREntireEplImgToY;	//��Ӱ�����Ӱ��ȫ������
	int m_nREntireEplImgHeight, m_nREntireEplImgWidth;	
	
	unsigned char* m_pLEplImgBits;							//��Ҫ���������Ӱ��
	int m_nLEplImgHeight, m_nLEplImgWidth, m_nLEplImgChannelNum;  //��Ҫ���������Ӱ��ߡ���������
	int m_nLEplImgFromX, m_nLEplImgFromY;						//��Ҫ���������Ӱ����ʼ���кţ�ԭ��λ�ò��䣩
	int m_nLEplImgToX, m_nLEplImgToY;							//��Ҫ���������Ӱ����ֹ���кţ�ԭ��λ�ò��䣩

	unsigned char* m_pREplImgBits;							//��Ҫ�����Һ���Ӱ��
	int m_nREplImgHeight, m_nREplImgWidth, m_nREplImgChannelNum;	//��Ҫ������Ӱ��ߡ���������
	int m_nREplImgFromX, m_nREplImgFromY;						//��Ҫ�����Һ���Ӱ����ʼ���кţ�ԭ��λ�ò��䣩
	int m_nREplImgToX, m_nREplImgToY;							//��Ҫ�����Һ���Ӱ����ֹ���кţ�ԭ��λ�ò��䣩
	int m_nOverlapFlag;									//�ص����ͣ������ɻ��߷���ȷ������ 1:�����ص���2�������ص���3�������ص���4�������ص�

#if 0
	
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	/* 
	���ú�������
	int nLOrgImgHeight, int nLOrgImgWidth, int nLOrgImgChannelNum,	//��Ӱ��ߡ���������
	double nLOrgImgXs, double nLOrgImgYs, double nLOrgImgZs, double nLOrgImgPhi, double nLOrgImgOmega, double nLOrgImgKappa,	//��Ӱ���ⷽλԪ��
	float nLOrgImgf, float nLOrgImgx0, float nLOrgImgy0, float nLOrgImgPixelSize,	//��Ӱ���������
	double nLOrgImgk1, double nLOrgImgk2, double nLOrgImgp1, double nLOrgImgp2,	    //��Ӱ��������
	int nROrgImgHeight, int nROrgImgWidth, int nROrgImgChannelNum,					//��Ӱ��ߡ���������
	double nROrgImgXs, double nROrgImgYs, double nROrgImgZs, double nROrgImgPhi, double nROrgImgOmega, double nROrgImgKappa,	//��Ӱ���ⷽλԪ��
	float nROrgImgf, float nROrgImgx0, float nROrgImgy0, float nROrgImgPixelSize,	//��Ӱ���������
	double nROrgImgk1, double nROrgImgk2, double nROrgImgp1, double nROrgImgp2,		//��Ӱ��������
	*/
	int SetPars(int nLOrgImgHeight, int nLOrgImgWidth, int nLOrgImgChannelNum,  
		double nLOrgImgXs, double nLOrgImgYs, double nLOrgImgZs, double nLOrgImgPhi, double nLOrgImgOmega, double nLOrgImgKappa,
		float nLOrgImgf, float nLOrgImgx0, float nLOrgImgy0, float nLOrgImgPixelSize, 
		double nLOrgImgk1, double nLOrgImgk2, double nLOrgImgp1, double nLOrgImgp2,
		int nROrgImgHeight, int nROrgImgWidth, int nROrgImgChannelNum, 
		double nROrgImgXs, double nROrgImgYs, double nROrgImgZs, double nROrgImgPhi, double nROrgImgOmega, double nROrgImgKappa,
		float nROrgImgf, float nROrgImgx0, float nROrgImgy0, float nROrgImgPixelSize, 
		double nROrgImgk1, double nROrgImgk2, double nROrgImgp1, double nROrgImgp2);

	//�ͷ��ڴ�����
	void ReleaseData();

	/* 
	���ɻҶȺ���Ӱ��� �� ������
	����ĺ���Ӱ���ɺ���Ӱ���Ӧ��ʵ�ʴ�Сȷ��
	��ȷ�������Ӱ��Χ���Һ���Ӱ��Χ�������Ӧ
	
	unsigned char* pLImgBits,	//��ԭʼӰ��
	unsigned char* pRImgBits,	//��ԭʼӰ��
	int nLEplImgChannel,		//���������Ӱ�񲨶���
	int nREplImgChannel			//�����Һ���Ӱ�񲨶���
	*/
	int GetElpStereoImgs(unsigned char* pLImgBits, int nLRowFrom, int nLColFrom, int nLRowNum, int nLColNum, int nLEplImgChannel, 
								 unsigned char* pRImgBits, int nRRowFrom, int nRColFrom, int nRRowNum, int nRColNum, int nREplImgChannel, 
								 bool bIsLREplImgSizeSame);


		/*
	��Ӱ���ɺ���Ӱ��������ԭʼӰ������
	float nEplImgX, float nEplImgY		//�����Ӱ������
	float* pOrgImgX, float* pOrgImgY	//��ԭʼӰ������
	*/
	double GetLImgOrgPos_From_EplPos(float nEplImgX, float nEplImgY, float* pOrgImgX, float* pOrgImgY);

	/*
	��Ӱ���ɺ���Ӱ��������ԭʼӰ������
	float nEplImgX, float nEplImgY		//�Һ���Ӱ������
	float* pOrgImgX, float* pOrgImgY	//��ԭʼӰ������
	*/
	double GetRImgOrgPos_From_EplPos(float nEplImgX, float nEplImgY, float* pOrgImgX, float* pnOrgImgY);

	/* 
	��Ӱ����ԭʼӰ�������ú���Ӱ������
	float nOrgImgX, float nOrgImgY,			//��ԭʼӰ������
	float* pEplImgX, float* pEplImgY		//�����Ӱ������
	*/
	int GetLImgEplPos_From_OrgPos(float nOrgImgX, float nOrgImgY, float* pEplImgX, float* pEplImgY);

	/* 
	��Ӱ����ԭʼӰ�������ú���Ӱ������
	float nOrgImgX, float nOrgImgY,			//��ԭʼӰ������
	float* pEplImgX, float* pEplImgY		//�Һ���Ӱ������
	*/
	int GetRImgEplPos_From_OrgPos(float nOrgImgX, float nOrgImgY, float* pEplImgX, float* pEplImgY);


	//��ʼ��                                                                     
	void InitData();
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
protected:

	//����ԭʼӰ��Χȷ�����Ӧ��������Ӱ��Χ
	void GetEplRange_From_OrgRange(int nOrgRowFrom, int nOrgColFrom, int nOrgRowNum, int nOrgColNum, 
								   int* nEplRowFrom, int* nEplRowTo, int* nEplColFrom, int* nEplColTo,
							 	   bool bIsLImg);

	//˫���Բ�����ȷ��������ĻҶ�
	void GetPixelGray(unsigned char* pOrgImgBits, int nOrgImgHeight, int nOrgImgWidth, int nOrgImgChannelNum, int nOrgImgWidthStep,
		float nImgX, float nImgY, 
		unsigned char** pptrImg, int nImgHeight, int nImgWidth, int nImgChannelNum);
	void GetPixelGray(unsigned char* pOrgImgBits, int nOrgImgRowFrom, int nOrgImgColFrom, int nOrgImgRowNum, int nOrgImgColNum, int nOrgImgChannelNum, int nOrgImgColStep,
		float nImgX, float nImgY, unsigned char** pptrImg, int nImgChannelNum);

	//������ת����                                                                     
	void transAngleToRotateMatrix(double nImgPhi, double nImgOmega, double nImgKappa, double r[3][3]);
	void transAngleToRotateMatrix(double nImgPhi, double nImgOmega, double nImgKappa, double r[9]);
	//�������Ӱ����ռ�����ϵ����Ӱ����ռ�����ϵ ����ת����   R1_R2                                                                   
	void R21Matrix(double rl[3][3], double rr[3][3], double R21[3][3]);

	//�������꾭�����������������(mm)
	void  Distort_Photo2MM(float xp, float yp, float* pxmc, float* pymc, 
		float pixelSize, double x0, double y0, double k1, double k2, double p1, double p2);
	//�������(mm)���㵽�������꣨���ǻ���
	int  Distort_MM2Photo(float xmc, float ymc, float* pxp, float* pyp, float pixelSize, double x0, double y0, double k1, double k2, double p1, double p2);

	/*                                                                      
	ʼ�հ������������ɺ���Ӱ��ʱ����ԭʼӰ�񵽺���Ӱ�����ʱ��Ҫ���е�����ת��(Ӱ������Ϊԭ��ʱ��
	
	W' = |cos(A)*W-sin(A)*H|;		H' = |sin(A)*W+cos(A)*H|

	x'		cos(A)  -sin(A)	  x-W'/2              W/2
		=					*            +                        
	y'	    sin(A)	 cos(A)	  y-H'/2		      H/2
	
	 A = ��0, 90, 180, 270}
	
	*/
	void TransImgPos_Org_From_Epl(float nImgX, float nImgY, float* nNewImgX, float* nNewImgY);
	void TransImgPos_Org_From_Epl(float nImgX, float nImgY, int nImgWidth, int nImgHeight, float* nNewImgX, float* nNewImgY);
	

	/*                                                                      
	ʼ�հ������������ɺ���Ӱ��ʱ����ԭʼӰ�񵽺���Ӱ�����ʱ��Ҫ���е�����ת��(Ӱ������Ϊԭ��ʱ��

	x'		cos(A)  sin(A)	  x-W/2     |cos(A)|  |sin(A)|    W/2
		=					*        +                     *
	y'	   -sin(A)	cos(A)	  y-H/2		|-sin(A)| |cos(A)|    H/2
	
	 A = ��0, 90, 180, 270}
	
	*/
	void TransImgPos_Epl_From_Org(float nImgX, float nImgY, int nImgWidth, int nImgHeight, float* nNewImgX, float* nNewImgY);
	/*                                                                      
	ʼ�հ������������ɺ���Ӱ��ʱ����ԭʼӰ�񵽺���Ӱ�����ʱ��Ҫ���е�����ת��(���½�Ϊԭ��ʱ��

	x'		cos(A)  sin(A)	  x-W/2     |cos(A)|  |sin(A)|    W/2
		=					*        +                     *
	y'	   -sin(A)	cos(A)	  y-H/2		|-sin(A)| |cos(A)|    H/2
	
	 A = ��0, 90, 180, 270}
	
	*/
	void TransImgPos_Epl_From_Org(float nImgX, float nImgY, float* nNewImgX, float* nNewImgY);
protected:
	//����
	bool m_bIsSetPars;								//�Ƿ����������
	double m_nLImgRM[3][3];											//��Ӱ����ת����

	double m_nRImgRM[3][3];											//��Ӱ����ת����

	double m_nBX, m_nBY, m_nBZ;										//��Ӱ��������ϵ�»�������
	double usl, vsl, wsl;											//��Ӱ���ⷽλԪ��Ϊ��׼��0��0��0��0��0��0���µĻ�������
	double usr, vsr, wsr;											//��Ӱ���ⷽλԪ��Ϊ��׼��0��0��0��0��0��0���µĻ�������
	double m_R1_R2[3][3];												//��Ӱ�������Ӱ�����ת����

	float m_nLImgHeight_2, m_nLImgWidth_2;							//��Ӱ��߿�һ��
	float m_nRImgHeight_2, m_nRImgWidth_2;							//��Ӱ��߿�һ��
	
	
public:
	
	//ԭʼӰ����Ϣ
	int m_nLImgHeight, m_nLImgWidth, m_nLImgChannelNum;	//��Ӱ��ߡ���������
	double m_nLImgXs, m_nLImgYs, m_nLImgZs, m_nLImgPhi, m_nLImgOmega, m_nLImgKappa;//��Ӱ���ⷽλԪ��
	float m_nLImgf, m_nLImgx0, m_nLImgy0, m_nLImgPixelSize;			//��Ӱ���������
	double m_nLImgk1, m_nLImgk2, m_nLImgp1, m_nLImgp2;				//��Ӱ��������

	int m_nRImgHeight, m_nRImgWidth, m_nRImgChannelNum;			//��Ӱ��ߡ���������
	double m_nRImgXs, m_nRImgYs, m_nRImgZs, m_nRImgPhi, m_nRImgOmega, m_nRImgKappa;		//��Ӱ���ⷽλԪ��
	float m_nRImgf, m_nRImgx0, m_nRImgy0, m_nRImgPixelSize;			//��Ӱ���������
	double m_nRImgk1, m_nRImgk2, m_nRImgp1, m_nRImgp2;				//��Ӱ��������


	//������Ϣ
	int m_nLEntireEplImgFromX, m_nLEntireEplImgFromY;				//��Ӱ�����Ӱ��ȫ������
	int m_nLEntireEplImgToX, m_nLEntireEplImgToY;
	int m_nLEntireEplImgHeight, m_nLEntireEplImgWidth;	
	int m_nREntireEplImgFromX, m_nREntireEplImgFromY, m_nREntireEplImgToX, m_nREntireEplImgToY;	//��Ӱ�����Ӱ��ȫ������
	int m_nREntireEplImgHeight, m_nREntireEplImgWidth;	
	
	unsigned char* m_pLEplImgBits;							//��Ҫ���������Ӱ��
	int m_nLEplImgHeight, m_nLEplImgWidth, m_nLEplImgChannelNum;  //��Ҫ���������Ӱ��ߡ���������
	int m_nLEplImgFromX, m_nLEplImgFromY;						//��Ҫ���������Ӱ����ʼ���кţ�ԭ��λ�ò��䣩
	int m_nLEplImgToX, m_nLEplImgToY;							//��Ҫ���������Ӱ����ֹ���кţ�ԭ��λ�ò��䣩

	unsigned char* m_pREplImgBits;							//��Ҫ�����Һ���Ӱ��
	int m_nREplImgHeight, m_nREplImgWidth, m_nREplImgChannelNum;	//��Ҫ������Ӱ��ߡ���������
	int m_nREplImgFromX, m_nREplImgFromY;						//��Ҫ�����Һ���Ӱ����ʼ���кţ�ԭ��λ�ò��䣩
	int m_nREplImgToX, m_nREplImgToY;							//��Ҫ�����Һ���Ӱ����ֹ���кţ�ԭ��λ�ò��䣩
	int m_nOverlapFlag;	

#endif
};

#endif