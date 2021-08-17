CFLAGS = -Wall -Wextra -Werror -pedantic -g
OBJ = $(addprefix $(OBJDIR), $(patsubst %.c, %.o, $(wildcard *.c)))
CFILES = $(wildcard *.c)


hsh: $(OBJ)
	gcc $(CFLAGS) -o hsh $(OBJ)
	make clean

$(OBJDIR)%.o: %.c headersh.h
	gcc $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR);

.PHONY: all
all : hsh


.PHONY: clean
clean:
	@rm *.o
