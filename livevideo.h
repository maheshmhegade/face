#ifndef LIVEVIDEO_H
#define LIVEVIDEO_H
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <QImage>
#include <QGraphicsView>

class liveVideo{

public:
    CvCapture *liveCapture;
    IplImage *tmpFace,*tmpImage;
    bool playStatus;
    const char *haarCascadePath;
    CvSeq *allFaces;
    CvMemStorage *tmpStorageFaceDetect;
    CvHaarClassifierCascade *faceDetectCascade;

    void initliveVideo();
    void togglePlayStatus();
    void startCapture();
    void detectFace(QGraphicsView *, QGraphicsView *, int *boundingBox);
    void displayVideo(IplImage*, QGraphicsView *);
    void stopCapture();

    ~liveVideo();

};
#endif // LIVEVIDEO_H
