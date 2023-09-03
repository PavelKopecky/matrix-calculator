/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 29.04.2023
*/

#pragma once
#include <cstdint>
#include "CMatrix.h"

/**
 * An abstract class representing a binary operator such as *, -, +
 */
class CBinaryOperator {
public:

    CBinaryOperator () = default;

    virtual ~CBinaryOperator() = default;

    /**
     * Virtual method, executes given operation based on its type
     * lhs + rhs, lhs * rhs, ...
     */
    virtual std::unique_ptr<CMatrix> execute (const CMatrix & lhs, const CMatrix & rhs) const = 0;

    /**
     * Virtual method, which creates a copy of a particular binary operator
     * @return a unique_ptr to a copy of this unary binary
     */
    virtual std::unique_ptr<CBinaryOperator> clone () const = 0;
};
