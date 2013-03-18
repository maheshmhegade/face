#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    facemodeltostore = 0;
    liveVideoObject.initliveVideo();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_saveFaceOnePB_clicked()
{
    Tlddatabase *tlddatabase = new Tlddatabase;
    facemodeltostore->Name = ui->faceOneLE->text();
    tlddatabase->insertFaceModel(facemodeltostore);
    delete tlddatabase;

}

void MainWindow::on_saveFaceTwoPB_clicked()
{
    Tlddatabase *tlddatabase = new Tlddatabase;
    facemodeltostore->Name = ui->faceTwoLE->text();
    tlddatabase->insertFaceModel(facemodeltostore);
    delete tlddatabase;
}

void MainWindow::on_capturePB_clicked()
{
    if (liveVideoObject.playStatus == false)
    {
        liveVideoObject.togglePlayStatus();
        liveVideoObject.startCapture();
    }
    else
    {
        liveVideoObject.togglePlayStatus();
        liveVideoObject.stopCapture();
    }
}

void MainWindow::on_faceDetectPB_clicked()
{

    liveVideoObject.detectFace(ui->faceOneGV,ui->faceTwoGV,boundingBox);

    liveVideoObject.togglePlayStatus();
    liveVideoObject.stopCapture();
    Tldrecognition* const tmpTLD          = new Tldrecognition;
    facemodeltostore = tmpTLD->getModeltoStore(boundingBox);
    cout << facemodeltostore->minVar << endl;
    delete tmpTLD;

}

void MainWindow::on_pushButton_clicked()
{

    Tlddatabase *tlddatabase = new Tlddatabase();

    for (int i = 1; i <= tlddatabase->queryNumfacesinDatabase();i++ )
    {
        unitFaceModel* const comparemodel = tlddatabase->getFaceModel(i);
        Tldrecognition* const tmpTLD      = new Tldrecognition;
        tmpTLD->getRecognitionConfidence(comparemodel);
        delete tmpTLD;
    }
    delete tlddatabase;

}

void MainWindow::on_showLivePB_clicked()
{
    Tlddatabase *tlddatabase = new Tlddatabase();

    for (int i = 1; i <= tlddatabase->queryNumfacesinDatabase();i++ )
    {
        unitFaceModel* const comparemodel = tlddatabase->getFaceModel(i);
        Tldrecognition* const tmpTLD      = new Tldrecognition;
        tmpTLD->getRecognitionConfidence(comparemodel);
        delete tmpTLD;
    }
    delete tlddatabase;

}
