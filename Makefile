bold := $(shell tput bold)
NC := $(shell tput sgr0)
red := $(shell tput setaf 1)
green := $(shell tput setaf 2)
yellow := $(shell tput setaf 3)
CC:=g++

SRC_DIR:= ./src/

LIBS:= -lGL -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

IMGUI_DIR= ./Thirdparty/imgui/

OBJECTS_DIR:= Objs/

OUTPUT:= Sim
OUTPUT_DIR:= ./Build/


SOURCES:= $(shell find $(SRC_DIR) -name  '*.cpp')

CCFLAGS= -std=c++17
OBJECTS:= $(patsubst %.cpp, %.o, $(subst ./src/, ./Objs/, $(SOURCES)))

VPATH_SRC:=$(sort $(dir $(VPATH_SRC)))

CREATE_DIRS:= $(OUTPUT_DIR) $(sort $(dir $(OBJECTS)))

vpath %.h $(HEADERS_DIR)
vpath %.cpp $(VPATH_SRC)

all: | prep
	@printf '$(red)Compiling and Linking the created objects\n$(NC)'
	@$(MAKE) -s $(OUTPUT_DIR)$(OUTPUT)
	@printf '$(green)Created binary file $(OUTPUT_DIR)$(OUTPUT)\n\n$(NC)'

$(OUTPUT_DIR)$(OUTPUT): $(OBJECTS)
	@$(CC) $(CCFLAGS) $(OBJECTS) -o $(OUTPUT_DIR)$(OUTPUT) $(LIBS)


prep:
	@mkdir -p $(CREATE_DIRS)

$(OBJECTS): $(OBJECTS_DIR)%.o : $(SRC_DIR)%.cpp
	@printf '$(bold)========== Compiling $(red)$(notdir $^)$(NC)$(bold) ======\n$(NC)'
	@$(CC) -c $(CCFLAGS) $< -o $@
	@printf '$(green)========== Compiled Successfully ======\n$(NC)'

.PHONY: clean

clean:
	@$(RM) $(OBJECTS)
	@$(RM) $(OUTPUT_DIR)$(OUTPUT)
	@printf 'Successfully Cleaned\n'

run:
	@$(MAKE) $(OUTPUT_DIR)$(OUTPUT) -s -j 10
	@./$(OUTPUT_DIR)$(OUTPUT)

print:
	@for obj in $(CREATE_DIRS); do\
		echo $$obj;\
	done