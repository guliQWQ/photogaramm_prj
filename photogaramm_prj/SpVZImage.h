// SpVZImage.h : main header file for the SPVZIMAGE DLL
/*----------------------------------------------------------------------+
|     SpVZImage                                                         |
|       Author:     DuanYanSong  2005/03/01                             |
|            Ver 1.0                                                    |
|       Copyright (c) 2005, Supresoft Corporation                       |
|          All rights reserved.                                         |
|       http://www.supresoft.com.cn                                     |
|     ysduan@supresoft.com.cn;ysduan@163.net                            |
+----------------------------------------------------------------------*/

#ifndef SPVZIMAGE_H_DUANYANSONG_2005_03_01_15_01_19451
#define SPVZIMAGE_H_DUANYANSONG_2005_03_01_15_01_19451
#include"windows.h"
//typedef bool BOOL;
//typedef unsigned char BYTE;
//typedef true TRUE;
//typedef false FALSE;
// 读写影像文件的函数库
// 此库提供读写影像的类型包括: BMP,TIF,JPG,ORL,VZ,LEI,BBI,BIL,NTF,DEM 影像
// 读影像分两步:
// 1. 先使用函数 ReadImgHdr 读影像文件的头.
//    得到影像的信息,包括: 行数,列数,颜色数
//    如果是正射影像(orl格式和tifw格式)影像头信息还包括
//    影像左下角点的地理坐标X0,Y0 以及像元地面分解率gsd和影像旋转角度kap
// 2. 根据影像头信息分配内存,然后使用函数 ReadImgDat 
//    读取影像的数据到分配好的内存中.
//
//  写影像就直接调用函数 SaveImg 一步完成,写影像的时候传入参数包括
//  影像文件名,影像数据的内存地址,影像行数,列数,颜色数

/* 例子程序: 读影像 "d:\test.bmp" ,保存为 "d:\test.jpg"
  
  int cols,rows,color; unsigned char *pImg; 
  ReadImgHdr("d:\\test.bmp",&cols,&rows,&color);
  pImg  = (unsigned char *)malloc( cols*rows*color );  
  ReadImgDat( "d:\\test.bmp",pImg );
  SaveImg( "d:\\test.jpg",pImg,cols,rows,color );

*/

//读影像文件头的函数 
// 参数说明: 
// strImgName ,影像的文件名
// cols,rows,color 分别是影像的列数,行数,颜色数(3:彩色1:灰度)
// x0,y0,gsd,kap   分别是影像的左下角点地理坐标x0,y0,像元地面分解率gsd和影像旋转角度
inline static BOOL    ReadImgHdr( const char *strImgName,int *cols,int *rows,int *color );

//读影像文件影像块数据的函数
// 参数说明: 
// strImgName ,影像的文件名 
// pImg       ,分配好的内存地址
// startCol     ,影像块的起始列
// startRow     ,影像块的起始行
// cols         ,影像块的列数
// rows         ,影像块的行数
// color      ,影像块的色彩，1 是灰度，3 是 RGB
// flipL2R    ,是否将影像进行左右翻转
inline static BOOL    ReadImgDat( const char *strImgName,unsigned char *pImg,
                                    int startCol,int startRow,int cols,int rows,int color=1,BOOL flipL2R=0 );

inline static BOOL    ReadAllImgInGray( const char *strImgName, unsigned char **pImg,int *cols,int *rows );

//写影像文件的函数
// 参数说明: 
// strImgName ,影像的文件名
// pImg       ,影像数据
// cols,rows,color 分别是影像的列数,行数,颜色数(3:RGB 1:灰度)
inline static BOOL    SaveImg( const char *strImgName,unsigned char *pImg,int cols,int rows,int color,bool bBGR=false );


// 读写 SPT 文件内容
inline static BOOL ReadSptFile(LPCSTR lpstrPathName,int *sptHdr_rows  ,int *sptHdr_cols    ,double *sptHdr_resolution,
                               char*  sptHdr_camera,short *sptHdr_type,short *sptHdr_colour,int *sptHdr_cameraReverse,
                               int *RotFlag,int *zoomX,int *zoomY );
inline static BOOL WriteSptFile(LPCSTR lpstrPathName,int sptHdr_rows  ,int sptHdr_cols    ,double sptHdr_resolution,
                                LPCSTR sptHdr_camera,short sptHdr_type,short sptHdr_colour,int sptHdr_cameraReverse,
                                int RotFlag,int zoomX,int zoomY );

// 读写 IOP 文件内容
inline static BOOL WriteIopFile(LPCSTR lpstrPathName,int sptHdr_rows,int sptHdr_cols,double *iop=NULL );
inline static BOOL ReadIopFile(LPCSTR lpstrPathName,int sptHdr_rows,int sptHdr_cols,double *iop=NULL );

inline static void Left2Right( BYTE *pBuf,int cols,int pxlByte );
inline static BOOL Rot180( BYTE *pBuf,int cols,int rows,int pxsz );
inline static BOOL Rot90( BYTE *pBuf,int colsS,int rowsS,int pxlBytes  );
inline static BOOL Rot270( BYTE *pBuf,int colsS,int rowsS,int pxlBytes  );

/////////////////////////////////////////////////////////////////////
// Read/Write GeoInf for OrthoImage Function 
/////////////////////////////////////////////////////////////////////
/*
A TFW file normally contains the following information:
Line Number Sample Value Meaning 
Line 1 +6.00 Cell size in the X direction 
Line 2 -0.00 Rotation in the X direction 
Line 3 -0.00 Rotation in the Y direction 
Line 4 -6.00 Cell size in the Y direction 
Line 5 1709053.00 Easting value of insertion point X 
Line 6 807714.00 Northing value of insertion point Y 
Note that sign of the cell size in Y (line 4) defines 
if the image insertion point is the upper left or lower left corner.
A positive means the "Y" values are increasing upwards and therefore, 
the registration must be starting at the bottom or lower left corner. 
A negative sign means that the insertion point is the upper left. 
The insertion point coordinates relate to the map corner of the image 
in its defined projection itself.
*/
inline static BOOL GetGeo4Tif(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY=NULL,BOOL bCornrInTif=FALSE,LPCSTR strExt=".tfw" );
inline static BOOL SetGeo2Tif(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY=0,BOOL bCornrInTif=TRUE,LPCSTR strExt=".tfw",int cols=0,int rows=0 );
inline static BOOL GetGeo4Orl(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY=NULL );
inline static BOOL SetGeo2Orl(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY=0,int cols=0,int rows=0 );
inline static BOOL GetGeo4Lei(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY=NULL );
inline static BOOL SetGeo2Lei(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY=0,int cols=0,int rows=0 );
inline static BOOL GetGeo4Bbi(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY=NULL);
inline static BOOL SetGeo2Bbi(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY=0,int cols=0,int rows=0,int blkSz=256);
inline static BOOL GetGeo4Dem(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY=NULL);
inline static BOOL SetGeo2Dem(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY=0);
inline static BOOL GetGeo4Jpg(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY=NULL,BOOL bCornrInTif=TRUE );
inline static BOOL SetGeo2Jpg(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY=0,BOOL bCornrInTif=TRUE,int cols=0,int rows=0 );
inline static BOOL GetGeo4Bmp(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY=NULL,BOOL bCornrInTif=TRUE );
inline static BOOL SetGeo2Bmp(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY=0,BOOL bCornrInTif=TRUE,int cols=0,int rows=0 );
inline static BOOL GetGeo4Img(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY=NULL );
inline static BOOL SetGeo2Img(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY=0,int cols=0,int rows=0 );
inline static BOOL GetGeo4Ecw(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY=NULL );
inline static BOOL SetGeo2Ecw(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY=0,int cols=0,int rows=0 );
inline static BOOL GetRot180(LPCSTR lpstrPathName);
inline static BOOL SetRot180(LPCSTR lpstrPathName,BOOL bR180=TRUE);


#ifndef SPVZIMAGE_LIB

    #define SPVZIMAGE_LIB  __declspec(dllimport)

/*#ifdef _X64*/
// 	#ifdef _DEBUG_SPVZIMAGE
// 	#pragma comment(lib,"SpVZImage64D.lib") 
// 	#pragma message("Automatically linking with SpVZImage64D.lib") 
// 	#else
	#pragma comment(lib,"SpVZImage64.lib") 
	#pragma message("Automatically linking with SpVZImage64.lib") //
//	#endif
// #else
// 	#ifdef _DEBUG_SPVZIMAGE
//     #pragma comment(lib,"SpVZImageD.lib") 
//     #pragma message("Automatically linking with SpVZImageD.lib") 
//     #else
//     #pragma comment(lib,"SpVZImage.lib") 
//     #pragma message("Automatically linking with SpVZImage.lib") 
//     #endif
//#endif
 
#else

#endif

#define MB  1024*1024
//!影像文件读写接口(启点左下的Raw方式)
/**
影像文件读写接口(启点左下的Raw方式)
此接口定义的是对影像文件的Raw方式访问，也就是说当影像文件使用此接口访问
获取的数据都是符合Raw方式，即：左下为（0,0）， 按行得到数据，并且影像象素占用字节为 1(灰度) 或者 3(RGB) 。
*/
class SPVZIMAGE_LIB CSpVZImage
{
public:
    CSpVZImage();
    virtual ~CSpVZImage();

    virtual CSpVZImage*        Clone(){ CSpVZImage *p = new CSpVZImage; p->Copy(this); return p; };
    virtual void            Copy( CSpVZImage* p){ memcpy( this,p,sizeof(CSpVZImage) ); };
    virtual void            Reset(){ Close(); };
    virtual bool            Init(){ return true; };    

    //! 文件访问模式
    enum OPENFLAGS { modeRead= 0x0000,modeCreate = 0x1000 };

    //!打开影像
    /**
    @param    lpstrPathName    LPCSTR lpstrPathName，文件名
    @param    flag            OpenFlags flag,打开模式 @see OpenFlags
    @param  maxBufSize        int maxBufSize,可以使用内存的最大值，-1为自动检测，如果影像小于此值时整个影像被读入内存。
    @return   成功TRUE,失败 FALSE;
    */
    virtual BOOL        Open ( LPCSTR lpstrPathName,UINT flag=modeRead,int maxBufSize=-1,CSpVZImage *pImgAcs=NULL );
    //!关闭影像
    virtual void        Close();
    
    //!读影像行
    /**
    *@param  pBuf    BYTE *pBuf ，读回的影像行地址，注意此空间必须大于等于影像行大小
    *@param  rowIdx  int rowIdx ，影像行号(Base 0)
    *@return 成功TRUE,失败 FALSE;
    */
    virtual BOOL        Read ( BYTE *pBuf,int rowIdx ){
        if ( !m_pImgAcs ) return FALSE;
        if ( BYTE(m_strPathName[254])==180 ){
            if ( !m_pImgAcs->Read(pBuf,m_nRows-1-rowIdx) ) return FALSE;
            Left2Right( pBuf,m_nCols,m_nPixelBytes );
            return TRUE;
        }else
            return m_pImgAcs->Read(pBuf,rowIdx);
    };
    
