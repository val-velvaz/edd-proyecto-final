# --- CONFIGURACIÓN DEL COMPILADOR ---
CXX = g++.exe

# --- CONFIGURACIÓN DEL PROYECTO ---
TARGET = output/recetario_game.exe

# --- CONFIGURACIÓN DE SFML (ESTÁTICO) ---
SFML_DIR = lib/SFML
SFML_INCLUDE = -I$(SFML_DIR)/include
SFML_STATIC_DEF = -DSFML_STATIC

# --- BANDERAS (FLAGS) DE COMPILACIÓN ---
# Optimizaciones para la versión final y flags necesarios
CXXFLAGS = -std=c++14 -Iinclude $(SFML_INCLUDE) $(SFML_STATIC_DEF) -m64 -O2 -Wall

# --- LIBRERÍAS DE ENLAZADO ESTÁTICO EN ORDEN ESTRICTO ---
# Se listan todas las dependencias de SFML, incluyendo las de audio y red,
# para asegurar que el enlazador encuentre todo lo que necesita.
LIBS = \
    -lsfml-graphics-s \
    -lsfml-window-s \
    -lsfml-audio-s \
    -lsfml-network-s \
    -lsfml-system-s \
    -lopengl32 \
    -lfreetype \
    -lwinmm \
    -lgdi32 \
    -m64 \
    -lws2_32 \
    -lopenal32 \
    -lflac \
    -lvorbisenc \
    -lvorbisfile \
    -lvorbis \
    -logg \
    -static-libgcc \
    -static-libstdc++

LDFLAGS = -L$(SFML_DIR)/lib $(LIBS)

# --- BÚSQUEDA RECURSIVA DE ARCHIVOS ---
SOURCES = $(shell find src -name '*.cpp')
OBJECTS = $(SOURCES:.cpp=.o)

# --- REGLAS DE MAKEFILE ---
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- REGLAS ADICIONALES ---
clean:
	rm -f $(OBJECTS) $(TARGET)

run: all
	./$(TARGET)