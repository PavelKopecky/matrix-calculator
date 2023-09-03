/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 24.05.2023
*/

#pragma once
#include <map>
#include "CMatrix.h"

/**
 * Class serving as a storage for all matrices for a given app
 */
class CMemory {
public:

    CMemory () = default;

    /**
     * Copy constructor, creates a deep copy of the memory in parameters
     * @param copy CMemory to be copied
     */
    CMemory (const CMemory & copy);

    /**
     * Op =, creates a deep copy of the memory in parameters
     * @param copy
     * @return this
     */
    CMemory & operator = (CMemory copy);

    ~CMemory() = default;

    /**
     * Looks for a matrix with the particular name
     * @param matrix name of the matrix to look far
     * @return true if this matrix exists in the m_Data map
     */
    bool contains (char matrix) const;

    /**
     * Checks if the memory contains any data
     * @return true if there are no matrices saved
     */
    bool empty () const;

    /**
     * Adds a matrix to the m_Data map, if the matrix already exists, overwrite it
     * calls the copy method of the matrix to get a unique_ptr
     * @param name name of the matrix (= key in the map)
     * @param matrix matrix to be saved
     */
    void add (char name, const CMatrix & matrix);

    /**
     * Returns a unique_ptr to a matrix from the m_Data map with the correct name
     * it is guaranteed, that such matrix exists
     * @param name name of the matrix (= key in the map)
     * @return unique_ptr to the searched matrix
     */
    std::unique_ptr<CMatrix> getCopy (char name) const;

    /**
     * Calls the print method of the matrix with name in parameters
     * @param matrix name of the matrix (= key in the map)
     * @param output ostream to print into
     */
    void print (char matrix, std::ostream & output) const;

    /**
     * Calls the print method on every matrix in the m_Data map
     * @param output ostream to print into
     */
    void print (std::ostream & output) const;

    /**
     * Saves all matrices saved in the m_Data map into a file
     * Calls the write method of every matrix
     * @param fileName name of the file to write into
     */
    void saveToFile (const std::string & fileName) const;

    /**
     * Removes a matrix with the name from parameters
     * The matrix is guaranteed to exist in the map
     * @param matrix name of the matrix to remove
     */
    void remove (char matrix);

private:

    /** contains all matrices */
    std::map<char, std::unique_ptr<CMatrix>> m_Data;
};
