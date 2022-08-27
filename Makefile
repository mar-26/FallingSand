IDIR = ./headers
OBJDIR = ./objs
SRCDIR = ./src

PLATFORM := $(shell uname)

ifeq ($(PLATFORM),Darwin)
	LIBS = -framework GLUT -framework OpenGL
	FLAGS = -O3 -g -Wdeprecated-declarations -Wno-deprecated -I$(IDIR)
else
	LIBS = -lGL -lGLU -lglut
	FLAGS = -O3 -g -I$(IDIR)
endif

SRCS = $(addprefix $(SRCDIR)/, main.cpp Vector3.cpp Particle.cpp Screen.cpp ParticleSystem.cpp HUD.cpp Behavior.cpp)
OBJS = $(addprefix $(OBJDIR)/, main.o Vector3.o Particle.o Screen.o ParticleSystem.o HUD.o Behavior.o)

PRODUCTS = fallingSand

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) -c -o $@ $< $(FLAGS)

all: $(PRODUCTS) $(OBJS)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(PRODUCTS): $(OBJS)
	$(CXX) -o $@ $^ $(FLAGS) $(LIBS)

.PHONY : clean

clean:
	rm -f $(PRODUCTS)
	rm -r $(OBJDIR)
