/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 07.05.2023
*/

#pragma once
#include "CUnaryOperator.h"

/**
 * A unary operator which transposes the matrix
 */
class CTranspose : public CUnaryOperator {
public:

    ~CTranspose() override = default;

    /**
     * Calls the transpose method of the matrix in parameters
     * @param matrix to be transposed
     * @return a pointer to the transposed copy of the matrix
     */
    std::unique_ptr<CMatrix> execute (const CMatrix & matrix) const override;

    /**
     * @return a unique_ptr to a copy of this unary operator
     */
    std::unique_ptr<CUnaryOperator> clone () const override;
};
