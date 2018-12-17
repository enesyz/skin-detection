#pragma once

#define _OPENCV_FLANN_HPP_
#include <opencv/cv.h>

/// In this class you are supposed to implement
/// a model for skin color, i.e. after training
/// the model with a number of training images,
/// it should be able to classify pixels in an
/// unknown image as either skin or non-skin.
///
/// The training works as follows: 
///   1. call startTraining(); This resets/initializes the model.
///   2. call train(img, mask) for every training image/mask-pair in your training data
///   3. call finishTrainin(); This finalizes the model.
///
/// After the training is finished, you can call
///   classify(img)
/// with an (unknown*) test image as parameter in order to classify
/// each pixel as either skin or non-skin.
///
/// * = not contained the training set
class SkinModel
{
    class SkinModelPimpl;
    SkinModelPimpl *pimpl;
public:
    /// Constructor
    SkinModel();

    /// Destructor
    ~SkinModel();

    /// Start the training.  This resets/initializes the model.
    void startTraining();

    /// Add a new training image/mask pair.  The mask should
    /// denote the pixels in the training image that are of skin color.
    ///
    /// @param img:  input image
    /// @param mask: mask which specifies, which pixels are skin/non-skin
    void train(const cv::Mat3b& img, const cv::Mat1b& mask);

    /// Finish the training.  This finalizes the model.  Do not call
    /// train() afterwards anymore.
    void finishTraining();

    /// Classify an unknown test image.  The result is a probability
    /// mask denoting for each pixel how likely it is of skin color.
    ///
    /// @param img: unknown test image
    /// @return:    probability mask of skin color likelihood
    cv::Mat1b classify(const cv::Mat3b& img);
};
