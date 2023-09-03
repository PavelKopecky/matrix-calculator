/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz>
* @date 29.04.2023
*/

#include "CMatrix.h"
#include <cmath>
#include <cfloat>

CMatrix::CMatrix (uint32_t rowCnt, uint32_t colCnt) :
    m_RowCount(rowCnt),
    m_ColCount(colCnt) {}

bool CMatrix::operator == (const CMatrix &rhs) const {

    if (m_RowCount != rhs.m_RowCount || m_ColCount != rhs.m_ColCount) return false;

    for (uint32_t i = 0; i < m_RowCount; i++) {
        for (uint32_t j = 0; j < m_ColCount; j++) {
            if (fabs(get(i, j) - rhs.get(i,j)) > 1000*DBL_EPSILON) return false;
        }
    }

    return true;
}

uint32_t CMatrix::colCount() const {
    return m_ColCount;
}

uint32_t CMatrix::rowCount() const {
    return m_RowCount;
}
