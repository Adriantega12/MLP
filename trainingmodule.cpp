#include "trainingmodule.h"

void TrainingModule::setupWeightMatrixes() {
    // First hidden layer
    weightMatrixes.push_back( new Matrix(neuronsLayer1, INPUT_SIZE + 1) );

    // Second hidden layer if exists
    if ( layerNum == 2 ) {
        weightMatrixes.push_back( new Matrix( neuronsLayer2, neuronsLayer1 + 1) );
        }

    // Output layer
    weightMatrixes.push_back( new Matrix(OUTPUT_SIZE, weightMatrixes.back()->getRows() + 1) );
    }

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
      rdg(-5.0, 5.0),
      layerNum(1),
      neuronsLayer1(1),
      neuronsLayer2(1) {

    }

TrainingModule::~TrainingModule() {

    }

void TrainingModule::connectGUIToValues(QLabel *cE, QLabel *conv) {
    currentEpochLbl = cE;
    convergenceEpochLbl = conv;
    }

void TrainingModule::setup(unsigned int mE, double lR, double dE, int lC, int n1, int n2) {
    maxEpochs = mE;
    learningRate = lR;
    desiredError = dE;
    layerNum = lC;
    neuronsLayer1 = n1;
    neuronsLayer2 = n2;
    setupWeightMatrixes();
    }

void TrainingModule::training() {
    double squaredError = 1.0;
    double error;
    // a0, [am, ... aM-1], and aM
    std::vector<std::vector<double>> outputVectors( layerNum + 2, std::vector<double>() );

    currentEpoch = 0;

    // While desired error is less than squared error or max epochs is reached
    while (currentEpoch < maxEpochs and squaredError > desiredError) {
        // ---- Start epoch -----
        // ---- Feedforward -----
        squaredError = error = 0.0;
        for (unsigned int trainingIndex = 0; trainingIndex < trainingSet.size(); ++trainingIndex) {
            //outputVectors[0] = trainingSet;


            }
        }
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
