#include "calib_c.h"

int cveEstimateAffine3D(
	cv::_InputArray* src, cv::_InputArray* dst,
	cv::_OutputArray* out, cv::_OutputArray* inliers,
	double ransacThreshold, double confidence)
{
#ifdef HAVE_OPENCV_CALIB
	return cv::estimateAffine3D(*src, *dst, *out, *inliers, ransacThreshold, confidence);
#else
	throw_no_calib();
#endif
}



//2D tracker
bool getHomographyMatrixFromMatchedFeatures(std::vector<cv::KeyPoint>* model, std::vector<cv::KeyPoint>* observed, std::vector< std::vector< cv::DMatch > >* matches, cv::Mat* mask, double randsacThreshold, cv::Mat* homography)
{
#ifdef HAVE_OPENCV_CALIB
	//cv::Mat_<int> indMat = (cv::Mat_<int>) cv::cvarrToMat(indices);

	cv::Mat_<uchar> maskMat = mask ? static_cast<cv::Mat_<uchar>>(*mask) : cv::Mat_<uchar>(matches->size(), 1, 255);
	int nonZero = mask ? cv::countNonZero(maskMat) : matches->size();
	if (nonZero < 4) return false;

	std::vector<cv::Point2f> srcPtVec;
	std::vector<cv::Point2f> dstPtVec;

	for (int i = 0; i < maskMat.rows; i++)
	{
		if (maskMat.at<uchar>(i))
		{
			int modelIdx = matches->at(i).at(0).trainIdx; //indMat(i, 0); 
			srcPtVec.push_back((*model)[modelIdx].pt);
			dstPtVec.push_back((*observed)[i].pt);
		}
	}

	//cv::Mat_<uchar> ransacMask(srcPtVec.size(), 1);
	std::vector<uchar> ransacMask;
	cv::Mat result = cv::findHomography(cv::Mat(srcPtVec), cv::Mat(dstPtVec), cv::RANSAC, randsacThreshold, ransacMask);
	if (result.empty())
	{
		return false;
	}
	cv::swap(result, *homography);

	int idx = 0;
	for (int i = 0; i < maskMat.rows; i++)
	{
		uchar* val = maskMat.ptr<uchar>(i);
		if (*val)
			*val = ransacMask[idx++];
	}
	return true;
#else
	throw_no_calib();
#endif
}

bool cveFindCirclesGrid(cv::_InputArray* image, CvSize* patternSize, cv::_OutputArray* centers, int flags, cv::Feature2D* blobDetector)
{
#ifdef HAVE_OPENCV_CALIB
	cv::Ptr<cv::Feature2D> ptr(blobDetector, [](cv::Feature2D*){});
	return cv::findCirclesGrid(*image, *patternSize, *centers, flags, ptr);
#else
	throw_no_calib();
#endif
}

void cveTriangulatePoints(cv::_InputArray* projMat1, cv::_InputArray* projMat2, cv::_InputArray* projPoints1, cv::_InputArray* projPoints2, cv::_OutputArray* points4D)
{
#ifdef HAVE_OPENCV_CALIB
	cv::triangulatePoints(*projMat1, *projMat2, *projPoints1, *projPoints2, *points4D);
#else
	throw_no_calib();
#endif
}

void cveCorrectMatches(cv::_InputArray* f, cv::_InputArray* points1, cv::_InputArray* points2, cv::_OutputArray* newPoints1, cv::_OutputArray* newPoints2)
{
#ifdef HAVE_OPENCV_CALIB
	cv::correctMatches(*f, *points1, *points2, *newPoints1, *newPoints2);
#else
	throw_no_calib();
#endif
}

bool cveFindChessboardCornersSB(cv::_InputArray* image, CvSize* patternSize, cv::_OutputArray* corners, int flags)
{
#ifdef HAVE_OPENCV_CALIB
	return cv::findChessboardCornersSB(*image, *patternSize, *corners, flags);
#else
	throw_no_calib();
#endif
}

