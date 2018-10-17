#include "trainingmodule.h"

void TrainingModule::setupWeightMatrixes() {
    if (!weightMatrixes.empty()) {
        for(int i = 0; i < weightMatrixes.size(); ++i) {
            delete weightMatrixes[i];
            }
        weightMatrixes.clear();
        }

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
    }

void TrainingModule::updateGUI(TrainingPlot* tp) {
    tp->updatePlot();
    updateLabels();
    }

double TrainingModule::sigmoidFunction(double xVal) {
    return 1.0 / (1.0 + exp( -xVal ) );
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
    return functionRes * (1.0 - functionRes);
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

Matrix TrainingModule::scalarByMatrix(double scalar, Matrix m) {
    Matrix result(m.getRows(), m.getColumns());

    for (int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getColumns(); ++j) {
            result[i][j] = scalar * m[i][j];
            }
        }

    return result;
}

std::vector<double> TrainingModule::pointwiseProductVector(std::vector<double> v1, std::vector<double> v2) {
    std::vector<double> result;

    for (int i = 0; i < v1.size(); ++i) {
        result.push_back( v1[i] * v2[i] );
        }

    return result;
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

Matrix* TrainingModule::getFirstLayerMatrix() {
    return weightMatrixes[0];
    }

void TrainingModule::training(TrainingPlot* tp , ErrorPlot* ep) {
    const unsigned int TOTAL_LAYERS = layerNum + 1;
    double squaredError = 100.0, sumError;
    std::vector<double> errorVect;
    // a0, [am, ..., aM-1], and aM
    std::vector<std::vector<double>> outputVectors( TOTAL_LAYERS + 1, std::vector<double>() );
    // n1, [nm, ..., nM-1], and nM
    std::vector<std::vector<double>> netVectors( TOTAL_LAYERS, std::vector<double>() );
    // s1, [sm, ..., sM-1], and sM
    std::vector<std::vector<double>> sensitivityVect( TOTAL_LAYERS, std::vector<double>() );
    // updates
    std::vector<std::vector<Matrix>> updateMatrices( trainingSet.size(), std::vector<Matrix>(weightMatrixes.size(), Matrix()) );

    currentEpoch = 0;

    // While desired error is less than squared error or max epochs is reached
    while (currentEpoch < maxEpochs and squaredError > desiredError) {
        // ---- Start epoch -----
        squaredError = 0.0;
        for (unsigned int trainingIndex = 0; trainingIndex < trainingSet.size(); ++trainingIndex) {
            // Input layer to a0
            outputVectors[0] = trainingSet[trainingIndex].inputs;

            // ---- Feedforward -----
            feedforward(outputVectors, netVectors);

            // ---- Error calculation ----
            errorVect = getError(trainingSet[trainingIndex].type, outputVectors[TOTAL_LAYERS]);
            sumError = pow(errorVect[0],2) + pow(errorVect[1],2) + pow(errorVect[2],2);
            squaredError += sumError/2.0;

            // ---- Backpropagation ----
            for (int i = TOTAL_LAYERS - 1; i >= 0; --i) {
                if ( i == TOTAL_LAYERS - 1 ) {
                    std::vector<double> sigmoidVect;
                    sigmoidVect.push_back(sigmoidDerivative(netVectors[i][0]));
                    sigmoidVect.push_back(sigmoidDerivative(netVectors[i][1]));
                    sigmoidVect.push_back(sigmoidDerivative(netVectors[i][2]));
                    sensitivityVect[i] = scalarByVector(-2.0, pointwiseProductVector(sigmoidVect, errorVect));
                    }
                else {
                    Matrix sigmoidMatrix(netVectors[i].size(), netVectors[i].size());
                    for (int j = 0; j < sigmoidMatrix.getRows(); ++j) {
                        sigmoidMatrix[j][j] = sigmoidDerivative(netVectors[i][j]);
                        }
                    Matrix transpose = weightMatrixes[i + 1]->transpose().cutFirstRow();
                    Matrix sigmoidTransposeProduct = sigmoidMatrix * transpose;
                    sensitivityVect[i] = sigmoidTransposeProduct * sensitivityVect[i + 1];
                    }
                }

            // ---- Get updates for this sample ----
            for ( int i = 0; i < weightMatrixes.size(); ++i ) {
                Matrix transpose = Matrix(outputVectors[i]);
                Matrix sensitivity = Matrix(scalarByVector( -learningRate, sensitivityVect[i])).transpose();
                Matrix update = sensitivity * transpose;
                (*weightMatrixes[i]) = (*weightMatrixes[i]) + update;
                }
            }

        qDebug() << currentEpoch << ": " << squaredError;
        ep->addData(currentEpoch, squaredError);
        ++currentEpoch;

        convergenceEpochLbl->setText( QString::number( currentEpoch ) );
        }
    updateGUI( tp );
    gradientGraph( tp );
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
    outputs[0].push_back(-1);
    outputs[0].push_back(x);
    outputs[0].push_back(y);
    results = feedforward(outputs, nets);
    return std::distance(results.begin(), std::max_element(results.begin(), results.end()));;
}

void TrainingModule::gradientGraph( TrainingPlot* tp ) {
    int output;
    for (double i = -5.0; i <= 5.0; i += 0.25 ) {
        for (double j = -5.0; j <= 5.0; j += 0.25) {
            output = getType(i, j);
            //qDebug() << "X: " << i << " Y: " << j << " Clase: " << output;
            tp->addToGradient(i, j, output);
            }
        }
    tp->updatePlot();
    }
