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
    for ( unsigned int i = 0; i < vect.size(); ++i ) {
        retVect[i] = sigmoidFunction(vect[i]);
        }
    return retVect;
    }

double TrainingModule::sigmoidDerivative(double xVal) {
    double functionRes = sigmoidFunction(xVal);
    return functionRes * (1 - functionRes);
    }

std::vector<double> TrainingModule::sigmoidDerivative(std::vector<double> vect) {
    std::vector<double> retVect(vect.size(), 0);
    for ( unsigned int i = 0; i < vect.size(); ++i ) {
        retVect[i] = sigmoidDerivative(vect[i]);
        }
    return retVect;
    }

std::vector<double> TrainingModule::scalarByVector(double scalar, std::vector<double> vect) {
    std::vector<double> retVect(vect.size(), 0);
    for ( unsigned int i = 0; i < vect.size(); ++i ) {
        retVect[i] = scalar * vect[i];
        }
    return retVect;
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
      layerNum(1),
      neuronsLayer1(1),
      neuronsLayer2(1),
      rdg(-5.0, 5.0) {
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
    const unsigned int TOTAL_LAYERS = layerNum + 1;
    double squaredError = 1.0;
    std::vector<double> errorVect;
    // a0, [am, ..., aM-1], and aM
    std::vector<std::vector<double>> outputVectors( TOTAL_LAYERS + 1, std::vector<double>() );
    // n1, [nm, ..., nM-1], and nM
    std::vector<std::vector<double>> netVectors( TOTAL_LAYERS, std::vector<double>() );
    // s1, [sm, ..., sM-1], and sM
    std::vector<std::vector<double>> sensitivityVect( TOTAL_LAYERS, std::vector<double>() );

    currentEpoch = 0;

    // While desired error is less than squared error or max epochs is reached
    while (currentEpoch < maxEpochs and squaredError > desiredError) {
        // ---- Start epoch -----

        squaredError = 0.0;
        for (unsigned int trainingIndex = 0; trainingIndex < trainingSet.size(); ++trainingIndex) {
            // Input layer to a0
            outputVectors[0] = trainingSet[0].inputs;

            // ---- Feedforward -----
            feedforward(outputVectors, netVectors);

            // ---- Backpropagation ----
            errorVect = getError(trainingSet[trainingIndex].type, outputVectors[TOTAL_LAYERS]);
            std::vector<double> derivative = sigmoidDerivative(netVectors[TOTAL_LAYERS - 1]);
            // sensitivityVect[TOTAL_LAYERS - 1] = Matrix(scalarByVector(-2, derivative)) * errorVect;
            // sensitivityVect[TOTAL_LAYERS - 1]

            for (int i = TOTAL_LAYERS - 2; i >= 0; --i) {
                Matrix transpose = weightMatrixes[i + 1]->transpose();
                Matrix sigmoidMatrix(weightMatrixes[i + 1]->getRows(), weightMatrixes[i + 1]->getRows());
                for (int j = 0; j < sigmoidMatrix.getRows(); ++j) {
                    sigmoidMatrix[j][j] = sigmoidDerivative(netVectors[i][j]);
                    }
                sensitivityVect[i] = sigmoidMatrix * transpose * sensitivityVect[i + 1];
                }
            squaredError += sqrt(pow(errorVect[0],2) + pow(errorVect[1],2) + pow(errorVect[2],2))/2;

            // ---- Weight update ----
            for ( int i = 0; i < weightMatrixes.size(); ++i ) {
                Matrix transpose = Matrix(outputVectors[i]);
                Matrix sensitivity = Matrix(scalarByVector(-learningRate, sensitivityVect[i])).transpose();
                Matrix update = sensitivity * transpose;
                (*weightMatrixes[i]) = (*weightMatrixes[i]) + update;
                }
            }
        ++currentEpoch;

        updateLabels();
        convergenceEpochLbl->setText( QString::number( currentEpoch ) );
        }
    }

std::vector<double> TrainingModule::feedforward(std::vector<std::vector<double>>& outputs, std::vector<std::vector<double>>& nets) {
    totalLayers = layerNum + 1;
    for (unsigned int i = 0; i < totalLayers; ++i) {
        nets[i] = (*weightMatrixes[i]) * outputs[i];
        outputs[i + 1] = sigmoidFunction(nets[i]);
        if ( i + 1 < totalLayers ) {
            outputs[i + 1].insert(outputs[i + 1].begin(), -1.0);
            }
        }

    return outputs[totalLayers];
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

int TrainingModule::getType(double x, double y) {
    std::vector<std::vector<double>> outputs(totalLayers + 1, std::vector<double>() );
    std::vector<double> results;
    std::vector<std::vector<double>> nets( totalLayers, std::vector<double>() );
    int r, g, b;
    outputs[0].push_back(-1);
    outputs[0].push_back(x);
    outputs[0].push_back(y);
    results = feedforward(outputs, nets);
    r = results[RED] > 0.9 ? 1 : 0;
    g = results[GREEN] > 0.9 ? 1 : 0;
    b = results[BLUE] > 0.9 ? 1 : 0;
    qDebug() << "R: " << r << " G: " << g << " B: " << b;
    return 0;
    }
