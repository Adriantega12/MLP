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

double TrainingModule::getError(Pair p, std::function<double (double)> activationFunction) {
    // return p.type - activationFunction( inputAndWeightsPointProduct( p.x, p.y ) );
    return 0.0;
    }

TrainingModule::TrainingModule()
    : weight0(0.0), weight1(0.0), weight2(0.0), currentEpoch(0),
      maxEpochs(99999), learningRate(0.0), desiredError(0.0), rdg(-5.0, 5.0) {

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
    weight0 = rdg();
    weight1 = rdg();
    weight2 = rdg();
    }

void TrainingModule::addPoint( double x, double y, int type ) {
    Pair p;
    trainingSet.push_back( p = { x, y, type } );
}

double TrainingModule::getType(double x, double y) {
    //return inputAndWeightsPointProduct( x, y );
    return 0.0;
    }

double TrainingModule::getSlope() {
    return - ( ( weight0 / weight2 ) / ( weight0 / weight1 ) );
    }

double TrainingModule::getYIntercept() {
    return weight0 / weight2;
    }
