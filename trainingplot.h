#ifndef TRAININGPLOT_H
#define TRAININGPLOT_H

#include "qcustomplot.h"
#include "trainingmodule.h"

class TrainingPlot {
    private:
        QCustomPlot* trainingPlot;

        QCPGraph* redPoints;
        QCPGraph* bluePoints;
        QCPGraph* greenPoints;

        QVector<double> lineX;
        QVector<double> lineY;

    public:
        TrainingPlot( QCustomPlot* plot );
        ~TrainingPlot();

        void setup( QCustomPlot* plot );

        void updatePlot(double slope, double yIntercept);

        void addPoint(double x, double y , int type);
    };

#endif // TRAININGPLOT_H
