#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc.hpp>
#include <stdio.h>
#include <format>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

constexpr double MinimumArea = 5000.00;
std::string gstreamer_pipeline(int capture_width, int capture_height, int framerate, int display_width, int display_height) {
    return
            " libcamerasrc ! video/x-raw, "
            " width=(int)" + std::to_string(capture_width) + ","
            " height=(int)" + std::to_string(capture_height) + ","
            " framerate=(fraction)" + std::to_string(framerate) +"/1 !"
            " videoconvert ! videoscale !"
            " video/x-raw,"
            " width=(int)" + std::to_string(display_width) + ","
            " height=(int)" + std::to_string(display_height) + " ! appsink";
}

int main(int argc, char* argv[])
{
  //pipeline parameters
    int capture_width = 800; //1280 ;
    int capture_height = 600; //720 ;
    int framerate = 15 ;
    int display_width = 640; //1280 ;
    int display_height = 480; //720 ;
    std::string pipeline = gstreamer_pipeline(capture_width, capture_height, framerate,
                                              display_width, display_height);
    std::cout << "Using pipeline: \n\t" << pipeline << "\n\n\n";
    VideoCapture cap(pipeline, CAP_GSTREAMER);
    bool update_bg_model = true;
    
    Ptr<BackgroundSubtractor> bg;
    bg = cv::createBackgroundSubtractorMOG2();
   
    std::vector < std::vector < cv::Point > >contours;

    // cv::namedWindow ("Frame");
    // cv::namedWindow ("Background");

    Mat frame, fgmask, fgimg, backgroundImage;
    unsigned int i = 0;
    for(;;)
    {
        cap >> frame;
        if (i % 5 == 0) {
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
        
	    imwrite(std::format("test{}.jpg", i), frame);
        }
        char k = (char)waitKey(30);
        if( k == 27 ) break;

    }

    return 0;
}