    //!写影像行
    /**
    *@param  pBuf    BYTE *pBuf ，写影像行地址，注意此空间必须大于等于影像行大小
    *@param  rowIdx  int rowIdx ，影像行号(Base 0)
    *@return 成功TRUE,失败 FALSE;
    */
    virtual BOOL        Write( BYTE *pBuf,int rowIdx ){
        return m_pImgAcs?m_pImgAcs->Write(pBuf,rowIdx):FALSE;
    };
    //!读影像块
    /**
    @param    pBuf        LPVOID pBuf     ，影像数据存放内存块
    @param  pxlBytes    int pxlBytes ，低16Bits为影像数据的每像素占的 BYTE , 可以取值: 1 或者 3，
                                       高16Bits为影像缩小的倍数*1000，如缩小1倍数据为0.5*10000(即：5000), 缩小2倍数据为0.25*10000(即：2500) 等等
                                       高低位数据组合使用方法：MAKELONG( pixelBytes,zoomRate*10000 )
    @param  sRow        int sRow ，影象区域起始行
    @param  sCol        int sCol ，影象区域起始列
    @param  rows        int rows ，影象区域行数
    @param  cols        int cols ，影象区域列数
    @return    成功TRUE,失败 FALSE;
    */
    virtual BOOL        Read ( BYTE* pBuf,int pxlBytes,int sRow,int sCol,int rows,int cols )
                        {
                            if ( !m_pImgAcs || m_openFlags!=modeRead ) return FALSE;
                            BOOL bRot180 = (BYTE(m_strPathName[254])==180)?TRUE:FALSE;
                            BOOL ret = bRot180?FALSE:m_pImgAcs->Read(pBuf,pxlBytes,sRow,sCol,rows,cols);
                            if ( !ret ){
                                
                                int pxlBytes0  = LOWORD(pxlBytes);  ret = TRUE;
                                if ( HIWORD(pxlBytes)==0 || HIWORD(pxlBytes)==10000 ){
                                    int be_row,be_col,ed_row,ed_col,col0=cols;    
                                    be_row=sRow; ed_row = rows + be_row; 
                                    be_col=sCol; ed_col = cols + be_col; 
                                    memset( pBuf, 0, rows*cols*pxlBytes0 );
                                    if ( be_row > m_nRows || be_col > m_nCols || ed_row < 0 || ed_col < 0 ) return FALSE;
                                    
                                    BYTE *pRowBuf = new BYTE[m_nCols*m_nPixelBytes +8];
                                    if ( be_row<0 || be_col<0 || ed_row>m_nRows || ed_col>m_nCols )
                                    {
                                        if (be_row < 0)       { pBuf -= (be_row*cols)*pxlBytes0; rows += be_row; be_row = 0; }
                                        if (be_col < 0)       { pBuf -= (be_col)*pxlBytes0;      cols += be_col; be_col = 0; }
                                        if (ed_row > m_nRows) { rows = m_nRows - be_row; }
                                        if (ed_col > m_nCols) { cols = m_nCols - be_col; }
                                    }
                                    if ( pxlBytes0==m_nPixelBytes || (pxlBytes0>1&&pxlBytes0<m_nPixelBytes) ){
                                        for ( int r=0;r<rows; r++ ){
                                            Read( pRowBuf,be_row+r );
                                            BYTE *pS = pRowBuf+be_col*m_nPixelBytes;
                                            BYTE *pD = pBuf;
                                            if ( pxlBytes0==m_nPixelBytes ) memcpy( pD,pS,cols*pxlBytes0 );                                                
                                            else{ for ( int c=0;c<cols;c++,pD+=pxlBytes0,pS+=m_nPixelBytes ) memcpy( pD,pS,pxlBytes0 ); }
                                            pBuf  += col0*pxlBytes0;                                              
                                        }
                                    }else
                                    if ( pxlBytes0==1 && m_nPixelBytes>=3 ){
                                        for ( int r=0;r<rows; r++ ){
                                            Read( pRowBuf,be_row+r );
                                            BYTE *pS = pRowBuf+be_col*m_nPixelBytes;
                                            for ( int c=0;c<cols;c++,pS+=m_nPixelBytes ){                                                
                                                pBuf[c] = (*pS + *(pS+1) + *(pS+2))/3;
                                            }
                                            pBuf += col0*pxlBytes0;                
                                        }
                                    }else
                                    if ( pxlBytes0>m_nPixelBytes ){
                                        for ( int r=0;r<rows; r++ ){
                                            Read( pRowBuf,be_row+r );
                                            BYTE *pS = pRowBuf+be_col*m_nPixelBytes;
                                            BYTE *pD = pBuf;

                                            if ( pxlBytes0==3 )  for ( int c=0;c<cols;c++,pD+=pxlBytes0,pS+=m_nPixelBytes ) *pD = *(pD+1) = *(pD+2) = *pS;
                                            else                 for ( int c=0;c<cols;c++,pD+=pxlBytes0,pS+=m_nPixelBytes ) memcpy( pD,pS,m_nPixelBytes );
                                            
                                            pBuf  += col0*pxlBytes0;                                              
                                        }
                                    }else                                        
                                        ret=FALSE;
                                    delete pRowBuf;
                                }else
                                {
                                    BYTE *pBufRow = new BYTE[ m_nCols*m_nPixelBytes ];
                                    int rS,cS,widthS=m_nCols,heightS=m_nRows,pxbS=m_nPixelBytes;                            
                                    float zoomRate = (HIWORD(pxlBytes)/10000.f);
                                    float x0 = sCol+0.5f,y0 = sRow+0.5f;
                                    BYTE *pRowBufD = pBuf; float tmp=0;
                                    for ( int r=0;r<rows;r++ )
                                    {
                                        tmp = (y0+ r)/zoomRate; rS = int( tmp>=-0.5?tmp+0.5:-1 );
                                        if ( rS>=0 && rS<heightS )
                                        {
                                            Read( pBufRow,rS );
                                            const BYTE*   pRowBufS = pBufRow;
                                            for ( int c=0;c<cols;c++ )
                                            {
                                                tmp = (x0+c)/zoomRate; cS = int( tmp>=-0.5?tmp+0.5:-1 );

                                                if ( cS>=0 && cS<widthS )
                                                {
                                                    BYTE *pD = pRowBufD+c*pxlBytes0; const BYTE *pS = pRowBufS+cS*pxbS;
                                                    if ( pxbS==1 && pxlBytes0==1 ){
                                                        *pD = *pS; 
                                                    }else
                                                    if ( pxbS==1 && pxlBytes0==3 ){
                                                        *pD = *(pD+1)= *(pD+2) = *pS;
                                                    }else 
                                                    if ( pxbS==3 && pxlBytes0==1 )
                                                    {
                                                        *pD = (*pS + *(pS+1) + *(pS+2))/3;
                                                    }else
                                                    if ( pxbS==3 && pxlBytes0==3 )
                                                    {
                                                        *pD = *pS; *( (WORD*)(pD+1) )= *((WORD*)(pS+1)); 
                                                    }
                                                }else
                                                    *((DWORD*)(pRowBufD+c*pxlBytes0))=0;
                                            }                                            
                                        }else 
                                            memset( pRowBufD,0,cols*pxlBytes0 );
                                        
                                        pRowBufD += (cols*pxlBytes0);
                                    }
                                    delete pBufRow;                                   
                                }
                            }
                            return (m_pImgAcs!=NULL); 
                        };
    
    //!获取影像像素字节数
    /**
    *@return 影像像素字节数 1（一般为灰度） 或 3（RGB彩色）
    */
    inline const  int GetPixelBytes(){ return m_nPixelBytes; };
    //!获取影像行数
    /**
    *@return 影像行数
    */
    inline const  int GetRows(){ return m_nRows; };
    //!获取影像列数
    /**
    *@return 影像列数 
    */
    inline const int GetCols(){ return m_nCols; };
    //!获取颜色表
    /**
    @param    int &size 颜色表长度。
    @return    RGBQUAD*颜色表。
    */
    inline const RGBQUAD* GetColorTable(int &size ){ size=m_nColorTab; return m_pColorTab; };

    //!设定颜色表
    /**
    设定影像颜色表，只有新建影像时此函数才可以使用,而且影像有索引时才可以设定颜色表。
    @param    pQuad RGBQUAD* pQuad 颜色表。
    @param  size int  size 颜色表长
    @return    无
    */
    inline void SetColorTable(RGBQUAD* pQuad, int  size){ m_nColorTab=size>256?256:size; memcpy(m_pColorTab,pQuad,sizeof(RGBQUAD)*m_nColorTab); if(m_pImgAcs)m_pImgAcs->SetColorTable(pQuad,size); UpdateImgBuf(); };
    //!设定影像行数
    /**
    设定影像行数，只有新建影像时此函数才可以使用
    *@param  int nRows:影像行数
    *@return 无
    */
    inline void SetRows(int nRows){ m_nRows=nRows; if(m_pImgAcs)m_pImgAcs->SetRows(nRows); UpdateImgBuf(); };
    //!设定影像列数
    /**
    设定影像列数，只有新建影像时此函数才可以使用
    *@param  int nCols:影像列数
    *@return 无
    */
    inline void SetCols(int nCols){ m_nCols=nCols; if(m_pImgAcs)m_pImgAcs->SetCols(nCols); UpdateImgBuf(); }; 
    //!设定像素字节数
    /**
    设定像素字节数，只有新建影像时此函数才可以使用
    *@param  int nPixelSize 像素字节数
    *@return 无
    */
    inline void SetPixelBytes(int nPixelBytes){ m_nPixelBytes=nPixelBytes;if(m_pImgAcs)m_pImgAcs->SetPixelBytes(nPixelBytes); UpdateImgBuf(); };

protected:
    //!更新影像的Buffer
    /**
    设定影像属性后更新影像的Buffer,此函数是针对新建影像使用的。
    */
    virtual void UpdateImgBuf(){};

protected:
    int             m_nRows,m_nCols,m_nPixelBytes,m_nColorTab;
    RGBQUAD            m_pColorTab[256];

    //!影像文件打开方式
    UINT            m_openFlags;
    //!影像类型
    UINT            m_imgType;
    //!接口实例
    CSpVZImage*     m_pImgAcs;
    //!影像文件路径
    char            m_strPathName[256];

private:
    //!内部实现的接口实例
    CSpVZImage*    m_pImgAcs0; 

public:
    enum OUTMSG{
         PROG_MSG   =   10,
         PROG_START =   11,
         PROG_STEP  =   12,
         PROG_OVER  =   13,
    };
    void         SetRevMsgWnd( HWND hWnd,UINT msgID ){   m_hWndRec=hWnd; m_msgID=msgID; if(m_pImgAcs)m_pImgAcs->SetRevMsgWnd(m_hWndRec,m_msgID); };
protected:
    virtual void ProgBegin(int range)       {if ( ::IsWindow(m_hWndRec) )::SendMessage( m_hWndRec,m_msgID,PROG_START,range );          };
    virtual void ProgStep(int& cancel)      {if ( ::IsWindow(m_hWndRec) )::SendMessage( m_hWndRec,m_msgID,PROG_STEP ,LONG(&cancel) );  };
    virtual void ProgEnd()                  {if ( ::IsWindow(m_hWndRec) )::SendMessage( m_hWndRec,m_msgID,PROG_OVER ,0 );              };
    virtual void PrintMsg(LPCSTR lpstrMsg ) {if ( ::IsWindow(m_hWndRec) )::SendMessage( m_hWndRec,m_msgID,PROG_MSG  ,UINT(lpstrMsg) ); };
private:
    HWND            m_hWndRec;
    UINT            m_msgID;    
};

