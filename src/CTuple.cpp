/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz>
* @date 29.04.2023
*/

#include "CTuple.h"

CTuple::CTuple(uint32_t row, uint32_t col, double val) :
    m_Row(row),
    m_Col(col),
    m_Val(val) {}

bool CTuple::operator < (const CTuple & cpy) const {

    if (m_Row != cpy.m_Row) {
        return m_Row < cpy.m_Row;
    } else if (m_Col != cpy.m_Col) {
        return m_Col < cpy.m_Col;
    } else return false;
}
