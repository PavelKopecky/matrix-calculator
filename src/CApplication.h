/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz>
* @date 29.04.2023
*/

#pragma once
#include "CMatrix.h"
#include "CMemory.h"
#include <string>
#include <exception>

/**
 * Class containing all data, represents the "calculator engine" itself
 */
class CApplication {
public:

    CApplication ();

    ~CApplication() = default;

    /**
     * Saves data in the CMemory into a text file (calls the saveToFile of the CMemory)
     * @param fileName name of the file
     */
    void saveToFile (const std::string & fileName);

    /**
     * Loads matrices from a file, overwrites currently saved data
     * @param fileName name of the file
     */
    void loadFromFile (const std::string & fileName);

    /**
     * Calls the print (all) method of CMemory, which calls the print method on every matrix in the app
     * @param os stream to print into
     */
    void print (std::ostream & os) const;

    /**
     * Calls the print (matrix) of CMemory, which calls the print method on the matrix with the name passed in parameters
     * @param matrixName name of the matrix to print
     * @param os stream to print into
     */
    void print (char matrixName, std::ostream & os) const;

    /**
     * Saves the matrix into CMemory
     * @param name name of the matrix, key in the map
     * @param matrix matrix to be saved
     */
    void addMatrix (char name, const CMatrix & matrix);

    /**
     * Returns a copy of the matrix found in the parameters
     * @param name of the matrix
     * @return unique_ptr to the copy of the matrix
     */
    std::unique_ptr<CMatrix> getCopy (char name) const;

    /**
     * Searches CMemory and tries to find a record with its key equal to the parameter
     * @param key value to search for
     * @return true if found, false if not
     */
    bool contains (char key) const;

    /**
     * Returns the value of m_Saved, indicating, whether the current data in m_Data is stored somewhere in a file
     * @return value of m_Saved
     */
    bool saved () const;

    /**
     * Tries to remove a matrix with the name in parameters from memory
     * @param matrix name of the matrix to remove
     */
    void remove (char matrix);

private:

    /** container which contains all matrices */
    CMemory m_Data;

    /**
     * Indicates whether all matrices in m_Date are saved in a file
     */
    bool m_Saved;
};
