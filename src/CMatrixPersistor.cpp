/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 16.05.2023
*/

#include "CMatrixPersistor.h"
#include <cfloat>
#include <algorithm>
#include <cmath>

std::unique_ptr<CMatrix> CMatrixPersistor::operator()(const std::vector<std::vector<double>> & data) const {

    uint32_t rowCount = data.size();
    uint32_t colCount = data[0].size();
    bool diagonal = rowCount == colCount;
    bool sparse = true;
    uint32_t limit = (rowCount <= colCount) ? rowCount : colCount;
    uint32_t count = 0;

    for (uint32_t i = 0; i < rowCount; ++i) {
        for (uint32_t j = 0; j < colCount; ++j) {
            if (fabs(data[i][j]) >= 100*DBL_EPSILON) {
                if (diagonal && i != j) diagonal = false;
                if (sparse && ++count > limit) sparse = false;
            }
            if (!diagonal && !sparse) break;
        }
        if (!diagonal && !sparse) break;
    }


    if (diagonal) {
        std::vector<double> diagonalVector;
        for (uint32_t i = 0; i < rowCount; i++) {
            diagonalVector.push_back(data[i][i]);
        }
        return CDiagonalMatrix(diagonalVector).clone();

    } else if (sparse) {
        std::vector<CTuple> sparseVector;
        for (uint32_t i = 0; i < rowCount; ++i) {
            for (uint32_t j = 0; j < colCount; ++j) {
                if (fabs(data[i][j]) >= 100*DBL_EPSILON) {
                    sparseVector.emplace_back(i, j, data[i][j]);
                }
            }
        }
        return CSparseMatrix(sparseVector, rowCount, colCount).clone();

    } else {
        return CDenseMatrix(data).clone();
    }
}

std::unique_ptr<CMatrix> CMatrixPersistor::operator()(std::string && data) const {

    //https://en.cppreference.com/w/cpp/algorithm/remove
    auto strEnd = std::remove(data.begin(), data.end(), ' '); //removes spaces
    data.erase(strEnd, data.end()); //shrinks the string back

    if (data[0] != '[' || data[data.size() - 1] != ']' || data[1] != '[')
            throw std::invalid_argument("ERROR: Failed to create the matrix");

    uint32_t index = 1;
    std::vector<std::vector<double>> newMatrix;
    bool dot = false;

    while (true) {
        std::vector<double> newRow;

        while (data[index++] != ']') {
            std::string newNumber; //= ""
            while (data[index] != ',' && data[index] != ']') {

                if ((data[index] >= '0' && data[index] <= '9') || data[index] == '.' || data[index] == '-') {
                    if (data[index] == '.') {
                        if (dot || newNumber.empty() || (newNumber.size() == 1 && newNumber[0] == '-')) throw std::invalid_argument("ERROR: Failed to create the matrix");
                        else dot = true;
                    }
                    else if (data[index] == '-' && !newNumber.empty()) throw std::invalid_argument("ERROR: Failed to create the matrix");

                    newNumber.push_back(data[index++]);
                } else throw std::invalid_argument("ERROR: Failed to create the matrix");
            }
            if (newNumber.empty()) throw std::invalid_argument("ERROR: Failed to create the matrix");
            newRow.push_back(std::atof(newNumber.c_str()));
            dot = false;
        }

        newMatrix.push_back(newRow);

        // ..3]]
        //     ^
        if (data[index] == ']') break;

        //..],[..
        //   ^^
        if (data[index++] != ',' || data[index] != '[') throw std::invalid_argument("ERROR: Failed to create the matrix");
    }

    if (index != data.size() - 1) {
        throw std::invalid_argument("ERROR: Failed to create the matrix");
    }

    //rows have different lengths
    for (uint32_t i = 1; i < newMatrix.size(); ++i) {
        if (newMatrix[i-1].size() != newMatrix[i].size()) throw std::invalid_argument("ERROR: Failed to create the matrix");
    }

    return this->operator()(newMatrix);
}
