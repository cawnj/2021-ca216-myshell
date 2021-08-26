# for building
dst = ../bin
separator = ------------------------------------------

targets = $(addprefix $(dst)/, $(patsubst %.c, %, $(wildcard *.c)))

build: $(targets)
	@true
	$(info $(separator))
	$(info Successfully compiled to "$(targets)")
	$(info $(separator))

# -lreadline to include readline library
$(dst)/%: %.c
	gcc -Wall -o $@ $< -lreadline


# for debug purposes
echo:
	echo $(targets)

clean:
	rm -f $(targets)

.PHONY: echo, clean