void cveEstimateChessboardSharpness(
	cv::_InputArray* image,
	CvSize* patternSize,
	cv::_InputArray* corners,
	float riseDistance,
	bool vertical,
	cv::_OutputArray* sharpness,
	CvScalar* result)
{
#ifdef HAVE_OPENCV_CALIB
	cv::Scalar r = cv::estimateChessboardSharpness(*image, *patternSize, *corners, riseDistance, vertical, sharpness ? *sharpness : static_cast<cv::OutputArray>(cv::noArray())) ;
	result->val[0] = r.val[0];
	result->val[1] = r.val[1];
	result->val[2] = r.val[2];
	result->val[3] = r.val[3];
#else
	throw_no_calib();
#endif
}

void cveDrawChessboardCorners(cv::_InputOutputArray* image, CvSize* patternSize, cv::_InputArray* corners, bool patternWasFound)
{
#ifdef HAVE_OPENCV_CALIB
	cv::drawChessboardCorners(*image, *patternSize, *corners, patternWasFound);
#else
	throw_no_calib();
#endif
}

void cveFilterSpeckles(cv::_InputOutputArray* img, double newVal, int maxSpeckleSize, double maxDiff, cv::_InputOutputArray* buf)
{
#ifdef HAVE_OPENCV_CALIB
	cv::filterSpeckles(*img, newVal, maxSpeckleSize, maxDiff, buf ? *buf : static_cast<cv::_InputOutputArray>(cv::noArray()));
#else
	throw_no_calib();
#endif
}

bool cveFindChessboardCorners(cv::_InputArray* image, CvSize* patternSize, cv::_OutputArray* corners, int flags)
{
#ifdef HAVE_OPENCV_CALIB
	return cv::findChessboardCorners(*image, *patternSize, *corners, flags);
#else
	throw_no_calib();
#endif
}

bool cveFind4QuadCornerSubpix(cv::_InputArray* image, cv::_InputOutputArray* corners, CvSize* regionSize)
{
#ifdef HAVE_OPENCV_CALIB
	return cv::find4QuadCornerSubpix(*image, *corners, *regionSize);
#else
	throw_no_calib();
#endif
}

void cveRodrigues(cv::_InputArray* src, cv::_OutputArray* dst, cv::_OutputArray* jacobian)
{
#ifdef HAVE_OPENCV_CALIB
	cv::Rodrigues(*src, *dst, jacobian ? *jacobian : static_cast<cv::OutputArray>(cv::noArray()));
#else
	throw_no_calib();
#endif
}

double cveCalibrateCamera(
	cv::_InputArray* objectPoints, cv::_InputArray* imagePoints, CvSize* imageSize,
	cv::_InputOutputArray* cameraMatrix, cv::_InputOutputArray* distCoeffs,
	cv::_OutputArray* rvecs, cv::_OutputArray* tvecs, int flags, CvTermCriteria* criteria)
{
#ifdef HAVE_OPENCV_CALIB
	return cv::calibrateCamera(*objectPoints, *imagePoints, *imageSize, *cameraMatrix, *distCoeffs, *rvecs, *tvecs, flags, *criteria);
#else
	throw_no_calib();
#endif
}

void cveReprojectImageTo3D(cv::_InputArray* disparity, cv::_OutputArray* threeDImage, cv::_InputArray* q, bool handleMissingValues, int ddepth)
{
#ifdef HAVE_OPENCV_CALIB
	cv::reprojectImageTo3D(*disparity, *threeDImage, *q, handleMissingValues, ddepth);
#else
	throw_no_calib();
#endif
}

void cveConvertPointsToHomogeneous(cv::_InputArray* src, cv::_OutputArray* dst)
{
#ifdef HAVE_OPENCV_CALIB
	cv::convertPointsToHomogeneous(*src, *dst);
#else
	throw_no_calib();
#endif
}

