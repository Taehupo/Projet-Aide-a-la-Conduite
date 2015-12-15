#include <cv.h>
#include <highgui.h>
using namespace std;

IplImage* imgTracking=0;

int lastX1 = -1;
int lastY1 = -1;

int lastX2 = -1;
int lastY2 = -1;

void trackObject(IplImage* imgThresh, int& ni){ //track the possition of the ball
  CvSeq* contour;  //hold the pointer to a contour
  CvSeq* result;     //hold sequence of points of a contour
  CvMemStorage *storage = cvCreateMemStorage(0); //storage area for all contours

  //finding all contours in the image
  cvFindContours(imgThresh, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

  //iterating through each contour
  while(contour)
  {
    //obtain a sequence of points of the countour, pointed by the variable 'countour'
    result = cvApproxPoly(contour, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contour)*0.02, 0);

    //if there are 3 vertices  in the contour and the area of the triangle is more than 100 pixels
    if(result->total==4 && fabs(cvContourArea(result, CV_WHOLE_SEQ))>100 )
    {
      //iterating through each point
      CvPoint *pt[4];
      for(int i=0;i<4;i++){
        pt[i] = (CvPoint*)cvGetSeqElem(result, i);
      }

      int posX=( pt[0]->x + pt[1]->x + pt[2]->x )/3;
      int posY=( pt[0]->y + pt[1]->y + pt[2]->y )/3;
      if (posY>400) {
        if(posX > 300 ){
          if(lastX1>=0 && lastY1>=0 && posX>=0 && posY>=0){
            // Draw a red line from the previous point to the current point
            cvLine(imgTracking, cvPoint(posX, posY), cvPoint(posX, posY), cvScalar(0,0,255), 10);
            cvLine(imgTracking, cvPoint(lastX1, lastY2), cvPoint(posX, posY), cvScalar(0,0,255),0);
          }

          ni++; cout << "++" << endl;
          lastX1 = posX;
          lastY1 = posY;  
        }
        else{
          if(lastX2>=0 && lastY2>=0 && posX>=0 && posY>=0){
            // Draw a blue line from the previous point to the current point
            cvLine(imgTracking, cvPoint(posX, posY), cvPoint(posX, posY), cvScalar(255,0,0), 10);
            cvLine(imgTracking, cvPoint(lastX2, lastY2), cvPoint(posX, posY), cvScalar(255,0,0),0);
          }

          lastX2 = posX;
          lastY2 = posY; 
        }
      }
    }


    //obtain the next contour
    contour = contour->h_next; 
  }

  cvReleaseMemStorage(&storage);
}


int main(){
	int i=0;
    //load the video file to the memory
    CvCapture *capture = cvCaptureFromAVI("v.mp4");

    if(!capture){
        printf("Capture failure\n");
        return -1;
    }
      
    IplImage* frame=0;
    
    frame = cvQueryFrame(capture); //On charge une frame       
    if(!frame) return -1;
   
    //create a blank image and assigned to 'imgTracking' which has the same size of original video
    imgTracking=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U, 3);
    cvZero(imgTracking); //covert the image, 'imgTracking' to black

    cvNamedWindow("Video");  
    
    cvNamedWindow("NB");
    //cvNamedWindow("Smooth");

    //iterate through each frames of the video     
    while(true){
		cout << i << endl;
        frame = cvQueryFrame(capture);
        if(!frame) break;
        frame=cvCloneImage(frame); 
         
        //smooth the original image using Gaussian kernel
        //cvSmooth(frame, frame, CV_GAUSSIAN,3,3);
        //cvShowImage("Smooth", frame);

        //converting the original image into grayscale
      IplImage* imgGrayScale = cvCreateImage(cvGetSize(frame), 8, 1); 
      cvCvtColor(frame,imgGrayScale,CV_BGR2GRAY);
        
       //thresholding the grayscale image to get better results
       cvThreshold(imgGrayScale,imgGrayScale,100,255,CV_THRESH_BINARY_INV); // Inversion binaire (NOIR/BLANC)
      
          cvShowImage("NB", imgGrayScale); //Affichage de l'image dans une fenetre
        
        //
        
        
        //track the possition of the ball
        trackObject(imgGrayScale, i); // fonction définie plus haut

        // Add the tracking image and the frame
        cvAdd(frame, imgTracking, frame); //On superpose les deux pour faire apparaitre les points
             
        cvShowImage("Video", frame);
        cvZero(imgTracking); // Supprimer les autres points
   
        //Clean up used images
        cvReleaseImage(&imgGrayScale); // destruction des images         
        cvReleaseImage(&frame);

        //Wait 10mS
        int c = cvWaitKey(15);//15
        //If 'ESC' is pressed, break the loop
        if((char)c==27 ) break;      
    }

    cvDestroyAllWindows();
    cvReleaseImage(&imgTracking);
    cvReleaseCapture(&capture);     

    return 0;
}