#ifndef _RGB2BGR_ASM
#define _RGB2BGR_ASM

#define     BGR2RGB     RGB2BGR 
static inline void RGB2BGR( BYTE *pBuf,int cols)
{
   if ( cols<=0 ) return;
#ifdef _X64
	BYTE t,*pRGB = pBuf; int i;
	for( i=0;i<cols;i++,pRGB+=3 ){ t = *pRGB; *pRGB = *(pRGB+2); *(pRGB+2) = t; }
#else
//    cols = cols -1; // exclude last pixel for memory crash .
//    _asm{
//         mov esi,pBuf
//         mov edx,cols
// _loop:
//         dec edx
//         mov eax, dword ptr[esi]
//         mov ebx, eax 
//         and ebx, 0FFh
//         mov ecx, eax 
//         and ecx, 0FF0000h
//         shl ebx, 10h
//         shr ecx, 10h
//         and eax, 0FF00FF00h
//         or  eax, ebx
//         or  eax, ecx
//         mov dword ptr[esi], eax
//         inc esi
//         inc esi
//         inc esi
//         cmp edx, 0h
//         jne _loop
//    }
   // patch process the last pixel
   BYTE t,*pRGB = pBuf+cols*3;
   t=pRGB[0]; pRGB[0]=pRGB[2]; pRGB[2]=t;
#endif
};
#endif

#ifndef _BND2RGB
#define _BND2RGB
static inline void Bnd2RGB(BYTE *pBuf,int cols,int band)
{
    if (cols<=0||band<=3) return;
#ifdef _X64
	BYTE t,*pRGB = pBuf; int i;
	for( i=0;i<cols;i++,pRGB+=3,pBuf+=band ){ *((WORD*)pRGB)=*((WORD*)pBuf); *(pRGB+2)=*(pBuf+2); }
#else
//     _asm{
//         mov edi,pBuf
//         mov esi,pBuf
//         mov edx,cols
// _loop:
//         dec edx
//         mov eax, dword ptr[esi]        
//         mov byte ptr[edi],al
//         shr eax, 08h
//         inc edi
//         mov word ptr[edi],ax
//         add esi,band
//         inc edi
//         inc edi
//         cmp edx, 0h
//         jne _loop
//   }
#endif
}
#endif

#ifndef _GETBIPXL
#define _GETBIPXL
static inline BYTE* GetBiPixel( float fx,float fy,int cols,int rows,int pxlBytes,BYTE *pBuf,UINT bkGrd=0xFFFFFFFF )
{
    static DWORD buf0=0; BYTE *buf=(BYTE*)&buf0;
    int r1,r2,r3,r4,col = int(fx),row=int(fy);
    if ( col<0||row<0||col>=cols-1 || row>=rows-1 ){ buf0=bkGrd; return buf; }
    
    float dx = fx-col,dy = fy-row; 
    BYTE *p,*p0 = pBuf+(row*cols+col)*pxlBytes; 
    if ( dx<0.05f && dy<0.05f ) return p0;
    p= p0 +0; r1 =*p ; r2 = *(p+pxlBytes); p += cols*pxlBytes; r3 =*p; r4 = *(p+pxlBytes);
    buf[0] = BYTE( (1-dx)*(1-dy)*r1+dx*(1-dy)*r2+(1-dx)*dy*r3+dx*dy*r4 );
    if ( pxlBytes==3 ){
        p= p0 +1; r1 =*p ; r2 = *(p+pxlBytes); p += cols*pxlBytes; r3 =*p; r4 = *(p+pxlBytes);
        buf[1] = BYTE( (1-dx)*(1-dy)*r1+dx*(1-dy)*r2+(1-dx)*dy*r3+dx*dy*r4 );
        p= p0 +2; r1 =*p ; r2 = *(p+pxlBytes); p += cols*pxlBytes; r3 =*p; r4 = *(p+pxlBytes);
        buf[2] = BYTE( (1-dx)*(1-dy)*r1+dx*(1-dy)*r2+(1-dx)*dy*r3+dx*dy*r4 );
    }
    return buf;
}
#endif

#ifndef _AUTOLEVEL
#define _AUTOLEVEL
#define AutoLevel Auto_Level
static inline void Auto_Level( BYTE *pImg,int cols,int rows ){
    int i,sum,minI,maxI,minSum,maxSum;
    BYTE *pS; UINT pTab[256];
    memset( pTab,0,sizeof(UINT)*256 ); sum=cols*rows;
    for ( pS=pImg,i=0;i<sum;i++,pS++ ) pTab[*pS]++;
    minSum=int( sum*0.005f );  if (minSum<10) minSum = 10;
    maxSum=int( sum*0.005f );  if (maxSum<10) maxSum = 10;                            
    for ( sum=0,minI=2;minI<254;minI++ ){ sum+=pTab[minI]; if (sum>minSum) break; }
    for ( sum=0,maxI=254;maxI>2;maxI-- ){ sum+=pTab[maxI]; if (sum>maxSum) break; }
    if ( (maxI-minI)<200 ){
        //cprintf("AutoLevel: %d >>>> %d\n",minI,maxI );
        for ( i=0;i<minI;i++ ) pTab[i]=0;
        for ( i=minI;i<maxI;i++ ) pTab[i] = 1+int( (i-minI)*254.f/(maxI-minI) );
        for( ;i<256;i++ ) pTab[i] = 255;
        sum=cols*rows;
        for ( pS=pImg,i=0;i<sum;i++,pS++ ) *pS = pTab[*pS];
    }
}
static inline  void Auto_Level( BYTE *pImg,int cols,int rows,int pxbs ){
    if (pxbs==1) Auto_Level(pImg,cols,rows);
    else{
        int i,sum,minI,maxI,minSum,maxSum;
        BYTE *pS; UINT pTab[256];
        memset( pTab,0,sizeof(UINT)*256 ); sum=cols*rows;
        for ( pS=pImg,i=0;i<sum*pxbs;i++,pS++ ) pTab[*pS]++;
        minSum=int( sum*0.0001f );  if (minSum<5) minSum = 5;
        maxSum=int( sum*0.0001f );  if (maxSum<5) maxSum = 5;                            
        for ( sum=0,minI=2;minI<254;minI++ ){ sum+=pTab[minI]; if (sum>minSum) break; }
        for ( sum=0,maxI=254;maxI>2;maxI-- ){ sum+=pTab[maxI]; if (sum>maxSum) break; }
        if ( (maxI-minI)<200 ){
            for ( i=0;i<minI;i++ ) pTab[i]=0;
            for ( i=minI;i<maxI;i++ ) pTab[i] = int( (i-minI)*(254.f/(maxI-minI)) );
            for ( ;i<256;i++ ) pTab[i] = 254;
            sum=cols*rows; for ( pS=pImg,i=0;i<sum*pxbs;i++,pS++ ) *pS = pTab[*pS];
        }        
    }
}
#endif

#ifndef _LEFT2RIGHTG
#define _LEFT2RIGHTG
inline static void Left2RighG(BYTE *pBufL,BYTE *pBufR,int cols_2)
{
    if ( cols_2<=0 ) return ; 
#ifdef _X64
	int i; BYTE t;
	for( i=0;i<cols_2;i++,pBufL++,pBufR-- ){ t = *pBufL; *pBufL = *pBufR; *pBufR = t; }	
#else
// 	_asm{
//         mov edi,pBufL
//         mov esi,pBufR        
//         mov ecx,cols_2  
// _loop:
//         dec ecx
//         mov al,byte ptr[edi]
//         mov bl,byte ptr[esi]
//         mov byte ptr[edi],bl
//         mov byte ptr[esi],al
//         inc edi
//         dec esi
//         cmp ecx, 0h
//         jne _loop
//     }
#endif
}
inline static void Left2Righ2(BYTE *pBufL,BYTE *pBufR,int cols_2)
{
    if ( cols_2<=0 ) return ;

#ifdef _X64
	int i; WORD t,*pS=(WORD*)pBufL,*pE=(WORD*)pBufR;
	for( i=0;i<cols_2;i++,pS++,pE-- ){ t = *pS; *pS = *pE; *pE = t; }	
#else
//     _asm{
//         mov edi,pBufL
//         mov esi,pBufR        
//         mov ecx,cols_2  
// _loop:
//         dec ecx
//         mov ax,short ptr[edi]
//         mov bx,short ptr[esi]
//         mov short ptr[edi],bx
//         mov short ptr[esi],ax
//         add edi,2h
//         sub esi,2h
//         cmp ecx, 0h
//         jne _loop
//     }
#endif
}
inline static void Left2Righ3(BYTE *pBufL,BYTE *pBufR,int cols_2)
{
    if ( cols_2<=0 ) return ;

#ifdef _X64
	int i; BYTE tB; WORD tW;
	for( i=0;i<cols_2;i++,pBufL+=3,pBufR-=3 ){ 
		tW = *((WORD*)pBufL); *((WORD*)pBufL) = *((WORD*)pBufR); *((WORD*)pBufR) = tW;
		tB = *(pBufL+2); *(pBufL+2) = *(pBufR+2); *(pBufR+2) = tB;
	}		
#else
//     _asm{
//         mov edi,pBufL
//         mov esi,pBufR        
//         mov ecx,cols_2  
// _loop:
//         dec ecx        
//         mov eax,int ptr[edi]
//         mov ebx,int ptr[esi]
//         mov byte ptr[edi],bl
//         mov byte ptr[esi],al
//         inc edi
//         inc esi
//         shr eax, 8h
//         shr ebx, 8h
//         mov short ptr[edi],bx
//         mov short ptr[esi],ax
//         add edi,2
//         sub esi,4        
//         cmp ecx, 0h
//         jne _loop
//     }
#endif
}
inline static void Left2Righ4(BYTE *pBufL,BYTE *pBufR,int cols_2)
{
    if ( cols_2<=0 ) return ;
#ifdef _X64
	int i; DWORD t,*pS=(DWORD*)pBufL,*pE=(DWORD*)pBufR;
	for( i=0;i<cols_2;i++,pS++,pE-- ){ t = *pS; *pS = *pE; *pE = t; }	
#else
//     _asm{
//         mov edi,pBufL
//         mov esi,pBufR        
//         mov ecx,cols_2  
// _loop:
//         dec ecx
//         mov eax,int ptr[edi]
//         mov ebx,int ptr[esi]
//         mov int ptr[edi],ebx
//         mov int ptr[esi],eax
//         add edi,4
//         sub esi,4
//         cmp ecx, 0h
//         jne _loop
//     }
#endif
}