void cveConvertPointsFromHomogeneous(cv::_InputArray* src, cv::_OutputArray* dst)
{
#ifdef HAVE_OPENCV_CALIB
	cv::convertPointsFromHomogeneous(*src, *dst);
#else
	throw_no_calib();
#endif
}

void cveFindEssentialMat(
	cv::_InputArray* points1, 
	cv::_InputArray* points2, 
	cv::_InputArray* cameraMatrix, 
	int method, 
	double prob, 
	double threshold,
	int maxIter,
	cv::_OutputArray* mask, 
	cv::Mat* essentialMat)
{
#ifdef HAVE_OPENCV_CALIB
	cv::Mat res = cv::findEssentialMat(
		*points1, 
		*points2, 
		*cameraMatrix, 
		method, 
		prob, 
		threshold,
		maxIter,
		mask ? *mask : static_cast<cv::OutputArray>(cv::noArray()));
	cv::swap(res, *essentialMat);
#else
	throw_no_calib();
#endif
}

void cveFindFundamentalMat(cv::_InputArray* points1, cv::_InputArray* points2, cv::_OutputArray* dst, int method, double param1, double param2, cv::_OutputArray* mask)
{
#ifdef HAVE_OPENCV_CALIB
	cv::Mat tmp = cv::findFundamentalMat(
		*points1, 
		*points2, 
		method, 
		param1, 
		param2, 
		mask ? *mask : static_cast<cv::OutputArray>(cv::noArray()));
	tmp.copyTo(*dst);
#else
	throw_no_calib();
#endif
}

void cveFindHomography(cv::_InputArray* srcPoints, cv::_InputArray* dstPoints, cv::_OutputArray* dst, int method, double ransacReprojThreshold, cv::_OutputArray* mask)
{
#ifdef HAVE_OPENCV_CALIB
	cv::Mat tmp = cv::findHomography(
		*srcPoints, 
		*dstPoints, 
		method, 
		ransacReprojThreshold, 
		mask ? *mask : static_cast<cv::OutputArray>(cv::noArray()));
	tmp.copyTo(*dst);
#else
	throw_no_calib();
#endif
}

void cveComputeCorrespondEpilines(cv::_InputArray* points, int whichImage, cv::_InputArray* f, cv::_OutputArray* lines)
{
#ifdef HAVE_OPENCV_CALIB
	cv::computeCorrespondEpilines(*points, whichImage, *f, *lines);
#else
	throw_no_calib();
#endif
}

void cveProjectPoints(
	cv::_InputArray* objPoints, cv::_InputArray* rvec, cv::_InputArray* tvec, cv::_InputArray* cameraMatrix, cv::_InputArray* distCoeffs,
	cv::_OutputArray* imagePoints, cv::_OutputArray* jacobian, double aspectRatio)
{
#ifdef HAVE_OPENCV_CALIB
	cv::projectPoints(
		*objPoints, 
		*rvec, *tvec, 
		*cameraMatrix, 
		distCoeffs ? *distCoeffs : static_cast<cv::InputArray>(cv::noArray()), 
		*imagePoints, 
		jacobian ? *jacobian : static_cast<cv::OutputArray>(cv::noArray()), aspectRatio);
#else
	throw_no_calib();
#endif
}

void cveCalibrationMatrixValues(
	cv::_InputArray* cameraMatrix, CvSize* imageSize, double apertureWidth, double apertureHeight,
	double* fovx, double* fovy, double* focalLength, CvPoint2D64f* principalPoint, double* aspectRatio)
{
#ifdef HAVE_OPENCV_CALIB
	double _fovx, _fovy, _focalLength, _aspectRatio;
	cv::Point2d _principalPoint;

	cv::calibrationMatrixValues(*cameraMatrix, *imageSize, apertureWidth, apertureHeight, _fovx, _fovy, _focalLength, _principalPoint, _aspectRatio);
	*fovx = _fovx;
	*fovy = _fovy;
	*focalLength = _focalLength;
	*aspectRatio = _aspectRatio;
	principalPoint->x = _principalPoint.x;
	principalPoint->y = _principalPoint.y;
#else
	throw_no_calib();
#endif
}

