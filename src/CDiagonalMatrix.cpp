/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz>
* @date 29.04.2023
*/

#include "CDiagonalMatrix.h"
#include <cfloat>
#include <cmath>

CDiagonalMatrix::CDiagonalMatrix(const std::vector<double> & cpy) :
    CMatrix(cpy.size(), cpy.size()),
    m_Data(cpy) {}

void CDiagonalMatrix::print (std::ostream & os) const {

    for (uint32_t i = 0; i < m_RowCount; i++) {
        os << "| ";
        for (uint32_t j = 0; j < m_ColCount; j++) {
            if (i == j && fabs(m_Data[i]) >= 100 * DBL_EPSILON) {
                os << m_Data[i] << ' ';
            } else os << "0 ";
        }
        os << "|\n";
    }
}

std::unique_ptr<CMatrix> CDiagonalMatrix::clone () const {

    return std::make_unique<CDiagonalMatrix>(*this);
}

double CDiagonalMatrix::get(uint32_t rowIndex, uint32_t colIndex) const {

    if (rowIndex != colIndex) {
        return 0;
    } else return m_Data[rowIndex];
}

std::unique_ptr<CMatrix> CDiagonalMatrix::transpose() const {

    return std::make_unique<CDiagonalMatrix>(*this);
}

std::unique_ptr<CMatrix> CDiagonalMatrix::gauss() const {

    return std::make_unique<CDiagonalMatrix>(*this);
}

void CDiagonalMatrix::write(std::ofstream &output) const {

    if (!(output << 'd')) {
        throw std::invalid_argument("ERROR: Cannot write into file.");
    }

    for (uint32_t i = 0; i < m_RowCount; ++i) {

        if (fabs(m_Data[i]) < 100*DBL_EPSILON) {
            if (!(output << " 0")) throw std::invalid_argument("ERROR: Cannot write into file.");
        } else  if (!(output << ' ' << m_Data[i])) {
            throw std::invalid_argument("ERROR: Cannot write into file.");
        }
    }
}

std::unique_ptr<CMatrix> CDiagonalMatrix::inverse() const {

    std::vector<double> diagonalVector;

    for (uint32_t i = 0; i < m_RowCount; ++i) {
        diagonalVector.push_back((double) 1 / m_Data[i]);
    }

    return CDiagonalMatrix(diagonalVector).clone();
}
