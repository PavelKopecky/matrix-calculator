/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 18.05.2023
*/


#pragma once
#include "CUnaryOperator.h"

/** Unary operator class, which finds an inverse matrix for a square matrix*/
class CInverse : public CUnaryOperator {
public:

    ~CInverse() override = default;

    /**
     * First checks if the determinant of the matrix does not equal 0 or if the matrix is not square.
     * If det == 0 or row count != column count, an inverse matrix does not exist and an exception is thrown.
     * If determinant != 0, calls the inverse method of the matrix
     * @param matrix matrix to find the inverse matrix to
     * @return a pointer to the inverse matrix
     */
    std::unique_ptr<CMatrix> execute (const CMatrix & matrix) const override;

    /**
     * @return a unique_ptr to a copy of this unary operator
     */
    std::unique_ptr<CUnaryOperator> clone () const override;
};
