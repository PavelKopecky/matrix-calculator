/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 01.05.2023
*/

#include "CMultiply.h"
#include "CMatrix.h"
#include "CMatrixPersistor.h"
#include <vector>

std::unique_ptr<CMatrix> CMultiply::execute (const CMatrix &lhs, const CMatrix &rhs) const {

    if (lhs.colCount() != rhs.rowCount()) {
        throw std::invalid_argument("ERROR: Multiplication - incompatible matrices.");
    }

    std::vector<std::vector<double>> data;

    for (uint32_t i = 0; i < lhs.rowCount(); ++i) {
        std::vector<double> newRow;
        for (uint32_t j = 0; j < rhs.colCount(); ++j) {
            double newNumber = 0;
            for (uint32_t k = 0; k < rhs.rowCount(); k++) {
                newNumber += lhs.get(i, k) * rhs.get(k, j);
            }
            newRow.push_back(newNumber);
        }
        data.push_back(newRow);
    }

    return CMatrixPersistor()(data);
}

std::unique_ptr<CBinaryOperator> CMultiply::clone() const {

    return std::make_unique<CMultiply>(*this);
}