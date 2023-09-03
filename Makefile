CXX=g++
LD=g++ -std=c++17 -Werror
CFLAGS=-std=c++17 -Wall -pedantic -Wno-long-long -O2 -Werror
HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
TESTOBJECTS = $(filter-out build/main.o, $(OBJECTS))
TARGET=kopecp14
TESTS=debug/gauss.test debug/add.test debug/mul.test debug/crop.test debug/detMat.test debug/mul.test debug/rank.test debug/tra.test debug/merge.test debug/inverse.test

.PHONY: compile
compile: $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: doc
doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

.PHONY: all
all: compile doc

.PHONY: clean
clean:
	rm -rf build/ debug/ *.o *.app kopecp14 *.matxt doc/

.PHONY: tests
tests: $(TESTS)
	./debug/gauss.test
	./debug/add.test
	./debug/mul.test
	./debug/crop.test
	./debug/detMat.test
	./debug/mul.test
	./debug/rank.test
	./debug/tra.test
	./debug/merge.test
	./debug/inverse.test

$(TARGET): $(OBJECTS)
	 $(LD) $^ -o $@

debug/add.test: tests/CAddTest.cpp $(TESTOBJECTS)
	mkdir -p debug
	 $(LD) $^ -o $@

debug/mul.test: tests/CMulTest.cpp $(TESTOBJECTS)
	mkdir -p debug
	 $(LD) $^ -o $@

debug/tra.test: tests/CTraTest.cpp $(TESTOBJECTS)
	mkdir -p debug
	 $(LD) $^ -o $@

debug/detMat.test: tests/CDeterminantTest.cpp $(TESTOBJECTS)
	mkdir -p debug
	 $(LD) $^ -o $@

debug/gauss.test: tests/CGaussTest.cpp $(TESTOBJECTS)
	mkdir -p debug
	$(LD) $^ -o $@

debug/rank.test: tests/CRankTest.cpp $(TESTOBJECTS)
	mkdir -p debug
	$(LD) $^ -o $@

debug/crop.test: tests/CCropTest.cpp $(TESTOBJECTS)
	mkdir -p debug
	$(LD) $^ -o $@

debug/merge.test: tests/CMergeTest.cpp $(TESTOBJECTS)
	mkdir -p debug
	$(LD) $^ -o $@

debug/inverse.test: tests/CInverseTest.cpp $(TESTOBJECTS)
	mkdir -p debug
	$(LD) $^ -o $@

build/%.o: src/%.cpp
	mkdir -p build
	$(CXX) $(CFLAGS) $< -c -o $@

#dependencies
build/CAbstractNode.o: src/CAbstractNode.cpp src/CAbstractNode.h src/CMatrix.h \
  src/CUnaryOperator.h src/CBinaryOperator.h

build/CAdd.o: src/CAdd.cpp src/CAdd.h src/CBinaryOperator.h src/CMatrix.h src/CMatrixPersistor.h \
  src/CSparseMatrix.h src/CTuple.h src/CDenseMatrix.h src/CDiagonalMatrix.h

build/CApplication.o: src/CApplication.cpp src/CApplication.h src/CMatrix.h src/CMemory.h \
  src/CMatrixPersistor.h src/CSparseMatrix.h src/CTuple.h src/CDenseMatrix.h \
  src/CDiagonalMatrix.h

build/CBinaryOperator.o: src/CBinaryOperator.cpp src/CBinaryOperator.h src/CMatrix.h

build/CCrop.o: src/CCrop.cpp src/CCrop.h src/CBinaryOperator.h src/CMatrix.h src/CMatrixPersistor.h \
  src/CSparseMatrix.h src/CTuple.h src/CDenseMatrix.h src/CDiagonalMatrix.h

build/CDenseMatrix.o: src/CDenseMatrix.cpp src/CDenseMatrix.h src/CMatrix.h src/CSparseMatrix.h \
  src/CTuple.h src/CDiagonalMatrix.h

build/CDeterminant.o: src/CDeterminant.cpp src/CDeterminant.h src/CUnaryOperator.h \
  src/CMatrix.h src/CDiagonalMatrix.h src/CDenseMatrix.h

