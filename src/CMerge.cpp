/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 14.05.2023
*/

#include "CMerge.h"
#include "CDenseMatrix.h"
#include "CMatrixPersistor.h"
#include <vector>

std::unique_ptr<CMatrix> CMerge::execute(const CMatrix &lhs, const CMatrix &rhs) const {

    std::vector<std::vector<double>> data;

    if (lhs.rowCount() == rhs.rowCount()) {
        data = CMerge::rightMerge(lhs, rhs);
    } else if (lhs.colCount() == rhs.colCount()) {
        data = CMerge::bottomMerge(lhs, rhs);
    } else throw std::invalid_argument("ERROR: Merge - incompatible matrices.");

     return CMatrixPersistor()(data);
}

std::vector<std::vector<double>> CMerge::rightMerge(const CMatrix & lhs, const CMatrix & rhs) const {

    std::vector<std::vector<double>> data;

    for (uint32_t i = 0; i < lhs.rowCount(); ++i) {
        std::vector<double> newRow;
        for (uint32_t j = 0; j < lhs.colCount(); ++j) {
            double newNumber = lhs.get(i,j);
            newRow.push_back(newNumber);
        }
        for (uint32_t j = 0; j < rhs.colCount(); ++j) {
            double newNumber = rhs.get(i,j);
            newRow.push_back(newNumber);
        }
        data.push_back(newRow);
    }

    return data;
}

std::vector<std::vector<double>> CMerge::bottomMerge(const CMatrix & lhs, const CMatrix & rhs) const {

    std::vector<std::vector<double>> data;

    for (uint32_t i = 0; i < lhs.rowCount(); ++i) {
        std::vector<double> newRow;
        for (uint32_t j = 0; j < lhs.colCount(); ++j) {
            double newNumber = lhs.get(i,j);
            newRow.push_back(newNumber);
        }
        data.push_back(newRow);
    }

    for (uint32_t i = 0; i < rhs.rowCount(); ++i) {
        std::vector<double> newRow;
        for (uint32_t j = 0; j < rhs.colCount(); ++j) {
            double newNumber = rhs.get(i,j);
            newRow.push_back(newNumber);
        }
        data.push_back(newRow);
    }

    return data;
}

std::unique_ptr<CBinaryOperator> CMerge::clone() const {

    return std::make_unique<CMerge>(*this);
}
