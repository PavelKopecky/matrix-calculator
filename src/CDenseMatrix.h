/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz>
* @date 29.04.2023
*/

#pragma once
#include "CMatrix.h"
#include <vector>

/**
 * Class representing a dense matrix
 * Data is stored in a vector of rows, row is a vector of doubles
 */
class CDenseMatrix : public CMatrix {
public:

    CDenseMatrix () = default;

    /**
     * Constructs a dense matrix with a 2D vector of doubles
     * @param cpy 2D vector to be copied
     */
    explicit CDenseMatrix (const std::vector<std::vector<double>> & cpy);

    ~CDenseMatrix() override = default;

    /**
     * Prints the matrix to the output as such:
     * | 1 2 |
     * | 3 4 |
     * @param os ostream to print into
     */
    void print (std::ostream & os) const override;

    /**
     * Clones this matrix.
     * @return unique_ptr to the copy of the matrix
     */
    std::unique_ptr<CMatrix> clone () const override;

    /**
     * Returns the element on the [rowIndex][colIndex] position
     * @param rowIndex row index
     * @param colIndex column index
     * @return value of the element
     */
    double get (uint32_t rowIndex, uint32_t colIndex) const override;

    /**
     * Transposes this (its copy) matrix -- swaps rows and columns
     * @return unique_ptr to the transposed matrix
     */
    std::unique_ptr<CMatrix> transpose () const override;

    /**
     * Executes the gaussian elimination method on this matrix
     * @return a unique_ptr to the newly created matrix
     */
    std::unique_ptr<CMatrix> gauss () const override;

    /**
     * Step 1: executes steps of the gaussian elimination method until there are zeroes everywhere except for the diagonal
     * Step 2: divide each row by an inverse number to the number on the diagonal
     * Apply the same actions on an identity matrix of the same size.
     * When the original matrix becomes an identity matrix, the former identity matrix will be our inverse matrix
     */
    std::unique_ptr<CMatrix> inverse () const override;

    /**
     * Writes parameters and elements of the matrix into an output file stream as such:
     * (matrixName)(matrixType) (rowCount) (columnCount) (... data ...)
     * @param output of stream to write into
     */
    void write (std::ofstream & output) const override;

private:

    /**
     * Swaps rows in the matrix starting from rowIndex such that the number on the rowIndex row in the columnIndex column is the highest
     * used in GEM
     */
    void orderRows (u_int32_t rowIndex, uint32_t columnIndex);

    /**
     * Swaps rows in this matrix starting from rowIndex such that the number on the rowIndex row in the columnIndex column is the highest
     * replicates the same swaps on the matrix in parameters
     */
    void orderRows (CDenseMatrix & secondMatrix, u_int32_t rowIndex, uint32_t columnIndex);

    /**
     * Adds coefficient * rowToAdd to targetRow
     * @param rowToAdd
     * @param targetRow
     * @param coefficient
     */
    void addRows (uint32_t rowToAdd, uint32_t targetRow, double coefficient);

    /**
     * Rows of the matrix
     */
    std::vector<std::vector<double>> m_Data;
};
