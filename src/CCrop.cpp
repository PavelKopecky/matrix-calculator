/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 13.05.2023
*/

#include "CCrop.h"
#include "CMatrixPersistor.h"

std::unique_ptr<CMatrix> CCrop::execute(const CMatrix & matrix, const CMatrix & offset) const {

    if (offset.get(0,0) + offset.get(1,0) > matrix.rowCount() ||
            offset.get(0,1) + offset.get(1,1) > matrix.colCount()) throw std::invalid_argument("ERROR: Crop out of bounds.");
    else if (offset.rowCount() != 2 || offset.colCount() != 2) throw std::invalid_argument("ERROR: Offset matrix must be 2x2.");

    std::vector<std::vector<double>> newMatrix;

    for (uint32_t i = 0; i < offset.get(0,0); ++i) {
        std::vector<double> newRow;
        for (uint32_t j = 0; j < offset.get(0,1); ++j) {
            double newNumber = matrix.get(i + (uint32_t) offset.get(1,0), j + (uint32_t) offset.get(1,1));
            newRow.push_back(newNumber);
        }
        newMatrix.push_back(newRow);
    }

    return CMatrixPersistor()(newMatrix);
}

std::unique_ptr<CBinaryOperator> CCrop::clone() const {

    return std::make_unique<CCrop>(*this);
}
