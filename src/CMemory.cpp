/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 24.05.2023
*/

#include "CMemory.h"

CMemory::CMemory(const CMemory & copy) {

    for (const auto & matrix : copy.m_Data) {
        m_Data.insert(std::make_pair(matrix.first, matrix.second->clone()));
    }
}

CMemory & CMemory::operator = (CMemory copy) {

    m_Data.swap(copy.m_Data);
    return * this;
}

bool CMemory::contains(char matrix) const {

    return m_Data.count(matrix);
}

bool CMemory::empty() const {

    return m_Data.empty();
}

std::unique_ptr<CMatrix> CMemory::getCopy(char name) const {

    return m_Data.at(name)->clone();
}

void CMemory::print (std::ostream & os) const {

    if (m_Data.empty()) {
        throw std::invalid_argument("No user-defined matrices currently saved.");
    }

    auto it = m_Data.begin();

    while (it != m_Data.end()) {
        os << it->first << ": \n";
        it->second->print(os);
        it = std::next(it);
    }
}

void CMemory::print (char matrixName, std::ostream & os) const {

    if (!m_Data.count(matrixName)) {
        throw std::invalid_argument("ERROR: No such matrix found.");
    } else {
        m_Data.at(matrixName)->print(os);
    }
}

void CMemory::saveToFile(const std::string &fileName) const {

    if (m_Data.empty()) {
        throw std::logic_error("No user-defined matrices currently saved.");
    }

    std::ofstream outputFile;
    outputFile.open(fileName);

    if (!outputFile) {
        throw std::invalid_argument("ERROR: Cannot open file.");
    }

    auto it = m_Data.begin();

    while (it != m_Data.end()) {
        if (!(outputFile << it->first)) {
            throw std::invalid_argument("ERROR: Cannot write into file.");
        }
        it->second->write(outputFile);
        if (!(outputFile << std::endl)) {
            throw std::invalid_argument("ERROR: Cannot write into file.");
        }
        it = std::next(it);
    }
}

void CMemory::add(char name, const CMatrix &matrix) {

    if (m_Data.count(name)) m_Data.erase(name);
    m_Data.insert(std::make_pair(name, matrix.clone()));
}

void CMemory::remove(char matrix) {
    m_Data.erase(matrix);
}
