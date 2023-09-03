/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 14.05.2023
*/


#pragma once
#include "CBinaryOperator.h"
#include <vector>

/**
 * Merges two matrices together. Primarily joins rows, secondarily joins columns. If the matrices cannot be joined, throws an exception.
 */
class CMerge : public CBinaryOperator {
public:

    ~CMerge() override = default;

    /**
     * Merges two matrices together. Primarily joins rows, secondarily joins columns. If the matrices cannot be joined, throws an exception.
     * @param lhs matrix to join onto (to the right / bottom side)
     * @param rhs matrix to be joined
     * @return unique_ptr to the newly created matrix
     */
    std::unique_ptr<CMatrix> execute (const CMatrix & lhs, const CMatrix & rhs) const override;

    /**
     * @return a unique_ptr to a copy of this binary operator
     */
    std::unique_ptr<CBinaryOperator> clone () const override;

private:
    /**
     * Joins the rhs matrix to the right of matrix lhs
     * @param lhs matrix to join onto
     * @param rhs matrix to be joined
     * @return m x n matrix as a vector of vectors of doubles
     */
    std::vector<std::vector<double>> rightMerge (const CMatrix & lhs, const CMatrix & rhs) const;

    /**
     * Joins the rhs matrix to the bottom of matrix lhs
     * @param lhs matrix to join onto
     * @param rhs matrix to be joined
     * @return m x n matrix as a vector of vectors of doubles
     */
    std::vector<std::vector<double>> bottomMerge (const CMatrix & lhs, const CMatrix & rhs) const;
};
