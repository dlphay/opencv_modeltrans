#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\types_c.h> 
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace cv;
int main()
{
    //��ȡͼ��Դ
    cv::Mat srcImage = cv::imread("model.jpg");  // ͼƬ·��  748*520
	cv::Mat demo_Image = cv::imread("demo.png");  // ͼƬ·��  614*404
	cv::Mat demo1_Image = cv::imread("demo1.jpg");  // ͼƬ·��  614*404
	cv::Mat demo2_Image = cv::imread("demo2.jpg");  // ͼƬ·��  614*404
	//���ͼƬ��ʧ�����˳�
    if (srcImage.empty()) 
	{
        return -1;  // �˳�
    }
    //תΪ�Ҷ�ͼ��
    cv::Mat srcGray;//�����޳�ʼ������
    cv::cvtColor(srcImage, srcGray,CV_RGB2GRAY);// ͼ��ĻҶ�ת��

	Mat srcGray_output = srcGray.clone();  
	// ͼ����ɫ���з�ת
	for(int x = 0;x<srcGray.rows;x++)       
    {       
        for(int y = 0;y<srcGray.cols;y++)  
        {  
            srcGray.at<uchar>(x,y)=255-srcGray.at<uchar>(x,y);  
			if(x < 138 || x>480)   srcGray.at<uchar>(x,y) = 0;
			if(y < 200 || y>360)   srcGray.at<uchar>(x,y) = 0;
        }  
    }  
	threshold(srcGray, srcGray, 100, 255, CV_THRESH_BINARY);  //ͼ���ֵ��
	Mat erzhihua_IMAGE = srcGray.clone();  
	//��̬ѧ�Ĵ���
	//������ (ȥ��һЩ���)  �����ֵ����ͼƬ���Ų�����Ȼ�ܶ࣬���������size  
	Mat element = getStructuringElement(MORPH_RECT, Size(4, 4));
	morphologyEx(srcGray, srcGray, MORPH_OPEN, element);
	//�ղ��� (����һЩ��ͨ��)    
	morphologyEx(srcGray, srcGray, MORPH_CLOSE, element);

	Mat OUTPUT_IMAGE = srcImage.clone(); 

	// ��ʼͼ���ں�0
	for(int x = 0;x<demo_Image.rows;x++)       
    {       
        for(int y = 0;y<demo_Image.cols;y++)  
        {  
			uchar *p_OUTPUT_IMAGE = OUTPUT_IMAGE.ptr<uchar>(x, y);
			uchar *p_demo = demo_Image.ptr<uchar>(x, y);
			uchar *p_srcGray = srcGray.ptr<uchar>(x, y);
			if(p_srcGray[0] == 255) //�·����ص�
			{
			        p_OUTPUT_IMAGE[0] = p_demo[0];
                    p_OUTPUT_IMAGE[1] = p_demo[1];
                    p_OUTPUT_IMAGE[2] = p_demo[2];
			}
        }  
    }  
	Mat OUTPUT_IMAGE1 = srcImage.clone(); 
	// ��ʼͼ���ں�1
	for(int x = 0;x<demo1_Image.rows;x++)       
    {       
        for(int y = 0;y<demo1_Image.cols;y++)  
        {  
			uchar *p_OUTPUT_IMAGE = OUTPUT_IMAGE1.ptr<uchar>(x, y);
			uchar *p_demo = demo1_Image.ptr<uchar>(x, y);
			uchar *p_srcGray = srcGray.ptr<uchar>(x, y);
			if(p_srcGray[0] == 255) //�·����ص�
			{
			        p_OUTPUT_IMAGE[0] = p_demo[0];
                    p_OUTPUT_IMAGE[1] = p_demo[1];
                    p_OUTPUT_IMAGE[2] = p_demo[2];
			}
        }  
    } 
	Mat OUTPUT_IMAGE2 = srcImage.clone(); 
	// ��ʼͼ���ں�2
	for(int x = 0;x<demo2_Image.rows;x++)       
    {       
        for(int y = 0;y<demo2_Image.cols;y++)  
        {  
			uchar *p_OUTPUT_IMAGE = OUTPUT_IMAGE2.ptr<uchar>(x, y);
			uchar *p_demo = demo2_Image.ptr<uchar>(x, y);
			uchar *p_srcGray = srcGray.ptr<uchar>(x, y);
			if(p_srcGray[0] == 255) //�·����ص�
			{
			        p_OUTPUT_IMAGE[0] = p_demo[0];
                    p_OUTPUT_IMAGE[1] = p_demo[1];
                    p_OUTPUT_IMAGE[2] = p_demo[2];
			}
        }  
    } 

    cv::imshow("ԭͼ��", srcImage);//��ʾԴͼ��
    cv::imshow("�ҶȻ�", srcGray_output);//��ʾ�Ҷ�ͼ��
	cv::imshow("��ֵ��", erzhihua_IMAGE);//��ʾ��ֵ��
	cv::imshow("��̬ѧ", srcGray);//��ʾ��̬ѧ
	cv::imshow("���ͼ", OUTPUT_IMAGE);//��ʾ���ͼ
	cv::imshow("���ͼ1", OUTPUT_IMAGE1);//��ʾ���ͼ
	cv::imshow("���ͼ2", OUTPUT_IMAGE2);//��ʾ���ͼ
    cv::waitKey(0); //�ȴ���������ͼƬһֱ��ʾ�⡣
    return 0;
}