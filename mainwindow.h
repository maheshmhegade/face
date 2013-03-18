#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "livevideo.h"
#include "tlddatabase.h"

using namespace libface;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    int boundingBox[4];
    unitFaceModel* facemodeltostore;
    liveVideo *liveVideoObject;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void on_saveFaceOnePB_clicked();

    void on_faceDetectPB_clicked();

    void on_showLivePB_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
