#include "livevideo.h"
#include <stdio.h>
#include <iostream>

using namespace std;

liveVideo::~liveVideo()
{
}

void liveVideo::detectFace(QGraphicsView *smallGraphicsObjectOne,QGraphicsView *smallGrahicsObjectTwo)
{
          playStatus = false;

          allFaces = cvHaarDetectObjects( tmpImage, faceDetectCascade,
                                          tmpStorageFaceDetect,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) );
          if (allFaces->total >= 1)
          {
              CvRect * tmpFaceLocation = (CvRect *)cvGetSeqElem(allFaces,0);
              cvSetImageROI( tmpImage,cvRect( tmpFaceLocation->x,tmpFaceLocation->y,tmpFaceLocation->width,tmpFaceLocation->height ) );
              IplImage *faceToDisplay = cvCreateImage(cvSize( tmpFaceLocation->width,tmpFaceLocation->height),tmpImage->depth,
                                                      tmpImage->nChannels);
              cvCopy(tmpImage,faceToDisplay);
              cvResetImageROI(tmpImage);
              liveVideo::displayVideo(faceToDisplay,smallGraphicsObjectOne);
          };

          if (allFaces->total == 2)
          {

              CvRect * tmpFaceLocation = (CvRect *)cvGetSeqElem(allFaces,1);
              cvSetImageROI( tmpImage,cvRect( tmpFaceLocation->x,tmpFaceLocation->y,tmpFaceLocation->width,tmpFaceLocation->height ) );
              IplImage *faceToDisplay = cvCreateImage(cvSize( tmpFaceLocation->width,tmpFaceLocation->height),tmpImage->depth,
                                                      tmpImage->nChannels);
              cvCopy(tmpImage,faceToDisplay);
              cvResetImageROI(tmpImage);
              liveVideo::displayVideo(faceToDisplay,smallGrahicsObjectTwo);
          }

         /* else
          {
              smallGrahicsObjectTwo->scene()->clear();
          }*/

         playStatus = true;
}

void liveVideo::startCapture()
{
       liveCapture = cvCaptureFromCAM(0);
       for(;;)
       {
            tmpImage = cvQueryFrame(liveCapture);

            if( tmpImage && (playStatus) )
            {
                cvWaitKey(30);
            }
            else
            {
                break;
            }
       }


}

void liveVideo::stopCapture()
{
    cvReleaseCapture( &liveCapture );
}
void liveVideo::initliveVideo()
{
    faceDetectCascade = 0;
    haarCascadePath = "/usr/share/apps/libkface/haarcascades/haarcascade_frontalface_alt.xml";
    faceDetectCascade = (CvHaarClassifierCascade*)cvLoad( haarCascadePath, 0, 0, 0 );
    liveCapture = 0;
    playStatus = false;
    tmpFace = 0;
    tmpStorageFaceDetect = cvCreateMemStorage(0);
}
void liveVideo::displayVideo(IplImage *imagetoDisplay,QGraphicsView *graphicsObject)
{
    cvCvtColor(imagetoDisplay,imagetoDisplay,CV_BGR2RGB);
    QImage image = QImage((uchar *)imagetoDisplay->imageData, imagetoDisplay->width, imagetoDisplay->height, QImage::Format_RGB888);
    QGraphicsScene* scene = new QGraphicsScene(graphicsObject);
    QPixmap tempimage = QPixmap::fromImage(image);
    QPixmap *backgroundPixmap = &tempimage;
    QPixmap sized = backgroundPixmap->scaled(QSize(graphicsObject->width(),graphicsObject->height()),Qt::IgnoreAspectRatio);
    QImage sizedImage = QImage(sized.toImage());
    scene->addPixmap(QPixmap::fromImage(sizedImage));
    graphicsObject->setScene(scene);
}

void liveVideo::togglePlayStatus()
{
    playStatus = (!playStatus);
}
