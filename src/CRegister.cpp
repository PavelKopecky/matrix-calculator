/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 20.05.2023
*/

#include "CRegister.h"
#include "CDeterminant.h"
#include "CGauss.h"
#include "CInverse.h"
#include "CMatrixRank.h"
#include "CTranspose.h"
#include "CAdd.h"
#include "CCrop.h"
#include "CMerge.h"
#include "CMultiply.h"
#include "CSubtract.h"

CRegister::CRegister() {

    m_UnaryOperators.insert(std::make_pair("det", CDeterminant().clone()));
    m_UnaryOperators.insert(std::make_pair("gem", CGauss().clone()));
    m_UnaryOperators.insert(std::make_pair("inv", CInverse().clone()));
    m_UnaryOperators.insert(std::make_pair("rank", CMatrixRank().clone()));
    m_UnaryOperators.insert(std::make_pair("tra", CTranspose().clone()));

    m_BinaryOperators.insert(std::make_pair("add", CAdd().clone()));
    m_BinaryOperators.insert(std::make_pair("+", CAdd().clone()));
    m_BinaryOperators.insert(std::make_pair("mul", CMultiply().clone()));
    m_BinaryOperators.insert(std::make_pair("*", CMultiply().clone()));
    m_BinaryOperators.insert(std::make_pair("sub", CSubtract().clone()));
    m_BinaryOperators.insert(std::make_pair("-", CSubtract().clone()));
    m_BinaryOperators.insert(std::make_pair("crop", CCrop().clone()));
    m_BinaryOperators.insert(std::make_pair("merge", CMerge().clone()));
}

int CRegister::contains(std::string op) const {

    //key is lowercase
    for (uint32_t i = 0; i < op.length(); ++i) {
        op[i] = tolower(op[i]);
    }

    if (m_BinaryOperators.count(op)) return 1;
    else if (m_UnaryOperators.count(op)) return -1;
    else return 0;
}

std::unique_ptr<CBinaryOperator> CRegister::getBinary(std::string op) const {

    //key is lowercase
    for (uint32_t i = 0; i < op.length(); ++i) {
        op[i] = tolower(op[i]);
    }

    return m_BinaryOperators.at(op)->clone();
}

std::unique_ptr<CUnaryOperator> CRegister::getUnary(std::string op) const {

    //key is lowercase
    for (uint32_t i = 0; i < op.length(); ++i) {
        op[i] = tolower(op[i]);
    }

    return m_UnaryOperators.at(op)->clone();
}

CRegister::CRegister(const CRegister & cpy) {

    for (const auto & binOp : cpy.m_BinaryOperators) {
        m_BinaryOperators.insert(std::make_pair(binOp.first, binOp.second->clone()));
    }
}

CRegister & CRegister::operator = (CRegister cpy) {

    m_BinaryOperators.swap(cpy.m_BinaryOperators);
    m_UnaryOperators.swap(cpy.m_UnaryOperators);

    return * this;
}
