################################################################################
#####                                                                      #####
#####          Micro C Compiler Project                                    #####
#####          INSA LYON IF-4-PLD-COMP                                     #####
#####          Made by students of INSA LYON IF4-H4112                     #####
#####                                                                      #####
################################################################################

#--------------------------------------
# Variable definition
#--------------------------------------

# Build mode
DEBUG=yes

# Defines
DEFINE_DEBUG=no
DEFINE_DETAIL=no

# Directory locations
OBJ_DIR=obj
GOBJ_DIR=genobj
BIN_DIR=bin
SRC_DIR=src
LEX_DIR=lex
YACC_DIR=yacc
GSRC_DIR=gensrc
DOC_DIR=doc
PSRC_DIR=pdfsrc


LXPREFIX=yy
YCPREFIX=tab

# Files needed for build
SRC=$(wildcard $(SRC_DIR)/*.cpp)
HEAD=$(wildcard $(SRC_DIR)/*.h)
LEX_SRC=$(wildcard $(LEX_DIR)/*.l) $(wildcard $(LEX_DIR)/*.lpp)
YACC_SRC=$(wildcard $(YACC_DIR)/*.y) $(wildcard $(YACC_DIR)/*.ypp)
DXFILE=Doxyfile

# Executables
RELEASE_EXEC=CCompiler.exe
TEST_EXEC=Lexer.exe
# Main files do not have a .h
RELEASE_MAIN=CCompiler
TEST_MAIN=LexerMain

# Files derived from source files
GSRC=$(filter %.c %.cpp,$(LEX_SRC:$(LEX_DIR)/%.l=$(GSRC_DIR)/%.$(LXPREFIX).c) \
$(LEX_SRC:$(LEX_DIR)/%.lpp=$(GSRC_DIR)/%.$(LXPREFIX).cpp) \
$(YACC_SRC:$(YACC_DIR)/%.y=$(GSRC_DIR)/%.$(YCPREFIX).c) \
$(YACC_SRC:$(YACC_DIR)/%.ypp=$(GSRC_DIR)/%.$(YCPREFIX).cpp))

GHEAD=$(filter %.h,$(YACC_SRC:$(YACC_DIR)/%.y=$(GSRC_DIR)/%.$(YCPREFIX).h) \
$(YACC_SRC:$(YACC_DIR)/%.ypp=$(GSRC_DIR)/%.$(YCPREFIX).h))

TMP=$(filter %.o,$(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) \
$(GSRC:$(GSRC_DIR)/%.c=$(GOBJ_DIR)/%.o) \
$(GSRC:$(GSRC_DIR)/%.cpp=$(GOBJ_DIR)/%.o))

RELEASE_OBJ=$(filter-out $(OBJ_DIR)/$(TEST_MAIN).o,$(TMP))
TEST_OBJ=$(filter-out $(OBJ_DIR)/$(RELEASE_MAIN).o,$(TMP))

PSRC=$(filter %.pdf,$(PSRC_DIR)/Makefile.pdf $(PSRC_DIR)/Doxyfile.pdf \
$(PSRC_DIR)/README.md.pdf $(SRC:$(SRC_DIR)/%.cpp=$(PSRC_DIR)/%.cpp.pdf) \
$(SRC:$(SRC_DIR)/%.c=$(PSRC_DIR)/%.c.pdf) \
$(HEAD:$(SRC_DIR)/%.h=$(PSRC_DIR)/%.h.pdf) \
$(LEX_SRC:$(LEX_DIR)/%.l=$(PSRC_DIR)/%.l.pdf) \
$(LEX_SRC:$(LEX_DIR)/%.lpp=$(PSRC_DIR)/%.lpp.pdf) \
$(YACC_SRC:$(YACC_DIR)/%.y=$(PSRC_DIR)/%.y.pdf) \
$(YACC_SRC:$(YACC_DIR)/%.ypp=$(PSRC_DIR)/%.ypp.pdf))

EXECFILES=$(BIN_DIR)/$(RELEASE_EXEC) $(BIN_DIR)/$(TEST_EXEC)
MAINFILES=$(EXECFILES:$(BIN_DIR)/%.exe=$(SRC_DIR)/%.cpp)
MAINOBJS=$(MAINFILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Build commands
CC=@gcc
CPP=@g++
LEX=@flex
YACC=@bison
LN=@g++
RM=rm
RMFLAGS=-f
ECHO=@echo
DOXY=@doxygen
ES=enscript
PSPDF=ps2pdf
ENCODE=iconv -f utf-8 -t iso-8859-1
PKMG=apt-get -y


# Selecting libraries and include directories
LIBS=-lfl
LIBSPATH=
INCLUDES=-Isrc -Igensrc

# Selecting compiler flags depending on build mode

ifeq ($(DEBUG),yes)
	CFLAGS=-Wshadow -Winit-self -Wredundant-decls \
    -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code \
    -Wmissing-declarations -Wmissing-include-dirs \
    -Wmain -pedantic -Wall \
    -Wextra -ansi -pg -g \
    -Wcast-qual -Wctor-dtor-privacy \
    -Wdisabled-optimization -Wformat=2 \
    -Wlogical-op -Wno-reorder\
    -Wnoexcept -Wold-style-cast -Woverloaded-virtual \
    -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel \
    -Wstrict-overflow=5 -Werror -Wno-sign-conversion -Wno-unused -fno-elide-constructors -std=c++11
#	CFLAGS=-Wextra -ansi -pg -g -pedantic -Wall -std=c++11 -Weffc++ -Wswitch-enum
	LNFLAGS=-g -pg
else
	CFLAGS=-s -O3 -fexpensive-optimizations -std=c++11
	DEFINE=
	LNFLAGS=
endif

LXFLAGS=
YCFLAGS="--report=all" -v
DXFLAGS=
ESFLAGS=--media=A4 --language=PostScript --color=1 --encoding=latin1

GENCFLAGS=-std=c++11
GENCPPFLAGS=$(CFLAGS)

# applying define directives
ifeq ($(DEFINE_DEBUG),yes)
	DEFINE=-DDEBUG
endif

ifeq ($(DEFINE_DETAIL),yes)
	#TMP=$(DEFINE)
	DEFINE+= -DDETAIL
endif



#--------------------------------------
# Build rules
#--------------------------------------
# Default Rule
all : dir $(EXECFILES)
test : all

# -----------------
# Rules to generate application file(s)
# -----------------

$(BIN_DIR)/$(RELEASE_EXEC) : $(RELEASE_OBJ)
	$(ECHO) "$(LN) -o $@ $^"
	@test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(LN) $(LNFLAGS) -o $@ $^ $(LIBS) $(LIBSPATH)

$(BIN_DIR)/$(TEST_EXEC) : $(TEST_OBJ)
	$(ECHO) "$(LN) -o $@ $^"
	@test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(LN) $(LNFLAGS) -o $@ $^ $(LIBS) $(LIBSPATH)

#$(EXECUTABLES) : $(OBJ)
#	$(ECHO) "$(LN) -o $@ $^"
#	@test -d $(BIN_DIR) || mkdir $(BIN_DIR)
#	$(LN) $(LNFLAGS) -o $@ $^ $(LIBS) $(LIBSPATH)

# -----------------
# Rule to generate documentation
# -----------------

$(DOC_DIR) : $(SRC_DIR) $(DXFILE) Makefile
	$(ECHO) $(DOXY) $(DXFILE)
	@test -d $(DOC_DIR) || mkdir $(DOC_DIR)
	$(DOXY) $(DXFILE) $(DXFLAGS)

# -----------------
# Rules to compile CPP files
# -----------------

$(MAINOBJS) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp Makefile
	$(ECHO) "$(CPP) -o $@ -c $<"
	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	$(CPP) -o $@ -c $< $(CFLAGS) $(INCLUDES) $(DEFINE)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(SRC_DIR)/%.h Makefile
	$(ECHO) "$(CPP) -o $@ -c $<"
	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	$(CPP) -o $@ -c $< $(CFLAGS) $(INCLUDES) $(DEFINE)

#$(OBJ_DIR)/$(RELEASE_MAIN).o : $(SRC_DIR)/$(RELEASE_MAIN).cpp Makefile
#	$(ECHO) "$(CPP) -o $@ -c $<"
#	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
#	$(CPP) -o $@ -c $< $(CFLAGS) $(INCLUDES) $(DEFINE)

#$(OBJ_DIR)/$(LEXER_MAIN).o : $(SRC_DIR)/$(LEXER_MAIN).cpp Makefile
#	$(ECHO) "$(CPP) -o $@ -c $<"
#	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
#	$(CPP) -o $@ -c $< $(CFLAGS) $(INCLUDES) $(DEFINE)

$(GOBJ_DIR)/%.o : $(GSRC_DIR)/%.cpp $(GHEAD) Makefile
	$(ECHO) "$(CPP) -o $@ -c $<"
	@test -d $(GOBJ_DIR) || mkdir $(GOBJ_DIR)
	$(CPP) -o $@ -c $< $(GENCFLAGS) $(INCLUDES)

# -----------------
# Rules to compile C files
# -----------------

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(SRC_DIR)/%.h Makefile
	$(ECHO) "$(CC) -o $@ -c $<"
	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES) $(DEFINE)

#rule to force generration of headers used by lexers
# $(GOBJ_DIR)/%.tab.o : $(GSRC_DIR)/%.tab.c Makefile $(GSRC_DIR)/%.yy.c
	# $(ECHO) "$(CC) -o $@ -c $<"
	# @test -d $(GOBJ_DIR) || mkdir $(GOBJ_DIR)
	# $(CC) $(INCLUDES) -o $@ -c $<

$(GOBJ_DIR)/%.o : $(GSRC_DIR)/%.c $(GHEAD) Makefile
	$(ECHO) "$(CC) -o $@ -c $<"
	@test -d $(GOBJ_DIR) || mkdir $(GOBJ_DIR)
	$(CC) -o $@ -c $< $(GENCFLAGS) $(INCLUDES)

# -----------------
# Rules to compile (F)LEX files
# -----------------

$(GSRC_DIR)/%.$(LXPREFIX).c : $(LEX_DIR)/%.l Makefile
	$(ECHO) "$(LEX) -P$(LXPREFIX) -o$@ $<"
	@test -d $(GSRC_DIR) || mkdir $(GSRC_DIR)
	$(LEX) $(LXFLAGS) -P$(LXPREFIX) -o$@ $<

$(GSRC_DIR)/%.$(LXPREFIX).cpp : $(LEX_DIR)/%.lpp Makefile
	$(ECHO) "$(LEX) -P$(LXPREFIX) --c++ -o$@ $<"
	@test -d $(GSRC_DIR) || mkdir $(GSRC_DIR)
	$(LEX) $(LXFLAGS) -P$(LXPREFIX) --c++ -o$@ $<

# -----------------
# Rules to compile YACC files
# -----------------

$(GSRC_DIR)/%.$(YCPREFIX).c : $(YACC_DIR)/%.y Makefile
	$(ECHO) "$(YACC) --defines=$(@:$(GSRC_DIR)/%.c=$(GSRC_DIR)/%.h) -o $@ $<"
	@test -d $(GSRC_DIR) || mkdir $(GSRC_DIR)
	$(YACC) $(YCFLAGS) --defines=$(@:$(GSRC_DIR)/%.c=$(GSRC_DIR)/%.h) -o $@ $<


$(GSRC_DIR)/%.$(YCPREFIX).cpp : $(YACC_DIR)/%.ypp Makefile
	$(ECHO) "$(YACC) --defines=$(@:$(GSRC_DIR)/%.cpp=$(GSRC_DIR)/%.h) -o $@ $<"
	@test -d $(GSRC_DIR) || mkdir $(GSRC_DIR)
	$(YACC) $(YCFLAGS) --defines=$(@:$(GSRC_DIR)/%.cpp=$(GSRC_DIR)/%.h) -o $@ $<


$(filter %.h,$(YACC_SRC:$(YACC_DIR)/%.y=$(GSRC_DIR)/%.$(YCPREFIX).h)) : %.h : %.c
$(filter %.h,$(YACC_SRC:$(YACC_DIR)/%.ypp=$(GSRC_DIR)/%.$(YCPREFIX).h)) : %.h : %.cpp

# -----------------
# Rules to create printable code
# -----------------

.PHONY : printable
printable : $(PSRC)

$(PSRC_DIR)/Makefile.pdf : Makefile
	$(ECHO) "$(ES) -Emakefile -p - $< | $(PSPDF) - $@"
	@test -d $(PSRC_DIR) || mkdir $(PSRC_DIR)
	@$(ENCODE) $< | $(ES) $(ESFLAGS) --highlight=makefile -p - | $(PSPDF) - $@

$(PSRC_DIR)/Doxyfile.pdf : Doxyfile
	$(ECHO) "$(ES) -Emakefile -p - $< | $(PSPDF) - $@"
	@test -d $(PSRC_DIR) || mkdir $(PSRC_DIR)
	@$(ENCODE) $< | $(ES) $(ESFLAGS) --highlight=makefile -p - | $(PSPDF) - $@

$(PSRC_DIR)/%.md.pdf : %.md
	$(ECHO) "$(ES) -p - $< | $(PSPDF) - $@"
	@test -d $(PSRC_DIR) || mkdir $(PSRC_DIR)
	@$(ENCODE) $< | $(ES) $(ESFLAGS) -p - | $(PSPDF) - $@

$(PSRC_DIR)/%.c.pdf : $(SRC_DIR)/%.c
	$(ECHO) "$(ES) -Ec -p - $< | $(PSPDF) - $@"
	@test -d $(PSRC_DIR) || mkdir $(PSRC_DIR)
	@$(ENCODE) $< | $(ES) $(ESFLAGS) --highlight=c -p - | $(PSPDF) - $@

$(PSRC_DIR)/%.cpp.pdf : $(SRC_DIR)/%.cpp
	$(ECHO) "$(ES) -Ecpp -p - $< | $(PSPDF) - $@"
	@test -d $(PSRC_DIR) || mkdir $(PSRC_DIR)
	@$(ENCODE) $< | $(ES) $(ESFLAGS) --highlight=cpp -p - | $(PSPDF) - $@

$(PSRC_DIR)/%.l.pdf : $(LEX_DIR)/%.l
	$(ECHO) "$(ES) -p - $< | $(PSPDF) - $@"
	@test -d $(PSRC_DIR) || mkdir $(PSRC_DIR)
	@$(ENCODE) $< | $(ES) $(ESFLAGS) -p - | $(PSPDF) - $@

$(PSRC_DIR)/%.lpp.pdf : $(LEX_DIR)/%.lpp
	$(ECHO) "$(ES) -p - $< | $(PSPDF) - $@"
	@test -d $(PSRC_DIR) || mkdir $(PSRC_DIR)
	@$(ENCODE) $< | $(ES) $(ESFLAGS) -p - | $(PSPDF) - $@

$(PSRC_DIR)/%.y.pdf : $(YACC_DIR)/%.y
	$(ECHO) "$(ES) -p - $< | $(PSPDF) - $@"
	@test -d $(PSRC_DIR) || mkdir $(PSRC_DIR)
	@$(ENCODE) $< | $(ES) $(ESFLAGS) -p - | $(PSPDF) - $@

$(PSRC_DIR)/%.ypp.pdf : $(YACC_DIR)/%.ypp
	$(ECHO) "$(ES) -p - $< | $(PSPDF) - $@"
	@test -d $(PSRC_DIR) || mkdir $(PSRC_DIR)
	@$(ENCODE) $< | $(ES) $(ESFLAGS) -p - | $(PSPDF) - $@

$(PSRC_DIR)/%.h.pdf : $(SRC_DIR)/%.h
	$(ECHO) "$(ES) -Ecpp -p - $< | $(PSPDF) - $@"
	@test -d $(PSRC_DIR) || mkdir $(PSRC_DIR)
	@$(ENCODE) $< | $(ES) $(ESFLAGS) --highlight=cpp -p - | $(PSPDF) - $@


#--------------------------------------
# Cleanup rules
#--------------------------------------

.PHONY: cleanall clean

clean:
	$(RM) $(RMFLAGS) $(TMP)
	$(RM) $(RMFLAGS) $(GSRC)
	$(RM) $(RMFLAGS) $(GHEAD)

cleanall: clean
	$(RM) $(RMFLAGS) $(PSRC)
	$(RM) $(RMFLAGS) $(BIN_DIR)/*
	$(RM) $(RMFLAGS) -r $(DOC_DIR)

#--------------------------------------
# Testing rules
#--------------------------------------

runtest: test
	cd tests && bash mktest.sh

#--------------------------------------
# Dependencies rules
#--------------------------------------

.PHONY: build-dependencies

build-dependencies:
	@$(PKMG) update
	@$(PKMG) install build-essentials flex bison doxygen texlive enscript ghostscript
#--------------------------------------
# Directory rules
#--------------------------------------
dir:
	@test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	@test -d $(GSRC_DIR) || mkdir $(GSRC_DIR)
	@test -d $(GOBJ_DIR) || mkdir $(GOBJ_DIR)
