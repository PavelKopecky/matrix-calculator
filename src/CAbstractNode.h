/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 11.05.2023
*/

#pragma once
#include "CMatrix.h"
#include "CUnaryOperator.h"
#include "CBinaryOperator.h"

/**
 * Abstract class used to compose an abstract syntax tree for parsing the expression.
 * https://en.wikipedia.org/wiki/Abstract_syntax_tree
 */
class CAbstractNode {
public:

    /**
     * Recursively frees all allocated memory of the child (leaf) nodes
     */
    ~CAbstractNode();

    /**
     * Constructs the node with a matrix
     * @param matrix
     */
    explicit CAbstractNode(std::unique_ptr<CMatrix> matrix);

    /**
     * Constructs the node with a binary operator
     * @param matrix
     */
    explicit CAbstractNode(std::unique_ptr<CBinaryOperator> binOp);

    /**
     * Constructs the node with a unary operator
     * @param matrix
     */
    explicit CAbstractNode(std::unique_ptr<CUnaryOperator> unOp);

    /**
     * If this node is an operator, these nodes will contain a matrix / other operator which will be used in this operator
     */
    CAbstractNode * leftNode;
    CAbstractNode * rightNode;

    /**
     * Evaluates the current node. If this node is an operator, it first evaluates the left and/or right node. (recursively)
     * @return matrix which is the result of an operation / stored in the node
     */
    std::unique_ptr<CMatrix> evaluate ();

private:
    /** unique_ptr to the specific binary operator */
    std::unique_ptr<CBinaryOperator> binaryOperator;

    /** unique_ptr to the specific unary operator */
    std::unique_ptr<CUnaryOperator> unaryOperator;

    /** unique_ptr to the specific matrix stored in this node */
    std::unique_ptr<CMatrix> matrix;
};
