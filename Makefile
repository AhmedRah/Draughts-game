SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

EXE1 := $(BIN_DIR)/server
EXE2 := $(BIN_DIR)/client

SRC1 := $(wildcard $(SRC_DIR)/*.c)
SRC1 := $(filter-out $(SRC_DIR)/client.c, $(SRC1))

SRC2 := $(wildcard $(SRC_DIR)/*.c)
SRC2 := $(filter-out $(SRC_DIR)/server.c, $(SRC2))

OBJ1 := $(SRC1:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ2 := $(SRC2:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP
CFLAGS 	 := -Wall
LDFLAGS  := -Llib
LDLIBS   := -lm

.PHONY: all clean

all: $(EXE1) $(EXE2)


$(EXE1): $(OBJ1) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(EXE2): $(OBJ2) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ1:.o=.d)
-include $(OBJ2:.o=.d)

