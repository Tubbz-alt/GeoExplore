
INCL=-I/opt/local/include
LIBS=-L/opt/local/lib -lopencv_core

testRender: testRender.cpp
	g++ $< -o $@  ${LIBS} ${INCL}


clean:
	rm testRender