double cveStereoCalibrate(
	cv::_InputArray* objectPoints, cv::_InputArray* imagePoints1, cv::_InputArray* imagePoints2,
	cv::_InputOutputArray* cameraMatrix1, cv::_InputOutputArray* distCoeffs1, cv::_InputOutputArray* cameraMatrix2, cv::_InputOutputArray* distCoeffs2,
	CvSize* imageSize, cv::_OutputArray* r, cv::_OutputArray* t, cv::_OutputArray* e, cv::_OutputArray* f, int flags, CvTermCriteria* criteria)
{
#ifdef HAVE_OPENCV_CALIB
	return cv::stereoCalibrate(*objectPoints, *imagePoints1, *imagePoints2, *cameraMatrix1, *distCoeffs1, *cameraMatrix2, *distCoeffs2, *imageSize, *r, *t, *e, *f,
		flags, *criteria);
#else
	throw_no_calib();
#endif
}

bool cveSolvePnP(cv::_InputArray* objectPoints, cv::_InputArray* imagePoints, cv::_InputArray* cameraMatrix, cv::_InputArray* distCoeffs, cv::_OutputArray* rvec, cv::_OutputArray* tvec, bool useExtrinsicGuess, int flags)
{
#ifdef HAVE_OPENCV_CALIB
	return cv::solvePnP(*objectPoints, *imagePoints, *cameraMatrix, *distCoeffs, *rvec, *tvec, useExtrinsicGuess, flags);
#else
	throw_no_calib();
#endif
}

bool cveSolvePnPRansac(
	cv::_InputArray* objectPoints, 
	cv::_InputArray* imagePoints, 
	cv::_InputArray* cameraMatrix, 
	cv::_InputArray* distCoeffs, 
	cv::_OutputArray* rvec, 
	cv::_OutputArray* tvec, 
	bool useExtrinsicGuess, 
	int iterationsCount, 
	float reprojectionError, 
	double confident, 
	cv::_OutputArray* inliers, 
	int flags)
{
#ifdef HAVE_OPENCV_CALIB
	return cv::solvePnPRansac(
		*objectPoints,
		*imagePoints,
		*cameraMatrix,
		distCoeffs ? *distCoeffs : static_cast<cv::InputArray>(cv::noArray()),
		*rvec,
		*tvec,
		useExtrinsicGuess,
		iterationsCount,
		reprojectionError,
		confident,
		inliers ? *inliers : static_cast<cv::OutputArray>(cv::noArray()),
		flags);
#else
	throw_no_calib();
#endif
}

int cveSolveP3P(
	cv::_InputArray* objectPoints,
	cv::_InputArray* imagePoints,
	cv::_InputArray* cameraMatrix,
	cv::_InputArray* distCoeffs,
	cv::_OutputArray* rvecs,
	cv::_OutputArray* tvecs,
	int flags)
{
#ifdef HAVE_OPENCV_CALIB
	return cv::solveP3P(*objectPoints, *imagePoints, *cameraMatrix, *distCoeffs, *rvecs, *tvecs, flags);
#else
	throw_no_calib();
#endif
}

void cveSolvePnPRefineLM(
	cv::_InputArray* objectPoints,
	cv::_InputArray* imagePoints,
	cv::_InputArray* cameraMatrix,
	cv::_InputArray* distCoeffs,
	cv::_InputOutputArray* rvec,
	cv::_InputOutputArray* tvec,
	CvTermCriteria* criteria)
{
#ifdef HAVE_OPENCV_CALIB
	cv::solvePnPRefineLM(
		*objectPoints, 
		*imagePoints, 
		*cameraMatrix, 
		distCoeffs ? *distCoeffs : static_cast<cv::InputArray>(cv::noArray()), 
		*rvec, 
		*tvec, 
		*criteria);
#else
	throw_no_calib();
#endif
}

