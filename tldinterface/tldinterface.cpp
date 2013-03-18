/*  Copyright 2011 AIT Austrian Institute of Technology
*
*   This file is part of OpenTLD.
*
*   OpenTLD is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   OpenTLD is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with OpenTLD.  If not, see <http://www.gnu.org/licenses/>.
*
*/
/*
 * MainX.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: Georg Nebehay
 */

#include "tldinterface.h"

#include "ImAcq.h"
#include "Gui.h"
#include "TLDUtil.h"

using namespace tld;
using namespace cv;

pair<unitFaceModel *,IplImage *> tldinterface::generatefacemodel()
{
    IplImage *img;
    for (int i = 0 ;i < 2 ;i++)//intentionally introduced delay to get clear image
    {
        img = imAcqGetImg(imAcq);
        cvWaitKey(30);
    }
    //detect face first
    haarCascadePath = "/usr/share/apps/libkface/haarcascades/haarcascade_frontalface_alt.xml";
    faceDetectCascade = (CvHaarClassifierCascade*)cvLoad( haarCascadePath, 0, 0, 0 );
    tmpStorageFaceDetect = cvCreateMemStorage(0);

    allFaces = cvHaarDetectObjects( img, faceDetectCascade,
                                    tmpStorageFaceDetect,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) );

    CvRect * tmpFaceLocation = (CvRect *)cvGetSeqElem(allFaces,0);
    int boundingBox[4];
    boundingBox[0] = tmpFaceLocation->x;
    boundingBox[1] = tmpFaceLocation->y;
    boundingBox[2] = tmpFaceLocation->width;
    boundingBox[3] = tmpFaceLocation->height;

    cvSetImageROI( img,cvRect( tmpFaceLocation->x,tmpFaceLocation->y,tmpFaceLocation->width,tmpFaceLocation->height ) );
    IplImage *faceToDisplay = cvCreateImage(cvSize( tmpFaceLocation->width,tmpFaceLocation->height),img->depth,
                                            img->nChannels);
    cvCopy(img,faceToDisplay);
    cvResetImageROI(img);

    Mat grey(img->height, img->width, CV_8UC1);
    cvtColor(cv::Mat(img), grey, CV_BGR2GRAY);

    tld->detectorCascade->imgWidth = grey.cols;
    tld->detectorCascade->imgHeight = grey.rows;
    tld->detectorCascade->imgWidthStep = grey.step;

    bool reuseFrameOnce = false;
    bool skipProcessingOnce = false;
    Rect bb = tldArrayToRect(boundingBox);

    printf("Starting at %d %d %d %d\n", bb.x, bb.y, bb.width, bb.height);

    tld->selectObject(grey, &bb);
    skipProcessingOnce = true;
    reuseFrameOnce = true;

    int numTrainImages = 0;
    while(imAcqHasMoreFrames(imAcq) && numTrainImages < 30)
    {
        numTrainImages++;
        double tic = cvGetTickCount();

        if(!reuseFrameOnce)
        {
            img = imAcqGetImg(imAcq);

            if(img == NULL)
            {
                printf("current image is NULL, assuming end of input.\n");
                break;
            }

            cvtColor(cv::Mat(img), grey, CV_BGR2GRAY);
        }

        if(!skipProcessingOnce)
        {
            tld->processImage(img);
        }
        else
        {
            skipProcessingOnce = false;
        }

        double toc = (cvGetTickCount() - tic) / cvGetTickFrequency();

        toc = toc / 1000000;

        float fps = 1 / toc;

        int confident = (tld->currConf >= threshold) ? 1 : 0;

        if(showOutput || saveDir != NULL)
        {
            char string[128];

            char learningString[10] = "";

            if(tld->learning)
            {
                strcpy(learningString, "Learning");
            }

            sprintf(string, "#%d,Posterior %.2f; fps: %.2f, #numwindows:%d, %s", imAcq->currentFrame - 1, tld->currConf, fps, tld->detectorCascade->numWindows, learningString);
            CvScalar yellow = CV_RGB(255, 255, 0);
            CvScalar blue = CV_RGB(0, 0, 255);
            CvScalar black = CV_RGB(0, 0, 0);
            CvScalar white = CV_RGB(255, 255, 255);

            if(tld->currBB != NULL)
            {
                CvScalar rectangleColor = (confident) ? blue : yellow;
                cvRectangle(img, tld->currBB->tl(), tld->currBB->br(), rectangleColor, 8, 8, 0);
            }

            CvFont font;
            cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, .5, .5, 0, 1, 8);
            cvRectangle(img, cvPoint(0, 0), cvPoint(img->width, 50), black, CV_FILLED, 8, 0);
            cvPutText(img, string, cvPoint(25, 25), &font, white);

            if(showForeground)
            {

                for(size_t i = 0; i < tld->detectorCascade->detectionResult->fgList->size(); i++)
                {
                    Rect r = tld->detectorCascade->detectionResult->fgList->at(i);
                    cvRectangle(img, r.tl(), r.br(), white, 1);
                }

            }


            if(showOutput)
            {
                gui->showImage(img);
                char key = gui->getKey();

                if(key == 'q') break;

                if(key == 'b')
                {

                    ForegroundDetector *fg = tld->detectorCascade->foregroundDetector;

                    if(fg->bgImg.empty())
                    {
                        fg->bgImg = grey.clone();
                    }
                    else
                    {
                        fg->bgImg.release();
                    }
                }

                if(key == 'c')
                {
                    //clear everything
                    tld->release();
                }

                if(key == 'l')
                {
                    tld->learningEnabled = !tld->learningEnabled;
                    printf("LearningEnabled: %d\n", tld->learningEnabled);
                }

                if(key == 'a')
                {
                    tld->alternating = !tld->alternating;
                    printf("alternating: %d\n", tld->alternating);
                }

                if(key == 'e')
                {
                    tld->writeToFile(modelExportFile);
                }

                if(key == 'i')
                {
                    tld->readFromFile(modelPath);
                }

                if(key == 'r')
                {
                    CvRect box;

                    if(getBBFromUser(img, box, gui) == PROGRAM_EXIT)
                    {
                        break;
                    }

                    Rect r = Rect(box);

                    tld->selectObject(grey, &r);
                }
            }

            if(saveDir != NULL)
            {
                char fileName[256];
                sprintf(fileName, "%s/%.5d.png", saveDir, imAcq->currentFrame - 1);

//                cvSaveImage(fileName, img);
            }
        }

        if(!reuseFrameOnce)
        {
            cvReleaseImage(&img);
        }
        else
        {
            reuseFrameOnce = false;
        }
    }
    unitFaceModel *facemodel = tld->putObjModel();
    return make_pair(facemodel,faceToDisplay);
}

