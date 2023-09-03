/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz>
* @date 29.04.2023
*/

#include "CApplication.h"
#include "CMatrixPersistor.h"
#include <algorithm>
#include <fstream>
#include <sstream>

CApplication::CApplication() :
        m_Saved(true) {
}

void CApplication::print (std::ostream & os) const {

    m_Data.print(os);
}

void CApplication::print (char matrixName, std::ostream & os) const {

    m_Data.print(matrixName, os);
}

std::unique_ptr<CMatrix> CApplication::getCopy(char name) const {

    if (m_Data.contains(name)) {
        return m_Data.getCopy(name);
    } else throw std::invalid_argument("ERROR: No such matrix found.");
}

void CApplication::saveToFile(const std::string & fileName) {

    m_Data.saveToFile(fileName);
    m_Saved = true;
}

void CApplication::addMatrix(char name, const CMatrix & matrix) {

    m_Data.add(name, matrix);
    m_Saved = false;
}

void CApplication::loadFromFile(const std::string &fileName) {

    std::ifstream inputFile;
    inputFile.open(fileName);

    if (!inputFile) {
        throw std::invalid_argument("ERROR: Cannot open file.");
    }

    CMemory newData;

    /**
     * Read until EOF
     *                                / -- not in diagonal matrices -- /
     * Format: (matrixCode)(matrixType) (rowCount) (columnCount) ( ... data ... )
     */
    while (inputFile.peek() != EOF) {

        if (inputFile.peek() == '\n') {
            while (inputFile.peek() != EOF && inputFile.peek() == '\n') inputFile.get();
            if (inputFile.peek() != EOF) throw std::invalid_argument("ERROR: File corrupt.");
            else break;
        }

        std::string nameType;

        std::string line;
        if (!std::getline(inputFile, line)) throw std::invalid_argument("ERROR: File corrupt.");
        std::istringstream lineStream(line);

        uint32_t rowCount, colCount;
        if (!(lineStream >> nameType) || lineStream.peek() == '\n' || lineStream.peek() == EOF) {
            throw std::invalid_argument("ERROR: File corrupt.");
        }

        if (nameType.size() != 2 || ((nameType[0] < 'A' || nameType[0] > 'Z') && (nameType[0] < 'a' || nameType[0] > 'z'))) {
                throw std::invalid_argument("ERROR: File corrupt.");
        }

        switch (nameType[1]) {
            case 'D' : {
                std::vector<std::vector<double>> data;

                if (!(lineStream >> rowCount >> colCount) || lineStream.peek() == '\n' || lineStream.peek() == EOF) {
                    throw std::invalid_argument("ERROR: File corrupt.");
                }

                for (uint32_t i = 0; i < rowCount; ++i) {
                    std::vector<double> newRow;
                    for (uint32_t j = 0; j < colCount; ++j) {
                        double newNumber;
                        if (!(lineStream >> newNumber)) throw std::invalid_argument("ERROR: File corrupt.");
                        newRow.push_back(newNumber);
                    }
                    data.push_back(newRow);
                }

                if (lineStream.peek() != EOF || newData.contains(nameType[0])) throw std::invalid_argument("ERROR: File corrupt.");

                newData.add(nameType[0], CDenseMatrix(data));
                break;
            }
            case 'd' : {

                std::vector<double> diagonalVector;

                while (!lineStream.eof() && lineStream.peek() != EOF) {
                    double newNumber;
                    if (!(lineStream >> newNumber)) throw std::invalid_argument("ERROR: File corrupt.");
                    diagonalVector.push_back(newNumber);
                }

                if (lineStream.peek() != EOF || newData.contains(nameType[0])) throw std::invalid_argument("ERROR: File corrupt.");

                newData.add(nameType[0], CDiagonalMatrix(diagonalVector));
                break;
            }
            case 'S' : {

                std::vector<CTuple> data;

                if (!(lineStream >> rowCount >> colCount) || lineStream.peek() == '\n' || lineStream.peek() == EOF) {
                    throw std::invalid_argument("ERROR: File corrupt.");
                }

                while (lineStream.peek() != EOF) {
                    double newNumber;
                    uint32_t row, col;

                    if (!(lineStream >> row >> col >> newNumber) || row >= rowCount || col >= colCount) throw std::invalid_argument("File corrupt.");
                    data.emplace_back(row, col, newNumber);
                }

                if (lineStream.peek() != EOF || newData.contains(nameType[0])) throw std::invalid_argument("ERROR: File corrupt.");

                newData.add(nameType[0], CSparseMatrix(data, rowCount, colCount));
                break;
            }
            default : throw std::invalid_argument("ERROR: File corrupt.");
        }
    }

    m_Data = newData;
    m_Saved = true;
}

bool CApplication::contains(char key) const {

    return m_Data.contains(key);
}

bool CApplication::saved() const {

    return m_Saved;
}

void CApplication::remove(char matrix) {

    if (!m_Data.contains(matrix)) throw std::invalid_argument("ERROR: Matrix with this name does not exist.");
    else m_Data.remove(matrix);
}
