#include "Tracker.hpp"

#include <spdlog/spdlog.h>
#include <functional>

#include <opencv4/opencv2/highgui.hpp>

Tracker::Tracker()
{
}

void Tracker::Initialize()
{
    spdlog::debug("Contructor");

    captureConfiguration = SL::Screen_Capture::CreateCaptureConfiguration(std::bind(&Tracker::CreateCaptureConfiguration, this));
    captureConfiguration->onNewFrame(std::bind(&Tracker::OnFrame, this, std::placeholders::_1, std::placeholders::_2));
    framgrabber = captureConfiguration->start_capturing();

    cv::startWindowThread();
    cv::namedWindow(wName, cv::WINDOW_NORMAL);
    cv::resizeWindow(wName, size / 2);

    framgrabber->setFrameChangeInterval(std::chrono::milliseconds(34));
}

Tracker::~Tracker()
{
    spdlog::debug("Destructor");
}

void Tracker::ExtractAndConvertToRGBA(const SL::Screen_Capture::Image &img, unsigned char *dst, size_t dst_size)
{
    assert(dst_size >= static_cast<size_t>(SL::Screen_Capture::Width(img) * SL::Screen_Capture::Height(img) * sizeof(SL::Screen_Capture::ImageBGRA)));
    auto imgsrc = StartSrc(img);
    auto imgdist = dst;
    for (auto h = 0; h < Height(img); h++)
    {
        auto startimgsrc = imgsrc;
        for (auto w = 0; w < Width(img); w++)
        {
            *imgdist++ = imgsrc->B;
            *imgdist++ = imgsrc->G;
            *imgdist++ = imgsrc->R;
            *imgdist++ = 0; // alpha should be zero
            imgsrc++;
        }
        imgsrc = SL::Screen_Capture::GotoNextRow(img, startimgsrc);
    }
}

std::vector<SL::Screen_Capture::Monitor> Tracker::CreateCaptureConfiguration()
{
    auto mons = SL::Screen_Capture::GetMonitors();
    size = cv::Size(mons[0].Width, mons[0].Height);

    return mons;
}

void Tracker::OnFrame(const SL::Screen_Capture::Image &img, const SL::Screen_Capture::Monitor &monitor)
{
    spdlog::info("onFrameChanged");
    auto width = SL::Screen_Capture::Width(img);
    auto height = SL::Screen_Capture::Height(img);

    auto size = width * height * sizeof(SL::Screen_Capture::ImageBGRA);
    auto imgbuffer(std::make_unique<unsigned char[]>(size));

    ExtractAndConvertToRGBA(img, imgbuffer.get(), size);
    auto mi = cv::Mat(cv::Size(width, height), CV_8UC4, imgbuffer.get()); //Mat(Size(Height, Width), Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]);
    StoreMatImage(mi);
}

void Tracker::Run()
{
    spdlog::debug("Run");

    while(true)
    {
        cv::imshow(wName, GetLastMatImage());
        cv::waitKey(1);
    }
}