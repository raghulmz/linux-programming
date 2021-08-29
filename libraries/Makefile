CC=gcc
LIB_DIR=lib
INCLUDE_DIR=include
OUT_DIR=out

OBJ_FILE=$(OUT_DIR)/simplelib.o
AR_FILE=$(LIB_DIR)/libsimple.a 

PIE_OBJ_FILE=$(OUT_DIR)/piesimplelib.o
SO_FILE_NAME=simplelib.so.1.1.1
SO_FILE=$(LIB_DIR)/$(SO_FILE_NAME)
SO=libsimple.so
SO_NAME=$(SO).1

PROG_FILE=program.c

CC_OPTS_PROG=-lsimple -I $(INCLUDE_DIR) -L $(LIB_DIR)

libdir:
	mkdir -p $(LIB_DIR)

includedir:
	mkdir -p $(INCLUDE_DIR)

outdir:
	mkdir -p $(OUT_DIR)

# Static Library
object: outdir
	$(CC) -c simplelib.c -o $(OBJ_FILE)
	file $(OBJ_FILE)

static-lib: object libdir
	ar cr $(AR_FILE) $(OBJ_FILE)
	file $(AR_FILE)
	ar t $(AR_FILE)

binary-with-staticlib: staticlib
	$(CC) -o $(OUT_DIR)/program $(PROG_FILE) $(CC_OPTS_PROG)
	file $(OUT_DIR)/program
	./$(OUT_DIR)/program

# Shared Library
pie-object: outdir
	$(CC) -fpie -c -o $(PIE_OBJ_FILE) simplelib.c
	file $(PIE_OBJ_FILE)

shared-lib: pie-object libdir
	$(CC) -o $(SO_FILE) $(PIE_OBJ_FILE) -shared -Wl,-soname,$(SO_NAME)
	file $(SO_FILE)
	readelf -a $(SO_FILE) | grep soname

link: clean shared-lib
	cd $(LIB_DIR) && ln -s $(SO_FILE_NAME) $(SO_NAME)
	cd $(LIB_DIR) && ln -s $(SO_NAME) $(SO)
	ls -lah $(LIB_DIR)

binary-with-shared: link
	$(CC) -o $(OUT_DIR)/program $(PROG_FILE) $(CC_OPTS_PROG)
	file $(OUT_DIR)/program
	LD_LIBRARY_PATH=$(LIB_DIR) ./$(OUT_DIR)/program

clean:
	rm --preserve-root -rf $(OUT_DIR) $(LIB_DIR)