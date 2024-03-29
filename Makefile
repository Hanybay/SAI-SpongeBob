# Variables

MAKE = make

## Compilateur

CC = gcc
OPTIONS1 = -Wall
OPTIONS2 = -W -g -std=c89 -pedantic -O3
FLAGS = -lglut -lGLU -lGL -lm

## Répertoires

SRC_DIR = ./src
HED_DIR = ./inc
OBJ_DIR = ./obj

## Dépendances

SRC = $(shell find $(SRC_DIR) -name "*.c")
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
INC = -I$(HED_DIR)

## Exécutables

EXEC = spongeBob-universe


# Fonctions

build:
	@mkdir -p $(OBJ_DIR)
	@echo "- Building..."
	@$(MAKE) $(EXEC) --no-print-directory
	@echo "- Done"

rebuild:
	@$(MAKE) clean --no-print-directory
	@$(MAKE) build --no-print-directory

clean:
	@echo "- Cleaning..."
	@rm -rf *~ $(EXEC) $(OBJ_DIR) $(SRC_DIR)/*~
	@echo "- Cleaning done"

.PHONY: build rebuild clean


# Compilation

$(EXEC): $(OBJ)
	@echo "+ Linking..."
	@$(CC) $(OPTIONS1) $^ -o $@ $(FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "+ + Compiling \"$(notdir $<)\""
	@$(CC) -o $@ -c $(OPTIONS1) $(INC) $<
