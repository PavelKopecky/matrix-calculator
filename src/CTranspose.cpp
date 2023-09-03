/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 07.05.2023
*/

#include "CTranspose.h"
#include <vector>

std::unique_ptr<CMatrix> CTranspose::execute(const CMatrix &matrix) const {

    return matrix.transpose();
}

std::unique_ptr<CUnaryOperator> CTranspose::clone() const {

    return std::make_unique<CTranspose>(*this);
}