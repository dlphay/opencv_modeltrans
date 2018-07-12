#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\types_c.h> 
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace cv;
int main()
{
    //读取图像源
    cv::Mat srcImage = cv::imread("model.jpg");  // 图片路径  748*520
	cv::Mat demo_Image = cv::imread("demo.png");  // 图片路径  614*404
	cv::Mat demo1_Image = cv::imread("demo1.jpg");  // 图片路径  614*404
	cv::Mat demo2_Image = cv::imread("demo2.jpg");  // 图片路径  614*404
	//如果图片打开失败则退出
    if (srcImage.empty()) 
	{
        return -1;  // 退出
    }
    //转为灰度图像
    cv::Mat srcGray;//创建无初始化矩阵
    cv::cvtColor(srcImage, srcGray,CV_RGB2GRAY);// 图像的灰度转换

	Mat srcGray_output = srcGray.clone();  
	// 图像颜色进行反转
	for(int x = 0;x<srcGray.rows;x++)       
    {       
        for(int y = 0;y<srcGray.cols;y++)  
        {  
            srcGray.at<uchar>(x,y)=255-srcGray.at<uchar>(x,y);  
			if(x < 138 || x>480)   srcGray.at<uchar>(x,y) = 0;
			if(y < 200 || y>360)   srcGray.at<uchar>(x,y) = 0;
        }  
    }  
	threshold(srcGray, srcGray, 100, 255, CV_THRESH_BINARY);  //图像二值化
	Mat erzhihua_IMAGE = srcGray.clone();  
	//形态学的处理
	//开操作 (去除一些噪点)  如果二值化后图片干扰部分依然很多，增大下面的size  
	Mat element = getStructuringElement(MORPH_RECT, Size(4, 4));
	morphologyEx(srcGray, srcGray, MORPH_OPEN, element);
	//闭操作 (连接一些连通域)    
	morphologyEx(srcGray, srcGray, MORPH_CLOSE, element);

	Mat OUTPUT_IMAGE = srcImage.clone(); 

	// 开始图像融合0
	for(int x = 0;x<demo_Image.rows;x++)       
    {       
        for(int y = 0;y<demo_Image.cols;y++)  
        {  
			uchar *p_OUTPUT_IMAGE = OUTPUT_IMAGE.ptr<uchar>(x, y);
			uchar *p_demo = demo_Image.ptr<uchar>(x, y);
			uchar *p_srcGray = srcGray.ptr<uchar>(x, y);
			if(p_srcGray[0] == 255) //衣服像素点
			{
			        p_OUTPUT_IMAGE[0] = p_demo[0];
                    p_OUTPUT_IMAGE[1] = p_demo[1];
                    p_OUTPUT_IMAGE[2] = p_demo[2];
			}
        }  
    }  
	Mat OUTPUT_IMAGE1 = srcImage.clone(); 
	// 开始图像融合1
	for(int x = 0;x<demo1_Image.rows;x++)       
    {       
        for(int y = 0;y<demo1_Image.cols;y++)  
        {  
			uchar *p_OUTPUT_IMAGE = OUTPUT_IMAGE1.ptr<uchar>(x, y);
			uchar *p_demo = demo1_Image.ptr<uchar>(x, y);
			uchar *p_srcGray = srcGray.ptr<uchar>(x, y);
			if(p_srcGray[0] == 255) //衣服像素点
			{
			        p_OUTPUT_IMAGE[0] = p_demo[0];
                    p_OUTPUT_IMAGE[1] = p_demo[1];
                    p_OUTPUT_IMAGE[2] = p_demo[2];
			}
        }  
    } 
	Mat OUTPUT_IMAGE2 = srcImage.clone(); 
	// 开始图像融合2
	for(int x = 0;x<demo2_Image.rows;x++)       
    {       
        for(int y = 0;y<demo2_Image.cols;y++)  
        {  
			uchar *p_OUTPUT_IMAGE = OUTPUT_IMAGE2.ptr<uchar>(x, y);
			uchar *p_demo = demo2_Image.ptr<uchar>(x, y);
			uchar *p_srcGray = srcGray.ptr<uchar>(x, y);
			if(p_srcGray[0] == 255) //衣服像素点
			{
			        p_OUTPUT_IMAGE[0] = p_demo[0];
                    p_OUTPUT_IMAGE[1] = p_demo[1];
                    p_OUTPUT_IMAGE[2] = p_demo[2];
			}
        }  
    } 

    cv::imshow("原图像", srcImage);//显示源图像
    cv::imshow("灰度化", srcGray_output);//显示灰度图像
	cv::imshow("二值化", erzhihua_IMAGE);//显示二值化
	cv::imshow("形态学", srcGray);//显示形态学
	cv::imshow("结果图", OUTPUT_IMAGE);//显示结果图
	cv::imshow("结果图1", OUTPUT_IMAGE1);//显示结果图
	cv::imshow("结果图2", OUTPUT_IMAGE2);//显示结果图
    cv::waitKey(0); //等待。可以让图片一直显示这。
    return 0;
}