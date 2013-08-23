#include "Utils.hpp"
int main(int argc, char const *argv[])
{
    std::vector<uint8_t> tmp;
    std::vector<double> norm;
    unsigned int w,h;
    lodepng::decode(tmp, w, h, "test.png");
    tmp = NN::Utils::Normallized2Png(NN::Utils::NormallizePngMax(tmp));
    lodepng::encode("test_res.png", tmp, w, h);
    return 0;
}