void cveSolvePnPRefineVVS(
	cv::_InputArray* objectPoints,
	cv::_InputArray* imagePoints,
	cv::_InputArray* cameraMatrix,
	cv::_InputArray* distCoeffs,
	cv::_InputOutputArray* rvec,
	cv::_InputOutputArray* tvec,
	CvTermCriteria* criteria,
	double VVSlambda)
{
#ifdef HAVE_OPENCV_CALIB
	cv::solvePnPRefineVVS(
		*objectPoints, 
		*imagePoints, 
		*cameraMatrix, 
		distCoeffs ? *distCoeffs : static_cast<cv::InputArray>(cv::noArray()),
		*rvec, 
		*tvec, 
		*criteria, 
		VVSlambda);
#else
	throw_no_calib();
#endif
}

int cveSolvePnPGeneric(
	cv::_InputArray* objectPoints,
	cv::_InputArray* imagePoints,
	cv::_InputArray* cameraMatrix,
	cv::_InputArray* distCoeffs,
	cv::_OutputArray* rvecs,
	cv::_OutputArray* tvecs,
	bool useExtrinsicGuess,
	int flags,
	cv::_InputArray* rvec,
	cv::_InputArray* tvec,
	cv::_OutputArray* reprojectionError)
{
#ifdef HAVE_OPENCV_CALIB
	return cv::solvePnPGeneric(
		*objectPoints, 
		*imagePoints, 
		*cameraMatrix, 
		*distCoeffs, 
		*rvecs, 
		*tvecs, 
		useExtrinsicGuess, 
		static_cast<cv::SolvePnPMethod>(flags), 
		rvec ? *rvec : static_cast<cv::InputArray>(cv::noArray()), 
		tvec ? *tvec : static_cast<cv::InputArray>(cv::noArray()), 
		reprojectionError ? *reprojectionError: static_cast<cv::OutputArray>(cv::noArray()));
#else
	throw_no_calib();
#endif
}


void cveGetOptimalNewCameraMatrix(
	cv::_InputArray* cameraMatrix, cv::_InputArray* distCoeffs,
	CvSize* imageSize, double alpha, CvSize* newImgSize,
	CvRect* validPixROI,
	bool centerPrincipalPoint,
	cv::Mat* newCameraMatrix)
{
#ifdef HAVE_OPENCV_CALIB
	cv::Rect r;
	cv::Mat m = cv::getOptimalNewCameraMatrix(
		*cameraMatrix, 
		distCoeffs ? *distCoeffs : static_cast<cv::InputArray>(cv::noArray()),
		*imageSize, 
		alpha, 
		*newImgSize,
		&r, 
		centerPrincipalPoint);
	if (validPixROI)
	{
		validPixROI->x = r.x;
		validPixROI->y = r.y;
		validPixROI->width = r.width;
		validPixROI->height = r.height;
	}
	cv::swap(m, *newCameraMatrix);
#else
	throw_no_calib();
#endif
}

void cveInitCameraMatrix2D(
	cv::_InputArray* objectPoints,
	cv::_InputArray* imagePoints,
	CvSize* imageSize,
	double aspectRatio,
	cv::Mat* cameraMatrix)
{
#ifdef HAVE_OPENCV_CALIB
	cv::Mat m = cv::initCameraMatrix2D(*objectPoints, *imagePoints, *imageSize, aspectRatio);
	cv::swap(m, *cameraMatrix);
#else
	throw_no_calib();
#endif
}

