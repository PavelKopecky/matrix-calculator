/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 06.05.2023
*/

#pragma once
#include "CMatrix.h"

/**
 * Abstract class representing a unary operator such transposition, GEM, etc.
 */
class CUnaryOperator {
public:

    CUnaryOperator() = default;

    virtual ~CUnaryOperator() = default;

    /**
     * Virtual method, executes given operation based on its type
     * returns a matrix
     */
    virtual std::unique_ptr<CMatrix> execute (const CMatrix & matrix) const = 0;

    /**
     * Virtual method, which creates a copy of a particular unary operator
     * @return a unique_ptr to a copy of this unary operator
     */
    virtual std::unique_ptr<CUnaryOperator> clone () const = 0;
};
