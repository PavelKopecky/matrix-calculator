/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz>
* @date 29.04.2023
*/

#pragma once
#include <memory>
#include <iostream>
#include <fstream>

/**
 * Abstract (not purely) class CMatrix, contains multiple virtual methods as well as the
 * op ==, which is used FOR TESTS ONLY
 */
class CMatrix {
public:

    CMatrix() = default;

    /** Constructs the matrix */
    CMatrix (uint32_t rowCnt, uint32_t colCnt);

    virtual ~CMatrix () noexcept = default;

    /**
     * Virtual method print, prints the values inside the matrix. Example:
     * | 1 0 |
     * | 0 1 |
     * Implementation depends on the child class
     * @param os stream to print to
     */
    virtual void print (std::ostream & os) const = 0;

    /**
     * Constructs a copy of the matrix
     * @return unique ptr to the copy of the matrix
     */
    virtual std::unique_ptr<CMatrix> clone () const = 0;

    /**
     * Compares whether *this matrix is equal to the matrix in parameters
     * @param rhs matrix to compare
     * @return true if the matrices are the same, false if not
     */
    bool operator == (const CMatrix & rhs) const;

    /**
     * Returns the value from the position [rowIndex, colIndex]
     * @param rowIndex
     * @param colIndex
     * @return value found
     */
    virtual double get (uint32_t rowIndex, uint32_t colIndex) const = 0;

    /**
     * Writes matrix data into the output file
     * @param output output file to write into
     */
    virtual void write (std::ofstream & output) const = 0;

    /**
     * Virtual method which transposes a copy of the matrix - swaps rows and columns
     * @return a unique pointer to the newly created matrix
     */
    virtual std::unique_ptr<CMatrix> transpose () const = 0;

    /**
     * Virtual method which executes the gaussian elimination method
     * a copy of the matrix
     * @return a unique pointer to the newly created matrix
     */
    virtual std::unique_ptr<CMatrix> gauss () const = 0;

    /**
     * Virtual method which finds an inverse matrix to this matrix
     * it is guaranteed that the matrix does have an inverse matrix
     * @return a unique pointer to the inverse matrix
     */
    virtual std::unique_ptr<CMatrix> inverse () const = 0;

    /**
     * @return number of rows - m_RowCount
     */
    uint32_t rowCount () const;

    /**
     * @return number of rows - m_ColCount
     */
    uint32_t colCount () const;

protected:

    /** row count of the matrix*/
    uint32_t m_RowCount;

    /** column count of the matrix*/
    uint32_t m_ColCount;
};
