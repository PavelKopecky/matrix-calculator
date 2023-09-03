/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 06.05.2023
*/

#include <cassert>
#include "../src/CApplication.h"
#include "../src/CAdd.h"
#include "../src/CSubtract.h"
#include "../src/CMatrixPersistor.h"

int main () {

    CApplication app;
    CMatrixPersistor persistor;

    app.addMatrix('A', *persistor("[[2,1],[1,2]]"));
    app.addMatrix('B', *persistor("[[1,0,0],[1,0,0]]"));
    app.addMatrix('C', *persistor("[[0,0],[0,0]]"));
    app.addMatrix('D', *persistor("[[1,0,0],[1,1,0],[1,1,1]]"));
    app.addMatrix('E', *persistor("[[3,0,1],[0,7,0],[-1,0,17]]"));
    app.addMatrix('F', *persistor("[[3,-31,-0.312],[37,7,5.312],[-0.001,0,17]]"));

    assert( *CAdd().execute(*app.getCopy('A'), *app.getCopy('A')) == *persistor("[[4,2],[2,4]]"));
    assert( *CAdd().execute(*app.getCopy('A'), *app.getCopy('C')) == *app.getCopy('A') );
    assert( *CAdd().execute(*app.getCopy('A'), *app.getCopy('C')) == *app.getCopy('A') );
    assert( *CSubtract().execute(*app.getCopy('A'), *app.getCopy('A')) == *persistor("[[0,0],[0,0]]"));
    assert( *CAdd().execute(*app.getCopy('D'), *app.getCopy('E')) == *CAdd().execute(*app.getCopy('E'), *app.getCopy('D')) );
    assert( !(*CSubtract().execute(*app.getCopy('D'), *app.getCopy('E')) == *CSubtract().execute(*app.getCopy('E'), *app.getCopy('D'))) );
    assert( *CAdd().execute(*app.getCopy('D'), *app.getCopy('E')) == *persistor("[[4,0,1],[1,8,0],[0,1,18]]") );
    assert( *CAdd().execute(*app.getCopy('E'), *app.getCopy('F')) == *persistor("[[6,-31,0.688],[37,14,5.312],[-1.001,0,34]]"));

    uint32_t exceptions = 0;

    try {
        CAdd().execute(*app.getCopy('A'), *app.getCopy('B'));
    } catch (...) {
        exceptions++;
    }

    try {
        CSubtract().execute(*app.getCopy('B'), *app.getCopy('A'));
    } catch (...) {
        exceptions++;
    }

    assert( exceptions == 2 );

    std::cout << "Addition and subtraction: All asserts passed." << std::endl;

    return EXIT_SUCCESS;
}
