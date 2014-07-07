#ifndef FFNEURALNETWORK_H
#define FFNEURALNETWORK_H

#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include "NeuronLayer.h"

float sigmoid(float x);
float sigmoidDerivative(float x);

class FFNeuralNetwork;

FFNeuralNetwork loadNN(std::string filename);

class FFNeuralNetwork
{
    public:
        FFNeuralNetwork();

        FFNeuralNetwork(const std::string& filename);

        FFNeuralNetwork(size_t inputNeurons, size_t numHidden, size_t neuronPerHidden, size_t outputNeurons);

        FFNeuralNetwork(size_t inputNeurons, size_t numHidden, size_t* hiddenSizes, size_t outputNeurons);

        virtual ~FFNeuralNetwork();

        void init(size_t inputNeurons, size_t numHidden, size_t neuronPerHidden, size_t outputNeurons);
        void init(size_t inputNeurons, size_t numHidden, size_t* hiddenSizes, size_t outputNeurons);

        void setFunctions(std::function<float(float)> activFunc = sigmoid, std::function<float(float)> deriv = sigmoidDerivative);

        void setInputs(const float* vals, size_t arrSize);
        void setInputs(const std::vector<float>& vals);

        void propagateForwards();

        std::vector<float> getOutputs();

        std::vector<float> processData(const float* vals, size_t arrSize);
        std::vector<float> processData(const std::vector<float>& vals);

        void train(const float* inputData, size_t inputSize, const float* expected, size_t expectedSize, size_t numEpochs = 2500, float learningRate = 1.0f, float momentum = 0.0f);
        void train(const std::vector<float>& inputData, const std::vector<float>& expected, size_t numEpochs = 2500, float learningRate = 1.0f, float momentum = 0.0f);

        std::vector<float> calculateOutputError(const float* expected);
        std::vector<float> calculateOutputError(const std::vector<float>& expected);

        std::vector<float> calculateHiddenError(NeuronLayer& nl);

        size_t size() const;

        NeuronLayer& operator[](size_t index);

        const NeuronLayer& operator[](size_t index) const;

        friend std::ostream& operator<<(std::ostream& stream, const FFNeuralNetwork& ffnn);

    private:
        NeuronLayer* layers;

        size_t layerCount;

        std::function<float(float)> activationFuncion;
        std::function<float(float)> activationDerivative;

};

//-------------------------------------------//

float sigmoid(float x) {
    return 1.0f / (1.0f + exp(-x) );
}

float sigmoidDerivative(float x) {
    float sigRes = sigmoid(x);
    return sigRes * (1.0f - sigRes);
}

FFNeuralNetwork loadNN(std::string filename) {
    std::fstream file;
    std::stringstream valueReader;

    size_t numLayers, inputSize, outputSize;
    size_t* hiddenSizes;

    float* weights;

    file.open(filename.c_str(), std::ios_base::in);

    std::string line;

    //skip first line, read to actual data
    std::getline(file, line);
    std::getline(file, line, '=');

    std::getline(file, line, ';');

    valueReader << line;

    valueReader >> numLayers;

    hiddenSizes = new size_t[numLayers - 2];


}

#endif // FFNEURALNETWORK_H