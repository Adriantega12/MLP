#ifndef TRAININGMODULE_H
#define TRAININGMODULE_H

#include <QLabel>
#include <QDebug>
#include <QtMath>

#include <vector>
#include <functional>

#include "randdouble.h"
/*#include "trainingplot.h"
#include "errorplot.h"*/

class TrainingModule {
    private:
        struct Pair {
            double x;
            double y;
            int type;
            };

        unsigned int currentEpoch;
        unsigned int maxEpochs;
        double learningRate;
        double desiredError;

        QLabel* currentEpochLbl;
        QLabel* convergenceEpochLbl;

        Rand_double rdg;

        std::vector<Pair> trainingSet;

        void updateLabels();

        // Maths
        static double sigmoidFunction(double xVal);
        double activationFunctionDerivative(std::function<double (double)> activationFunction , double xVal);
        double getError(Pair p, std::function<double (double)> activationFunction);

    public:
        static const int RED = 0;
        static const int BLUE = 1;
        static const int GREEN = 2;

        TrainingModule();
        ~TrainingModule();

        void connectGUIToValues(QLabel* cE, QLabel* conv );

        void setup(unsigned int mE, double lR, double dE);

        void updateValues();

        void addPoint( double x, double y, int type = RED );

        double getType( double x, double y );

        /*
        double getSlope();
        double getYIntercept();
        */
    };

#endif // TRAININGMODULE_H
