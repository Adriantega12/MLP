#include "trainingmodule.h"

void TrainingModule::setupWeightMatrixes() {
    // First hidden layer
    Matrix* first = new Matrix(neuronsLayer1, INPUT_SIZE + 1);
    initializeMatrix(first);
    weightMatrixes.push_back( first );

    // Second hidden layer if exists
    if ( layerNum == 2 ) {
        Matrix* secondHidden = new Matrix( neuronsLayer2, neuronsLayer1 + 1);
        initializeMatrix(secondHidden);
        weightMatrixes.push_back( secondHidden );
        }

    // Output layer weights
    Matrix* outputWeights = new Matrix(OUTPUT_SIZE, weightMatrixes.back()->getRows() + 1);
    initializeMatrix(outputWeights);
    weightMatrixes.push_back( outputWeights );
}

void TrainingModule::initializeMatrix(Matrix* m ) {
    for (int i = 0; i < m->getRows(); ++i) {
        for (int j = 0; j < m->getColumns(); ++j) {
            (*m)[i][j] = rdg();
            }
        }
    }

void TrainingModule::updateLabels() {
    currentEpochLbl->setText( QString::number( currentEpoch ) );
    convergenceEpochLbl->setText( QString::number( 0 ) );
    }

double TrainingModule::sigmoidFunction(double xVal) {
    return 1.0 / (1.0 + qExp( -xVal ) );
    }

std::vector<double> TrainingModule::sigmoidFunction(std::vector<double> vect) {
    std::vector<double> retVect(vect.size(), 0);
    //retVect[0] = -1.0;
    for ( int i = 0; i < vect.size(); ++i ) {
        retVect[i] = TrainingModule::sigmoidFunction(vect[i]);
        }
    return retVect;
    }

double TrainingModule::activationFunctionDerivative(std::function<double(double)> activationFunction, double xVal) {
    double functionRes = activationFunction( xVal );
    return functionRes * ( 1 - functionRes );
    }

std::vector<double> TrainingModule::getError(std::vector<int> type, std::vector<double> obtained) {
    std::vector<double> error;
    error.push_back(type[RED] - obtained[RED]);
    error.push_back(type[GREEN] - obtained[GREEN]);
    error.push_back(type[BLUE] - obtained[BLUE]);
    return error;
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
    const int TOTAL_LAYERS = layerNum + 1;
    double squaredError = 1.0;
    double error;
    // a0, [am, ... aM-1], and aM
    std::vector<std::vector<double>> outputVectors( TOTAL_LAYERS, std::vector<double>() );
    // n1, [nm, ... nM-1], and nM
    std::vector<std::vector<double>> netVectors( TOTAL_LAYERS, std::vector<double>() );

    currentEpoch = 0;

    // While desired error is less than squared error or max epochs is reached
    while (currentEpoch < maxEpochs and squaredError > desiredError) {
        // ---- Start epoch -----

        squaredError = error = 0.0;
        for (unsigned int trainingIndex = 0; trainingIndex < trainingSet.size(); ++trainingIndex) {
            // Input layer to a0
            outputVectors[0] = trainingSet[0].inputs;

            // ---- Feedforward -----
            // NO SE ESTÀ ANEXANDO LA ENTRADA DEL UMBRAL
            for (unsigned int i = 0; i < TOTAL_LAYERS; ++i) {
                netVectors[i] = (*weightMatrixes[i]) * outputVectors[i];
                if (i + 1 < layerNum + 1) {
                    outputVectors[i + 1] = sigmoidFunction(netVectors[i]);
                    outputVectors[i + 1].insert(outputVectors[i + 1].begin(), -1.0);
                    }
                }

            // Backpropagation
            // sensitivity[TOTAL_LAYERS - 1] = -2 * sigmoidDerivate(netVectors[TOTAL_LAYERS - 1]) * error
            }
        }
    }

void TrainingModule::addPoint( double x, double y, int t ) {
    Inputs p;
    std::vector<double> in;
    std::vector<int> type;
    in.push_back(-1.0);
    in.push_back(x);
    in.push_back(y);
    type.push_back(t == RED);
    type.push_back(t == GREEN);
    type.push_back(t == BLUE);
    trainingSet.push_back( p = { in, type } );
    }

double TrainingModule::getType(double x, double y) {
    return 0.0;
    }
