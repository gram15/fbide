# Project: FBIde0.4
# Makefile created by Dumbledore
# modified by VonGodric

CPP  = g++ -D__DEBUG__ -DNO_GCC_PRAGMA
CC   = gcc -D__DEBUG__
WINDRES = 
RES  = 
OBJ  = obj/main.o obj/loadui.o obj/help.o obj/config.o obj/file.o obj/edit.o obj/search.o obj/view.o obj/fbedit.o obj/configdiag.o obj/lang.o obj/buffer.o obj/bufferlist.o obj/run.o obj/browser.o obj/format.o obj/about.o obj/wxmynotebook.o $(RES)
LINKOBJ  = obj/main.o obj/loadui.o obj/help.o obj/config.o obj/file.o obj/edit.o obj/search.o obj/view.o obj/fbedit.o obj/configdiag.o obj/lang.o obj/buffer.o obj/bufferlist.o obj/run.o obj/browser.o obj/format.o obj/about.o obj/wxmynotebook.o $(RES)
LIBS =  `wx-config --libs` -L"/usr/lib/x86_64-linux-gnu" -lwx_gtk2u_stc-3.0 -lpng
INCS =  -I"/usr/include" 
CXXINCS =  -I"/usr/include/wx-3.0/wx/stc"
BIN  = output/fbide
CXXFLAGS = $(CXXINCS) -O4 -g `wx-config --cxxflags` 
CFLAGS = $(INCS) -fexpensive-optimizations -O3 -g
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before output/fbide all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "output/fbide" $(LIBS)

obj/main.o: src/main.cpp
	$(CPP) -c src/main.cpp -o obj/main.o $(CXXFLAGS)

obj/loadui.o: src/loadui.cpp
	$(CPP) -c src/loadui.cpp -o obj/loadui.o $(CXXFLAGS)

obj/help.o: src/help.cpp
	$(CPP) -c src/help.cpp -o obj/help.o $(CXXFLAGS)

obj/config.o: src/config.cpp
	$(CPP) -c src/config.cpp -o obj/config.o $(CXXFLAGS)

obj/file.o: src/file.cpp
	$(CPP) -c src/file.cpp -o obj/file.o $(CXXFLAGS)

obj/edit.o: src/edit.cpp
	$(CPP) -c src/edit.cpp -o obj/edit.o $(CXXFLAGS)

obj/search.o: src/search.cpp
	$(CPP) -c src/search.cpp -o obj/search.o $(CXXFLAGS)

obj/view.o: src/view.cpp
	$(CPP) -c src/view.cpp -o obj/view.o $(CXXFLAGS)

obj/fbedit.o: src/fbedit.cpp
	$(CPP) -c src/fbedit.cpp -o obj/fbedit.o $(CXXFLAGS)

obj/configdiag.o: src/configdiag.cpp
	$(CPP) -c src/configdiag.cpp -o obj/configdiag.o $(CXXFLAGS)

obj/lang.o: src/lang.cpp
	$(CPP) -c src/lang.cpp -o obj/lang.o $(CXXFLAGS)

obj/buffer.o: src/buffer.cpp
	$(CPP) -c src/buffer.cpp -o obj/buffer.o $(CXXFLAGS)

obj/bufferlist.o: src/bufferlist.cpp
	$(CPP) -c src/bufferlist.cpp -o obj/bufferlist.o $(CXXFLAGS)

obj/run.o: src/run.cpp
	$(CPP) -c src/run.cpp -o obj/run.o $(CXXFLAGS)

obj/browser.o: src/browser.cpp
	$(CPP) -c src/browser.cpp -o obj/browser.o $(CXXFLAGS)

obj/format.o: src/format.cpp
	$(CPP) -c src/format.cpp -o obj/format.o $(CXXFLAGS)

obj/about.o: src/about.cpp
	$(CPP) -c src/about.cpp -o obj/about.o $(CXXFLAGS)

obj/wxmynotebook.o: src/wxmynotebook.cpp
	$(CPP) -c src/wxmynotebook.cpp -o obj/wxmynotebook.o $(CXXFLAGS)
