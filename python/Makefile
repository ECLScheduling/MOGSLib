CPP=g++
PYTHON_VERSION = 2.7
PV = 27
PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)
PYTHON_LIB = /usr/lib/python$(PYTHON_VERSION)/config
LIBS = -L$(PYTHON_LIB) -lboost_python$(PV) -lpython$(PYTHON_VERSION)
MOGSLIB = ../include/

TARGET = mogslib
SOURCES = load_oblivious

all: $(TARGET).so

$(TARGET).so: $(SOURCES).o
	$(CPP) -shared -Wl,--export-dynamic $(SOURCES).o $(LIBS) -o $(TARGET).so

$(SOURCES).o: $(SOURCES).cpp
	$(CPP) -I$(PYTHON_INCLUDE) -I$(MOGSLIB) -fPIC -c $(SOURCES).cpp

clean:
	rm $(SOURCES).o $(TARGET).so
