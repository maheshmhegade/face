#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    liveVideoObject = new liveVideo();
    facemodeltostore = 0;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_saveFaceOnePB_clicked()
{
    Tlddatabase *tlddatabase = new Tlddatabase;
    facemodeltostore = faceData.first;
    facemodeltostore->Name = ui->faceOneLE->text();
    cout << qPrintable(facemodeltostore->Name) << endl;
    tlddatabase->insertFaceModel(facemodeltostore);
    delete tlddatabase;

}

void MainWindow::on_faceDetectPB_clicked()
{
    Tldrecognition* const tmpTLD          = new Tldrecognition;
    faceData = tmpTLD->getModeltoStore();
    //facemodeltostore = faceData.first;
    liveVideoObject->displayVideo(faceData.second,ui->faceOneGV);
    delete tmpTLD;
}

void MainWindow::on_showLivePB_clicked()
{
    liveVideoObject->togglePlayStatus();

    if(liveVideoObject->playStatus == true)
    {
        Tlddatabase *tlddatabase = new Tlddatabase();

        QList<unitFaceModel*> comparemodels;

        for (int i = 1; i <= tlddatabase->queryNumfacesinDatabase();i++ )
        {
            comparemodels.push_back(tlddatabase->getFaceModel(i));
        }
        delete tlddatabase;

        Tldrecognition* const tmpTLD      = new Tldrecognition;
        tmpTLD->getRecognitionConfidence(comparemodels);
        delete tmpTLD;
    }
}
