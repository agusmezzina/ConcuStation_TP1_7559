# Makefile para generar un ejecutable diferente para cada proceso.

CC=g++
CFLAGS=-O0 -Wall -g3

# Directorios de trabajo
ODIR=bin
DIR=src
DIR_JE=src/JefeEstacion
DIR_E=src/Empleado
DIR_CC=src/ConsultarCaja
DIR_CM=src/Common
DIR_LC=src/LectorComandos

# Definición de código fuente
DEPS=$(wildcard $(DIR)/*.h)
SRC=$(wildcard $(DIR)/*.cpp)
OBJ=$(patsubst $(DIR)/%.cpp, $(ODIR)/$(DIR)/%.o, $(SRC))

DEPS_JE=$(wildcard $(DIR_JE)/*.h)
SRC_JE=$(wildcard $(DIR_JE)/*.cpp)
OBJ_JE=$(patsubst $(DIR_JE)/%.cpp, $(ODIR)/$(DIR_JE)/%.o, $(SRC_JE))

DEPS_E=$(wildcard $(DIR_E)/*.h)
SRC_E=$(wildcard $(DIR_E)/*.cpp)
OBJ_E=$(patsubst $(DIR_E)/%.cpp, $(ODIR)/$(DIR_E)/%.o, $(SRC_E))

DEPS_CC=$(wildcard $(DIR_CC)/*.h)
SRC_CC=$(wildcard $(DIR_CC)/*.cpp)
OBJ_CC=$(patsubst $(DIR_CC)/%.cpp, $(ODIR)/$(DIR_CC)/%.o, $(SRC_CC))

DEPS_CM=$(wildcard $(DIR_CM)/*.h)
SRC_CM=$(wildcard $(DIR_CM)/*.cpp)
OBJ_CM=$(patsubst $(DIR_CM)/%.cpp, $(ODIR)/$(DIR_CM)/%.o, $(SRC_CM))

DEPS_LC=$(wildcard $(DIR_LC)/*.h)
SRC_LC=$(wildcard $(DIR_LC)/*.cpp)
OBJ_LC=$(patsubst $(DIR_LC)/%.cpp, $(ODIR)/$(DIR_LC)/%.o, $(SRC_LC))

#--------------------------------------------------------------------------------------------------------------

# Reglas

$(ODIR)/$(DIR)/%.o: $(DIR)/%.cpp $(DEPS)
	@mkdir -p $(@D)
	@$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/$(DIR_JE)/%.o: $(DIR_JE)/%.cpp $(DEPS_JE)
	@mkdir -p $(@D)
	@$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/$(DIR_E)/%.o: $(DIR_E)/%.cpp $(DEPS_E)
	@mkdir -p $(@D)
	@$(CC) -c -o $@ $< $(CFLAGS)
	
$(ODIR)/$(DIR_CC)/%.o: $(DIR_CC)/%.cpp $(DEPS_CC)
	@mkdir -p $(@D)
	@$(CC) -c -o $@ $< $(CFLAGS)
	
$(ODIR)/$(DIR_CM)/%.o: $(DIR_CM)/%.cpp $(DEPS_CM)
	@mkdir -p $(@D)
	@$(CC) -c -o $@ $< $(CFLAGS)
	
$(ODIR)/$(DIR_LC)/%.o: $(DIR_LC)/%.cpp $(DEPS_LC)
	@mkdir -p $(@D)
	@$(CC) -c -o $@ $< $(CFLAGS)

ConcuStation: $(OBJ) $(OBJ_CM)
	$(CC) $^ -o $(ODIR)/$@ $(CFLAGS) -lm

JefeEstacion: $(OBJ_JE) $(OBJ_CM)
	$(CC) $^ -o $(ODIR)/$@ $(CFLAGS)
	
Empleado: $(OBJ_E) $(OBJ_CM)
	$(CC) $^ -o $(ODIR)/$@ $(CFLAGS)

ConsultarCaja: $(OBJ_CC) $(OBJ_CM)
	$(CC) $^ -o $(ODIR)/$@ $(CFLAGS)
	
LectorComandos: $(OBJ_LC) $(OBJ_CM)
	$(CC) $^ -o $(ODIR)/$@ $(CFLAGS)
	
all: ConcuStation JefeEstacion Empleado ConsultarCaja LectorComandos

.PHONY: clean all

clean:
	@rm -f $(ODIR)/$(DIR)/*.o
	@rm -f $(ODIR)/$(DIR_CM)/*.o
	@rm -f $(ODIR)/$(DIR_JE)/*.o
	@rm -f $(ODIR)/$(DIR_E)/*.o
	@rm -f $(ODIR)/$(DIR_CC)/*.o
	@rm -f $(ODIR)/$(DIR_LC)/*.o
