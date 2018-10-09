#define _SCL_SECURE_NO_WARNINGS
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;
using namespace std;
char port_name[] = { "\\\\.\\COM3" };
char output[255];
char incomingData[255];

using namespace cv;
const int key_esc = 27;
const int key_space = 32;
int LearningTime = 0;
char name[130];
char *PAPER = (char*)"PAPER", *NONE = (char*) "NONE", *ON = (char*)"ON";

using namespace std;

Mat subframe;
String hand_cascade_name1 = "paper2.xml";
String hand_cascade_name2 = "data.xml";
String hand_cascade_name3 = "data.xml";
CascadeClassifier hand_cascade1;
CascadeClassifier hand_cascade2;
CascadeClassifier hand_cascade3;
string window_name = "Capture - Face detection";


char detectAndDisplay(  Mat frame,
                        Mat sobel,
                        Mat grad_x,
                        Mat grad_y,
                        Mat abs_grad_x,
                        Mat abs_grad_y,
                        CascadeClassifier hand_cascade1, CascadeClassifier hand_cascade2, CascadeClassifier hand_cascade3);

int main(int argc, char **argv)
{
	Mat frame,
        sobel,
	    frame1,
	    grad_x,
	    grad_y,
	    abs_grad_x,
	    abs_grad_y;
	unsigned char insert_key;
	/*
	CvVideoWriter *writer;
	char AviFileName[]="Output.avi";
	int AviForamt = -1;
	int FPS = 6,key=-1;
	int AviColor = 1;
	*/

	VideoCapture cap(1); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
	{
		return -1;
	}
	cap >> frame;

	while (1)
	{
		cap >> frame;
		detectAndDisplay( frame,
                          sobel,
                          grad_x,
                          grad_y,
                          abs_grad_x,abs_grad_y,
                          hand_cascade1,
                          hand_cascade2,
                          hand_cascade3);

		imshow("Org_imShow", frame);
		insert_key = waitKey(10);
		if (insert_key == key_esc)
		{
			cap.release();
			destroyAllWindows();
			break;
		}
	}
		return 0;
}
