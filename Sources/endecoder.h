#ifndef _CLASSES
#define _CLASSES

#include <iostream>
#include <string>
#include <unistd.h>
#include "exceptions.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>



// This class gets image path and text which wanted to be embedded

class encoder {
private:
    cv::Mat image;
    std::string text;
    std::string path;
    void initialize();
    
public:
    encoder(const std::string &path, const std::string &image_path);
    void start();
    void save(std::string image_path);
    ~encoder();
};


// class for image to decode text

class decoder {
public:
    cv::Mat image;
    std::string text;
public:
    decoder(const std::string &image_path);
    void start();
    void show();
    ~decoder();
};

#endif
