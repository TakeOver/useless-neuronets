#pragma once
#include <cassert>
#include <cstdint>
#include <vector>
#include <iostream>
namespace NN{
    struct Neuron{
        double power = 0;        
    };
    class KokhonenNN{
    public:
        std::vector<std::vector<double>> W; // W[ j ][ i ] - Weight of link between N[ 0 ][ i ] and N[ 1 ][ j ]; So, W[ j ] - vector of weights of N[ 1 ][ j ] neuron.
        std::vector<Neuron> layer;
        const uint32_t inputs, outputs;
        KokhonenNN(const decltype(W) & W, const decltype(layer) & layer):W(W),layer(layer),inputs(W[0].size()),outputs(layer.size()){}; 
        ~KokhonenNN(){}
        void ResetPower(){
            for(auto &x : layer){
                x.power = 0;
            }
        }
        template<typename T> void ProcessInput(const std::vector<T> & input){
            for ( uint32_t i = 0; i < layer.size(); ++ i ) {
                for ( uint32_t j = 0; j < input.size(); ++ j ) {
                        layer[i].power += input[ j ] * W[ i ][ j ];
                }
            }
        }
        uint32_t GetMaximum(){
            uint32_t max = 0;
            for ( uint32_t i = 1; i < layer.size(); ++ i ) {
                if ( layer[ i ].power > layer[ max ].power ) {
                    max = i;
                }
            }
            return max;
        }
        static KokhonenNN* createWithRandomWeights(uint32_t inputs, uint32_t outputs){
            decltype(W) result;
            for ( uint32_t i = 0; i < outputs; ++ i ){
                result.push_back({});
                for( uint32_t j = 0; j < inputs; ++ j){
                    result[i].push_back(1.0/outputs);
                }
            }
            decltype(layer) neurons;
            neurons.push_back({});
            for(uint32_t i = 0; i < outputs; ++ i){
                neurons.push_back(Neuron());
            }
            return new KokhonenNN(result, neurons);
        }
        static KokhonenNN* createWithZeroWeights(uint32_t inputs, uint32_t outputs){
            decltype(W) result;
            for ( uint32_t i = 0; i < outputs; ++ i ){
                result.push_back({});
                for( uint32_t j = 0; j < inputs; ++ j){
                    result[i].push_back(0);
                }
            }
            decltype(layer) neurons;
            for(uint32_t i = 0; i < outputs; ++ i){
                neurons.push_back(Neuron());
            }
            return new KokhonenNN(result, neurons);
        }
        template<typename T> void Study(const std::vector<T> & input, uint32_t correct, bool check = true){
            if(check){
                this->ProcessInput(input);
                auto res = this->GetMaximum();
                this->ResetPower();
                if(res == correct){
                    return;
                }
            }
            auto &w = W[correct];
            for(uint32_t i = 0; i < inputs; ++ i) {
                w[i] = w[i] + 0.02*(input[i] - w[i]);
            }
        }
    };
}