float tldinterface::getrecognitionconfidence(unitFaceModel *comparemodel)
{
    IplImage *img = imAcqGetImg(imAcq);
    Mat grey(img->height, img->width, CV_8UC1);
    cvtColor(cv::Mat(img), grey, CV_BGR2GRAY);

    tld->detectorCascade->imgWidth = grey.cols;
    tld->detectorCascade->imgHeight = grey.rows;
    tld->detectorCascade->imgWidthStep = grey.step;

    bool reuseFrameOnce = false;
    bool skipProcessingOnce = false;

    tld->getObjModel(comparemodel);
    reuseFrameOnce = true;

    int numTrainImages = 0;
    while(imAcqHasMoreFrames(imAcq) && numTrainImages < 150)
    {
        numTrainImages++;
        double tic = cvGetTickCount();

        if(!reuseFrameOnce)
        {
            img = imAcqGetImg(imAcq);

            if(img == NULL)
            {
                printf("current image is NULL, assuming end of input.\n");
                break;
            }

            cvtColor(cv::Mat(img), grey, CV_BGR2GRAY);
        }

        if(!skipProcessingOnce)
        {
            tld->processImage(img);
        }
        else
        {
            skipProcessingOnce = false;
        }

        double toc = (cvGetTickCount() - tic) / cvGetTickFrequency();

        toc = toc / 1000000;

        float fps = 1 / toc;

        int confident = (tld->currConf >= threshold) ? 1 : 0;

        if(showOutput || saveDir != NULL)
        {
            char string[128];

            char learningString[10] = "";

            if(tld->learning)
            {
                strcpy(learningString, "Learning");
            }

            sprintf(string, "#%d,Posterior %.2f; fps: %.2f, #numwindows:%d, %s", imAcq->currentFrame - 1, tld->currConf, fps, tld->detectorCascade->numWindows, learningString);
            CvScalar yellow = CV_RGB(255, 255, 0);
            CvScalar blue = CV_RGB(0, 0, 255);
            CvScalar black = CV_RGB(0, 0, 0);
            CvScalar white = CV_RGB(255, 255, 255);

            if(tld->currBB != NULL)
            {
                CvScalar rectangleColor = (confident) ? blue : yellow;
                cvRectangle(img, tld->currBB->tl(), tld->currBB->br(), rectangleColor, 8, 8, 0);
            }

            CvFont font;
            cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, .5, .5, 0, 1, 8);
            cvRectangle(img, cvPoint(0, 0), cvPoint(img->width, 50), black, CV_FILLED, 8, 0);
            cvPutText(img, string, cvPoint(25, 25), &font, white);

            if(showForeground)
            {

                for(size_t i = 0; i < tld->detectorCascade->detectionResult->fgList->size(); i++)
                {
                    Rect r = tld->detectorCascade->detectionResult->fgList->at(i);
                    cvRectangle(img, r.tl(), r.br(), white, 1);
                }

            }


            if(showOutput)
            {
                gui->showImage(img);
                char key = gui->getKey();

                if(key == 'q') break;

                if(key == 'b')
                {

                    ForegroundDetector *fg = tld->detectorCascade->foregroundDetector;

                    if(fg->bgImg.empty())
                    {
                        fg->bgImg = grey.clone();
                    }
                    else
                    {
                        fg->bgImg.release();
                    }
                }

                if(key == 'c')
                {
                    //clear everything
                    tld->release();
                }

                if(key == 'l')
                {
                    tld->learningEnabled = !tld->learningEnabled;
                    printf("LearningEnabled: %d\n", tld->learningEnabled);
                }

                if(key == 'a')
                {
                    tld->alternating = !tld->alternating;
                    printf("alternating: %d\n", tld->alternating);
                }

                if(key == 'e')
                {
                    tld->writeToFile(modelExportFile);
                }

                if(key == 'i')
                {
                    tld->readFromFile(modelPath);
                }

                if(key == 'r')
                {
                    CvRect box;

                    if(getBBFromUser(img, box, gui) == PROGRAM_EXIT)
                    {
                        break;
                    }

                    Rect r = Rect(box);

                    tld->selectObject(grey, &r);
                }
            }

            if(saveDir != NULL)
            {
                char fileName[256];
                sprintf(fileName, "%s/%.5d.png", saveDir, imAcq->currentFrame - 1);

//                cvSaveImage(fileName, img);
            }
        }

        if(!reuseFrameOnce)
        {
            cvReleaseImage(&img);
        }
        else
        {
            reuseFrameOnce = false;
        }
    }

    if(exportModelAfterRun)
    {
//        tld->writeToFile(modelExportFile);
    }
    return 0.34;
}
