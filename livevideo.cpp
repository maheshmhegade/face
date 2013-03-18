#include "livevideo.h"
#include <stdio.h>
#include <iostream>

using namespace std;

liveVideo::~liveVideo()
{
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
