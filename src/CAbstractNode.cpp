/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 11.05.2023
*/

#include "CAbstractNode.h"

CAbstractNode::CAbstractNode(std::unique_ptr<CMatrix> matrix) :
    leftNode(nullptr),
    rightNode(nullptr),
    binaryOperator(nullptr),
    unaryOperator(nullptr),
    matrix(matrix->clone()) {}

CAbstractNode::CAbstractNode(std::unique_ptr<CBinaryOperator> binOp) :
    leftNode(nullptr),
    rightNode(nullptr),
    binaryOperator(binOp->clone()),
    unaryOperator(nullptr),
    matrix(nullptr) {
}

CAbstractNode::CAbstractNode(std::unique_ptr<CUnaryOperator> unOp) :
        leftNode(nullptr),
        rightNode(nullptr),
        binaryOperator(nullptr),
        unaryOperator(unOp->clone()),
        matrix(nullptr) {
}

/**
 * Evaluates which action to do based on which ptr is non-null and returns the result matrix
 */
std::unique_ptr<CMatrix> CAbstractNode::evaluate() {

    if (matrix != nullptr) return matrix->clone();

    else if (unaryOperator != nullptr) {
        if (leftNode != nullptr) return unaryOperator->execute(*leftNode->evaluate());
        else if (rightNode != nullptr) return unaryOperator->execute(*rightNode->evaluate());
        else throw std::invalid_argument("ERROR: Syntax error.");

    } else if (binaryOperator != nullptr) {
        if (leftNode == nullptr || rightNode == nullptr) throw std::invalid_argument("ERROR: Syntax error.");
        return binaryOperator->execute(*leftNode->evaluate(), *rightNode->evaluate());
    }

    else throw std::invalid_argument("ERROR: Syntax error.");
}

CAbstractNode::~CAbstractNode() {

    if (leftNode) {
        delete leftNode;
        leftNode = nullptr;
    }

    if (rightNode) {
        delete rightNode;
        rightNode = nullptr;
    }
}
