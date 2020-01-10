CC = gcc

INCLUDE = -I/usr/local/include -I/usr/include
LIB = -L/usr/local/lib -L/usr/lib -lm -lssl -lcrypto -g -std=c99 -Wall

all: cert check

cert: cert.c HMAC.c
	$(CC) -o cert $(INCLUDE) cert.c HMAC.c $(LIB)

check: check.c HMAC.c
	$(CC) -o check $(INCLUDE) check.c HMAC.c $(LIB)

clean:
	rm cert
	rm check
