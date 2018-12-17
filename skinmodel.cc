#include "skinmodel.h"
#include <cmath>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

/// Constructor
SkinModel::SkinModel()
{
}

/// Destructor
SkinModel::~SkinModel() 
{
}

/// Start the training.  This resets/initializes the model.
///
/// Implementation hint:
/// Use this function to initialize/clear data structures used for training the skin model.
void SkinModel::startTraining()
{
    //--- IMPLEMENT THIS ---//
    
}

/// Add a new training image/mask pair.  The mask should
/// denote the pixels in the training image that are of skin color.
///
/// @param img:  input image
/// @param mask: mask which specifies, which pixels are skin/non-skin
void SkinModel::train(const cv::Mat3b& img, const cv::Mat1b& mask)
{

	//--- IMPLEMENT THIS ---//
}

/// Finish the training.  This finalizes the model.  Do not call
/// train() afterwards anymore.
///
/// Implementation hint:
/// e.g normalize w.r.t. the number of training images etc.
void SkinModel::finishTraining()
{
	//--- IMPLEMENT THIS ---//

}


/// Classify an unknown test image.  The result is a probability
/// mask denoting for each pixel how likely it is of skin color.
///
/// @param img: unknown test image
/// @return:    probability mask of skin color likelihood
cv::Mat1b SkinModel::classify(const cv::Mat3b& img1)
{
    cv::Mat3b img;
    cv::Mat1b skin = cv::Mat1b::zeros(img1.rows, img1.cols);
    cv::cvtColor(img1, img, CV_BGR2HSV);
    cv::GaussianBlur(img, img, cv::Size(11,11), 1, 1);
    
	//--- IMPLEMENT THIS ---//
    for (int row = 0; row < img1.rows; ++row) {
        for (int col = 0; col < img1.cols; ++col) {

			if (false)
				skin(row, col) = rand()%256;

			if (false)
				skin(row, col) = img(row,col)[2];

			if (false) {
			
				cv::Vec3b bgr = img(row, col);
                if (bgr[2] > bgr[1] && bgr[1] > bgr[0] && bgr[2]<190){
                    int val = (4*(bgr[2] - bgr[1]));
                    if (val > 60) {
                        skin(row, col) = 0;
                    }else{
                        if((160 < col < img.cols-200))
                            skin(row, col) = 20*(bgr[2] - bgr[1]);
                        else{
                        skin(row, col) = 20*(bgr[2] - bgr[1]);
                        }
                        skin(row, col) = 2*(bgr[2] - bgr[1]);

                    }
                }
			}
            if(true){
            if( (img(row,col)[0]>0) && (img(row,col)[0] < 20) && (img(row,col)[1]>0)
               && (img(row,col)[1]<177) && (img(row,col)[2]>47) && (img(row,col)[2]<255) ){
                if(col > img1.cols){
                    for(int i=0; i<3; ++i){
                        img(row,col)[i] = 0;
                    }
                }
                else{
                    for(int i=0; i<3; ++i){
                        img(row,col)[i] = 255;
                    }
                }
            } // do nothing
            else{
                if(col > img1.cols-90){
                    for(int i=0; i<3; ++i){
                        img(row,col)[i] = 0;
                    }
                }
                else{
                    for(int i=0; i<3; ++i){
                        img(row,col)[i] = 0;
                    }
                }
            }
            }
        }
    }
    
    
    cv::Mat1b img_gray;
    cv::cvtColor(img, img_gray, CV_BGR2GRAY);
    cv::threshold(img_gray, img_gray, 60, 255, CV_THRESH_BINARY);
    cv::morphologyEx(img_gray, img_gray, CV_MOP_CLOSE, cv::Mat1b(9,9,1), cv::Point(-1, -1), 1);

    cv::medianBlur(img_gray, img_gray, 23);
    skin = img_gray;

    return skin;
}

