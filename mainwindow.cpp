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
    facemodeltostore->Name = ui->faceOneLE->text();
    tlddatabase->insertFaceModel(facemodeltostore);
    delete tlddatabase;

}

void MainWindow::on_faceDetectPB_clicked()
{
    Tldrecognition* const tmpTLD          = new Tldrecognition;
    pair<unitFaceModel*,IplImage*> faceData = tmpTLD->getModeltoStore();
    facemodeltostore = faceData.first;
    liveVideoObject->displayVideo(faceData.second,ui->faceOneGV);
    delete tmpTLD;
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
