/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz>
* @date 29.04.2023
*/

#include "CDenseMatrix.h"
#include "CMatrixPersistor.h"
#include <cfloat>
#include <cmath>

CDenseMatrix::CDenseMatrix(const std::vector<std::vector<double>> & cpy) :
    m_Data(cpy) {

    if (!m_Data.empty()) { //should not happen but to be safe
        m_RowCount = m_Data.size();
        m_ColCount = m_Data[0].size();
    } else {
        m_RowCount = 0;
        m_ColCount = 0;
    }
}

void CDenseMatrix::print (std::ostream & os) const {

    for (uint32_t i = 0; i < m_RowCount; i++) {
        os << "| ";
        for (uint32_t j = 0; j < m_ColCount; j++) {
            if (fabs(m_Data[i][j]) < 1000*DBL_EPSILON) {
                os << "0 ";
            } else os << m_Data[i][j] << ' ';
        }
        os << "|\n";
    }
}

std::unique_ptr<CMatrix> CDenseMatrix::clone () const {

    return std::make_unique<CDenseMatrix>(*this);
}

double CDenseMatrix::get(uint32_t rowIndex, uint32_t colIndex) const {

    return m_Data[rowIndex][colIndex];
}

std::unique_ptr<CMatrix> CDenseMatrix::transpose() const {

    std::vector<std::vector<double>> data;

    for (uint32_t i = 0; i < m_ColCount; ++i) {
        std::vector<double> newRow;
        for (uint32_t j = 0; j < m_RowCount; ++j) {
            newRow.push_back(m_Data[j][i]);
        }        data.push_back(newRow);
    }

    return std::make_unique<CDenseMatrix>(CDenseMatrix(data));
}

void CDenseMatrix::orderRows(u_int32_t rowIndex, uint32_t columnIndex) {

    bool found = false;
    uint32_t topIndex = 0;

    for (uint32_t i = m_RowCount - 1; i >= rowIndex && i != UINT32_MAX; --i) {
        if (fabs(m_Data[i][columnIndex]) > 100*DBL_EPSILON) {
            found = true;
            topIndex = i;
            break;
        }
    }

    //no non zeroes found on in this column
    if (!found && columnIndex < m_ColCount - 1) orderRows(rowIndex, columnIndex + 1);
    else if (!found && columnIndex == m_ColCount - 1) return;

    uint32_t botIndex = rowIndex;

    while (botIndex <= m_RowCount - 1 && fabs(m_Data[botIndex][columnIndex]) > 100*DBL_EPSILON) botIndex++;

    while (botIndex < topIndex) {

        std::vector<double> tmp = m_Data[topIndex];
        m_Data[topIndex] = m_Data[botIndex];
        m_Data[botIndex] = tmp;

        while (botIndex <= m_RowCount - 1 && fabs(m_Data[botIndex][columnIndex]) > 100*DBL_EPSILON) botIndex++;
        while (topIndex != 0 && fabs(m_Data[topIndex][columnIndex]) <= 100*DBL_EPSILON) topIndex--;
    }
}

void CDenseMatrix::addRows(uint32_t rowToAdd, uint32_t targetRow, double coefficient) {

    for (uint32_t j = 0; j < m_ColCount; ++j) {
        m_Data[targetRow][j] += coefficient * m_Data[rowToAdd][j];
    }
}

void CDenseMatrix::orderRows(CDenseMatrix & secondMatrix, u_int32_t rowIndex, uint32_t columnIndex) {

    bool found = false;
    uint32_t topIndex = 0;

    for (uint32_t i = m_RowCount - 1; i >= rowIndex && i != UINT32_MAX; --i) {
        if (fabs(m_Data[i][columnIndex]) > 100*DBL_EPSILON) {
            found = true;
            topIndex = i;
            break;
        }
    }

    //no non zeroes found on in this column
    if (!found && columnIndex < m_ColCount - 1) orderRows(secondMatrix,rowIndex, columnIndex + 1);
    else if (!found && columnIndex == m_ColCount - 1) return;

    uint32_t botIndex = rowIndex;

    while (botIndex <= m_RowCount - 1 && fabs(m_Data[botIndex][columnIndex]) > 100*DBL_EPSILON) botIndex++;

    while (botIndex < topIndex) {

        std::vector<double> tmp = m_Data[topIndex];
        m_Data[topIndex] = m_Data[botIndex];
        m_Data[botIndex] = tmp;

        tmp = secondMatrix.m_Data[topIndex];
        secondMatrix.m_Data[topIndex] = secondMatrix.m_Data[botIndex];
        secondMatrix.m_Data[botIndex] = tmp;

        while (botIndex <= m_RowCount - 1 && fabs(m_Data[botIndex][columnIndex]) > 100*DBL_EPSILON) botIndex++;
        while (topIndex != 0 && fabs(m_Data[topIndex][columnIndex]) <= 100*DBL_EPSILON) topIndex--;
    }
}

