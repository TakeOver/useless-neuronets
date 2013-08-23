#pragma once
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include "./../LodePNG/lodepng.h"
#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL
#include <vector>
/*#include <boost/mpl/vector.hpp>
#include <boost/gil/extension/dynamic_image/any_image.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
*/namespace NN{
    namespace Utils{

        template<typename T> inline
        std::vector<T> Matrix2Vec(const std::vector<std::vector<T>> & matrix){
            std::vector<T> result;
            for ( auto &vec : matrix ) {
                result.push_back(vec);
            }
        }
        std::vector<uint8_t> File2Vector(const std::string & path) {
            std::wifstream in (path);
            std::vector<uint8_t> res;
            if(!in){
                std::wcerr << L"Failed to open file with number\n";
                return {};
            }
            for( uint i = 0; i < 32; ++ i ){
                std::wstring buf;
                std::getline(in,buf);
                for( uint j = 0; j < 32; ++ j) {
                    res.push_back(buf[j] - '0');
                }
            }
            
            return res;
        }
        inline
        std::vector<std::vector<uint8_t>>& loadData(const std::string &dir, 
                                                    const std::vector<std::string>& paths, 
                                                    std::vector<std::vector<uint8_t>>& data,
                                                    std::vector<uint8_t> & labels){
            for(auto&x:paths){
                labels.push_back(x[0]-'0');
                data.push_back(File2Vector(dir+x));
            }
            return data;
        }
        inline
        uint32_t loadDataPng(const std::string &dir, 
                                                    const std::vector<std::string>& paths, 
                                                    std::vector<std::vector<uint8_t>>& data,
                                                    std::vector<uint8_t> & labels){
            uint32_t w,h;
            for(auto&x:paths){
                labels.push_back(x[0]-'0');
                std::vector<uint8_t> img;
                lodepng::decode(img,w,h,dir+x);
                data.push_back(img);
            }
            return 4*w*h;
        }

    }
}