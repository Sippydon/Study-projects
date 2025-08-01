all: cipher

cipher:
	gcc -Wall -Werror -Wextra cipher.c -o ../build/cipher

clean:
	rm -rf ../build/cipher

rebuild:
	$(MAKE) clean
	$(MAKE) all