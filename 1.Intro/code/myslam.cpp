#include <opencv2/opencv.hpp>

// ORB-SLAM的系统接口
#include "System.h"

#include <string>
#include <chrono>   // for time stamp
#include <iostream>

using namespace std;

string parameterFile = "./myslam.yaml";
string vocFile = "./Vocabulary/ORBvoc.txt";

int main(int argc, char **argv) {

    // 声明 ORB-SLAM2 系统
    ORB_SLAM2::System SLAM(vocFile, parameterFile, ORB_SLAM2::System::MONOCULAR, true);

    // 获取相机图像代码
    cv::VideoCapture cap(0);    // change to 1 if you want to use USB camera.

    // 分辨率设为640x480
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

    // 记录系统时间
    auto start = chrono::system_clock::now();

    while (1) {
        cv::Mat frame;
        cap >> frame;   // 读取相机数据
        auto now = chrono::system_clock::now();
        auto timestamp = chrono::duration_cast<chrono::milliseconds>(now - start);
        SLAM.TrackMonocular(frame, double(timestamp.count())/1000.0);
    }

    return 0;
}
