/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 30.04.2023
*/

#include "CSubtract.h"
#include "CMatrix.h"
#include "CMatrixPersistor.h"
#include <vector>

std::unique_ptr<CMatrix> CSubtract::execute (const CMatrix &lhs, const CMatrix &rhs) const {

    if (lhs.colCount() != rhs.colCount() || lhs.rowCount() != rhs.rowCount()) {
        throw std::invalid_argument("ERROR: Subtraction - incompatible matrices.");
    }

    std::vector<std::vector<double>> data;

    for (uint32_t i = 0; i < rhs.rowCount(); ++i) {
        std::vector<double> newRow;
        for (uint32_t j = 0; j < rhs.colCount(); ++j) {
            newRow.push_back(lhs.get(i, j) - rhs.get(i, j));
        }
        data.push_back(newRow);
    }

    return CMatrixPersistor()(data);
}

std::unique_ptr<CBinaryOperator> CSubtract::clone() const {

    return std::make_unique<CSubtract>(*this);
}
