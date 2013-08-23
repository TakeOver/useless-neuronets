#define nullptr NULL
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include "paths.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nn = NN::KohonenNN::createWithZeroWeights(100*100*4,10);
    for(std::string* i =test_png; i < test_png+20; ++ i){
        ui->pathList->addItem(QString(i->c_str()));
    }
    QObject::connect(ui->pathList, SIGNAL(itemClicked(QListWidgetItem*)),
                     this, SLOT(onItemClicked(QListWidgetItem*)));
    ui->imgView->setPixmap(QPixmap("/home/TakeOver/neuronet/KohonenNN/tests/Png/train/0_0.png"));
    QObject::connect(ui->teachButton, SIGNAL(clicked()),
                     this, SLOT(onTeachClicked()));
    QObject::connect(ui->testButton, SIGNAL(clicked()),
                     this, SLOT(onTestClicked()));

}

void MainWindow::onItemClicked(QListWidgetItem* wi){
    ui->imgView->setPixmap(QPixmap("/home/TakeOver/neuronet/KohonenNN/tests/Png/train/" +wi->text()));
}
void MainWindow::onTeachClicked(){
    unsigned int w,h;
    std::vector<unsigned char> img;
    std::string path = (ui->pathList->selectedItems()[0]->text().toStdString());
    lodepng::decode(img,w,h,("/home/TakeOver/neuronet/KohonenNN/tests/Png/train/" + path));
    unsigned char correct = path[0]-'0';
    nn->Study(img,correct);
    QMessageBox msg;
    msg.setText("NN teached!");
    msg.exec();
}
void MainWindow::onTestClicked(){
    unsigned int w,h;
    std::vector<unsigned char> img;
    std::string path = (ui->pathList->selectedItems()[0]->text().toStdString());
    lodepng::decode(img,w,h,"/home/TakeOver/neuronet/KohonenNN/tests/Png/train/" + path);
    unsigned char correct = path[0]-'0';
    nn->ProcessInput(img);
    QMessageBox msg;
    msg.setText("NN result:" + QString((char)(nn->GetMaximum()+'0')) + " true answer:" + QString((char)(correct+'0')));
    msg.exec();
    nn->ResetPower();

}

MainWindow::~MainWindow()
{
    delete ui;
}
