#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{

    Mat imgOriginal;
    imgOriginal = imread("test2.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! imgOriginal.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

      int iLowH = 0;
     int iHighH = 179;

      int iLowS = 0; 
     int iHighS = 255;

      int iLowV = 0;
     int iHighV = 255;

      //Create trackbars in "Control" window
     cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
     cvCreateTrackbar("HighH", "Control", &iHighH, 179);

      cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
     cvCreateTrackbar("HighS", "Control", &iHighS, 255);

      cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
     cvCreateTrackbar("HighV", "Control", &iHighV, 255);

      while (true)
            {
            Mat dessins = imgOriginal.clone();
            Mat imgHSV;

           cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
         
          Mat imgThresholded;

           inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
              
          //morphological opening (remove small objects from the foreground)
          erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
          dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

           //morphological closing (fill small holes in the foreground)
          dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
          erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5,  5)) );

              vector<Vec3f> circles;

              /// Apply the Hough Transform to find the circles
              HoughCircles( imgThresholded, circles, CV_HOUGH_GRADIENT, 1, imgThresholded.rows/8, 200, 25, 10, 50 );

              /// Draw the circles detected
              for( size_t i = 0; i < circles.size(); i++ )
              {
                  Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
                  int radius = cvRound(circles[i][2]);
                  // circle center
                  circle( dessins, center, 3, Scalar(0,255,0), -1, 8, 0 );
                  // circle outline
                  circle( dessins, center, radius, Scalar(0,0,255), 3, 8, 0 );
               }



           imshow("Thresholded Image", imgThresholded); //show the thresholded image
          imshow("Original", dessins); //show the original image

                if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
               {
                    cout << "esc key is pressed by user" << endl;
                    break; 
               }

            

        }

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}