/* Fisheye calibration */
void cveFisheyeProjectPoints(cv::_InputArray* objectPoints, cv::_OutputArray* imagePoints, cv::_InputArray* rvec, cv::_InputArray* tvec,
	cv::_InputArray* K, cv::_InputArray* D, double alpha, cv::_OutputArray* jacobian)
{
#ifdef HAVE_OPENCV_CALIB
	cv::fisheye::projectPoints(
		*objectPoints, 
		*imagePoints, 
		*rvec, 
		*tvec, 
		*K, 
		*D, 
		alpha, 
		jacobian ? *jacobian : static_cast<cv::OutputArray>(cv::noArray()));
#else
	throw_no_calib();
#endif
}

void cveFisheyeDistortPoints(cv::_InputArray* undistored, cv::_OutputArray* distorted, cv::_InputArray* K, cv::_InputArray* D, double alpha)
{
#ifdef HAVE_OPENCV_CALIB
	cv::fisheye::distortPoints(*undistored, *distorted, *K, *D, alpha);
#else
	throw_no_calib();
#endif
}

void cveFisheyeUndistortPoints(cv::_InputArray* distorted, cv::_OutputArray* undistorted, cv::_InputArray* K, cv::_InputArray* D, cv::_InputArray* R, cv::_InputArray* P)
{
#ifdef HAVE_OPENCV_CALIB
	cv::fisheye::undistortPoints(
		*distorted, 
		*undistorted, 
		*K, 
		*D, 
		R ? *R : static_cast<cv::InputArray>(cv::noArray()), 
		P ? *P : static_cast<cv::InputArray>(cv::noArray()));
#else
	throw_no_calib();
#endif
}

void cveFisheyeInitUndistortRectifyMap(
	cv::_InputArray* K, 
	cv::_InputArray* D, 
	cv::_InputArray* R, 
	cv::_InputArray* P, 
	CvSize* size, 
	int m1Type, 
	cv::_OutputArray* map1, 
	cv::_OutputArray* map2)
{
#ifdef HAVE_OPENCV_CALIB
	cv::fisheye::initUndistortRectifyMap(
		*K, 
		*D, 
		*R, 
		*P, 
		*size, 
		m1Type, 
		*map1, 
		map2 ? *map2 : static_cast<cv::OutputArray>(cv::noArray()));
#else
	throw_no_calib();
#endif
}

void cveFisheyeUndistortImage(cv::_InputArray* distorted, cv::_OutputArray* undistored, cv::_InputArray* K, cv::_InputArray* D, cv::_InputArray* Knew, CvSize* newSize)
{
#ifdef HAVE_OPENCV_CALIB
	cv::fisheye::undistortImage(
		*distorted, 
		*undistored, 
		*K, 
		*D, 
		Knew ? *Knew : static_cast<cv::InputArray>(cv::noArray()), 
		*newSize);
#else
	throw_no_calib();
#endif
}

void cveFisheyeEstimateNewCameraMatrixForUndistortRectify(cv::_InputArray* K, cv::_InputArray* D, CvSize* imageSize, cv::_InputArray* R, cv::_OutputArray* P, double balance, CvSize* newSize, double fovScale)
{
#ifdef HAVE_OPENCV_CALIB
	cv::fisheye::estimateNewCameraMatrixForUndistortRectify(*K, *D, *imageSize, *R, *P, balance, *newSize, fovScale);
#else
	throw_no_calib();
#endif
}

void cveFisheyeStereoRectify(cv::_InputArray* K1, cv::_InputArray*D1, cv::_InputArray* K2, cv::_InputArray* D2, CvSize* imageSize,
	cv::_InputArray* R, cv::_InputArray* tvec, cv::_OutputArray* R1, cv::_OutputArray* R2, cv::_OutputArray* P1, cv::_OutputArray* P2, cv::_OutputArray* Q, int flags,
	CvSize* newImageSize, double balance, double fovScale)
{
#ifdef HAVE_OPENCV_CALIB
	cv::fisheye::stereoRectify(*K1, *D1, *K2, *D2, *imageSize, *R, *tvec, *R1, *R2, *P1, *P2, *Q, flags, *newImageSize, balance, fovScale);
#else
	throw_no_calib();
#endif
}

