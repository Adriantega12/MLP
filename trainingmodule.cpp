#include "trainingmodule.h"

void TrainingModule::updateLabels() {
    currentEpochLbl->setText( QString::number( currentEpoch ) );
    convergenceEpochLbl->setText( QString::number( 0 ) );
    }

double TrainingModule::sigmoidFunction(double xVal) {
    return 1.0 / (1.0 + qExp( -xVal ) );
    }

double TrainingModule::activationFunctionDerivative(std::function<double(double)> activationFunction, double xVal) {
    double functionRes = activationFunction( xVal );
    return functionRes * ( 1 - functionRes );
    }

double TrainingModule::getError(Inputs p, std::function<double (double)> activationFunction) {
    return 0.0;
    }

TrainingModule::TrainingModule()
    : currentEpoch(0),
      maxEpochs(99999),
      learningRate(0.0),
      desiredError(0.0),
      rdg(-5.0, 5.0) {

    }

TrainingModule::~TrainingModule() {

    }

void TrainingModule::connectGUIToValues(QLabel *cE, QLabel *conv) {
    currentEpochLbl = cE;
    convergenceEpochLbl = conv;
    }

void TrainingModule::setup(unsigned int mE, double lR, double dE) {
    maxEpochs = mE;
    learningRate = lR;
    desiredError = dE;
    }

void TrainingModule::addPoint( double x, double y, int type ) {
    Inputs p;
    std::vector<double> in;
    in.push_back(-1.0);
    in.push_back(x);
    in.push_back(y);
    trainingSet.push_back( p = { in, type } );
    }

double TrainingModule::getType(double x, double y) {
    return 0.0;
    }
