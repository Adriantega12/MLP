#include "trainingplot.h"

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

void TrainingPlot::updatePlot(double slope, double yIntercept) {
    /*
    lineY[0] = lineX[0] * slope + yIntercept;
    lineY[1] = lineX[1] * slope + yIntercept;
    lineY[2] = lineX[2] * slope + yIntercept;

    for ( unsigned int i = 0; i < lineY.size(); ++i ) {
        lineY[i] = lineX[i] * slope + yIntercept;
        }

    trainingPlot->graph(2)->setData(lineX, lineY);
    trainingPlot->replot();
    */
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
