#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    }

MainWindow::~MainWindow() {
    delete ui;
    }

void MainWindow::on_layerNumSB_valueChanged(int layerNum) {
    ui->neurons2SB->setEnabled(layerNum == 2 ? true : false);
    }
