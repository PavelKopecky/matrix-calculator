/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 20.05.2023
*/


#pragma once
#include "CBinaryOperator.h"
#include "CUnaryOperator.h"
#include <map>
#include <string>

/**
 * Class which serves as a container for all operators, used for creating the AST in CParser
 */
class CRegister {
public:

    /**
     * Adds pointers to all operators to their appropriate map
     */
    CRegister();

    /**
     * copy constructor - creates a deep copy of the register in parameters
     * @param cpy register to be copied
     */
    CRegister (const CRegister & cpy);

    ~CRegister() = default;

    /**
     * Op =, creates a deep copy of the register in parameters
     * @param cpy
     * @return this
     */
    CRegister & operator = (CRegister cpy);

    /**
     * Checks if the operator with the name op exists in on of the containers
     * @param op name of the operator
     * @return 1 if the operator is a binary operator, -1 if unary, 0 if the register does not contain such operator
     */
    int contains (std::string op) const;

    /**
     * Returns a pointer to the correct unary operator
     * The unary operator is guaranteed to exist
     * @param op code of the unary operator
     * @return pointer to the correct unary operator
     */
    std::unique_ptr<CUnaryOperator> getUnary (std::string op) const;

    /**
     * Returns a pointer to the correct binary operator
     * The binary operator is guaranteed to exist
     * @param op code of the binary operator
     * @return pointer to the correct binary operator
     */
    std::unique_ptr<CBinaryOperator> getBinary (std::string op) const;

private:
    /**
     * Map containing all unary operators, key == code of the operator (eg. tra)
     */
    std::map<std::string, std::unique_ptr<CUnaryOperator>> m_UnaryOperators;

    /**
     * Map containing all binary operators, key == code of the operator (eg. +, mul, ...)
     */
    std::map<std::string, std::unique_ptr<CBinaryOperator>> m_BinaryOperators;
};
