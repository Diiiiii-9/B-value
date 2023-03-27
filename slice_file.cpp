#include "mainwindow.h"
#include "regression.h"
#include "header.h"
#include <algorithm>

void MainWindow::saveData(string fileName, MatrixXd  matrix)
{
    const static IOFormat CSVFormat(FullPrecision, DontAlignCols, ", ", "\n");

    ofstream file(fileName);
    if (file.is_open())
    {
        file << matrix.format(CSVFormat);
        file.close();
    }
}

MatrixXd MainWindow::openData(string fileToOpen)
{
    //cout << "open data:bingo1" << endl;
    // the matrix entries are stored in this variable row-wise.
    vector<double> matrixEntries;

    // in this object we store the data from the matrix
    ifstream matrixDataFile(fileToOpen);

    // this variable is used to store the row of the matrix that contains commas
    string matrixRowString;

    // this variable is used to store the matrix entry;
    string matrixEntry;

    // this variable is used to track the number of rows
    int matrixRowNumber = 0;

    getline(matrixDataFile, matrixRowString);//先读取第一行数据，并且丢掉

    while (getline(matrixDataFile, matrixRowString)) // here we read a row by row of matrixDataFile and store every line into the string variable matrixRowString
    {
        stringstream matrixRowStringStream(matrixRowString); //convert matrixRowString that is a string to a stream variable.

        while (getline(matrixRowStringStream, matrixEntry, ',')) // here we read pieces of the stream matrixRowStringStream until every comma, and store the resulting character into the matrixEntry
        {
            matrixEntries.push_back(stod(matrixEntry));   //here we convert the string to double and fill in the row vector storing all the matrix entries
        }
        matrixRowNumber++; //update the column numbers
    }

    // here we convet the vector variable into the matrix and return the resulting object,
    // note that matrixEntries.data() is the pointer to the first memory location at which the entries of the vector matrixEntries are stored;

    if(matrixRowNumber == 0)
        cout << "matrix == 0";


    return Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(matrixEntries.data(), matrixRowNumber, matrixEntries.size() / matrixRowNumber);

}



void MainWindow::sliceMatrix(MatrixXd& srcMatrixs)
{

    int n = 0;//将计算初始到第一个点

    cout << srcMatrixs.rows()-interv << endl;

    for (n = 0; n < srcMatrixs.rows(); n=n+m )
    {
        cout << n << ":";


        MatrixXd cal_mat = srcMatrixs.middleRows(max(0,n-interv), min(int(srcMatrixs.rows()),n+interv)-max(0,n-interv));

        final_vec.push_back(srcMatrixs(n,0));

        cal_slope(cal_mat);
    }

    if((srcMatrixs.rows()-1) % m != 0)
    {
        n = srcMatrixs.rows()-1;

        MatrixXd cal_mat = srcMatrixs.middleRows(max(0,n-interv), min(int(srcMatrixs.rows()),n+interv)-max(0,n-interv));

        final_vec.push_back(srcMatrixs(n,0));

        cal_slope(cal_mat);
    }

}
