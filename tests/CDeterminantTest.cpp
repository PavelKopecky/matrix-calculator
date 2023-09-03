/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 09.05.2023
*/

#include <cassert>
#include "../src/CDeterminant.h"
#include "../src/CMatrixPersistor.h"

int main () {

    CMatrixPersistor persistor;

    assert ( CDeterminant().execute(*persistor("[[2,1],[1,2]]"))->get(0,0) == 3 );
    assert ( CDeterminant().execute(*persistor("[[0,0],[0,0]]"))->get(0,0) == 0 );
    assert ( CDeterminant().execute(*persistor("[[1,0],[0,1]]"))->get(0,0) == 1 );
    assert ( CDeterminant().execute(*persistor("[[1,0],[1,0]]"))->get(0,0) == 0 );
    assert ( CDeterminant().execute(*persistor("[[-2,1,7],[1,-1,2],[9,0,1]]"))->get(0,0) == 82 );
    assert ( CDeterminant().execute(*persistor("[[1,0,0,0],[0,4,0,0],[0,0,2,0],[0,0,0,3]]"))->get(0,0) == 24 );
    assert ( CDeterminant().execute(*persistor("[[1,0,0,0],[0,4,0,0],[0,0,2,0],[0,0,0,0]]"))->get(0,0) == 0 );
    assert ( CDeterminant().execute(*persistor("[[1,0,0,0],[0,1,0,0],[0,0,2,0],[0,0,0,0.1]]"))->get(0,0) == 0.2 );
    assert ( CDeterminant().execute(*persistor("[[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,1]]"))->get(0,0) == 0 );
    assert ( CDeterminant().execute(*persistor("[[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]"))->get(0,0) == 0 );
    assert ( CDeterminant().execute(*persistor("[[0,2,0],[0,0,3],[4,0,0]]"))->get(0,0) == 24 );
    assert ( CDeterminant().execute(*persistor("[[0,0,3],[0,0,3],[4,0,0]]"))->get(0,0) == 0 );
    assert ( CDeterminant().execute(*persistor("[[0,2],[3,0]]"))->get(0,0) == -6 );
    assert ( CDeterminant().execute(*persistor("[[2]]"))->get(0,0) == 2 );
    assert ( CDeterminant().execute(*persistor("[[0]]"))->get(0,0) == 0 );

    bool exception = false;

    try {
        CDeterminant().execute( *persistor("[[1,0,0,0],[0,0,2,0],[0,0,0,3]]"));
    } catch (...) {
        exception = true;
    }

    assert( exception );

    std::cout << "Determinant: All asserts passed." << std::endl;

    return EXIT_SUCCESS;
}
