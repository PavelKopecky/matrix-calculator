/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz>
* @date 29.04.2023
*/

#pragma once
#include "CMatrix.h"
#include "CTuple.h"
#include <vector>

/**
 * Class representing a sparse matrix, where the number of non zeroes is <= the lower of row count, column count
 * Data stored in a vector of CTuples (row number, column number, value)
 */
class CSparseMatrix : public CMatrix {
public:

    CSparseMatrix () = default;

    /**
     * Constructs a sparse matrix with the rowCnt and colCnt in parameters and copies the cpy vector which
     * contains all non-zero values
     * @param cpy CTuple vector to copy
     * @param rowCnt row count of the sparse matrix
     * @param colCnt column count of the sparse matrix
     */
    CSparseMatrix (const std::vector<CTuple> & cpy, uint32_t rowCnt, uint32_t colCnt);

    ~CSparseMatrix() override = default;

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
     * Swaps the number of columns and rows, swaps the column and row number of every element in m_Data
     * @return a unique_ptr to the newly created matrix
     */
    std::unique_ptr<CMatrix> transpose () const override;

    /**
     * Converts the matrix into a dense matrix and calls the gauss method of the dense matrix
     * It is very likely that the intermediate result will be a dense matrix, and the result will be saved correctly if not
     * @return a unique_ptr to the newly created matrix
     */
    std::unique_ptr<CMatrix> gauss () const override;

    /**
     * Converts the matrix into a dense matrix and calls the inverse method of the dense matrix
     * It is very likely that the intermediate result will be a dense matrix, and the result will be saved correctly if not
     * @return a unique_ptr to the newly created matrix
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
     * Contains CTuples - which is a trio of three elements: row index, column index and the value of the element on these coordinates
     */
    std::vector<CTuple> m_Data;
};
