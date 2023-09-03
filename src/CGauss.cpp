/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 11.05.2023
*/

#include "CGauss.h"

std::unique_ptr<CMatrix> CGauss::execute(const CMatrix &matrix) const {

    return matrix.gauss();
}

std::unique_ptr<CUnaryOperator> CGauss::clone() const {

    return std::make_unique<CGauss>(*this);
}
