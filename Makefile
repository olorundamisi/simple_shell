all:
	gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

betty:
	betty * > betty.log

run:
	./hsh

clean:
	rm ./hsh
