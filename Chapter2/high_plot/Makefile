CCHECKS = -fsanitize=address
CWARNINGS = -Wall -Wextra -Wuninitialized 
CFLAGS = $(CWARNINGS) -lm -lSDL2 -lSDL2_ttf

main: build_main run_main clean_main  
	@echo ./build/main done

build_main: ./src/main.c 
	@echo [INFO] building main
	@gcc ./src/main.c $(CFLAGS) -o ./build/main

run_main:
	@echo
	./build/main
	@echo

clean_main:
	@echo [INFO] removing all build files
	@rm ./build/main

debug_main: debug_build_main
	gdb ./build/main

debug_build_main: ./src/main.c
	@echo [INFO] building main
	gcc ./src/main.c $(CFLAGS) -ggdb -o ./build/main

profile_main: profile_build_main
	./build/main
	@echo
	gprof ./build/main gmon.out | /home/almog/.local/bin/gprof2dot | dot -Tpng -Gdpi=200 -o output.png
	imview ./output.png
	# xdg-open ./output.png
	@echo
	rm ./gmon.out ./output.png 
	make clean_main

profile_build_main: ./src/main.c
	@echo [INFO] building main
	@gcc ./src/main.c $(CFLAGS) -p -ggdb -o ./build/main

# valgrind -s --leak-check=full ./build/main
# cloc --exclude-lang=JSON,make .

#############################################################
teapot_example: build_teapot_example run_teapot_example clean_teapot_example  
	@echo ./build/teapot_example done

build_teapot_example: ./src/teapot_example.c 
	@echo [INFO] building teapot_example
	@gcc ./src/teapot_example.c $(CFLAGS) -o ./build/teapot_example

run_teapot_example:
	@echo
	./build/teapot_example
	@echo

clean_teapot_example:
	@echo [INFO] removing all build files
	@rm ./build/teapot_example

debug_teapot_example: debug_build_teapot_example
	gdb ./build/teapot_example

debug_build_teapot_example: ./src/teapot_example.c
	@echo [INFO] building teapot_example
	@gcc ./src/teapot_example.c $(CFLAGS) -ggdb -o ./build/teapot_example

profile_teapot_example: profile_build_teapot_example
	./build/teapot_example
	@echo
	gprof ./build/teapot_example gmon.out | /home/almog/.local/bin/gprof2dot | dot -Tpng -Gdpi=200 -o output.png
	imview ./output.png
	# xdg-open ./output.png
	@echo
	rm ./gmon.out ./output.png 
	make clean_teapot_example

profile_build_teapot_example: ./src/teapot_example.c
	@echo [INFO] building teapot_example
	@gcc ./src/teapot_example.c $(CFLAGS) -p -ggdb -o ./build/teapot_example

# valgrind -s --leak-check=full ./temp
# cloc --exclude-lang=JSON,make .


#############################################################
temp: build_temp run_temp clean_temp  
	@echo ./build/temp done

build_temp: ./src/temp.c 
	@echo [INFO] building temp
	@gcc ./src/temp.c $(CFLAGS) -o ./build/temp

run_temp:
	@echo
	./build/temp
	@echo

clean_temp:
	@echo [INFO] removing all build files
	@rm ./build/temp

debug_temp: debug_build_temp
	gdb ./build/temp

debug_build_temp: ./src/temp.c
	@echo [INFO] building temp
	@gcc ./src/temp.c $(CFLAGS) -ggdb -o ./build/temp

profile_temp: profile_build_temp
	./build/temp
	@echo
	gprof ./build/temp gmon.out | /home/almog/.local/bin/gprof2dot | dot -Tpng -Gdpi=200 -o output.png
	imview ./output.png
	# xdg-open ./output.png
	@echo
	rm ./gmon.out ./output.png 
	make clean_temp

profile_build_temp: ./src/temp.c
	@echo [INFO] building temp
	@gcc ./src/temp.c $(CFLAGS) -p -ggdb -o ./build/temp

# valgrind -s --leak-check=full ./temp
# cloc --exclude-lang=JSON,make .
