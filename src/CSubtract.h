/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 30.04.2023
*/

#pragma once
#include "CBinaryOperator.h"
#include <memory>

/**
 * Represents standard subtraction between two matrices OF THE SAME SIZE
 */
class CSubtract : public CBinaryOperator {
public:

    ~CSubtract() override = default;

    /**
     * Executes the A - B operation
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

