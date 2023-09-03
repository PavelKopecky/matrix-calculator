/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz>
* @date 29.04.2023
*/

#include "CSparseMatrix.h"
#include "CDenseMatrix.h"
#include <algorithm>

CSparseMatrix::CSparseMatrix(const std::vector<CTuple> & cpy, uint32_t rowCnt, uint32_t colCnt) :
    CMatrix(rowCnt, colCnt),
    m_Data(cpy) {
    std::sort(m_Data.begin(), m_Data.end());
}

void CSparseMatrix::print (std::ostream & os) const {

    uint32_t index = 0;
    uint32_t maxIndex = m_Data.size();

    for (uint32_t i = 0; i < m_RowCount; i++) {
        os << "| ";
        for (uint32_t j = 0; j < m_ColCount; j++) {
            if (index < maxIndex && m_Data[index].m_Row == i && m_Data[index].m_Col == j) {
                os << m_Data[index++].m_Val << ' ';
            } else os << "0 ";
        }
        os << "|\n";
    }
}

std::unique_ptr<CMatrix> CSparseMatrix::clone () const {

    return std::make_unique<CSparseMatrix>(*this);
}

double CSparseMatrix::get (uint32_t rowIndex, uint32_t colIndex) const {

    for (const auto & i : m_Data) {
        if (i.m_Row > rowIndex) {
            return 0;
        } else if (i.m_Row == rowIndex && i.m_Col == colIndex) {
            return i.m_Val;
        }
    }

    return 0;
}

std::unique_ptr<CMatrix> CSparseMatrix::transpose() const {

    CSparseMatrix newMatrix;
    newMatrix.m_ColCount = m_RowCount;
    newMatrix.m_RowCount = m_ColCount;

    for (const auto & tuple : m_Data) {
        newMatrix.m_Data.emplace_back(tuple.m_Col, tuple.m_Row, tuple.m_Val);
    }    sort(newMatrix.m_Data.begin(), newMatrix.m_Data.end());

    return std::make_unique<CSparseMatrix>(newMatrix);
}

/**
 * The sparse matrix will be converted to a dense matrix as it is very likely, the (intermediate) result will be a dense matrix
 */
std::unique_ptr<CMatrix> CSparseMatrix::gauss() const {

    std::vector<std::vector<double>> matrix;

    for (uint32_t i = 0; i < m_RowCount; ++i) {
        std::vector<double> newRow;
        for (uint32_t j = 0; j < m_ColCount; ++j) {
            newRow.push_back(0);
        }
        matrix.push_back(newRow);
    }

    for (const CTuple & tuple : m_Data) {
        matrix[tuple.m_Row][tuple.m_Col] = tuple.m_Val;
    }

    return CDenseMatrix(matrix).gauss();
}

void CSparseMatrix::write(std::ofstream &output) const {

    if (!(output << "S " << m_RowCount << ' ' << m_ColCount )) {
        throw std::invalid_argument("ERROR: Cannot write into file.");
    }

    for (uint32_t i = 0; i < m_Data.size(); ++i) {
        if (!(output << ' ' << m_Data[i].m_Row << ' ' << m_Data[i].m_Col << ' ' <<  m_Data[i].m_Val)) {
            throw std::invalid_argument("ERROR: Cannot write into file.");
        }
    }
}

/**
 * The sparse matrix will be converted to a dense matrix as it is very likely, the (intermediate) result will be a dense matrix
 */
std::unique_ptr<CMatrix> CSparseMatrix::inverse() const {

    std::vector<std::vector<double>> matrix;

    for (uint32_t i = 0; i < m_RowCount; ++i) {
        std::vector<double> newRow;
        for (uint32_t j = 0; j < m_ColCount; ++j) {
            newRow.push_back(0);
        }
        matrix.push_back(newRow);
    }

    for (const CTuple & tuple : m_Data) {
        matrix[tuple.m_Row][tuple.m_Col] = tuple.m_Val;
    }

    return CDenseMatrix(matrix).inverse();
}
