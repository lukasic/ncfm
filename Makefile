CXX=g++
CXXFLAGS=-std=c++11 -pedantic -Wall -ggdb -g -D__DEBUG__ -Wno-long-long -O0 -ggdb
LD=g++ 
LDFLAGS= -std=c++11 -lmenu -lpanel -lncurses  -std=c++11
OBJ=src/FSSymlink.o src/Command.o src/constants.o src/Logger.o src/FSPath.o \
  src/FSDir.o src/FSFile.o src/FSObject.o src/NCFolderView.o src/NCObject.o \
  src/NCPanel.o src/NCPanelContainer.o src/NCRowMenu.o src/NCScreen.o src/NCWidget.o \
  src/main.o src/shared.o src/third_party.o

all: ncfm
compile: ncfm

ncfm: $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o ncfm

run: ncfm
	./ncfm

doc: Doxyfile
	doxygen Doxyfile

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf debug.log
	rm -rf src/*.o
	rm -rf ncfm
	if [ -d doc ]; then rm -rf doc; fi

sudebug: kasicluk/kasicluk
	sudo gdb ./ncfm

debug: kasicluk/kasicluk
	gdb ./ncfm

FSDir.o: src/FSDir.cpp src/FSPath.h src/constants.h src/FSDir.h src/FSObject.h \
  src/third_party.h src/FSFile.h src/Logger.h
FSPath.o: src/FSPath.cpp src/FSPath.h src/third_party.h src/Logger.h
FSFile.o: src/FSFile.cpp src/FSPath.h src/FSFile.h src/FSObject.h src/FSSymlink.h src/Logger.h
FSSymlink.o: src/FSFile.cpp src/FSPath.h src/FSFile.h src/FSObject.h src/Logger.h
FSObject.o: src/FSObject.cpp src/FSPath.h src/Logger.h
NCFolderView.o: src/NCFolderView.cpp src/NCFolderView.h src/FSDir.h \
  src/constants.h src/FSObject.h src/third_party.h src/NCPanel.h \
  src/NCWidget.h src/NCObject.h src/NCPanelContainer.h src/shared.h src/Logger.h
NCObject.o: src/NCObject.cpp src/NCObject.h
NCPanel.o: src/NCPanel.cpp src/NCPanel.h src/NCWidget.h src/NCObject.h \
  src/NCPanelContainer.h src/NCFolderView.h src/FSDir.h src/constants.h \
  src/FSObject.h src/third_party.h src/shared.h src/Logger.h
NCPanelContainer.o: src/NCPanelContainer.cpp src/NCPanel.h src/NCWidget.h \
  src/NCObject.h src/NCPanelContainer.h src/NCFolderView.h src/FSDir.h \
  src/constants.h src/FSObject.h src/third_party.h src/Logger.h
NCRowMenu.o: src/NCRowMenu.cpp src/NCObject.h src/NCWidget.h \
  src/NCRowMenu.h src/constants.h src/Logger.h
NCScreen.o: src/NCScreen.cpp src/NCScreen.h src/NCPanelContainer.h \
  src/NCPanel.h src/NCWidget.h src/NCObject.h src/NCFolderView.h \
  src/FSDir.h src/constants.h src/FSObject.h src/third_party.h \
  src/NCRowMenu.h src/shared.h src/Logger.h
NCWidget.o: src/NCWidget.cpp src/NCWidget.h src/NCObject.h
main.o: src/main.cpp src/NCScreen.h src/NCPanelContainer.h src/NCPanel.h \
  src/NCWidget.h src/NCObject.h src/NCFolderView.h src/FSDir.h \
  src/constants.h src/FSObject.h src/third_party.h src/Logger.h
shared.o: src/shared.cpp src/shared.h src/Logger.h
third_party.o: src/third_party.cpp src/third_party.h src/Logger.h
Logger.o: src/Logger.cpp src/Logger.h src/constants.h
constants.o: src/constants.h src/constants.cpp
Command.o: src/Command.h src/Command.cpp

