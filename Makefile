
all: projX

projX: projX.cpp DataType.h DataType.cpp SmartPtr.h SmartPtr.cpp
	g++ projX.cpp DataType.h DataType.cpp SmartPtr.h SmartPtr.cpp -o projX

clean:
		rm -f projX
		rm -f *.o
		rm -f *.h.gch
