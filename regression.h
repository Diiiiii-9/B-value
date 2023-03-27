#ifndef REGRESSION_H
#define REGRESSION_H
#include "header.h"

class regression
{
    // Dynamic array which is going
    // to contain all (i-th x)
    vector<float> x;

    // Dynamic array which is going
    // to contain all (i-th y)
    vector<float> y;

    // Store the coefficient/slope in
    // the best fitting line
    float coeff;

    // Store the constant term in
    // the best fitting line
    float constTerm;

    // Contains sum of product of
    // all (i-th x) and (i-th y)
    float sum_xy;

    // Contains sum of all (i-th x)
    float sum_x;

    // Contains sum of all (i-th y)
    float sum_y;

    // Contains sum of square of
    // all (i-th x)
    float sum_x_square;

    // Contains sum of square of
    // all (i-th y)
    float sum_y_square;


public:
    // Constructor to provide the default values to all the terms in the object of class regression
    regression();


    // Function that calculate the coefficient/
    // slope of the best fitting line
    void calculateCoefficient();

    void calculateConstantTerm();

    // Function that return the number
    // of entries (xi, yi) in the data set
    int sizeOfData();

    // Function that return the coefficient/
    // slope of the best fitting line
    float coefficient();

    float constant();

    // Function that print the best
    // fitting line
    void PrintBestFittingLine();


    // Function to take input from the dataset
    void takeInput(MatrixXd cal_mat);

    // Function to predict the value
    // corresponding to some input
    float predict(float x);


    // Function that returns overall
    // sum of square of errors
    float errorSquare();


    // Functions that return the error
    // i.e the difference between the
    // actual value and value predicted
    // by our model
    float errorIn(float num);

};

// Driver code
void cal_slope(MatrixXd cal_mat);

#endif // REGRESSION_H
