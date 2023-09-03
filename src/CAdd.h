/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 29.04.2023
*/

#pragma once
#include "CBinaryOperator.h"
#include <memory>

/**
 * Represents standard addition between two matrices OF THE SAME SIZE
 */
class CAdd : public CBinaryOperator {
public:

    ~CAdd () override = default;

    /**
     * Executes the A + B operation, if defined
     * @param lhs A
     * @param rhs B
     * @return (unique pointer to the) result matrix of the operation
     */
    std::unique_ptr<CMatrix> execute(const CMatrix &lhs, const CMatrix &rhs) const override;

    /**
     * @return a unique_ptr to a copy of this binary operator
     */
    std::unique_ptr<CBinaryOperator> clone () const override;
};
