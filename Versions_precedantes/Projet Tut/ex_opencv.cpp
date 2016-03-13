#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <ctime>
#include <ratio>

using namespace std;
using namespace std::chrono;

IplImage* imgTracking=0;

CvFont font;
double hScale=1.0;
double vScale=1.0;
int    lineWidth=1;

bool grid=false;

int lastX1 = -1;
int lastY1 = -1;

int lastX2 = -1;
int lastY2 = -1;

duration<double> time_span;
high_resolution_clock::time_point t12, t22;

double vitesse [3] = {100};
double vitesse_lue;
double avg = 100;
float taille_ligne = 13;

unsigned int lastElem = 0;
unsigned int cpt=0;

unsigned int readArea [3];

void avgSpeed () {
  cout << "avgSpeed" << endl;
  avg=0;
  for (unsigned int i=0; i<3; ++i)
    avg += vitesse[i];
  avg/=3;
  //cout << "avg  "<<avg;
}

const string doubleToStr(double x){
  stringstream ss;
  ss << x;
  return ss.str();
}

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

      int posX=( pt[0]->x + pt[1]->x + pt[2]->x +pt[3]->x )/4;
      int posY=( pt[0]->y + pt[1]->y + pt[2]->y +pt[3]->y )/4;
      if (posY>400) {
        if(posX > 300 && posX < 600 ){
          if(lastX1>=0 && lastY1>=0 && posX>=0 && posY>=0){
            // Draw a red line from the previous point to the current point
            cvLine(imgTracking, cvPoint(posX, posY), cvPoint(posX, posY), cvScalar(0,0,255), 10);
            
            cvLine(imgTracking, cvPoint(pt[0]->x, pt[0]->y), cvPoint(pt[1]->x, pt[1]->y), cvScalar(0,0,255),4);
            cvLine(imgTracking, cvPoint(pt[1]->x, pt[1]->y), cvPoint(pt[2]->x, pt[2]->y), cvScalar(0,0,255),4);
            cvLine(imgTracking, cvPoint(pt[2]->x, pt[2]->y), cvPoint(pt[3]->x, pt[3]->y), cvScalar(0,0,255),4);
            cvLine(imgTracking, cvPoint(pt[3]->x, pt[3]->y), cvPoint(pt[0]->x, pt[3]->y), cvScalar(0,0,255),4);

            if (lastY1-posY>0) { // Si on change de ligne (sur la même file)

              time_span = duration_cast<duration<double>> (high_resolution_clock::now() - t12); // Calcul du temps
              t12 = high_resolution_clock::now(); // Prise du nouveau temps 
              vitesse_lue = taille_ligne/double(time_span.count())*3.6; //calcul de la vitesse taille_ligne(ligne+noir)/temps*conversion_M/S_Km/h
              
              if (vitesse_lue<((cpt++>2)?vitesse_lue:avg)*1.25 && vitesse_lue>((cpt++>2)?vitesse_lue:avg)*0.75 && vitesse_lue<200)
              {
                vitesse[lastElem%3] = vitesse_lue;
                lastElem++;
                avgSpeed();
                std::cout << "New line " << lastY1-posY <<  " " << time_span.count() << " Vitesse : " << avg << std::endl;
              }
                
            }
          }

          //ni++; cout << "++" << endl;
          lastX1 = posX;
          lastY1 = posY;  
        }
        else{
          if(lastX2>=0 && lastY2>=0 && posX>=0 && posY>=0){
            // Draw a blue line from the previous point to the current point
            cvLine(imgTracking, cvPoint(posX, posY), cvPoint(posX, posY), cvScalar(255,0,0), 10);

            cvLine(imgTracking, cvPoint(pt[0]->x, pt[0]->y), cvPoint(pt[1]->x, pt[1]->y), cvScalar(255,0,0),4);
            cvLine(imgTracking, cvPoint(pt[1]->x, pt[1]->y), cvPoint(pt[2]->x, pt[2]->y), cvScalar(255,0,0),4);
            cvLine(imgTracking, cvPoint(pt[2]->x, pt[2]->y), cvPoint(pt[3]->x, pt[3]->y), cvScalar(255,0,0),4);
            cvLine(imgTracking, cvPoint(pt[3]->x, pt[3]->y), cvPoint(pt[0]->x, pt[3]->y), cvScalar(255,0,0),4);
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

void panneau(unsigned int xPos, unsigned int yPos) {
  cvLine(imgTracking, cvPoint(xPos,yPos), cvPoint(xPos+30,yPos), cvScalar(0,0,255),2);
  cvLine(imgTracking, cvPoint(xPos,yPos), cvPoint(xPos+15,yPos-30), cvScalar(0,0,255),2);
  cvLine(imgTracking, cvPoint(xPos+15,yPos-30), cvPoint(xPos+30,yPos), cvScalar(0,0,255),2);

  cvLine(imgTracking, cvPoint(xPos+15,yPos-22), cvPoint(xPos+15,yPos-10), cvScalar(0,0,255),2);
  cvLine(imgTracking, cvPoint(xPos+15,yPos-5), cvPoint(xPos+15,yPos-5), cvScalar(0,0,255),2);

}

void traceGrille() {
  for (unsigned int i=0; i<500; i+=100) {
    for (unsigned int j=0; j<1000; j+=100) {
      cvLine(imgTracking, cvPoint(j,0), cvPoint(j,1000), cvScalar(255,255,255),1);

    }
    cvLine(imgTracking, cvPoint(0,i), cvPoint(1000,i), cvScalar(255,255,255),1);
  }
}

int main(){
  cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX, 1,1);
	int i=0;
    //load the video file to the memory
    CvCapture *capture = cvCaptureFromAVI("b.mp4");

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
		//cout << i << endl;
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
        if (grid) traceGrille();

        //Affichage de la vidéo sur l'écran
        cvPutText (imgTracking,doubleToStr(int(avg)).c_str(),cvPoint(40,30), &font, cvScalar(0,(avg<=100)?255:0,(avg>100)?255:0)); //BGR
        if (avg>100) panneau(5,30);
        // Add the tracking image and the frame
        cvAdd(frame, imgTracking, frame); //On superpose les deux pour faire apparaitre les points

        cvShowImage("Video", frame);
        cvSaveImage("test.jpg", frame);
        cvZero(imgTracking); // Supprimer les autres points

        //Clean up used images
        cvReleaseImage(&imgGrayScale); // destruction des images         
        cvReleaseImage(&frame);

        //Wait 10mS
        int c = cvWaitKey(15);//15 30 30 30
        //If 'ESC' is pressed, break the loop
        if ((char)c==71 || (char)c==103) grid=!grid;
        if((char)c==27 ) break;
        
    }

    cvDestroyAllWindows();
    cvReleaseImage(&imgTracking);
    cvReleaseCapture(&capture);     

    return 0;
}
