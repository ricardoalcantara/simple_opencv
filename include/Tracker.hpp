#ifndef TRACKER_H
#define TRACKER_H

#include "ScreenCapture.h"
#include <opencv4/opencv2/core.hpp>
// #include <vector>

class Tracker
{
public:
    Tracker();
    ~Tracker();
    void Run();
    void Initialize();

private:
    std::shared_ptr<SL::Screen_Capture::IScreenCaptureManager> framgrabber;
    cv::String wName;
    cv::Size size = {800, 600};
    std::mutex mutex;
    cv::Mat matImg;
    std::shared_ptr<SL::Screen_Capture::ICaptureConfiguration<SL::Screen_Capture::ScreenCaptureCallback>> captureConfiguration;

private:
    void ExtractAndConvertToRGBA(const SL::Screen_Capture::Image &, unsigned char *, size_t);
    void OnFrame(const SL::Screen_Capture::Image &, const SL::Screen_Capture::Monitor &);
    std::vector<SL::Screen_Capture::Monitor> CreateCaptureConfiguration();

    cv::Mat GetLastMatImage() { return matImg; }
    void StoreMatImage(cv::Mat matImg)
    {
        const std::lock_guard<std::mutex> lock(mutex);
        this->matImg = matImg;
    }
};

#endif
