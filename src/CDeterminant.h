/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 09.05.2023
*/

#pragma once
#include "CUnaryOperator.h"

/**
 * Class which finds the determinant of a square matrix.
 */
class CDeterminant : public CUnaryOperator {
public:

    ~CDeterminant() override = default;

    /**
     * Finds the determinant of a square matrix
     * Multiplies an element in the first row with the determinant of the square matrix left underneath (recursively)
     * Repeats for each element in the first row
     * @param matrix a matrix to find the determinant of
     * @return determinant - matrix 1x1
     */
    std::unique_ptr<CMatrix> execute (const CMatrix & matrix) const override;

    /**
     * @return a unique_ptr to a copy of this unary operator
     */
    std::unique_ptr<CUnaryOperator> clone () const override;
};
