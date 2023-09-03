/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 18.05.2023
*/

#include "CInverse.h"
#include "CDeterminant.h"
#include <cfloat>
#include <cmath>

std::unique_ptr<CMatrix> CInverse::execute(const CMatrix & matrix) const {

    if (matrix.colCount() != matrix.rowCount() || fabs(CDeterminant().execute(matrix)->get(0,0)) <= 1000*DBL_EPSILON)
        throw std::invalid_argument("ERROR: Matrix does not a have an inverse matrix.");

    return matrix.inverse();
}

std::unique_ptr<CUnaryOperator> CInverse::clone() const {

    return std::make_unique<CInverse>(*this);
}