inline static void CopyRGB( BYTE *pD,BYTE *pS ){ *(pD++)=*(pS++);*((WORD*)pD)=*((WORD*)pS); }
inline static void Left2Right( BYTE *pBuf,int cols,int pxlByte )
{
    BYTE rgb[32]; 
    if ( pxlByte==1 ){
        Left2RighG( pBuf,pBuf+cols-1,cols/2 );
    }else 
    if ( pxlByte==2 ){
        Left2Righ2( pBuf,pBuf+(cols-1)*pxlByte,cols/2 );        
    }else
    if ( pxlByte==3 ){
        Left2Righ3( pBuf,pBuf+(cols-1)*pxlByte,cols/2 );
    }else
    if ( pxlByte==4 ){
        Left2Righ4( pBuf,pBuf+(cols-1)*pxlByte,cols/2 );           
    }else
    if ( pxlByte==8 ){
        int i,cols_2=cols/2; LONGLONG *pS=(LONGLONG*)pBuf,*pD=(LONGLONG*)(pBuf+(cols-1)*pxlByte),tL;
        for ( i=0;i<cols_2;i++,pS++,pD-- ){ tL=*pS; *pS=*pD; *pD=tL; }
    }else{
        for ( int i=0;i<cols/2;i++ ){
            memcpy( rgb,pBuf+i*pxlByte,pxlByte );
            memcpy( pBuf+i*pxlByte,pBuf+(cols-1-i)*pxlByte,pxlByte );
            memcpy( pBuf+(cols-1-i)*pxlByte,rgb,pxlByte );
        }
    }
}
#endif

inline static BOOL Rot180( BYTE *pBuf,int cols,int rows,int pxsz )
{
    int rdLineBytes = cols*pxsz; if ( !pBuf||!cols||!rows||!pxsz ) return FALSE;
    BYTE *pWrite = pBuf,*pRead = pBuf+(rows-1)*rdLineBytes ;
    BYTE *pT = new BYTE[ rdLineBytes ];
    for ( int r=0;r<rows/2;r++,pWrite+=rdLineBytes,pRead-=rdLineBytes ){
        memcpy( pT,pWrite,rdLineBytes );
        memcpy( pWrite,pRead,rdLineBytes );
        memcpy( pRead,pT,rdLineBytes );
        Left2Right( pRead ,cols,pxsz );
        Left2Right( pWrite,cols,pxsz );
    }
    delete[] pT; return TRUE;
}

inline static BOOL Rot90( BYTE *pBuf,int colsS,int rowsS,int pxlBytes  )
{
    if ( !pBuf||!colsS||!rowsS||!pxlBytes ) return FALSE;
    int r,lineSize = colsS*pxlBytes,lnSzN=rowsS*pxlBytes;
    BYTE *pD,*pS,*pBufN = new BYTE[rowsS*colsS*pxlBytes +8];
    for ( r=0;r<colsS;r++,pBuf+=pxlBytes ){  
        pS = pBuf; pD = pBufN+(colsS-1-r)*lnSzN;        
        if ( pxlBytes==3 ){ for(int j=0;j<rowsS;j++,pD+=3,pS+=lineSize ){ *((WORD*)pD)=*((WORD*)pS);*(pD+2)=*(pS+2); } }
        else{ for(int j=0;j<rowsS;j++,pD++,pS+=lineSize ) *pD=*pS; }
    }
    pBuf -= colsS*pxlBytes; 
    memcpy( pBuf,pBufN,rowsS*colsS*pxlBytes );
    delete[] pBufN;  return TRUE;
}

inline static BOOL Rot270( BYTE *pBuf,int colsS,int rowsS,int pxlBytes  )
{
    if ( !pBuf||!colsS||!rowsS||!pxlBytes ) return FALSE;
    int r,lineSize = colsS*pxlBytes,lnSzN=rowsS*pxlBytes;
    BYTE *pD,*pS,*pBufN = new BYTE[rowsS*colsS*pxlBytes +8];
    for ( r=0;r<colsS;r++,pBuf+=pxlBytes){  
        pS = pBuf; pD = pBufN+(r+1)*lnSzN-pxlBytes;
        if ( pxlBytes==3 ){ for(int j=0;j<rowsS;j++,pD-=3,pS+=lineSize ){ *((WORD*)pD)=*((WORD*)pS);*(pD+2)=*(pS+2); } }
        else for(int j=0;j<rowsS;j++,pD--,pS+=lineSize ) *pD=*pS;
    }
    pBuf -= colsS*pxlBytes; 
    memcpy( pBuf,pBufN,rowsS*colsS*pxlBytes );
    delete[] pBufN;  return TRUE;
}

//////////////////////////////////////////////////////////////////
//
// 以下是函数的实现代码
//
//////////////////////////////////////////////////////////////////
inline static BOOL    ReadImgHdr( const char *strImgName,int *cols,int *rows,int *color )
{
    *cols=0; *rows=0; *color=0;
    CSpVZImage imgFile; if ( !imgFile.Open(strImgName) ) return FALSE;
    *cols = imgFile.GetCols(); *rows = imgFile.GetRows();  *color= imgFile.GetPixelBytes();
    return (*cols)*(*rows)*(*color)!=0;
}

inline static BOOL    ReadImgDat(const char *strImgName,unsigned char *pImg,
                                 int startCol,int startRow,int cols,int rows,int color,BOOL flipL2R )
{
    static CSpVZImage imgFile; static char strPN[512]=" ";
    if ( _stricmp( strPN,strImgName )!=0 ){ imgFile.Close(); strPN[0]=0; if ( !imgFile.Open(strImgName,CSpVZImage::modeRead,32*MB) ) return FALSE; strcpy(strPN,strImgName); }
    if ( flipL2R && color==1  ){
        imgFile.Read( pImg,color,startRow,startCol,rows,cols );
        Left2RighG( pImg,pImg+cols-1,cols/2 ); return TRUE;
    }else
        return imgFile.Read( pImg,color,startRow,startCol,rows,cols );    
}

inline static BOOL    ReadAllImgInGray( const char *strImgName, unsigned char **pImg,int *cols,int *rows )
{
    CSpVZImage imgFile;  *pImg=NULL; *cols=0; *rows=0;
    if ( !imgFile.Open(strImgName,CSpVZImage::modeRead,32*MB) ) return FALSE;
    *cols = imgFile.GetCols(); *rows = imgFile.GetRows();
    *pImg = new unsigned char[ (*cols)*(*rows) +8];
    if ( !imgFile.Read( *pImg,1,0,0,*rows,*cols ) ){ delete *pImg; *pImg=NULL; *cols=0; *rows=0; return FALSE; }
    return TRUE;
}

inline static BOOL    SaveImg( const char *strImgName,unsigned char *pImg,int cols,int rows,int color,bool bBGR )
{
    CSpVZImage imgFile; if ( !imgFile.Open( strImgName,CSpVZImage::modeCreate ) ) return FALSE;
    imgFile.SetCols(cols); imgFile.SetRows(rows); imgFile.SetPixelBytes(color);
    BYTE *pRow=new BYTE[ cols*color +8];
    for ( int i=0;i<rows;i++,pImg+=cols*color ){ 
        memcpy( pRow,pImg,cols*color ); if (color==3&&bBGR) RGB2BGR(pRow,cols);
        imgFile.Write( pRow,i );  
    }
    delete pRow; imgFile.Close();
    return TRUE;
}

inline static BOOL   CopyImg(const char *strSrc,const char *strDes)
{
    CSpVZImage imgFileS,imgFileD; 
    if ( !imgFileS.Open(strSrc) || !imgFileD.Open(strDes,CSpVZImage::modeCreate) ) return FALSE;
    int i,cols = imgFileS.GetCols(),rows=imgFileS.GetRows(),color=imgFileS.GetPixelBytes();
    imgFileD.SetCols(cols); imgFileD.SetRows(rows); imgFileD.SetPixelBytes(color);
    BYTE *pRow=new BYTE[ cols*color +8];
    for ( i=0;i<rows;i++ ){ 
        imgFileS.Read( pRow,i );
        imgFileD.Write( pRow,i );  
    }
    delete pRow; imgFileS.Close(); imgFileD.Close();
    return TRUE;
}

inline static BOOL ReadSptFile(LPCSTR lpstrPathName,int *sptHdr_rows  ,int *sptHdr_cols    ,double *sptHdr_resolution,
                               char*  sptHdr_camera,short *sptHdr_type,short *sptHdr_colour,int *sptHdr_cameraReverse,
                               int *RotFlag,int *zoomX,int *zoomY )
{
    FILE *fSpt = fopen( lpstrPathName,"rt" ); 
    if ( !fSpt ) return FALSE;
    char strLine[256];

    fgets( strLine,256,fSpt ); *sptHdr_rows =atoi(strLine);
    fgets( strLine,256,fSpt ); *sptHdr_cols =atoi(strLine);
    fgets( strLine,256,fSpt ); *sptHdr_resolution   =atof(strLine);
    fgets( sptHdr_camera,256,fSpt ); if ( sptHdr_camera[strlen(sptHdr_camera)-1]=='\n' ) sptHdr_camera[strlen(sptHdr_camera)-1]=0;
    fgets( strLine,256,fSpt ); *sptHdr_type            =atoi(strLine);
    fgets( strLine,256,fSpt ); *sptHdr_colour        =atoi(strLine);
    fgets( strLine,256,fSpt ); *sptHdr_cameraReverse=atoi(strLine);
    fgets( strLine,256,fSpt ); *RotFlag     = atoi(strLine);
    fgets( strLine,256,fSpt ); *zoomX       = (strlen(strLine)>2)?atoi(strLine):100; if(*zoomX==0) *zoomX=100;
    fgets( strLine,256,fSpt ); *zoomY       = (strlen(strLine)>2)?atoi(strLine):100; if(*zoomY==0) *zoomY=100;
    fclose( fSpt );

    return TRUE;
}

inline static BOOL WriteSptFile(LPCSTR lpstrPathName,int sptHdr_rows  ,int sptHdr_cols    ,double sptHdr_resolution,
                                LPCSTR sptHdr_camera,short sptHdr_type,short sptHdr_colour,int sptHdr_cameraReverse,
                                int RotFlag,int zoomX,int zoomY )
{
    FILE *fSpt = fopen( lpstrPathName,"wt" ); 
    if ( !fSpt ) return FALSE;
    fprintf( fSpt, "%d\n", sptHdr_rows );
    fprintf( fSpt, "%d\n", sptHdr_cols );
    fprintf( fSpt, "%.6lf\n",sptHdr_resolution );
    fprintf( fSpt, "%s\n", sptHdr_camera );
    fprintf( fSpt, "%d\n", sptHdr_type );
    fprintf( fSpt, "%d\n", sptHdr_colour );
    fprintf( fSpt, "%d\n", sptHdr_cameraReverse );
    fprintf( fSpt, "%d\n", RotFlag );
    fprintf( fSpt, "%d\n", zoomX );
    fprintf( fSpt, "%d\n", zoomY );
    fclose( fSpt );
    return TRUE;
}

