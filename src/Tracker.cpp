#include "Tracker.hpp"

#include <spdlog/spdlog.h>
#include <functional>
#include <memory>

#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>

Tracker::Tracker()
{
    spdlog::debug("Tracker Contructor");

    captureConfiguration = SL::Screen_Capture::CreateCaptureConfiguration(std::bind(&Tracker::CreateCaptureConfiguration, this));
    captureConfiguration->onNewFrame(std::bind(&Tracker::OnFrame, this, std::placeholders::_1, std::placeholders::_2));
}

bool Tracker::IsCapturing()
{
    return framgrabber && !framgrabber->isPaused();
}

void Tracker::StartCapturing()
{
    if (framgrabber)
    {
        framgrabber->resume();
    }
    else
    {
        framgrabber = captureConfiguration->start_capturing();
        framgrabber->setFrameChangeInterval(std::chrono::milliseconds(100));
    }
}

void Tracker::StopCapturing()
{
    if (framgrabber)
    {
        framgrabber->pause();
    }
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

    // Todo, better imgBuffer allocation
    auto size = width * height * sizeof(SL::Screen_Capture::ImageBGRA);
    unsigned char *imgbuffer = (unsigned char *)malloc(size);

    ExtractAndConvertToRGBA(img, imgbuffer, size);
    imageTexture.SetBuffer(width, height, imgbuffer);
}

void Tracker::Run()
{
    spdlog::debug("Run");

    while (true)
    {
        cv::imshow(wName, GetLastMatImage());
        cv::waitKey(1);
    }
}
