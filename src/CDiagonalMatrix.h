/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz>
* @date 29.04.2023
*/

#pragma once
#include "CMatrix.h"
#include <vector>

/**
 * Class representing a diagonal matrix
 * Data is stored in a vector of doubles - diagonal
 */
class CDiagonalMatrix : public CMatrix {
public:

    CDiagonalMatrix () = default;

    /**
     * Constructs a diagonal matrix with the numbers on the diagonal from the cpy vector
     * Sets zeroes elsewhere
     * @param cpy the vector to be copied from
     */
    explicit CDiagonalMatrix (const std::vector<double> & cpy);

    ~CDiagonalMatrix() override = default;

    /**
     * Prints the matrix to the output as such:
     * | 1 2 |
     * | 3 4 |
     * @param os ostream to print into
     */
    void print (std::ostream & os) const override;

    /**
     * Creates a copy of the matrix
     * @return a unique_ptr to the copy of the matrix
     */
    std::unique_ptr<CMatrix> clone () const override;

    /**
     * Returns a number from the matrix, if rowIndex != colIndex, automatically returns a zero
     * @param rowIndex rowIndex of the element
     * @param colIndex columnIndex of the element
     * @return value of the element
     */
    double get (uint32_t rowIndex, uint32_t colIndex) const override;

    /**
     * Returns a copy of this matrix (a diagonal matrix is symmetrical)
     * @return a unique_ptr to the copy of the matrix
     */
    std::unique_ptr<CMatrix> transpose () const override;

    /**
     * Returns a copy of this matrix (a diagonal matrix is automatically in the upper triangular form)
     * @return a unique_ptr to the copy of the matrix
     */
    std::unique_ptr<CMatrix> gauss () const override;

    /**
     * Creates a matrix with inverse elements to the elements on the diagonal
     * @return a unique_ptr to the copy of the matrix
     */
    std::unique_ptr<CMatrix> inverse () const override;

    /**
     * Writes the parameters of the matrix into the ofstream in the parameters
     * @param output ofstream to write into
     */
    void write (std::ofstream & output) const override;

private:

    /**
     * Vector containing elements on the diagonal
     */
    std::vector<double> m_Data;
};