double cveFisheyeCalibrate(cv::_InputArray* objectPoints, cv::_InputArray* imagePoints, CvSize* imageSize,
	cv::_InputOutputArray* K, cv::_InputOutputArray* D, cv::_OutputArray* rvecs, cv::_OutputArray* tvecs, int flags,
	CvTermCriteria* criteria)
{
#ifdef HAVE_OPENCV_CALIB
	return cv::fisheye::calibrate(*objectPoints, *imagePoints, *imageSize, *K, *D, *rvecs, *tvecs, flags, *criteria);
#else
	throw_no_calib();
#endif
}

double cveFisheyeStereoCalibrate(cv::_InputArray* objectPoints, cv::_InputArray* imagePoints1,
	cv::_InputArray* imagePoints2, cv::_InputOutputArray* K1, cv::_InputOutputArray* D1, cv::_InputOutputArray* K2, cv::_InputOutputArray* D2,
	CvSize* imageSize, cv::_OutputArray* R, cv::_OutputArray* T, int flags, CvTermCriteria* criteria)
{
#ifdef HAVE_OPENCV_CALIB
	return cv::fisheye::stereoCalibrate(*objectPoints, *imagePoints1, *imagePoints2, *K1, *D1, *K2, *D2, *imageSize, *R, *T, flags, *criteria);
#else
	throw_no_calib();
#endif
}

void cveInitUndistortRectifyMap(cv::_InputArray* cameraMatrix, cv::_InputArray* distCoeffs, cv::_InputArray* r, cv::_InputArray* newCameraMatrix, CvSize* size, int m1type, cv::_OutputArray* map1, cv::_OutputArray* map2)
{
#ifdef HAVE_OPENCV_CALIB
	cv::initUndistortRectifyMap(
		*cameraMatrix, *distCoeffs, 
		r ? *r : static_cast<cv::_InputArray>(cv::noArray()), 
		*newCameraMatrix, 
		*size, 
		m1type, 
		*map1, 
		map2 ? *map2 : static_cast<cv::OutputArray>(cv::noArray()));
#else
	throw_no_calib();
#endif
}

void cveUndistort(cv::_InputArray* src, cv::_OutputArray* dst, cv::_InputArray* cameraMatrix, cv::_InputArray* distorCoeffs, cv::_InputArray* newCameraMatrix)
{
#ifdef HAVE_OPENCV_CALIB
	cv::undistort(
		*src, 
		*dst, 
		*cameraMatrix, 
		*distorCoeffs, 
		newCameraMatrix ? *newCameraMatrix : static_cast<cv::InputArray>(cv::noArray()));
#else
	throw_no_calib();
#endif
}

void cveUndistortPoints(cv::_InputArray* src, cv::_OutputArray* dst, cv::_InputArray* cameraMatrix, cv::_InputArray* distCoeffs, cv::_InputArray* r, cv::_InputArray* p)
{
#ifdef HAVE_OPENCV_CALIB
	cv::undistortPoints(
		*src, 
		*dst, 
		*cameraMatrix, 
		*distCoeffs, 
		r ? *r : static_cast<cv::InputArray>(cv::noArray()), 
		p ? *p : static_cast<cv::InputArray>(cv::noArray()));
#else
	throw_no_calib();
#endif
}

void cveGetDefaultNewCameraMatrix(cv::_InputArray* cameraMatrix, CvSize* imgsize, bool centerPrincipalPoint, cv::Mat* cm)
{
#ifdef HAVE_OPENCV_CALIB
	cv::Mat res = cv::getDefaultNewCameraMatrix(*cameraMatrix, *imgsize, centerPrincipalPoint);
	cv::swap(*cm, res);
#else
	throw_no_calib();
#endif
}

