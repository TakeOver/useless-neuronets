#define nullptr NULL
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include "./../Kohonen/Utils.hpp"
#include "paths.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nn = NN::KohonenNN::createWithFixedWeights(100*100,10,0);
    for(std::string* i =test_png; i < test_png+sizeof(test_png); ++ i){
        ui->pathList->addItem(QString(i->c_str()));
    }
    QObject::connect(ui->pathList, SIGNAL(itemClicked(QListWidgetItem*)),
                     this, SLOT(onItemClicked(QListWidgetItem*)));
    QObject::connect(ui->teachButton, SIGNAL(clicked()),
                     this, SLOT(onTeachClicked()));
    QObject::connect(ui->testButton, SIGNAL(clicked()),
                     this, SLOT(onTestClicked()));

}

void MainWindow::onItemClicked(QListWidgetItem* wi){
    ui->imgView->setPixmap(QPixmap("./tests/Png/train/" +wi->text()));
}
void MainWindow::onTeachClicked(){
    if(ui->pathList->selectedItems().size() == 0){
        return;
    }
    unsigned int w,h;
    std::vector<unsigned char> img;
    std::string path = (ui->pathList->selectedItems()[0]->text().toStdString());
    lodepng::decode(img,w,h,("./tests/Png/train/" + path));
    std::vector<double> norm = NN::Utils::NormallizePng(img);
    unsigned char correct = path[0]-'0';
    nn->Study(norm,correct);
    QMessageBox msg;
    msg.setText("NN teached!");
    msg.exec();
}
void MainWindow::onTestClicked(){
    if(ui->pathList->selectedItems().size() == 0){
        return;
    }
    unsigned int w,h;
    std::vector<unsigned char> img;
    std::string path = (ui->pathList->selectedItems()[0]->text().toStdString());
    lodepng::decode(img,w,h,"./tests/Png/train/" + path);
    unsigned char correct = path[0]-'0';
    std::vector<double> norm  = NN::Utils::NormallizePng(img);
    nn->ProcessInput(norm);
    QMessageBox msg;
    msg.setText("NN result:" + QString((char)(nn->GetMaximum()+'0')) + " true answer:" + QString((char)(correct+'0')));
    msg.exec();
    nn->ResetPower();

}

MainWindow::~MainWindow()
{
    delete ui;
    for(uint32_t i = 0; i < 10; ++ i){
        std::vector<uint8_t> img = NN::Utils::Normallized2Png(nn->W[i]);
        std::string path = "./tests/Png/train/";
        path+= char('0'+i);
        path+= "_matrix.png";
        lodepng::encode(path,img,100,100);
    }
    delete nn;
}
