#include "trainingplot.h"

double TrainingPlot::getSlope(std::vector<double> vect) {
    return - ( ( vect[0] / vect[2] ) / ( vect[0] / vect[1] ) );
    }

double TrainingPlot::getYIntercept(std::vector<double> vect) {
    return vect[0] / vect[2];
    }

TrainingPlot::TrainingPlot( QCustomPlot* plot ) {
    bluePoints = new QCPGraph( plot->xAxis, plot->yAxis );
    redPoints = new QCPGraph( plot->xAxis, plot->yAxis );
    greenPoints = new QCPGraph( plot->xAxis, plot->yAxis );

    setup( plot );
    }

TrainingPlot::~TrainingPlot() {

    }

void TrainingPlot::setup( QCustomPlot* plot ) {
    trainingPlot = plot;

    // Set styles for training plot
    // Margin visibility
    plot->xAxis2->setVisible(true);
    plot->yAxis2->setVisible(true);

    // Ranges
    plot->xAxis->setRange( -5.0, 5.0 );
    plot->yAxis->setRange( -5.0, 5.0 );
    plot->xAxis2->setRange( -5.0, 5.0 );
    plot->yAxis2->setRange( -5.0, 5.0 );

    // Colors of margins
    plot->xAxis->setBasePen( QPen( Qt::gray ) );
    plot->yAxis->setBasePen( QPen( Qt::gray ) );
    plot->xAxis2->setBasePen( QPen( Qt::gray ) );
    plot->yAxis2->setBasePen( QPen( Qt::gray ) );

    // Colors of axis
    plot->xAxis->grid()->setZeroLinePen( QPen( Qt::black ) );
    plot->yAxis->grid()->setZeroLinePen( QPen( Qt::black ) );

    // Set styles for inputs
    redPoints->setPen( QPen(Qt::red) );
    redPoints->setLineStyle( QCPGraph::lsNone );
    redPoints->setScatterStyle(QCPScatterStyle::ssCircle);
    bluePoints->setPen( QPen(Qt::blue) );
    bluePoints->setLineStyle( QCPGraph::lsNone );
    bluePoints->setScatterStyle(QCPScatterStyle::ssCircle);
    greenPoints->setPen( QPen(Qt::green) );
    greenPoints->setLineStyle( QCPGraph::lsNone );
    greenPoints->setScatterStyle(QCPScatterStyle::ssCircle);
}

void TrainingPlot::setupMatrix(Matrix* m) {
    firstLayer = m;
    QVector<double> lineX, lineY;
    lineX.push_back(-6);
    lineX.push_back(0);
    lineX.push_back(6);
    lineY.push_back(0);
    lineY.push_back(0);
    lineY.push_back(0);
    for (int i = 0; i < m->getRows(); ++i) {
        trainingPlot->addGraph();
        lineY[0] = -6 * getSlope((*m)[i]) + getYIntercept((*m)[i]);
        lineY[1] = 0 * getSlope((*m)[i]) + getYIntercept((*m)[i]);
        lineY[2] = 6 * getSlope((*m)[i]) + getYIntercept((*m)[i]);
        trainingPlot->graph(3 + i)->setData(lineX, lineY);
        }
    trainingPlot->replot();
    }

void TrainingPlot::updatePlot() {
    QVector<double> lineX, lineY;
    lineX.push_back(-6);
    lineX.push_back(0);
    lineX.push_back(6);
    lineY.push_back(0);
    lineY.push_back(0);
    lineY.push_back(0);
    for (int i = 0; i < firstLayer->getRows(); ++i) {
        trainingPlot->addGraph();
        lineY[0] = -6 * getSlope((*firstLayer)[i]) + getYIntercept((*firstLayer)[i]);
        lineY[1] = 0 * getSlope((*firstLayer)[i]) + getYIntercept((*firstLayer)[i]);
        lineY[2] = 6 * getSlope((*firstLayer)[i]) + getYIntercept((*firstLayer)[i]);
        trainingPlot->graph(3 + i)->setData(lineX, lineY);
        }
    trainingPlot->replot();
    }

void TrainingPlot::addPoint( double x, double y, int type ) {
    switch (type) {
        case TrainingModule::RED:
            redPoints->addData(x, y);
            break;
        case TrainingModule::BLUE:
            bluePoints->addData(x, y);
            break;
        case TrainingModule::GREEN:
            greenPoints->addData(x, y);
            break;
        default:
            break;
        }

    trainingPlot->replot();
    }