build/CDiagonalMatrix.o: src/CDiagonalMatrix.cpp src/CDiagonalMatrix.h src/CMatrix.h

build/CGauss.o: src/CGauss.cpp src/CGauss.h src/CUnaryOperator.h src/CMatrix.h

build/CInterface.o: src/CInterface.cpp src/CInterface.h src/CApplication.h src/CMatrix.h \
  src/CMemory.h src/CParser.h src/CAbstractNode.h src/CUnaryOperator.h src/CBinaryOperator.h \
  src/CMatrixPersistor.h src/CSparseMatrix.h src/CTuple.h src/CDenseMatrix.h \
  src/CDiagonalMatrix.h src/CRegister.h

build/CInverse.o: src/CInverse.cpp src/CInverse.h src/CUnaryOperator.h src/CMatrix.h \
  src/CDeterminant.h

build/CMatrix.o: src/CMatrix.cpp src/CMatrix.h

build/CMatrixPersistor.o: src/CMatrixPersistor.cpp src/CMatrixPersistor.h src/CMatrix.h \
  src/CSparseMatrix.h src/CTuple.h src/CDenseMatrix.h src/CDiagonalMatrix.h

build/CMatrixRank.o: src/CMatrixRank.cpp src/CMatrixRank.h src/CUnaryOperator.h src/CMatrix.h \
  src/CDiagonalMatrix.h

build/CMemory.o: src/CMemory.cpp src/CMemory.h src/CMatrix.h

build/CMerge.o: src/CMerge.cpp src/CMerge.h src/CBinaryOperator.h src/CMatrix.h src/CDenseMatrix.h \
  src/CMatrixPersistor.h src/CSparseMatrix.h src/CTuple.h src/CDiagonalMatrix.h

build/CMultiply.o: src/CMultiply.cpp src/CMultiply.h src/CBinaryOperator.h src/CMatrix.h \
  src/CDiagonalMatrix.h src/CDenseMatrix.h src/CSparseMatrix.h src/CTuple.h \
  src/CMatrixPersistor.h

build/CParser.o: src/CParser.cpp src/CParser.h src/CApplication.h src/CMatrix.h src/CMemory.h \
  src/CAbstractNode.h src/CUnaryOperator.h src/CBinaryOperator.h src/CMatrixPersistor.h \
  src/CSparseMatrix.h src/CTuple.h src/CDenseMatrix.h src/CDiagonalMatrix.h src/CRegister.h

build/CRegister.o: src/CRegister.cpp src/CRegister.h src/CBinaryOperator.h src/CMatrix.h \
  src/CUnaryOperator.h src/CDeterminant.h src/CGauss.h src/CInverse.h src/CMatrixRank.h \
  src/CTranspose.h src/CAdd.h src/CCrop.h src/CMerge.h src/CMultiply.h src/CSubtract.h

build/CSparseMatrix.o: src/CSparseMatrix.cpp src/CSparseMatrix.h src/CMatrix.h src/CTuple.h \
  src/CDenseMatrix.h

build/CSubtract.o: src/CSubtract.cpp src/CSubtract.h src/CBinaryOperator.h src/CMatrix.h \
  src/CMatrixPersistor.h src/CSparseMatrix.h src/CTuple.h src/CDenseMatrix.h \
  src/CDiagonalMatrix.h

build/CTranspose.o: src/CTranspose.cpp src/CTranspose.h src/CUnaryOperator.h src/CMatrix.h

build/CTuple.o: src/CTuple.cpp src/CTuple.h

build/CUnaryOperator.o: src/CUnaryOperator.cpp src/CUnaryOperator.h src/CMatrix.h

build/main.o: src/main.cpp src/CInterface.h src/CApplication.h src/CMatrix.h src/CMemory.h \
  src/CParser.h src/CAbstractNode.h src/CUnaryOperator.h src/CBinaryOperator.h \
  src/CMatrixPersistor.h src/CSparseMatrix.h src/CTuple.h src/CDenseMatrix.h \
  src/CDiagonalMatrix.h src/CRegister.h
