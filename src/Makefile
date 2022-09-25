CC = gcc
CFLAGS = -Wall -Werror -Wextra
F_FILES = converters/*.c others/*.c arithmetic/*.c comparison/*.c additional/*.c common/*.c

all: clean s21_decimal.a

test:

s21_decimal.a: clean
	${CC} ${CFLAGS} -c ${F_FILES}
	mkdir obj
	mv *.o obj/
	ar rc s21_decimal.a obj/*.o
	rm -rf obj
gcov_report:

clean:
	rm -rf *.o
	rm -rf obj/*.o
	rm -rf *.a