/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 12.05.2023
*/

#include "CMatrixRank.h"
#include "CMatrix.h"
#include "CDiagonalMatrix.h"
#include <cfloat>
#include <cmath>

std::unique_ptr<CMatrix> CMatrixRank::execute (const CMatrix & matrix) const {

    double rank = matrix.rowCount();
    std::unique_ptr<CMatrix> gaussianMatrix = matrix.gauss();
    bool emptyRow = true;

    for (uint32_t i = 0; i < matrix.rowCount(); ++i) {
        for (uint32_t j = 0; j < matrix.colCount(); ++j) {
            if (fabs(gaussianMatrix->get(matrix.rowCount() - i - 1, matrix.colCount() - j - 1)) >= 100*DBL_EPSILON) {
                emptyRow = false;
                break;
            }
        }

        if (emptyRow) {
            rank--;
        } else break; //Necessarily the last row
    }

    return CDiagonalMatrix({rank}).clone();
}

std::unique_ptr<CUnaryOperator> CMatrixRank::clone() const {

    return std::make_unique<CMatrixRank>(*this);
}