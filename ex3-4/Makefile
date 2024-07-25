# Makefile: https://www.gnu.org/software/make/manual/make.html

# Define the Java compiler to use
JC = javac

# Directories
SRC_DIR = src
BIN_DIR = bin
LIB_DIR = lib
DOCS_DIR = docs

# Define compiler flags
DEST = -d $(BIN_DIR)
CLASSPATH = -cp $(BIN_DIR):$(LIB_DIR)/*

JUNIT = org.junit.runner.JUnitCore

SOURCES := $(wildcard $(SRC_DIR)/**/*.java)
JAVA_DOCS := $(filter-out src/base/Prim.java, $(wildcard $(SRC_DIR)/base/*.java))
CLASSES := $(SOURCES:src/%.java=bin/%.class)

# Default target to build everything
all: $(CLASSES)

bin/%.class: src/%.java
	$(JC) $(DEST) $(CLASSPATH) $(SRC_DIR)/**/*.java

# Rule to run the tests
test: all
	@echo "Running tests..."
	java $(CLASSPATH) $(JUNIT) test.PriorityQueueTest
	java $(CLASSPATH) $(JUNIT) test.GraphTest

# Rule to generate Javadoc
docs: $(JAVA_DOCS)
	@echo "Generating Javadoc..."
	javadoc -d $(DOCS_DIR) $(JAVA_DOCS)
	@echo "Javadoc generated successfully in 'docs' directory."

# Rule to clean the project
clean:
	@echo "Cleaning build, bin and docs directories..."
	rm -rf $(BIN_DIR) $(DOCS_DIR)

# Help rule
help:
	@echo "Makefile commands:"
	@echo "  all   - Build the entire project"
	@echo "  test  - Run the test executable"
	@echo "  docs  - Generate Javadoc"
	@echo "  clean - Clean object files and executables"

.PHONY: all clean test