inline static BOOL WriteIopFile(LPCSTR lpstrPathName,int sptHdr_rows,int sptHdr_cols,double *iop )
{
    FILE *fIop = fopen( lpstrPathName,"wt" );
    if ( fIop )
    {
        if ( iop )
        {
            double tt =iop[2]*iop[5] - iop[4]*iop[3];
            fprintf(fIop,"  %.6lf   %.6lf\n",iop[0],iop[1] );
            fprintf(fIop,"  0.000   0.000\n\n");
            fprintf(fIop,"  %.9lf   %.9lf\n",iop[2],iop[3]);
            fprintf(fIop,"  %.9lf   %.9lf\n\n",iop[4],iop[5]);
            fprintf(fIop,"  %.9lf   %.9lf\n",iop[5]/tt,iop[3]/tt);
            fprintf(fIop,"  %.9lf   %.9lf\n",iop[4]/tt,iop[2]/tt);
            fclose( fIop );
        }else
        {
            fprintf(fIop,"  %.6lf   %.6lf\n",sptHdr_rows/2,sptHdr_cols/2.0 );
            fprintf(fIop,"  0.000   0.000\n");
            fprintf(fIop,"  1.000   0.000\n");
            fprintf(fIop,"  0.000   1.000\n");
            fprintf(fIop,"  1.000   0.000\n");
            fprintf(fIop,"  0.000   1.000\n");
            fclose( fIop );
        }
    }
    return TRUE;
}

inline static BOOL ReadIopFile(LPCSTR lpstrPathName,int sptHdr_rows,int sptHdr_cols,double *iop )
{
    FILE *fIop = fopen( lpstrPathName,"rt" );
    if ( fIop )
    {
        double tt;
        fscanf( fIop,"%lf%lf",&iop[0],&iop[1] );
        fscanf( fIop,"%lf%lf",&tt,&tt );
        fscanf( fIop,"%lf%lf",&iop[2],&iop[3] );
        fscanf( fIop,"%lf%lf",&iop[4],&iop[5] );            
        fscanf( fIop,"%lf%lf",&iop[6],&iop[7] );
        fscanf( fIop,"%lf%lf",&iop[8],&iop[9] );        
        fclose( fIop );
        return TRUE;
    }
    return FALSE;
}


inline static DWORD  _SeekTif( HANDLE hFile, LONGLONG distance, DWORD MoveMethod ){
    LARGE_INTEGER li; li.QuadPart = distance;
    return ::SetFilePointer( hFile,li.LowPart,&li.HighPart,MoveMethod );    
};
inline static void  _ReadTifTag( HANDLE hFile,WORD &tagId,WORD &tagType,DWORD &tagSize,DWORD &tagVal ){
    DWORD rwByte=0;
    ::ReadFile( hFile,&tagId     ,2,&rwByte,NULL );
    ::ReadFile( hFile,&tagType   ,2,&rwByte,NULL );
    ::ReadFile( hFile,&tagSize   ,4,&rwByte,NULL );
    ::ReadFile( hFile,&tagVal    ,4,&rwByte,NULL );   
};

inline BOOL _GetGeo4Tif(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY)
{
    #define   _TIFFTAG_IMAGEWIDTH         256    // image width  in pixels 
    #define   _TIFFTAG_IMAGELENGTH        257    // image height in pixels 

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    // GeoTiff    
    #define TIFFTAG_GEOPIXELSCALE        33550    // double xyzScale[3]
    #define TIFFTAG_GEOTIEPOINTS         33922    // double tiePts[][6]
    #define TIFFTAG_GEOTRANSMATRIX       34264    // double matrix[16]
    #define TIFFTAG_GEOKEYDIRECTORY      34735    // short geoKey[][4]
    
    #define   GTModelTypeGeoKey           1024 
        typedef enum {
            ModelTypeProjected  = 1,  /* Projection Coordinate System */
            ModelTypeGeographic = 2,  /* Geographic latitude-longitude System */
            ModelTypeGeocentric = 3,  /* Geocentric (X,Y,Z) Coordinate System */
        }modeltype_t;    
    #define   GTRasterTypeGeoKey          1025
    #define         RasterPixelIsArea        1
    #define         RasterPixelIsPoint       2
    #define   GTCitationGeoKey            1026 // ascii information
    
    #define GeographicTypeGeoKey            2048
    #define GeogGeodeticDatumGeoKey           2050
    #define GeogPrimeMeridianGeoKey           2051
    #define GeogLinearUnitsGeoKey         2052
    #define GeogLinearUnitSizeGeoKey        2053
    #define GeogAngularUnitsGeoKey          2054
    #define GeogAngularUnitSizeGeoKey     2055
    #define GeogEllipsoidGeoKey               2056
    #define GeogSemiMajorAxisGeoKey           2057
    #define GeogSemiMinorAxisGeoKey           2058
    #define GeogPrimeMeridianLongGeoKey       2059
    
    #define ProjectedCSTypeGeoKey         3072
    #define ProjectionGeoKey                3074
    #define ProjCoordTransGeoKey            3075
    
    #define ProjFalseEastingGeoKey          3082  
    #define ProjFalseNorthingGeoKey           3083  
    #define ProjFalseOriginLongGeoKey     3084  
    #define ProjFalseOriginLatGeoKey        3085  
    #define ProjFalseOriginEastingGeoKey    3086  
    #define ProjFalseOriginNorthingGeoKey 3087  
    #define ProjCenterLongGeoKey            3088  
    #define ProjCenterLatGeoKey             3089  
    #define ProjCenterEastingGeoKey           3090  
    #define ProjCenterNorthingGeoKey        3091  
    #define ProjScaleAtNatOriginGeoKey      3092  
    #define ProjScaleAtCenterGeoKey           3093  
    
    #define TIFFTAG_GEODOUBLEPARAMS      34736
    #define TIFFTAG_GEOASCIIPARAMS       34737

    HANDLE hFile = ::CreateFile( lpstrPathName,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_FLAG_RANDOM_ACCESS,NULL ); 
    if ( !hFile || hFile==INVALID_HANDLE_VALUE ) return FALSE;

    DWORD rwByte; WORD wflag; DWORD lflag; LONGLONG offset; 
    wflag=0x4949; ::ReadFile( hFile,&wflag,2,&rwByte,NULL ); // 'II'
    if ( wflag != 0x4949 ){ ::CloseHandle( hFile ); return FALSE; }
    wflag=0x002A; ReadFile( hFile,&wflag,2,&rwByte,NULL ); // 42
    if ( wflag != 0x002A ){ ::CloseHandle( hFile ); return FALSE; }
    lflag=0x0008; ::ReadFile( hFile,&lflag,4,&rwByte,NULL ); // Offset
    offset = lflag; _SeekTif( hFile,offset,FILE_BEGIN );
    WORD tagSum = 0x000D; ::ReadFile( hFile,&tagSum,2,&rwByte,NULL ); // TagSum

    // geo inf
    double Ex=0,Ny=0,Dx=1,Dy=1,Rx=0,Ry=0; bool bCorner=false,bTfw=true;
    
    int imgCols=0,imgRows=0; DWORD DatOff;
    WORD tagId; WORD tagType; DWORD tagSize,tagVal; 
    for( WORD i=0;i<tagSum;i++ ){
        _SeekTif( hFile,offset+2+i*12,FILE_BEGIN );
        tagId=0; tagType=0; tagSize = 0; tagVal = 0;
        _ReadTifTag( hFile,tagId,tagType,tagSize,tagVal );
        switch( tagId ){
            case _TIFFTAG_IMAGEWIDTH:
                imgCols = tagVal;
                break;
            case _TIFFTAG_IMAGELENGTH:
                imgRows   = tagVal;
                break;
                            
            ///////////////////////////////////////////////////////////
            case TIFFTAG_GEOTRANSMATRIX:
                DatOff = tagVal;
                if ( tagSize>1 ){
                    double padfMatrix[16];
                    _SeekTif( hFile,DatOff,FILE_BEGIN );
                    ReadFile( hFile,padfMatrix,sizeof(padfMatrix),&rwByte,NULL ); 
                    Dx = padfMatrix[0];
                    Dy = padfMatrix[5];
                    Ex = padfMatrix[3];
                    Ny = padfMatrix[7];
                    bTfw = false;
                }
                break;
            case TIFFTAG_GEOPIXELSCALE:
                DatOff = tagVal;
                if ( tagSize>1 ){
                    double pxlScale[3];
                    _SeekTif( hFile,DatOff,FILE_BEGIN ); 
                    ReadFile( hFile,pxlScale,sizeof(pxlScale),&rwByte,NULL );
                    Dx =  pxlScale[0];
                    Dy = -pxlScale[1];
                }
                break;
            case TIFFTAG_GEOTIEPOINTS:
                DatOff = tagVal;
                if ( tagSize>1 ){
                    double tiePts[6];
                    _SeekTif( hFile,DatOff,FILE_BEGIN ); 
                    ReadFile( hFile,tiePts,sizeof(tiePts),&rwByte,NULL );  
                    Ex = tiePts[3];
                    Ny = tiePts[4];
                    bTfw = false;
                }
                break;
                
            case TIFFTAG_GEOKEYDIRECTORY:
                DatOff = tagVal;
                if ( tagSize>1 ){
                    struct geoKeyDirs{
                        unsigned short ent_key;        // Key id           
                        unsigned short ent_location;   // key loca  , if ent_location==0 value is ent_val_offset , if ent_location==34736 vlue is TIFFTAG_GEODOUBLEPARAMS [ent_val_offset]
                        unsigned short ent_count;      // key count , the value's size .  
                        unsigned short ent_val_offset; // key value or tag offset  
                    }geoKey[32]; if (tagSize>sizeof(geoKey)) tagSize=sizeof(geoKey);
                    _SeekTif( hFile,DatOff,FILE_BEGIN ); 
                    ReadFile( hFile,geoKey,tagSize,&rwByte,NULL );    
                    for( int k=1;k<geoKey[0].ent_val_offset;k++ ){
                        switch( geoKey[k].ent_key ){
                        case GTModelTypeGeoKey:
                            break;
                        case GTRasterTypeGeoKey:
                            if ( geoKey[k].ent_val_offset==1 ){
                                bCorner = false;
                            }else{
                                bCorner = true;
                            }
                            break;
                        }
                    }
                }
                break;
                
            case TIFFTAG_GEODOUBLEPARAMS:
                break;
            case TIFFTAG_GEOASCIIPARAMS:
                break;
        }
    }
    ::CloseHandle( hFile );

    double cosKap=1,sinKap=0; int orthRows = imgRows;
    *kap  =  0;
    *gsdX =  Dx/cosKap;
    *gsdY = -Dy/cosKap;
    *x0 = (Dy>=0)?(Ex):(Ex+sinKap* (*gsdY)*(orthRows-1));
    *y0 = (Dy>=0)?(Ny):(Ny-cosKap* (*gsdY)*(orthRows-1));

    return bTfw?FALSE:TRUE;
}

