/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 12.05.2023
*/

#pragma once
#include "CUnaryOperator.h"

/**
 * Finds the rank of the matrix using GEM
 * the rank of the matrix is equal to the number of rows containing some non-zero values, after executing GEM.
 */
class CMatrixRank : public CUnaryOperator {
public:

    ~CMatrixRank() override = default;

    /**
     * Calls the gauss method of the matrix in parameters
     * and then counts the number of rows containing non-zero values.
     * @param matrix matrix to find the rank of
     * @return 1x1 matrix containing rank of the matrix
     */
    std::unique_ptr<CMatrix> execute (const CMatrix & matrix) const override;

    /**
     * @return a unique_ptr to a copy of this unary operator
     */
    std::unique_ptr<CUnaryOperator> clone () const override;
};
