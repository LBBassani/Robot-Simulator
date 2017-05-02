CC			    = clang++
RM			    = rm -f
CPPFLAGS		= -Wall -O3 -std=c++11 #-DDEBUG -DKEY_AND_MOUSE_EVENT_VERBOSE

LDDFLAGS		= -lglut -lGL -lX11 -lGLU -lm
SRCEXT := cpp
SOURCESDIR = src
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%, $(SRCDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

TARGET := bin/wcg

all: ${TARGET}

clean:
	rm $(OBJECTS)
	rm $(TARGET)

%.o: %.cpp
	$(CC) -c $< $(CPPFLAGS)
	cd ..
	mv *.o ./src
	cd src

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(CPPFLAGS)"; $(CC) $^ -o $(TARGET) $(CPPFLAGS) $(LDDFLAGS)

