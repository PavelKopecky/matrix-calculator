/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 01.05.2023
*/

#pragma once
#include "CBinaryOperator.h"
#include <memory>

/**
 * Represents multiplication between two compatible matrices A, B
 * Requirement for multiplication of two matrices: Column count A == Row count B
 */
class CMultiply : public CBinaryOperator {
public:

    ~CMultiply() override = default;

    /**
     * Executes the A * B operation
     * @param lhs Matrix A
     * @param rhs Matrix B
     * @return (unique pointer to the) result matrix of the operation
     */
    std::unique_ptr<CMatrix> execute(const CMatrix &lhs, const CMatrix &rhs) const override;

    /**
     * @return a unique_ptr to a copy of this binary operator
     */
    std::unique_ptr<CBinaryOperator> clone () const override;
};
