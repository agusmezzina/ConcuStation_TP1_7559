# Makefile para generar un ejecutable diferente para cada proceso.
# Hay que completar a mano los nombres de los fuentes (por ahora).

CC=g++
CFLAGS=-O0 -Wall

ODIR=bin
DIR=src
DIR_JE=src/JefeEstacion
DIR_E=src/Empleado
DIR_CC=src/ConsultarCaja
DIR_CM=src/Common

#Agregar headers y archivos de código nuevos de la carpeta src/JefeEstacion
DEPS_JE=$(DIR_JE)/JefeEstacion.h
OBJ_JE=$(ODIR)/$(DIR_JE)/main.o $(ODIR)/$(DIR_JE)/JefeEstacion.o

#Agregar headers y archivos de código nuevos de la carpeta src/Empleado
DEPS_E=$(DIR_E)/Empleado.h
OBJ_E=$(ODIR)/$(DIR_E)/main.o $(ODIR)/$(DIR_E)/Empleado.o

#Agregar headers y archivos de código nuevos de la carpeta src/ConsultarCaja
DEPS_CC=$(DIR_CC)ConsultarCaja.h
OBJ_CC=$(ODIR)/$(DIR_CC)/main.o $(ODIR)/$(DIR_CC)/ConsultarCaja.o

#Agregar headers y archivos de código nuevos de la carpeta src
DEPS=
OBJ=$(ODIR)/$(DIR)/ConcuStation.o

#Agregar headers y archivos de código nuevos de la carpeta src/Common
DEPS_CM=$(DIR_CM)/EventHandler.h $(DIR_CM)/MemoriaCompartida2.h $(DIR_CM)/ProcessManager.h $(DIR_CM)/SIGINT_Handler.h $(DIR_CM)/SignalHandler.h
OBJ_CM=$(ODIR)/$(DIR_CM)/ProcessManager.o $(ODIR)/$(DIR_CM)/SignalHandler.o

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

ConcuStation: $(OBJ) $(OBJ_CM)
	$(CC) $^ -o $(ODIR)/$@ $(CFLAGS)

JefeEstacion: $(OBJ_JE) $(OBJ_CM)
	$(CC) $(OBJ_JE) -o $(ODIR)/$@ $(CFLAGS)
	
Empleado: $(OBJ_E) $(OBJ_CM)
	$(CC) $^ -o $(ODIR)/$@ $(CFLAGS)

ConsultarCaja: $(OBJ_CC) $(OBJ_CM)
	$(CC) $^ -o $(ODIR)/$@ $(CFLAGS)
	
all: ConcuStation JefeEstacion Empleado ConsultarCaja

.PHONY: clean

clean:
	@rm -f $(ODIR)/$(DIR)/*.o
	@rm -f $(ODIR)/$(DIR_CM)/*.o
	@rm -f $(ODIR)/$(DIR_JE)/*.o
	@rm -f $(ODIR)/$(DIR_E)/*.o
	@rm -f $(ODIR)/$(DIR_CC)/*.o
