#include "Utils.hpp"
#include "Kohonen.hpp"
#include "./../LodePNG/lodepng.h"
#include "./../tests/paths.h"
int main(int argc, char const *argv[])
{       
    std::vector<unsigned char> img;
    uint size;
    std::vector<std::vector<uint8_t>> train;
    std::vector<uint8_t> trainlabels;
    size = NN::Utils::loadDataPng("./../tests/Png/train/", test_png, train, trainlabels);
    NN::KohonenNN* nn = NN::KohonenNN::createWithZeroWeights(size, 10);
    for(uint i = 0; i < train.size(); ++ i ){
        nn->Study(train[i], trainlabels[i],false);
    }

    for(uint i = 0; i < train.size(); ++ i ){
        nn->ProcessInput(train[i]);
        std::wcout << L"expected " << trainlabels[i] << L" found " << nn->GetMaximum() << L"\n";
        nn->ResetPower();
    }
    return 0;
}