#ifndef PMATRICIES_H
#define PMATRICIES_H

#include "opencv2/opencv.hpp"


class Pmatricies
{
public:
    Pmatricies();
private:
    cv::Mat MatBase;
    cv::Mat MatImage;
    float   glPmat[16];
};

#endif // PMATRICIES_H