void cveEstimateAffine2D(
	cv::_InputArray* from, cv::_InputArray* to,
	cv::_OutputArray* inliners,
	int method, double ransacReprojThreshold,
	int maxIters, double confidence,
	int refineIters,
	cv::Mat* affine)
{
#ifdef HAVE_OPENCV_CALIB
	cv::Mat m = cv::estimateAffine2D(
		*from, *to, 
		inliners ? *inliners : static_cast<cv::OutputArray>(cv::noArray()), 
		method, ransacReprojThreshold, maxIters, confidence, refineIters);
	cv::swap(m, *affine);
#else
	throw_no_calib();
#endif
}

void cveEstimateAffinePartial2D(
	cv::_InputArray* from, cv::_InputArray* to,
	cv::_OutputArray* inliners,
	int method, double ransacReprojThreshold,
	int maxIters, double confidence,
	int refineIters,
	cv::Mat* affine)
{
#ifdef HAVE_OPENCV_CALIB
	cv::Mat m = cv::estimateAffinePartial2D(
		*from, *to,
		inliners ? *inliners : static_cast<cv::OutputArray>(cv::noArray()),
		method, ransacReprojThreshold, maxIters, confidence, refineIters);
	cv::swap(m, *affine);
#else
	throw_no_calib();
#endif
}

void cveCalibrateHandEye(
	cv::_InputArray* R_gripper2base, cv::_InputArray* t_gripper2base,
	cv::_InputArray* R_target2cam, cv::_InputArray* t_target2cam,
	cv::_OutputArray* R_cam2gripper, cv::_OutputArray* t_cam2gripper,
	int method)
{
#ifdef HAVE_OPENCV_CALIB
	cv::calibrateHandEye(
		*R_gripper2base, *t_gripper2base,
		*R_target2cam, *t_target2cam,
		*R_cam2gripper, *t_cam2gripper,
		static_cast<cv::HandEyeCalibrationMethod>(method));
#else
	throw_no_calib();
#endif
}

void cveRQDecomp3x3(
	cv::_InputArray* src,
	CvPoint3D64f* out,
	cv::_OutputArray* mtxR,
	cv::_OutputArray* mtxQ,
	cv::_OutputArray* Qx,
	cv::_OutputArray* Qy,
	cv::_OutputArray* Qz)
{
#ifdef HAVE_OPENCV_CALIB
	cv::Vec3d result = cv::RQDecomp3x3(
		*src,
		*mtxR,
		*mtxQ,
		Qx ? *Qx : static_cast<cv::OutputArray>(cv::noArray()),
		Qy ? *Qy : static_cast<cv::OutputArray>(cv::noArray()),
		Qz ? *Qz : static_cast<cv::OutputArray>(cv::noArray())
	);
	out->x = result[0];
	out->y = result[1];
	out->z = result[2];
#else
	throw_no_calib();
#endif
}

void cveDecomposeProjectionMatrix(
	cv::_InputArray* projMatrix,
	cv::_OutputArray* cameraMatrix,
	cv::_OutputArray* rotMatrix,
	cv::_OutputArray* transVect,
	cv::_OutputArray* rotMatrixX,
	cv::_OutputArray* rotMatrixY,
	cv::_OutputArray* rotMatrixZ,
	cv::_OutputArray* eulerAngles)
{
#ifdef HAVE_OPENCV_CALIB
	cv::decomposeProjectionMatrix(
		*projMatrix,
		*cameraMatrix,
		*rotMatrix,
		*transVect,
		rotMatrixX ? *rotMatrixX : static_cast<cv::_OutputArray>(cv::noArray()),
		rotMatrixY ? *rotMatrixY : static_cast<cv::_OutputArray>(cv::noArray()),
		rotMatrixZ ? *rotMatrixZ : static_cast<cv::_OutputArray>(cv::noArray()),
		eulerAngles ? *eulerAngles : static_cast<cv::_OutputArray>(cv::noArray())
	);
#else
	throw_no_calib();
#endif
}