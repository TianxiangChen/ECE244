FLAGS = -g -Wall -DX11 

HDR = ../graphics.h ../easygl.h ../easygl_constants.h 

SRC = ../graphics.cpp ../easygl.cpp example.cpp

BACKUP_FILENAME=`date "+backup-%Y%m%d-%H%M.zip"`

#Need to tell the linker to link the X11 libraries
example: graphics.o easygl.o example.o
	g++ $(FLAGS) graphics.o easygl.o example.o -lX11 -o example 

graphics.o: ../graphics.cpp $(HDR)
	g++ -c $(FLAGS) ../graphics.cpp

easygl.o: ../easygl.cpp $(HDR)
	g++ -c $(FLAGS) ../easygl.cpp

example.o: example.cpp $(HDR)
	g++ -c $(FLAGS) example.cpp


backup:
	echo Backing up your files into ${BACKUP_FILENAME}
	zip ${BACKUP_FILENAME} *.cpp *.h makefile *.sln *.vcxproj 

