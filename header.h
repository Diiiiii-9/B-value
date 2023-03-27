#ifndef HEADER_H
#define HEADER_H


#pragma once
#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <Eigen/QR>
#include <unsupported/Eigen/Polynomials>

using namespace std;
using namespace Eigen;

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatXXdR;
extern Matrix<double, Dynamic, Dynamic> final_E_value;
extern std::vector<double> final_vec;
extern MatrixXd matrix_source;
extern string input_file;
extern int interv;//表示取值区间为[n-interv,n=interv]
extern int m;//m表示循环间隔 例如 m=5 则为每隔5个取一个点进行计算
extern int flag; //flag表示源数据的计算列数


#endif // HEADER_H
