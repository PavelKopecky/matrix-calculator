/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 13.05.2023
*/

#include <cassert>
#include "../src/CApplication.h"
#include "../src/CCrop.h"
#include "../src/CMatrixPersistor.h"

int main () {

    CApplication app;
    CMatrixPersistor persistor;

    app.addMatrix('A', *persistor("[[3,4],[1,9]]"));
    app.addMatrix('B', *persistor("[[1,0,0],[1,0,0]]"));
    app.addMatrix('C', *persistor("[[1,0],[0,1]]"));
    app.addMatrix('D', *persistor("[[1,0,0],[1,1,0],[1,1,1]]"));
    app.addMatrix('E', *persistor("[[3,0,0],[0,7,0],[0,0,17]]"));
    app.addMatrix('F', *persistor("[[0,0,0],[0,1,0]]"));
    app.addMatrix('G', *persistor("[[1,2],[1,3],[2,4],[2,5]]"));
    app.addMatrix('H', *persistor("[[0,1,2],[3,2,6],[1,3,2]]"));
    app.addMatrix('I', *persistor("[[1,3,1,9],[1,1,-1,1],[3,11,5,35]]"));
    app.addMatrix('J', *persistor("[[1,0,0],[-1,0,0]]"));
    app.addMatrix('K', *persistor("[[-24,1,-2],[-3,2,-6],[1,-3,2]]"));
    app.addMatrix('L', *persistor("[[-24,1,-2]]"));

    assert ( *CCrop().execute(*app.getCopy('A'), *persistor("[[2,2],[0,0]]")) == *app.getCopy('A') );
    assert ( *CCrop().execute(*app.getCopy('B'), *persistor("[[2,2],[0,0]]")) == *persistor("[[1,0],[1,0]]") );
    assert ( *CCrop().execute(*app.getCopy('C'), *persistor("[[2,2],[0,0]]")) == *app.getCopy('C') );
    assert ( *CCrop().execute(*app.getCopy('I'), *persistor("[[2,2],[0,0]]")) == *persistor("[[1,3],[1,1]]") );
    assert ( *CCrop().execute(*app.getCopy('G'), *persistor("[[2,2],[0,0]]")) == *persistor("[[1,2],[1,3]]") );
    assert ( *CCrop().execute(*app.getCopy('H'), *persistor("[[2,2],[1,1]]")) == *persistor("[[2,6],[3,2]]") );
    assert ( *CCrop().execute(*app.getCopy('I'), *persistor("[[2,2],[1,1]]")) == *persistor("[[1,-1],[11,5]]") );
    assert ( *CCrop().execute(*app.getCopy('G'), *persistor("[[2,2],[2,0]]")) == *persistor("[[2,4],[2,5]]") );
    assert ( *CCrop().execute(*app.getCopy('G'), *persistor("[[3,2],[1,0]]")) == *persistor("[[1,3],[2,4],[2,5]]") );
    assert ( *CCrop().execute(*app.getCopy('E'), *persistor("[[2,3],[1,0]]")) == *persistor("[[0,7,0],[0,0,17]]"));

    uint32_t exceptions = 0;

    try {
        CCrop().execute(*app.getCopy('L'), *persistor("[[2,2],[0,0]]"));
    } catch (...) {
        exceptions++;
    }

    try {
        CCrop().execute(*app.getCopy('A'), *persistor("[[2,2],[1,1]]"));
    } catch (...) {
        exceptions++;
    }

    try {
        CCrop().execute(*app.getCopy('B'), *persistor("[[2,2],[1,1]]"));
    } catch (...) {
        exceptions++;
    }

    try {
        CCrop().execute(*app.getCopy('I'), *persistor("[[2,2],[2,0]]"));
    } catch (...) {
        exceptions++;
    }

    try {
        CCrop().execute(*app.getCopy('J'), *persistor("[[2,2],[2,0]]"));
    } catch (...) {
        exceptions++;
    }

    try {
        CCrop().execute(*app.getCopy('E'), *persistor("[[3,2],[1,0]]"));
    } catch (...) {
        exceptions++;
    }

    assert( exceptions == 6 );

    std::cout << "Crop: All asserts passed." << std::endl;

    return EXIT_SUCCESS;
}
