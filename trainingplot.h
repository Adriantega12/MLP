#ifndef TRAININGPLOT_H
#define TRAININGPLOT_H

#include "qcustomplot.h"
#include "trainingmodule.h"
#include "matrix.h"

class TrainingPlot {
    private:
        QCustomPlot* trainingPlot;

        QCPGraph* redPoints;
        QCPGraph* bluePoints;
        QCPGraph* greenPoints;
        QCPGraph* gradientRed;
        QCPGraph* gradientBlue;
        QCPGraph* gradientGreen;

        Matrix* firstLayer;

        double getSlope(std::vector<double>);
        double getYIntercept(std::vector<double>);

        QVector<QVector<double>> linesX;
        QVector<QVector<double>> linesY;

    public:
        TrainingPlot( QCustomPlot* plot );
        ~TrainingPlot();

        void setup( QCustomPlot* plot );
        void setupMatrix( Matrix* );

        void updatePlot();

        void addPoint(double x, double y , int type);

        void addToGradient( double x, double y, int type );
    };

#endif // TRAININGPLOT_H
