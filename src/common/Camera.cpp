#include "Camera.h"


namespace MapGen{
    Camera::Camera(const CameraParameters &params) {
        params_ = params;
    }

	CameraParameters Camera::get_camera_params() const {
		return params_;
	}

    cv::Mat Camera::get_intrinsic_matrix() const{
    	cv::Mat K = cv::Mat::zeros(3,3,CV_64F);

    	K.at<double>(0,0) = params_.fx;
    	K.at<double>(1,1) = params_.fy;
    	K.at<double>(0,2) = params_.cx;
    	K.at<double>(1,2) = params_.cy;
    	K.at<double>(2,2) = 1;

    	return K;
    }

	// initialize a dummy one
	Camera::Camera():params_() {}
}