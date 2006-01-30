# Project: FBIde0.4
# Makefile created by Dumbledore
# modified by VonGodric

CPP  = g++ -D__DEBUG__
CC   = gcc -D__DEBUG__
WINDRES = 
RES  = 
OBJ  = obj/linux/main.o obj/linux/loadui.o obj/linux/help.o obj/linux/config.o obj/linux/file.o obj/linux/edit.o obj/linux/search.o obj/linux/view.o obj/linux/fbedit.o obj/linux/configdiag.o obj/linux/lang.o obj/linux/buffer.o obj/linux/bufferlist.o obj/linux/run.o obj/linux/browser.o obj/linux/format.o obj/linux/about.o obj/linux/wxmynotebook.o $(RES)
LINKOBJ  = obj/linux/main.o obj/linux/loadui.o obj/linux/help.o obj/linux/config.o obj/linux/file.o obj/linux/edit.o obj/linux/search.o obj/linux/view.o obj/linux/fbedit.o obj/linux/configdiag.o obj/linux/lang.o obj/linux/buffer.o obj/linux/bufferlist.o obj/linux/run.o obj/linux/browser.o obj/linux/format.o obj/linux/about.o obj/linux/wxmynotebook.o $(RES)
LIBS =  `wx-config --libs` -lwx_gtk2_stc-2.6 -lpng
INCS =  -I"/usr/include" 
CXXINCS =  -I"/usr/include/wx-2.6/wx/stc" 
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

obj/linux/main.o: src/main.cpp
	$(CPP) -c src/main.cpp -o obj/linux/main.o $(CXXFLAGS)

obj/linux/loadui.o: src/loadui.cpp
	$(CPP) -c src/loadui.cpp -o obj/linux/loadui.o $(CXXFLAGS)

obj/linux/help.o: src/help.cpp
	$(CPP) -c src/help.cpp -o obj/linux/help.o $(CXXFLAGS)

obj/linux/config.o: src/config.cpp
	$(CPP) -c src/config.cpp -o obj/linux/config.o $(CXXFLAGS)

obj/linux/file.o: src/file.cpp
	$(CPP) -c src/file.cpp -o obj/linux/file.o $(CXXFLAGS)

obj/linux/edit.o: src/edit.cpp
	$(CPP) -c src/edit.cpp -o obj/linux/edit.o $(CXXFLAGS)

obj/linux/search.o: src/search.cpp
	$(CPP) -c src/search.cpp -o obj/linux/search.o $(CXXFLAGS)

obj/linux/view.o: src/view.cpp
	$(CPP) -c src/view.cpp -o obj/linux/view.o $(CXXFLAGS)

obj/linux/fbedit.o: src/fbedit.cpp
	$(CPP) -c src/fbedit.cpp -o obj/linux/fbedit.o $(CXXFLAGS)

obj/linux/configdiag.o: src/configdiag.cpp
	$(CPP) -c src/configdiag.cpp -o obj/linux/configdiag.o $(CXXFLAGS)

obj/linux/lang.o: src/lang.cpp
	$(CPP) -c src/lang.cpp -o obj/linux/lang.o $(CXXFLAGS)

obj/linux/buffer.o: src/buffer.cpp
	$(CPP) -c src/buffer.cpp -o obj/linux/buffer.o $(CXXFLAGS)

obj/linux/bufferlist.o: src/bufferlist.cpp
	$(CPP) -c src/bufferlist.cpp -o obj/linux/bufferlist.o $(CXXFLAGS)

obj/linux/run.o: src/run.cpp
	$(CPP) -c src/run.cpp -o obj/linux/run.o $(CXXFLAGS)

obj/linux/browser.o: src/browser.cpp
	$(CPP) -c src/browser.cpp -o obj/linux/browser.o $(CXXFLAGS)

obj/linux/format.o: src/format.cpp
	$(CPP) -c src/format.cpp -o obj/linux/format.o $(CXXFLAGS)

obj/linux/about.o: src/about.cpp
	$(CPP) -c src/about.cpp -o obj/linux/about.o $(CXXFLAGS)

obj/linux/wxmynotebook.o: src/wxmynotebook.cpp
	$(CPP) -c src/wxmynotebook.cpp -o obj/linux/wxmynotebook.o $(CXXFLAGS)
