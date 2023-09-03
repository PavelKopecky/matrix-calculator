/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 11.05.2023
*/


#pragma once
#include "CUnaryOperator.h"

/**
 * A unary operator which executes the Gaussian elimination method on a given matrix
 * returns a unique_ptr to the new matrix
 */
class CGauss : public CUnaryOperator {
public:

    ~CGauss() override = default;

    /**
     * Calls the gauss method of the matrix in parameters
     * @param matrix matrix to use the GEM on
     * @return a pointer to the new copy of the matrix
     */
    std::unique_ptr<CMatrix> execute (const CMatrix & matrix) const override;

    /**
     * @return a unique_ptr to a copy of this unary operator
     */
    std::unique_ptr<CUnaryOperator> clone () const override;
};
