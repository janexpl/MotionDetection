#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc.hpp>
#include <stdio.h>

#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

constexpr double MinimumArea = 5000.00;
int main(int argc, char* argv[])
{

    VideoCapture cap;
    bool update_bg_model = true;
    cap.open(atoi(argv[1]));
    Ptr<BackgroundSubtractor> bg;
    bg = cv::createBackgroundSubtractorMOG2();
   
    std::vector < std::vector < cv::Point > >contours;

    // cv::namedWindow ("Frame");
    // cv::namedWindow ("Background");

    Mat frame, fgmask, fgimg, backgroundImage;

    for(;;)
    {
        cap >> frame;
        bg->apply(frame, fgimg);
        bg->getBackgroundImage(backgroundImage);
        erode (fgimg, fgimg, cv::Mat ());
        dilate (fgimg, fgimg, cv::Mat ());

        cv::findContours (fgimg, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
        for (auto && contour : contours) {
            auto area = cv::contourArea(contour);
            if (area < MinimumArea) {
                continue;
            }
            cout << "Detected" << endl;
            // cv::drawContours (frame, contours, -1, cv::Scalar (0, 0, 255), 2);
        }



        // cv::imshow ("Frame", frame);
        // cv::imshow ("Background", backgroundImage);


        char k = (char)waitKey(30);
        if( k == 27 ) break;

    }

    return 0;
}
