/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz>
* @date 29.04.2023
*/

#pragma once
#include <cstdint>

/**
 * Class representing a tuple of values - row number, column number, value - used in sparse matrices
 */
class CTuple {
public:

    /**
     * Constructs object with values in parameters
     * @param row row number
     * @param col column number
     * @param val value
     */
    CTuple (uint32_t row, uint32_t col, double val);

    /**
     * Operator <, compares two CTuple objects
     * Primary comparison - row number, secondary - column number
     * Used in sorting
     * @param cpy
     * @return true if this CTuple is lower
     */
    bool operator < (const CTuple & cpy) const;

    /** row index of the element */
    uint32_t m_Row;

    /** column index of the element */
    uint32_t m_Col;

    /** value of the element */
    double m_Val;
};
