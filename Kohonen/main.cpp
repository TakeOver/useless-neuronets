#include "Utils.hpp"
#include "Kokhonen.hpp"
#include "../tests/paths.h"
int main(int argc, char const *argv[])
{
    auto nn = NN::KokhonenNN::createWithZeroWeights(1024, 10);
    std::vector<std::vector<uint8_t>> traindata,testdata;
    std::vector<uint8_t> trainlabels,testlabels;
    NN::Utils::loadData("./../tests/testDigits/",testing_paths,testdata,testlabels);
    NN::Utils::loadData("./../tests/trainingDigits/",training_paths,traindata,trainlabels);
    bool interactive = true;
    std::wcout << L"Interactive mode? [y/n]";
    wchar_t c;
    std::wcin >> c;
    std::wcout << L'\n';
    interactive = c == L'y';
    for(uint32_t i = 0; i< traindata.size(); ++ i){
        nn->Study(traindata[i],trainlabels[i]);
        nn->ResetPower();
    }
    uint32_t ok = 0;
    for(uint32_t i =0; i < testdata.size(); ++ i ){
        for(uint k = 0; interactive && k < 32; ++ k){
            for(uint j = 0; j < 32; ++j){
                std::wcout << (int)testdata[i][k*32+j];
            }
            std::wcout << L'\n';
        }
        std::wcout << L"expected " << testlabels[i] << " matched ";
        nn->ProcessInput(testdata[i]);
        uint32_t max;
        std::wcout << (max=nn->GetMaximum()) << L"\n";
        ok+= (max == testlabels[i]);
        if(max != testlabels[i]){
            nn->Study(testdata[i],testlabels[i],false);
        }
        nn->ResetPower();
        if(interactive){
            std::wcin.get();
        }
    }
    std::wcout << L"KokhonenNN matched " << ((100.0*ok)/testlabels.size()) << "% tests\n";
    return 0;
}