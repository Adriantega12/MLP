#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect( ui->trainingPlot, SIGNAL( mousePress(QMouseEvent*) ), this, SLOT( plotClick(QMouseEvent*) ) );
    }

MainWindow::~MainWindow() {
    delete ui;
    }

void MainWindow::plotClick(QMouseEvent* evt) {
    if ( ui->trainingPlot->axisRect()->rect().contains( evt->pos() ) ) {
        double x = ui->trainingPlot->xAxis->pixelToCoord( evt->x() ),
               y = ui->trainingPlot->yAxis->pixelToCoord( evt->y() );

        if ( ui->classifyCB->isChecked() ) {
            //double type = trainingModule->getType( x, y );

            //if ( type <= 0 ) {
                //trainingPlot->addRedPoint( x, y );
                //trainingModule->addPoint( x, y, TrainingModule::RED );
            //    }
            //else {
                //trainingPlot->addBluePoint( x, y );
                //trainingModule->addPoint( x, y, TrainingModule::BLUE );
            //    }
            return;
            }

        // Add points according to the selected class
        if ( ui->redRB->isChecked() ) {
            //trainingPlot->addRedPoint( x, y );
            //trainingModule->addPoint( x, y, TrainingModule::RED );
            }
        else if ( ui->blueRB->isChecked() ) {
            //trainingPlot->addBluePoint( x, y );
            //trainingModule->addPoint( x, y, TrainingModule::BLUE );
            }
        }
    }

void MainWindow::on_layerNumSB_valueChanged(int layerNum) {
    ui->neurons2SB->setEnabled(layerNum == 2 ? true : false);
    }
