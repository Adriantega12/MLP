#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Training module setup
    trainingModule = new TrainingModule;
    trainingModule->connectGUIToValues(ui->currentEpochVal, ui->convergenceEpochVal);

    // Training plot setup
    trainingPlot = new TrainingPlot( ui->trainingPlot );

    connect( ui->trainingPlot, SIGNAL( mousePress(QMouseEvent*) ), this, SLOT( plotClick(QMouseEvent*) ) );
    }

MainWindow::~MainWindow() {
    delete trainingPlot;
    delete trainingModule;
    delete ui;
    }

void MainWindow::plotClick(QMouseEvent* evt) {
    if ( ui->trainingPlot->axisRect()->rect().contains( evt->pos() ) ) {
        int classType;
        double x = ui->trainingPlot->xAxis->pixelToCoord( evt->x() ),
               y = ui->trainingPlot->yAxis->pixelToCoord( evt->y() );

        if ( ui->classifyCB->isChecked() ) {
            int type = trainingModule->getType( x, y );

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
            trainingModule->addPoint( x, y, TrainingModule::RED );
            trainingPlot->addPoint( x, y, TrainingModule::RED );
            }
        else if ( ui->blueRB->isChecked() ) {
            trainingModule->addPoint( x, y, TrainingModule::BLUE );
            trainingPlot->addPoint( x, y, TrainingModule::BLUE );
            }
        else if ( ui->greenRB->isChecked() ) {
            trainingModule->addPoint( x, y, TrainingModule::GREEN );
            trainingPlot->addPoint( x, y, TrainingModule::GREEN );
            }
        }
    }

void MainWindow::on_layerNumSB_valueChanged(int layerNum) {
    ui->neurons2SB->setEnabled(layerNum == 2 ? true : false);
    }

void MainWindow::on_initializeBttn_clicked() {
    trainingModule->setup( ui->maxEpochsSB->value(), ui->learnRateSB->value(), ui->desiredErrorSB->value(),
                           ui->layerNumSB->value(), ui->neurons1SB->value(), ui->neurons2SB->value() );
    trainingPlot->setupMatrix(trainingModule->getFirstLayerMatrix());
    }

void MainWindow::on_trainBttn_clicked() {
    trainingModule->training( trainingPlot );
    }
