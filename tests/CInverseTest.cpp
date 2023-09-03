/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 18.05.2023
*/


#include <cassert>
#include "../src/CApplication.h"
#include "../src/CInverse.h"
#include "../src/CMultiply.h"
#include "../src/CMatrixPersistor.h"

int main () {

    CApplication app;
    CMatrixPersistor persistor;

    app.addMatrix('A', *persistor("[[4,3],[2,1]]"));
    app.addMatrix('B', *persistor("[[1,-2],[0.5,-0.75]]"));
    app.addMatrix('C', *persistor("[[1,0,0],[0,0,-2],[0,1,0]]"));
    app.addMatrix('D', *persistor("[[-3,2,-4],[1,0,1],[-2,-3,0]]"));
    app.addMatrix('E', *persistor("[[4,0,0],[0,-0.5,0],[0,0,-2]]"));

    assert( *CInverse().execute(*app.getCopy('A')) == *persistor("[[-0.5,1.5],[1,-2]]"));
    assert( *CInverse().execute(*app.getCopy('B')) == *persistor("[[-3,8],[-2,4]]"));
    assert( *CInverse().execute(*app.getCopy('C')) == *persistor("[[1,0,0],[0,0,1],[0,-0.5,0]]"));
    assert( *CInverse().execute(*app.getCopy('D')) == *persistor("[[-3,-12,-2],[2,8,1],[3,13,2]]"));
    assert( *CInverse().execute(*app.getCopy('E')) == *persistor("[[0.25,0,0],[0,-2,0],[0,0,-0.5]]"));

    app.addMatrix('F', *persistor("[[1,5,8],[-0.6,6,-2],[5,1,11]]"));
    app.addMatrix('G', *persistor("[[-3,2,-4,9],[12,1,0,1],[-2,-3,0,-9],[1.2,3.4,11,19.2]]"));
    app.addMatrix('H', *persistor("[[1,2,3,4,5],[6,7,8,9,10],[13,15,16,18,19],[-1,-7,10,2,11],[-0.6,23,132,9,12]]"));

    assert( *CMultiply().execute(*CInverse().execute(*app.getCopy('F')), *app.getCopy('F')) == *persistor("[[1,0,0],[0,1,0],[0,0,1]]"));
    assert( *CMultiply().execute(*CInverse().execute(*app.getCopy('G')), *app.getCopy('G')) == *persistor("[[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]]"));
    assert( *CMultiply().execute(*CInverse().execute(*app.getCopy('H')), *app.getCopy('H')) == *persistor("[[1,0,0,0,0],[0,1,0,0,0],[0,0,1,0,0],[0,0,0,1,0],[0,0,0,0,1]]"));

    uint32_t exceptions = 0;

    try {
        CInverse().execute(*persistor("[[1,0,0,0,0],[0,1,0,0,0],[0,0,1,0,0],[0,0,0,0,0],[0,0,0,0,1]]"));
    } catch (...) {
        exceptions++;
    }

    try {
        CInverse().execute(*persistor("[[-0.6,6,-2],[5,1,11]]"));
    } catch (...) {
        exceptions++;
    }

    try {
        CInverse().execute(*persistor("[[1,5],[-0.6,6],[5,1]]"));
    } catch (...) {
        exceptions++;
    }

    try {
        CInverse().execute(*persistor("[[1,1],[1,1]]"));
    } catch (...) {
        exceptions++;
    }

    try {
        CInverse().execute(*persistor("[[1,1],[2,2]]"));
    } catch (...) {
        exceptions++;
    }

    try {
        CInverse().execute(*persistor("[[0,0],[1,3]]"));
    } catch (...) {
        exceptions++;
    }

    try {
        CInverse().execute(*persistor("[[0,0,1],[0,0,4.6],[11,2,-13.4]]"));
    } catch (...) {
        exceptions++;
    }

    assert( exceptions == 7 );

    std::cout << "Inverse: All asserts passed." << std::endl;

    return EXIT_SUCCESS;
}
