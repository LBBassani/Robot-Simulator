CC			    = g++
RM			    = rm -f
CPPFLAGS		= -Wall -std=c++11 -g #-DDEBUG -DKEY_AND_MOUSE_EVENT_VERBOSE

LDDFLAGS		= -lglut -lGL -lX11 -lGLU -lm
SRCEXT := cpp
SOURCESDIR = src
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%, $(SRCDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

TARGET := bin/wcg

all: ${TARGET}

clean:
	-rm $(OBJECTS)
	-rm $(TARGET)
	./gradlew clean
	-rm gradle -rf

%.o: %.cpp
	$(CC) -c $< $(CPPFLAGS)
	cd ..
	mv *.o ./src
	cd src

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(CPPFLAGS)"; $(CC) $^ -o $(TARGET) $(CPPFLAGS) $(LDDFLAGS)