/*
A TFW file normally contains the following information:
Line Number Sample Value Meaning 
Line 1 +6.00 Cell size in the X direction 
Line 2 -0.00 Rotation in the X direction 
Line 3 -0.00 Rotation in the Y direction 
Line 4 -6.00 Cell size in the Y direction 
Line 5 1709053.00 Easting value of insertion point X 
Line 6 807714.00 Northing value of insertion point Y 
Note that sign of the cell size in Y (line 4) defines 
if the image insertion point is the upper left or lower left corner.
A positive means the "Y" values are increasing upwards and therefore, 
the registration must be starting at the bottom or lower left corner. 
A negative sign means that the insertion point is the upper left. 
The insertion point coordinates relate to the map corner of the image 
in its defined projection itself.

// Following is refers to GeoTIFF organization http://trac.osgeo.org/geotiff/

    ESRI's world file is a separate file with limited metadata content designed 
  only for use in Arc/Info and other ESRI softwares, though widely supported 
  by other software. The world reference file only contains the coefficients 
  for an affine transformation between raster coordinates, and world coordinates, 
  but no definition of the coordinate system.
    The GeoTIFF structure, by comparison, is rich in content and packs everything
  into a single file. The GeoTIFF tag stucture covers more diverse options for 
  projection spaces, datums, ellipsoids, coordinate types, and related geographic 
  features than the ESRI tag. And the GeoTIFF structure is intended to become entirely
  public domain, unlike tags withheld for private implementations. 

The contents of the worldfile are six numbers (each on their own line): 
A
B
C
D
E
F

The georeferenced location of a pixel center can be computed as: 
Xgeo = E + Xpixel * A + Ypixel * C
Ygeo = F + Ypixel * D + Xpixel * B

So, a typical (north up) arrangement would be: 
pixel width in geounits
0
0
pixel height in geounits (normally negative)
top left X geo location
top left Y geo location
*/
#include "math.h"
inline static BOOL GetGeo4Tif(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY,BOOL bCorner,LPCSTR strExt )
{
    if ( _strcmpi(strExt,".tfw")==0 ){
        BOOL ret = _GetGeo4Tif( lpstrPathName,x0,y0,kap,gsdX,gsdY );
        if ( ret ) return ret;
    }
    
    double Dx,Dy,Rx,Ry,Ex,Ny,cosKap,sinKap; int orthRows = 0;
    CSpVZImage imgFile; if ( !imgFile.Open(lpstrPathName) ) return FALSE;
    orthRows = imgFile.GetRows(); imgFile.Close();
    
    char strTfw[256]; strcpy( strTfw,lpstrPathName ); strcpy( strrchr(strTfw,'.'),strExt );
    FILE *ftfw = fopen( strTfw,"rt" ); if (!ftfw) return FALSE;
    fscanf( ftfw,"%lf",&Dx );
    fscanf( ftfw,"%lf",&Rx );
    fscanf( ftfw,"%lf",&Ry );
    fscanf( ftfw,"%lf",&Dy );
    fscanf( ftfw,"%lf",&Ex );
    fscanf( ftfw,"%lf",&Ny );
    fclose( ftfw ); 
    
    if (bCorner){ Ex += Dx/2; Ny += Dy/2; }// pixel corner to center. (the start pos in vz is center of pixel, so must be sub half of dx and dy) 

    *kap = atan2( Rx,Dx ); cosKap=cos(*kap); sinKap=sin(*kap); 
    if ( cosKap==0 ){
        *gsdX = Ry/sinKap;
        if (gsdY) *gsdY = Rx/sinKap;        
    }else{
        *gsdX = Dx/cosKap;
        if (gsdY) *gsdY = -Dy/cosKap;
    }

    *x0 = (Dy>=0)?(Ex):(Ex+sinKap* (gsdY?*gsdY:*gsdX)*(orthRows-1));
    *y0 = (Dy>=0)?(Ny):(Ny-cosKap* (gsdY?*gsdY:*gsdX)*(orthRows-1));

    return TRUE;
};

inline static BOOL SetGeo2Tif(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY,BOOL bCorner,LPCSTR strExt,int cols,int rows )
{
    if ( cols==0||rows==0 ){
        CSpVZImage imgFile; if ( !imgFile.Open(lpstrPathName) ) return FALSE;
        cols = imgFile.GetCols(); rows = imgFile.GetRows(); imgFile.Close(); 
    }    
    if ( gsdY==0 ) gsdY = gsdX;
    double Dx,Dy,Rx,Ry,Ex,Ny,cosKap,sinKap; int orthRows = rows;
    cosKap=cos(kap); sinKap=sin(kap);
    Dx =  cosKap*gsdX; //  cosA*dx
    Rx =  sinKap*gsdY; //  sinA*dy
    Ry =  sinKap*gsdX; //  sinA*dx
    Dy = -cosKap*gsdY; // -cosA*dy
    Ex = (Dy>=0)?( x0 ):( x0-sinKap*gsdY*(orthRows-1) );
    Ny = (Dy>=0)?( y0 ):( y0+cosKap*gsdY*(orthRows-1) );
    if (bCorner){ Ex -= Dx/2; Ny -= Dy/2; }// pixel center to corner.

    char strTfw[256]; strcpy( strTfw,lpstrPathName ); strcpy( strrchr(strTfw,'.'),strExt );
    FILE *ftfw = fopen( strTfw,"wt" ); if (!ftfw) return FALSE;
    fprintf( ftfw,"\t%.12lf\n",Dx );
    fprintf( ftfw,"\t%.12lf\n",Rx );
    fprintf( ftfw,"\t%.12lf\n",Ry );
    fprintf( ftfw,"\t%.12lf\n",Dy );
    fprintf( ftfw,"\t%.12lf\n",Ex );
    fprintf( ftfw,"\t%.12lf\n",Ny );
    fclose(ftfw); return TRUE;
};

inline static BOOL GetGeo4Jpg(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY,BOOL bCornrInTif ){ return GetGeo4Tif( lpstrPathName,x0,y0,kap,gsdX,gsdY,bCornrInTif,".jpw" ); }
inline static BOOL SetGeo2Jpg(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY,BOOL bCornrInTif,int cols,int rows )    { return SetGeo2Tif( lpstrPathName,x0,y0,kap,gsdX,gsdY,bCornrInTif,".jpw",cols,rows ); }
inline static BOOL GetGeo4Bmp(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY,BOOL bCornrInTif ){ return GetGeo4Tif( lpstrPathName,x0,y0,kap,gsdX,gsdY,bCornrInTif,".bmw" ); }
inline static BOOL SetGeo2Bmp(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY,BOOL bCornrInTif,int cols,int rows )    { return SetGeo2Tif( lpstrPathName,x0,y0,kap,gsdX,gsdY,bCornrInTif,".bmw",cols,rows ); }

inline static BOOL GetGeo4Orl(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY )
{
    HANDLE hFile = ::CreateFile( lpstrPathName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_FLAG_RANDOM_ACCESS,NULL );
    if ( hFile == INVALID_HANDLE_VALUE ) return FALSE;
    typedef struct tagImageHeaderORTHO
    {
        int           rows;           // image rows
        int           cols;           // image columns
        short         colour;     // 1 : black_white, 3 : true color
        double        original_x,original_y;    //ground coordinates of down-left coner
        float         orthoimgscale;
        double        kapa;                       // rotation angle from x-axis of groud system to  x-axis of DEM/Ortho image 
        float         pixelsizeX,pixelsizeY;    // output size of pixels cooresponding to the orthoing scale
        unsigned char gridFlag;                   // useless now
        float         gridIntervalX,gridIntervalY;  // useless now
        long          smallImgPtr,polygonPtr;     // useless now
    }ImageHeaderORTHO; ImageHeaderORTHO orthHdr; memset( &orthHdr,0,sizeof(orthHdr) );

    unsigned char b[10]; short  special[12]; DWORD rw;
    ::ReadFile( hFile,b,sizeof(b),&rw,NULL );
    ::ReadFile( hFile,special,sizeof(special),&rw,NULL );
    ::ReadFile( hFile,&(orthHdr.colour),sizeof(orthHdr)-sizeof(int)*2,&rw,NULL );
    ::CloseHandle( hFile );

    *x0          = orthHdr.original_x       ;
    *y0          = orthHdr.original_y       ;    
    *kap         = orthHdr.kapa             ;
    *gsdX         = int(orthHdr.pixelsizeX*orthHdr.orthoimgscale+0.9);
    *gsdX        /= 1000.f;
    if ( orthHdr.orthoimgscale<0.001 ) *gsdX=orthHdr.pixelsizeX; 
    if ( *gsdX==0 ) *gsdX = 1; 

    if ( gsdY ){
        *gsdY         = int(orthHdr.pixelsizeY*orthHdr.orthoimgscale+0.9);
        *gsdY        /= 1000.f;
        if ( orthHdr.orthoimgscale<0.001 ) *gsdY=orthHdr.pixelsizeY; 
        if ( *gsdY==0 ) *gsdY = 1;
    }
    return TRUE;
};

inline static BOOL SetGeo2Orl(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY,int cols,int rows )
{
    HANDLE hFile = ::CreateFile( lpstrPathName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_FLAG_RANDOM_ACCESS,NULL );
    if ( hFile == INVALID_HANDLE_VALUE ) return FALSE;
    if ( gsdY==0 ) gsdY = gsdX;
    
    typedef struct tagImageHeaderORTHO
    {
        int           rows;           // image rows
        int           cols;           // image columns
        short         colour;     // 1 : black_white, 3 : true color
        double        original_x,original_y;    //ground coordinates of down-left coner
        float         orthoimgscale;
        double        kapa;                       // rotation angle from x-axis of groud system to  x-axis of DEM/Ortho image 
        float         pixelsizeX,pixelsizeY;    // output size of pixels cooresponding to the orthoing scale
        unsigned char gridFlag;                   // useless now
        float         gridIntervalX,gridIntervalY;  // useless now
        long          smallImgPtr,polygonPtr;     // useless now
    }ImageHeaderORTHO; ImageHeaderORTHO orthHdr; memset( &orthHdr,0,sizeof(orthHdr) );

    unsigned char b[10]; short  special[12]; DWORD rw;
    ::ReadFile( hFile,b,sizeof(b),&rw,NULL );
    ::ReadFile( hFile,special,sizeof(special),&rw,NULL );
    ::ReadFile( hFile,&(orthHdr.colour),sizeof(orthHdr)-sizeof(int)*2,&rw,NULL );
    
    orthHdr.original_x    = x0;
    orthHdr.original_y    = y0;
    orthHdr.orthoimgscale = 1000;
    orthHdr.kapa          = kap;
    orthHdr.pixelsizeX    = float(gsdX);
    orthHdr.pixelsizeY    = float(gsdY); 

    ::SetFilePointer( hFile,0,NULL,FILE_BEGIN );
    ::WriteFile( hFile,       b,       sizeof(b),&rw,NULL );
    ::WriteFile( hFile, special, sizeof(special),&rw,NULL );
    ::WriteFile( hFile,&orthHdr.colour,sizeof(ImageHeaderORTHO)-sizeof(int)*2,&rw,NULL ); 
    
    ::CloseHandle( hFile );
    return TRUE;
};

