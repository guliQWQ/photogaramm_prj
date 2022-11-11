// photogaramm_prj.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include "CFeature_Extraction.h"
#include "CFeature_Matching.h"
#include "fmeeting.h"
#include "string.h"

int main(int argc, char **argv)
{
    printf("This system is for photogrammetry\n");
    printf("The copyright belongs to LiaoWenting\n");
    printf("If you meet any problems in using this program, please contact liaowt23@mail2.sysu.edu.cn\n");
    if (argc == 1)
    {
        printf("The keywords of this program are:\n");
        printf("1. feature_extraction\n");
        printf("2. feature_matching\n");
        printf("3. camera_calibration\n");
        printf("4. front_meeting\n");
        printf("反正选前方交会一套都做完了\n");
        return 0;
    }

    //create empty prj file
    if (argc == 2)
    {
        if (strcmp(argv[1], "feature_extraction") == 0)//特征提取
        {
            CFeature_Extraction feat_ext;
            feat_ext.create_empty_prj_file_for_feat_extraction("G:\\OpenCV\\feat_ext.txt");
        }
        
    }

    //processing
    if (argc == 3)
    {
        if (strcmp(argv[1], "feature_extraction") == 0)
        {
            CFeature_Extraction feat_ext;

            feat_ext.feat_extraction_with_Moravec(argv[2]);//图像路径
        }
        if (strcmp(argv[1], "front_meeting") == 0) {
            front_meeting fm;
            fm.frontmeet(argv[2]);
        }

        }
    
    if (argc == 4) {
        if (strcmp(argv[1], "feature_matching") == 0) {
            CFeature_Matching feat_ext;

            //feat_ext.feat_matching(argv[2], argv[3], 0);//图像路径
        }
    }

    if (argc == 5) {
        if (strcmp(argv[1], "calibration") == 0) {
            CFeature_Matching feat_ext;
            feat_ext.calibration(argv[2], argv[3],argv[4]);//图像路径
        }
    }
    return 1;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
