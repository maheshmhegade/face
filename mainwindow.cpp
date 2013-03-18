#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    liveVideoObject.initliveVideo();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_saveFaceOnePB_clicked()
{

}

void MainWindow::on_saveFaceTwoPB_clicked()
{

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
    unitFaceModel* const facemodeltostore = tmpTLD->getModeltoStore(boundingBox);
}

void MainWindow::on_showLivePB_clicked()
{

}