inline static BOOL GetGeo4Lei( LPCSTR lpszPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY )
{
    HANDLE hFile = ::CreateFile( lpszPathName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_FLAG_RANDOM_ACCESS,NULL );
    if ( hFile == INVALID_HANDLE_VALUE ) return FALSE;
    
    typedef struct  tagVirImgHeader1
    {
        short         pixelBytes;
        double        original_x,original_y;
        float         orthoimgscale;
        double        kapa;
        float         pixelsizeX,pixelsizeY;
        unsigned char gridFlag;
        float         gridIntervalX,gridIntervalY;
        long          smallImgPtr,polygonPtr;
    }VirImgHeader1;
    typedef struct tagSptImgHeader
    {
        double  resolution;       //pixel size(mm)
        char    camera[260];    //filename of camera calibration data
        short   type;         //type of image ( 0=aerial 2=close range 10=spot )
        int     cameraReverse;  //camera reverse ( 1=Yes 0=No )
    }SptImgHeader;
    struct ImageInfo
    {
        BYTE  image_type;
        union tagVIMGHDR
        {
            VirImgHeader1 orthoHeader;
            SptImgHeader  sptHeader;
        }info_header;
    }info;
    struct AD_BITMAPINFO
    {
        BITMAPFILEHEADER    bmfHeader;
        BITMAPINFOHEADER    bmiHeader;
        LONG    adBlockWidth;        // 4*x
        LONG    adBlockHeight;
        LONG    adBlockXNum;
        LONG    adBlockYNum;
        LONG    adRealWidth;
        LONG    adRealHeight;
        LONG    adAerialSum;    
        LONG    reserved1,reserved2;
    }adInfo; DWORD rw;
    ::ReadFile( hFile,&adInfo,sizeof(adInfo),&rw,NULL );
    ::SetFilePointer( hFile,adInfo.bmfHeader.bfOffBits-sizeof(ImageInfo),NULL,FILE_BEGIN );
    ::ReadFile( hFile,&info,sizeof(info),&rw,NULL );
    ::CloseHandle( hFile );
    if ( adInfo.bmfHeader.bfType != 0x4d4d ) return FALSE;
    
    if ( info.image_type==0x0001 ){
        *kap = info.info_header.orthoHeader.kapa;
        *gsdX = info.info_header.orthoHeader.pixelsizeX/1000*info.info_header.orthoHeader.orthoimgscale;
        if (gsdY) *gsdY = info.info_header.orthoHeader.pixelsizeY/1000*info.info_header.orthoHeader.orthoimgscale;
        *x0 = info.info_header.orthoHeader.original_x;
        *y0 = info.info_header.orthoHeader.original_y;
    }
    return TRUE;
};

inline static BOOL SetGeo2Lei(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY,int cols,int rows )
{
    HANDLE hFile = ::CreateFile( lpstrPathName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_FLAG_RANDOM_ACCESS,NULL );
    if ( hFile == INVALID_HANDLE_VALUE ) return FALSE;
    if ( gsdY==0 ) gsdY = gsdX;
    
    typedef struct  tagVirImgHeader1
    {
        short         pixelBytes;
        double        original_x,original_y;
        float         orthoimgscale;
        double        kapa;
        float         pixelsizeX,pixelsizeY;
        unsigned char gridFlag;
        float         gridIntervalX,gridIntervalY;
        long          smallImgPtr,polygonPtr;
    }VirImgHeader1;
    typedef struct tagSptImgHeader
    {
        double  resolution;       //pixel size(mm)
        char    camera[260];    //filename of camera calibration data
        short   type;         //type of image ( 0=aerial 2=close range 10=spot )
        int     cameraReverse;  //camera reverse ( 1=Yes 0=No )
    }SptImgHeader;
    struct ImageInfo
    {
        BYTE  image_type;
        union tagVIMGHDR
        {
            VirImgHeader1 orthoHeader;
            SptImgHeader  sptHeader;
        }info_header;
    }info;
    struct AD_BITMAPINFO
    {
        BITMAPFILEHEADER    bmfHeader;
        BITMAPINFOHEADER    bmiHeader;
        LONG    adBlockWidth;        // 4*x
        LONG    adBlockHeight;
        LONG    adBlockXNum;
        LONG    adBlockYNum;
        LONG    adRealWidth;
        LONG    adRealHeight;
        LONG    adAerialSum;    
        LONG    reserved1,reserved2;
    }adInfo; DWORD rw;
    ::ReadFile( hFile,&adInfo,sizeof(adInfo),&rw,NULL );
    ::SetFilePointer( hFile,adInfo.bmfHeader.bfOffBits-sizeof(ImageInfo),NULL,FILE_BEGIN );
    ::ReadFile( hFile,&info,sizeof(info),&rw,NULL );
    
    if ( adInfo.bmfHeader.bfType == 0x4d4d ){
        if ( gsdY==0 ) gsdY = gsdX;
        info.image_type = 0x0001;
        info.info_header.orthoHeader.original_x    = x0;
        info.info_header.orthoHeader.original_y    = y0;
        info.info_header.orthoHeader.orthoimgscale = 1000;
        info.info_header.orthoHeader.kapa          = kap;
        info.info_header.orthoHeader.pixelsizeX    = float(gsdX);
        info.info_header.orthoHeader.pixelsizeY    = float(gsdY); 
        ::SetFilePointer( hFile,adInfo.bmfHeader.bfOffBits-sizeof(ImageInfo),NULL,FILE_BEGIN );
        ::WriteFile( hFile,&info,sizeof(info),&rw,NULL );
    }
    ::CloseHandle( hFile );
    return TRUE;
};

inline static BOOL GetGeo4Bbi(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY)
{
    char strGeo[256]; strcpy( strGeo,lpstrPathName ); strcat( strGeo,".geo" );
    FILE *fgeo = fopen( strGeo,"rt" ); if (!fgeo) return FALSE;

    char strTag[64],strSig[64],strVal[256];
    while ( !feof(fgeo) ){
        fscanf( fgeo,"%s%s%s",strTag,strSig,strVal );
        if ( _strcmpi(strTag,"MinX")==0 ) *x0  = atof(strVal); 
        if ( _strcmpi(strTag,"MinY")==0 ) *y0  = atof(strVal); 
        if ( _strcmpi(strTag,"Kapa")==0 ) *kap = atof(strVal); 
        if ( _strcmpi(strTag,"Gsd" )==0 ) *gsdX= atof(strVal); 
    }
    fclose(fgeo);
    if ( gsdY ) *gsdY = *gsdX;
    return TRUE;
}


inline static BOOL SetGeo2Bbi(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY,int cols,int rows,int blkSz)
{
    char strGeo[256]; strcpy( strGeo,lpstrPathName ); strcat( strGeo,".geo" );
    char strOld[256]; strcpy( strOld,lpstrPathName ); strcat( strOld,".old" );
    ::CopyFile( strGeo,strOld,FALSE );
    if ( gsdY==0 ) gsdY = gsdX;
    if ( cols==0 || rows==0 ){
        CSpVZImage imgFile; 
        if ( imgFile.Open(lpstrPathName) ){
            cols = imgFile.GetCols(); rows = imgFile.GetRows(); imgFile.Close();
        }
    }
    FILE *fgeo = fopen( strGeo,"wt" ); if (!fgeo) return FALSE;
    FILE *fold = fopen( strOld,"rt" ); 
    if ( fold ){
        char strTag[64],strSig[64],strVal[256];
        while ( !feof(fold) ){
            if ( fscanf( fold,"%s%s%s",strTag,strSig,strVal )>3 ){
                if ( _strcmpi(strTag,"BlkSize")==0 && blkSz==0 ) blkSz = atoi(strVal);
                if ( _strcmpi(strTag,"Rows")==0 && rows==0 ) rows = atoi(strVal);
                if ( _strcmpi(strTag,"Cols")==0 && cols==0 ) cols = atoi(strVal);
            }
        }
        fclose(fold);
    }
    if ( blkSz==0 ) blkSz = 256;

    fprintf( fgeo, "MinX    := %15.6lf\n", x0   ); 
    fprintf( fgeo, "MinY    := %15.6lf\n", y0   ); 
    fprintf( fgeo, "MeaZ    := 0.0\n"           ); 
    fprintf( fgeo, "Kapa    := %15.6lf\n", kap  ); 
    fprintf( fgeo, "Gsd     := %15.6lf\n", gsdX ); 
    fprintf( fgeo, "Rows    := %d\n", rows  );  
    fprintf( fgeo, "Cols    := %d\n", cols  ); 
    fprintf( fgeo, "BlkSize := %d\n", blkSz   ); 
    fprintf( fgeo, "BlkRows := %d\n", rows/blkSz+ ((rows%blkSz)!=0?1:0) ); 
    fprintf( fgeo, "BlkCols := %d\n", cols/blkSz+ ((cols%blkSz)!=0?1:0) ); 
    fprintf( fgeo, "Type    := %d\n", 0     );         

    fclose(fgeo); 
    return TRUE;
}

inline static BOOL SetGeo2Dem(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY,int cols,int rows)
{
    char strNew[256]; strcpy( strNew,lpstrPathName ); strcat( strNew,".new" );
    FILE *fold = fopen( lpstrPathName,"rt" );  if (!fold) return FALSE; 
    FILE *fdem = fopen( strNew,"wt" );         if (!fdem) return FALSE;
    if ( gsdY==0 ) gsdY = gsdX;
    
    double t; char strLine[512]; if ( gsdY==0 ) gsdY = gsdX;
    fscanf( fold,"%lf%lf%lf%lf",&t,&t,&t,&t,&t,&cols,&rows ); fgets( strLine,512,fold );
    fprintf( fdem,"%.6lf %.6lf %.6lf %.3lf %.3lf %d %d\n",x0,y0,kap,gsdX,gsdY,cols,rows );
    while ( !feof(fold) ){ fgets( strLine,512,fold ); fprintf( fdem,strLine ); }
    fclose(fold); fclose(fdem);
    
    ::CopyFile( strNew,lpstrPathName,FALSE );
}

