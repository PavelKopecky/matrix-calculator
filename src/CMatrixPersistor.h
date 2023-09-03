/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 16.05.2023
*/


#pragma once
#include "CMatrix.h"
#include "CSparseMatrix.h"
#include "CDenseMatrix.h"
#include "CDiagonalMatrix.h"

/**
 * Class which converts a std::vector<std::vector<double>> or a std::string to a unique pointer to a matrix of the correct type
 */
class CMatrixPersistor {
public:

    /**
     * Converts the std::vector<std::vector<double>> passed in parameters to a unique pointer to the correct matrix type
     * @param data m*n vector - data for the matrix
     * @return unique pointer to a matrix of the correct type
     */
    std::unique_ptr<CMatrix> operator () (const std::vector<std::vector<double>> & data) const;

    /**
     * Converts the string passed in parameters to a unique pointer to the correct matrix type
     * @param data string to evaluate
     * @return unique pointer to a matrix of the correct type
     */
    std::unique_ptr<CMatrix> operator () (std::string && data) const;
};
