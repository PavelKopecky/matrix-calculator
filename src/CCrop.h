/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 13.05.2023
*/


#pragma once
#include "CBinaryOperator.h"

/**
 * Crops matrix with dimensions received as a 2x2 matrix
 * |    x    ,    y     |
 * | offset x, offset y |
 */
class CCrop : public CBinaryOperator {
public:

    ~CCrop() override = default;

    /**
     * Crops the matrix found in "matrix" with offset and dimensions found in "offset"
     * @param matrix matrix to crop
     * @param offset 2x2 matrix which determines how to crop the matrix
     * @return unique_ptr to the cropped matrix
     */
    std::unique_ptr<CMatrix> execute (const CMatrix & matrix, const CMatrix & offset) const override;

    /**
     * @return a unique_ptr to a copy of this binary operator
     */
    std::unique_ptr<CBinaryOperator> clone () const override;
};
