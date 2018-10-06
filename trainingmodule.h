#ifndef TRAININGMODULE_H
#define TRAININGMODULE_H

#include <QLabel>
#include <QDebug>
#include <QtMath>

#include <vector>
#include <functional>

#include "randdouble.h"
#include "matrix.h"
/*#include "trainingplot.h"
#include "errorplot.h"*/

class TrainingModule {
    private:
        struct Inputs {
            std::vector<double> inputs;
            std::vector<int> type;
            };

        unsigned int currentEpoch;
        unsigned int maxEpochs;
        double learningRate;
        double desiredError;
        unsigned int layerNum;
        unsigned int neuronsLayer1;
        unsigned int neuronsLayer2;

        QLabel* currentEpochLbl;
        QLabel* convergenceEpochLbl;

        Rand_double rdg;

        std::vector<Inputs> trainingSet;
        std::vector<Matrix*> weightMatrixes;
        std::vector<std::vector<double>> outputVectors;

        void setupWeightMatrixes();
        void initializeMatrix( Matrix* );
        void updateLabels();

        // Maths
        static double sigmoidFunction(double xVal);
        static std::vector<double> sigmoidFunction(std::vector<double> xVal);
        double activationFunctionDerivative(std::function<double (double)> activationFunction , double xVal);
        std::vector<double> getError(std::vector<int>, std::vector<double>);

    public:
        static const int RED = 0;
        static const int BLUE = 1;
        static const int GREEN = 2;

        static const int INPUT_SIZE = 2;
        static const int OUTPUT_SIZE = 3;

        TrainingModule();
        ~TrainingModule();

        void connectGUIToValues(QLabel* cE, QLabel* conv );

        void setup(unsigned int mE, double lR, double dE, int lC, int n1, int n2);

        void training();

        void updateValues();

        void addPoint( double x, double y, int type = RED );

        double getType( double x, double y );
    };

#endif // TRAININGMODULE_H
