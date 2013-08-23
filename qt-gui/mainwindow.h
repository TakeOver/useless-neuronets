#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./../Kohonen/Kohonen.hpp"
#include "./../LodePNG/lodepng.h"
class QListWidgetItem;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void onItemClicked(QListWidgetItem*);
    void onTeachClicked();
    void onTestClicked();
    
private:
    NN::KohonenNN *nn;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
