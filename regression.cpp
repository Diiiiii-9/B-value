#include "regression.h"
#include "header.h"
#include "mainwindow.h"
#include <stdio.h>
#include <math.h>

regression::regression()
{
    coeff = 0;
    constTerm = 0;
    sum_y = 0;
    sum_y_square = 0;
    sum_x_square = 0;
    sum_x = 0;
    sum_xy = 0;
}

void removeRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove)
{
    unsigned int numRows = matrix.rows()-1;
    unsigned int numCols = matrix.cols();

    if( rowToRemove < numRows )
        matrix.block(rowToRemove,0,numRows-rowToRemove,numCols) = matrix.block(rowToRemove+1,0,numRows-rowToRemove,numCols);

    matrix.conservativeResize(numRows,numCols);
}

void removeColumn(Eigen::MatrixXd& matrix, unsigned int colToRemove)
{
    unsigned int numRows = matrix.rows();
    unsigned int numCols = matrix.cols()-1;

    if( colToRemove < numCols )
        matrix.block(0,colToRemove,numRows,numCols-colToRemove) = matrix.block(0,colToRemove+1,numRows,numCols-colToRemove);

    matrix.conservativeResize(numRows,numCols);
}

// Function that calculate the coefficient/
// slope of the best fitting line
void regression::calculateCoefficient()
{
    float N = x.size();
    float numerator
        = (N * sum_xy - sum_x * sum_y);
    float denominator
        = (N * sum_x_square - sum_x * sum_x);

    coeff = numerator / denominator;
    //cout << "coeff:" << coeff << endl;
}


// Member function that will calculate
// the constant term of the best
// fitting line
void regression::calculateConstantTerm()
{
    float N = x.size();
    float numerator
        = (sum_y * sum_x_square - sum_x * sum_xy);
    float denominator
        = (N * sum_x_square - sum_x * sum_x);
    constTerm = numerator / denominator;
}


// Function that return the number
// of entries (xi, yi) in the data set
int regression::sizeOfData()
{
    return x.size();
}

// Function that return the coefficient/
// slope of the best fitting line
float regression::coefficient()
{
    if (coeff == 0)
        calculateCoefficient();
    return coeff;
}


// Function that return the constant
// term of the best fitting line
float regression::constant()
{
    if (constTerm == 0)
        calculateConstantTerm();
    return constTerm;
}


// Function that print the best
// fitting line
void regression::PrintBestFittingLine()
{

    calculateCoefficient();
    calculateConstantTerm();
    //cout << "The best slope is k = " << coeff << endl;
    final_vec.push_back(coeff*(-1));

    if(coeff>0)
        cout << "coeff is:" << coeff << endl;
}

// Function to take input from the dataset
void regression::takeInput(MatrixXd cal_mat)
{

    for (int i = 0; i < cal_mat.rows(); i++) {

        float xi;
        float yi;

        xi = cal_mat(i,0);
        yi = cal_mat(i,1);

        sum_xy += xi * yi;
        sum_x += xi;
        sum_y += yi;
        sum_x_square += xi * xi;
        sum_y_square += yi * yi;
        x.push_back(xi);
        y.push_back(yi);
    }

}


// Function to predict the value
// corresponding to some input
float regression::predict(float x)
{
    return coeff * x + constTerm;
}

// Function that returns overall
// sum of square of errors
float regression::errorSquare()
{
    float ans = 0;
    for (int i = 0;
         i < x.size(); i++) {
        ans += ((predict(x[i]) - y[i])
                * (predict(x[i]) - y[i]));
    }
    return ans;
}

// Functions that return the error
// i.e the difference between the
// actual value and value predicted
// by our model
float regression::errorIn(float num)
{
    for (int i = 0;
         i < x.size(); i++) {
        if (num == x[i]) {
            return (y[i] - predict(x[i]));
        }
    }
    return 0;
}


// Driver code
void cal_slope(MatrixXd cal_mat)
{
    regression reg;

    MatrixXd slice_cal_mat = MatrixXd::Zero(13,2);//一共十三个x值

    for(int i = 0; i < slice_cal_mat.rows(); i++)
    {
        slice_cal_mat(i,0)=28+2*i;
    }

    for(int i = 0; i < cal_mat.rows(); i++)
    {
        for(int j = 0; j < slice_cal_mat.rows(); j++)
        {
            if(cal_mat(i,1) > slice_cal_mat(j,0))
            {
                slice_cal_mat(j,1)++;
            }
        }
    }


    //删除-inf的变量
    for(int k = slice_cal_mat.rows()-1; k >= 0 ; k--)
    {
        slice_cal_mat(k,0) = slice_cal_mat(k,0) / 20;
        if(slice_cal_mat(k,1)==0)
        {
            removeRow(slice_cal_mat,k);
        }
        else
        {
            slice_cal_mat(k,1)=log10(slice_cal_mat(k,1));
        }
    }

    //cout << slice_cal_mat ;

    // Calling function takeInput to
    // take input of n pairs
    reg.takeInput(slice_cal_mat);

    // Printing the best fitting line
    reg.PrintBestFittingLine();

//        cout << "--" << reg.errorSquare() << "--";

    //cout << endl;

}


