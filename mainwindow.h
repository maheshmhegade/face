#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "livevideo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    liveVideo liveVideoObject;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void on_saveFaceOnePB_clicked();

    void on_saveFaceTwoPB_clicked();

    void on_capturePB_clicked();

    void on_faceDetectPB_clicked();

    void on_showLivePB_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
