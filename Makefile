# DIRECTORIES
SYSROOT_DIR := ../sysroot
SYSROOT_INCLUDE_DIR := $(SYSROOT_DIR)/usr/include
SYSROOT_LIB_DIR := $(SYSROOT_DIR)/usr/lib
SRC_DIR := ./src
OBJ_DIR := ./obj
INCLUDE_DIR := ./include

# TARGET
LIBC := $(SYSROOT_LIB_DIR)/libc.a
CRT0 := $(SYSROOT_LIB_DIR)/crt0.o

# SOURCE FILES
C_SRC_FILES := $(shell find $(SRC_DIR) -name '*.c')
ASM_SRC_FILES := $(shell find $(SRC_DIR) -name '*.asm')
HEADER_FILES := $(shell find $(INCLUDE_DIR) -name '*.h')
CRT0_SRC := ./crt0.asm

# OBJECT FILES
C_OBJ_FILES := $(C_SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
ASM_OBJ_FILES := $(ASM_SRC_FILES:$(SRC_DIR)/%.asm=$(OBJ_DIR)/%.o)

# PROGRAMS
CC := x86_64-los-gcc
CC_FLAGS := -c -Wall

ASM := nasm
ASM_FLAGS := -f elf64

AR := x86_64-los-ar
AR_FLAGS := rcs

# BASE RULES
all: install

clean:
	rm -rf $(SYSROOT_LIB_DIR)/*
	rm -rf $(SYSROOT_INCLUDE_DIR)/*
	rm -rf $(OBJ_DIR)/*

install: dirs includes $(LIBC) $(CRT0)

# COMPILATION RULES
.SECONDEXPANSION:

includes: $(HEADER_FILES)
	cp -r $(INCLUDE_DIR)/ $(SYSROOT_INCLUDE_DIR)/..


$(LIBC): $(C_OBJ_FILES) $(ASM_OBJ_FILES)
	$(AR) $(AR_FLAGS) $@ $^

$(CRT0): $(CRT0_SRC)
	$(ASM) $(ASM_FLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $$(@D)/.
	$(CC) $(CC_FLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm | $$(@D)/.
	$(ASM) $(ASM_FLAGS) -o $@ $^

# DIRECTORY RULES
$(OBJ_DIR)/.:
	@mkdir -p $@

$(OBJ_DIR)%/.:
	@mkdir -p $@

dirs:
	@mkdir -p $(OBJ_DIR)

# . RULES
.PRECIOUS: $(OBJ_DIR)/. $(OBJ_DIR)%/.
.PHONY: dirs