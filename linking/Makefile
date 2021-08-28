CC=gcc

OUT_DIR=./out

HELLO = hello.c
# Preprocessed file
HELLO_I = $(OUT_DIR)/hello.i
# Assembly File
HELLO_S = $(OUT_DIR)/hello.s
# Object File
HELLO_O = $(OUT_DIR)/hello.o
# Statically linked binary
HELLO_ST = $(OUT_DIR)/hello_s
# Linked unstripped binary
HELLO_D = $(OUT_DIR)/hello_d
# Stripped
HELLO_strip = $(OUT_DIR)/hello_stripped

# Dynamically linked binary
HELLO_DY = $(OUT_DIR)/hello_dy

# With debugging symbols
HELLO_DEBUG = $(OUT_DIR)/hello_debugs

out-dir:
	mkdir -p $(OUT_DIR)/

# 1
preprocess: $(HELLO) out-dir
	# cpp $(HELLO) > $(HELLO_I)
	$(CC) -E $(HELLO) -o $(HELLO_I)

# 2
compile: preprocess
	$(CC) -S $(HELLO_I) -o $(HELLO_S)

# 3 Relocatable
assemble: compile
	# as $(HELLO_S) -o $(HELLO_O)
	$(CC) $(HELLO_S) -o $(HELLO_O) -c
	objdump -D $(HELLO_O) > $(HELLO_O).dump

# 4:  
link: assemble
	$(CC) -o $(HELLO_D) $(HELLO_O)

# 5:  
strip: link
	strip -o $(HELLO_strip) $(HELLO_D)

########################################################################

static: $(HELLO) out-dir
	$(CC) -static --no-pie -o $(HELLO_ST) $(HELLO)
	objdump -D $(HELLO_ST) > $(HELLO_ST).dump

dyn: $(HELLO) out-dir
	$(CC)	 -o $(HELLO_DY) $(HELLO)
	objdump -D $(HELLO_DY) > $(HELLO_DY).dump  

debug: $(HELLO) out-dir
	$(CC) -g -o $(HELLO_DEBUG) $(HELLO)

clean:
	rm -rf $(OUT_DIR)

all: link static dyn