std::unique_ptr<CMatrix> CDenseMatrix::gauss() const {

    CDenseMatrix newMatrix(*this);
    uint32_t steps = (m_RowCount < m_ColCount) ? m_RowCount : m_ColCount;
    double value = 0;
    uint32_t pos = 0;

    /**
     * Orders rows of the matrix so that the top row has the leftmost non-zero element
     * and then adds multiples of this row to bottom rows so that erases the non-zero elements
     * in the same column, repeat for each column
     */
    for (uint32_t i = 0; i < steps; ++i) {

        newMatrix.orderRows(i, i);

        for (uint32_t j = i; j < m_ColCount; ++j) {
            if (fabs(newMatrix.get(i, j)) > 100*DBL_EPSILON) {
                value = newMatrix.get(i, j);
                pos = j;
                break;
            }
        }
        if (fabs(value) <= 100*DBL_EPSILON) break;

        for (uint32_t j = i + 1; j < m_RowCount; ++j) {
            if (fabs(newMatrix.get(j, pos)) <= 100*DBL_EPSILON) break;
            double coefficient =  (double) - (newMatrix.get(j, pos) / (newMatrix.get(i, pos)));
            newMatrix.addRows(i, j, coefficient);
            newMatrix.m_Data[j][pos] = 0; //in case double magic happens and an exact zero is not set on the correct position
        }
    }

    return CMatrixPersistor()(newMatrix.m_Data);
}

void CDenseMatrix::write(std::ofstream & output) const {

    if (!(output << "D " << m_RowCount << ' ' << m_ColCount)) {
        throw std::invalid_argument("ERROR: Cannot write into the file.");
    }

    for (uint32_t i = 0; i < m_RowCount; ++i) {
        for (uint32_t j = 0; j < m_ColCount; ++j) {

            if (fabs(m_Data[i][j]) < 1000*DBL_EPSILON) {
                if (!(output << " 0")) throw std::invalid_argument("ERROR: Cannot write into the file.");
            } else if (!(output << ' ' << m_Data[i][j])) {
                throw std::invalid_argument("ERROR: Cannot write into the file.");
            }
        }
    }
}

std::unique_ptr<CMatrix> CDenseMatrix::inverse() const {

    CDenseMatrix newMatrix(*this);
    uint32_t steps = (m_RowCount < m_ColCount) ? m_RowCount : m_ColCount;
    double value = 0;
    uint32_t pos = 0;

    /** Create the identity matrix */

    std::vector<std::vector<double>> identityData;

    for (uint32_t i = 0; i < m_RowCount; ++i) {
        std::vector<double> newRow;
        for (uint32_t j = 0; j < m_RowCount; ++j) {
            if (i == j) newRow.push_back(1);
            else newRow.push_back(0);
        }
        identityData.push_back(newRow);
    }

    CDenseMatrix identityMatrix(identityData);

    /** Transform the original matrix into a matrix in an upper triangular form
     * and apply the same changes to the identity matrix*/

    for (uint32_t i = 0; i < steps; ++i) {

        newMatrix.orderRows(identityMatrix, i, i);

        for (uint32_t j = i; j < m_ColCount; ++j) {
            if (fabs(newMatrix.get(i, j)) > 100*DBL_EPSILON) {
                value = newMatrix.get(i, j);
                pos = j;
                break;
            }
        }
        if (fabs(value) <= 100*DBL_EPSILON) break;

        for (uint32_t j = i + 1; j < m_RowCount; ++j) {
            if (fabs(newMatrix.get(j, pos)) <= 100*DBL_EPSILON) break;
            double coefficient = (double) - (newMatrix.get(j, pos) / (newMatrix.get(i, pos)));
            newMatrix.addRows(i, j, coefficient);
            identityMatrix.addRows(i, j, coefficient);
            newMatrix.m_Data[j][pos] = 0; //in case double magic happens and an exact zero is not set on the correct position
        }
    }

    /** Original matrix is now in an upper triangular form */

    for (uint32_t i = m_ColCount - 1; i != 0; --i) {
        for (uint32_t j = i - 1; j != UINT32_MAX; --j) {
            if (fabs(newMatrix.get(j, i)) < 100*DBL_EPSILON) continue;
            double coefficient =  (double) - (newMatrix.get(j, i) / (newMatrix.get(i, i)));
            newMatrix.addRows(i, j, coefficient);
            identityMatrix.addRows(i, j, coefficient);
            newMatrix.m_Data[j][i] = 0; //in case double magic happens and an exact zero is not set on the correct position
        }
    }

    /** Original matrix is now a diagonal matrix */

    for (uint32_t i = 0; i < m_RowCount; ++i) {
        double coefficient =  newMatrix.m_Data[i][i];
        for (uint32_t j = 0; j < m_RowCount; ++j) {
            identityMatrix.m_Data[i][j] *= (double) 1/coefficient;
        }
    }

    return CMatrixPersistor()(identityMatrix.m_Data);
}
