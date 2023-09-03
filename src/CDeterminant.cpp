/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 09.05.2023
*/

#include "CDeterminant.h"
#include "CDiagonalMatrix.h"
#include "CDenseMatrix.h"

std::unique_ptr<CMatrix> CDeterminant::execute (const CMatrix & matrix) const {

    double determinant = 0;

    if (matrix.rowCount() != matrix.colCount()) throw std::invalid_argument("ERROR: Determinant - not a square matrix.");
    else if (matrix.rowCount() == 2) {
        determinant = matrix.get(0,0)*matrix.get(1,1) - matrix.get(1,0)*matrix.get(0,1);
        return CDiagonalMatrix({determinant}).clone();
    } else if (matrix.rowCount() == 1) return matrix.clone();

    /**
     * Multiply numbers on the first row with matrix created from the remaining free rows and columns
     * Eg:
     * | (1) 2  3 | Multiply one with the determinant of matrix [[1,2],[2,11]]
     * | 5 (1  2) |
     * | 4 (2 11) |
     * Sign must change for every column
     */

    int sgn = 1;
    for (uint32_t i = 0; i < matrix.rowCount(); ++i) {

        std::vector<std::vector<double>> newMatrixRows;
        for (uint32_t k = 1; k < matrix.rowCount(); ++k) {
            std::vector<double> newRow;
            for (uint32_t j = 0; j < matrix.colCount(); ++j) {
                if (j == i) continue;
                newRow.push_back(matrix.get(k,j));
            }
            newMatrixRows.push_back(newRow);
        }
        CDenseMatrix newMatrix(newMatrixRows);

        determinant += sgn * matrix.get(0, i) * CDeterminant().execute(newMatrix)->get(0,0);
        sgn *= -1;
    }

    return CDiagonalMatrix({determinant}).clone();
}

std::unique_ptr<CUnaryOperator> CDeterminant::clone() const {

    return std::make_unique<CDeterminant>(*this);
}