inline static void DegMinSec2Deg(double* angle)
{
    double degree = int(*angle);
    double minute = int((*angle - degree) * 100+0.5);
    double second = ((*angle -degree)* 100 - minute) * 100;
    if (second >= 60) { minute++; second = ((*angle -degree)* 100 - minute) * 100; }
    *angle = degree + minute / 60 + second / 3600;
}
inline static BOOL GetGeo4Dem(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY)
{
    struct SPDEMHDR
    {
        double  startX;
        double  startY;   
        double  kapa;
        double  intervalX;
        double  intervalY;
        int       column;
        int       row;    
    }demHdr; memset( &demHdr,0,sizeof(demHdr) );
    char str[512]; 
    
    FILE *fDem = fopen( lpstrPathName,"rt" );  
    if ( !fDem ) return FALSE;
    fscanf( fDem,"%s",str );
    if ( strncmp(str,"DEMBIN",6)==0 || strncmp(str,"DEMBSH",6)==0 )
    {
        fclose( fDem ); fDem = fopen( lpstrPathName,"rb" );
        fread( str,512,1,fDem );
        fread( &demHdr,sizeof(demHdr),1,fDem );                                        
    }else
    {
        if ( strstr( str,"SDTF" ) )
        {
            double Ex=0,Ny=0; float zoom=100; int hrLine=0; char *pV;
            if ( strstr( str,"DataMark" ) )
            {
                pV = strchr( str,':' );
                while( pV )
                {
                    if ( strstr(str,"Alpha" ) ) demHdr.kapa      = atof(pV+1); else
                    if ( strstr(str,"X0"    ) ) Ex               = atof(pV+1); else
                    if ( strstr(str,"Y0"    ) ) Ny               = atof(pV+1); else
                    if ( strstr(str,"DX"    ) ) demHdr.intervalX = atof(pV+1); else
                    if ( strstr(str,"DY"    ) ) demHdr.intervalY = atof(pV+1); else
                    if ( strstr(str,"Row"   ) ) demHdr.row       = atoi(pV+1); else
                    if ( strstr(str,"Col"   ) ) demHdr.column    = atoi(pV+1); else
                    if ( strstr(str,"Hzoom" ) ) zoom             = float( atof(pV+1) );
                    hrLine ++; fgets( str,256,fDem ); pV = strchr( str,':' );
                }
                fclose(fDem); 
            }else
            {   
                fscanf( fDem,"%s",str );
                fscanf( fDem,"%s",str );
                fscanf( fDem,"%lf",&demHdr.kapa );
                fscanf( fDem,"%s",str );
                fscanf( fDem,"%lf",&Ex );
                fscanf( fDem,"%lf",&Ny );
                fscanf( fDem,"%lf",&demHdr.intervalX );
                fscanf( fDem,"%lf",&demHdr.intervalY );
                fscanf( fDem,"%d",&demHdr.row     ); 
                fscanf( fDem,"%d",&demHdr.column  ); 
                fscanf( fDem,"%f",&zoom );
                fclose(fDem); 
                
            }
            double cosKap=cos(demHdr.kapa),sinKap=sin(demHdr.kapa); 
            demHdr.startX = Ex+sinKap* (demHdr.intervalY)*(demHdr.row-1);
            demHdr.startY = Ny-cosKap* (demHdr.intervalY)*(demHdr.row-1);
        }else
        {
            char strType[8]; memset(strType, 0, sizeof(strType));
            fseek(fDem, 8, SEEK_SET); fscanf(fDem, "%8s", strType); strType[3] = '\0';
            BOOL bGJBFormat = (_stricmp(strType, "MGM") == 0 || _stricmp(strType, "GEM") == 0 || _stricmp(strType, "MDM") == 0 || _stricmp(strType, "DEM") == 0);
            if (bGJBFormat)
            {
                struct HEAD
                {
                    char ver[8], type[8], pathname[256];
                    char mapTool[256], edtTool[256];
                    char precision[8], mangNote[1024];
                    double xCutConst, yCutConst;
                    double minX, minY, maxX, maxY;
                    double dX, dY;
                    int secNum;
                };
                BOOL bGeodetic = (_stricmp(strType, "MDM") == 0 || _stricmp(strType, "DEM") == 0);
                HEAD hdr; memset(&hdr, 0, sizeof(hdr));
                fseek(fDem, 0, SEEK_SET); 
                fread( hdr.ver,        sizeof(hdr.ver),        1,fDem);
                fread( hdr.type,     sizeof(hdr.type),        1,fDem);
                fread( hdr.pathname, sizeof(hdr.pathname),  1,fDem);
                fread( hdr.mapTool,    sizeof(hdr.mapTool),    1,fDem);
                fread( hdr.edtTool,    sizeof(hdr.edtTool),    1,fDem);
                fread( hdr.precision,sizeof(hdr.precision),   1,fDem);
                fread( hdr.mangNote, sizeof(hdr.mangNote),  1,fDem);
                fread(&hdr.xCutConst,sizeof(hdr.xCutConst),   1,fDem); 
                fread(&hdr.yCutConst,sizeof(hdr.yCutConst),   1,fDem); 
                fread(&hdr.minX,     sizeof(hdr.minX),        1,fDem); 
                fread(&hdr.minY,     sizeof(hdr.minY),        1,fDem); 
                fread(&hdr.maxX,     sizeof(hdr.maxX),        1,fDem); 
                fread(&hdr.maxY,     sizeof(hdr.maxY),        1,fDem); 
                fread(&hdr.dX,       sizeof(hdr.dX),        1,fDem); 
                fread(&hdr.dY,       sizeof(hdr.dY),        1,fDem); 
                fread(&hdr.secNum,   sizeof(hdr.secNum),    1,fDem);                              
                fclose( fDem );                 
                if (bGeodetic) DegMinSec2Deg(&hdr.xCutConst);
                if (bGeodetic) DegMinSec2Deg(&hdr.yCutConst);
                if (bGeodetic) DegMinSec2Deg(&hdr.minX);
                if (bGeodetic) DegMinSec2Deg(&hdr.minY);                               
                if (bGeodetic) DegMinSec2Deg(&hdr.maxX);                        demHdr.startX = hdr.minX + hdr.xCutConst;
                if (bGeodetic) DegMinSec2Deg(&hdr.maxY);                        demHdr.startY = hdr.minY + hdr.yCutConst;
                if (bGeodetic){ hdr.dX /= 10000; DegMinSec2Deg(&hdr.dX); };     demHdr.kapa = 0;
                if (bGeodetic){ hdr.dY /= 10000; DegMinSec2Deg(&hdr.dY); };     demHdr.intervalX = hdr.dX; 
                if (hdr.secNum < 1) return FALSE; 

                demHdr.intervalY = hdr.dY;
                demHdr.column = int(ceil((hdr.maxX - hdr.minX)/hdr.dX) + 1);
                demHdr.row    = int(ceil((hdr.maxY - hdr.minY)/hdr.dY) + 1);                
            }else{
                fclose( fDem ); fDem = fopen( lpstrPathName,"rt" );
                if( fscanf( fDem,"%lf%lf%lf%lf%lf%d%d",&demHdr.startX,
                    &demHdr.startY,&demHdr.kapa,&demHdr.intervalX ,
                    &demHdr.intervalY,&demHdr.column,&demHdr.row)<7 )
                {  fclose( fDem );  return FALSE; }
            }
        }
    }
    *x0  = demHdr.startX;
    *y0  = demHdr.startY;
    *kap = demHdr.kapa;
    *gsdX = demHdr.intervalX;
    if ( gsdY ) *gsdY = demHdr.intervalY;
    return TRUE;
}

#ifdef _GEOIMG
#include "ErdasImg.h"
#else
#pragma message("Warning! Have not define _GEOIMG ,you can not get geo info from .img file.\n警告：你没有定义 _GEOIMG ,你将不能获取 img 格式影像文件的地理信息。") 
#endif
inline static BOOL GetGeo4Img(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY )
{
#ifdef _GEOIMG
    return GetGeo4ImgFile(lpstrPathName,x0,y0,kap,gsdX);
#else
    if ( gsdY ) *gsdY = *gsdX;
    return 0;
#endif
}

inline static BOOL SetGeo2Img(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY,int cols,int rows )
{
#ifdef _GEOIMG
    return SetGeo2ImgFile(lpstrPathName,x0,y0,kap,gsdX); 
#else
    return 0;
#endif
}

inline static BOOL GetGeo4Ecw(LPCSTR lpstrPathName,double *x0,double *y0,double *kap,double *gsdX,double *gsdY )
{
    BOOL ret = FALSE;
    typedef BOOL (CALLBACK* LPFNDLLFUNC_GEO)( UINT,double *,double *,double *,double * );
    HMODULE hDll = ::LoadLibrary( "SpVZImageECW.dll" ); 
    if ( hDll ){
        LPFNDLLFUNC_GEO m_pfSpGetGeo = (LPFNDLLFUNC_GEO )::GetProcAddress( hDll,"C_SpGetGeoInf" );
        if ( m_pfSpGetGeo ) ret=m_pfSpGetGeo( UINT(lpstrPathName),x0,y0,kap,gsdX );
        ::FreeLibrary( hDll ); 
    }

    if ( gsdY ) *gsdY = *gsdX;
    return ret;
}

inline static BOOL SetGeo2Ecw(LPCSTR lpstrPathName,double x0,double y0,double kap,double gsdX,double gsdY,int cols,int rows )
{
    return FALSE;
}

inline static BOOL GetRot180(LPCSTR lpstrPathName)
{
    HANDLE hFile = ::CreateFile( lpstrPathName,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_FLAG_RANDOM_ACCESS,NULL );
    if ( hFile == INVALID_HANDLE_VALUE ) return FALSE; 
    ::SetFilePointer( hFile,-8,NULL,FILE_END ); DWORD rw=0;
    char strRot[8]; memset(strRot,0,sizeof(strRot) );
    ::ReadFile( hFile,strRot,8,&rw,NULL );
    ::CloseHandle( hFile );
    return ( strcmp(strRot,"R=180")==0?TRUE:FALSE );
}

inline static BOOL SetRot(LPCSTR lpstrPathName,int rot){
    char strRot[8]; strcpy( strRot,"R=000" ); 
    if ( rot==90  ) strcpy( strRot,"R=090" ); 
    if ( rot==180 ) strcpy( strRot,"R=180" ); 
    if ( rot==270 ) strcpy( strRot,"R=270" );

    HANDLE hFile = ::CreateFile( lpstrPathName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_FLAG_RANDOM_ACCESS,NULL );
    if ( hFile == INVALID_HANDLE_VALUE ) return FALSE;
    ::SetFilePointer( hFile,-8,NULL,FILE_END ); DWORD rw=0; char str[8];
    ::ReadFile( hFile,str,8,&rw,NULL );
    if ( strcmp(str,"R=180")==0 || strcmp(str,"R=000")==0 || strcmp(str,"R=090")==0 || strcmp(str,"R=270")==0 ){
        ::SetFilePointer( hFile,-8,NULL,FILE_END );
        ::WriteFile( hFile,strRot,8,&rw,NULL );
    }else{
        ::WriteFile( hFile,strRot,8,&rw,NULL ); 
    }
    ::CloseHandle( hFile );
    return TRUE;
}

inline static int GetRot(LPCSTR lpstrPathName)
{
    DWORD rw=0; char str[8];
    HANDLE hFile = ::CreateFile( lpstrPathName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_FLAG_RANDOM_ACCESS,NULL );
    if ( hFile == INVALID_HANDLE_VALUE ) return 0;
    ::SetFilePointer( hFile,-8,NULL,FILE_END ); 
    ::ReadFile( hFile,str,8,&rw,NULL ); ::CloseHandle( hFile );

    if ( strcmp(str,"R=090")==0 ) return 90;
    if ( strcmp(str,"R=180")==0 ) return 180;
    if ( strcmp(str,"R=270")==0 ) return 270; 
    return 0;
}

inline static BOOL SetRot180(LPCSTR lpstrPathName,BOOL bR180)
{
    HANDLE hFile = ::CreateFile( lpstrPathName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_FLAG_RANDOM_ACCESS,NULL );
    if ( hFile == INVALID_HANDLE_VALUE ) return FALSE;
    ::SetFilePointer( hFile,-8,NULL,FILE_END ); DWORD rw=0;
    char strRot[8];  ::ReadFile( hFile,strRot,8,&rw,NULL );
    if ( strcmp(strRot,"R=180")==0 || strcmp(strRot,"R=000")==0 ){
        if ( bR180 ) strcpy( strRot,"R=180" );
        else strcpy( strRot,"R=000" );
        ::SetFilePointer( hFile,-8,NULL,FILE_END );
        ::WriteFile( hFile,strRot,8,&rw,NULL );
    }else{
        if ( bR180 ){ strcpy( strRot,"R=180" ); ::WriteFile( hFile,strRot,8,&rw,NULL ); }
    }
    ::CloseHandle( hFile );
    return TRUE;
}

#endif
