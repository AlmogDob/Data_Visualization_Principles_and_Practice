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

#############################################################
video_ship: build_Aobj2c
	@echo
	./build/Aobj2c ./obj_files/video_ship.obj > ./build/video_ship.c
	@echo
	rm ./build/Aobj2c
	@echo ./build/Aobj2c done

skull: build_Aobj2c
	@echo
	@./build/Aobj2c ./obj_files/Skull/Skull_v3_L2.obj > ./build/Skull_v3_L2.c
	# @./build/Aobj2c ./obj_files/Skull/Skull_v3_L2.obj
	@echo
	rm ./build/Aobj2c
	@echo ./build/Aobj2c done

axis: build_Aobj2c
	@echo
	# @./build/Aobj2c ./obj_files/axis.obj > ./build/axis.c
	@./build/Aobj2c ./obj_files/axis.obj
	@echo
	rm ./build/Aobj2c
	@echo ./build/Aobj2c done

f16: build_Aobj2c
	@echo
	# @./build/Aobj2c ./obj_files/f16/f16.obj > ./build/f16.c
	@./build/Aobj2c ./obj_files/f16/f16.obj
	@echo
	rm ./build/Aobj2c
	@echo ./build/Aobj2c done

teapot: build_Aobj2c
	@echo
	./build/Aobj2c ./obj_files/teapot.obj > ./build/teapot.c
	@echo
	rm ./build/Aobj2c
	@echo ./build/Aobj2c done

Aobj2c: build_Aobj2c
	@echo
	@cat input.txt | ./build/Aobj2c 
	@echo
	rm ./build/Aobj2c
	@echo ./build/Aobj2c done

build_Aobj2c: ./src/Aobj2c.c
	gcc ./src/Aobj2c.c $(CFLAGS) -o ./build/Aobj2c

run_Aobj2c:
	./build/Aobj2c

clean_Aobj2c:
	@echo
	rm ./build/Aobj2c

debug_Aobj2c: debug_build_Aobj2c
	gdb ./build/Aobj2c

debug_build_Aobj2c: ./src/Aobj2c.c
	@gcc ./src/Aobj2c.c $(CFLAGS) -g -o ./build/Aobj2c

profile_Aobj2c: profile_build_Aobj2c
	./build/Aobj2c
	@echo
	gprof ./build/Aobj2c gmon.out | /home/almog/.local/bin/gprof2dot | dot -Tpng -Gdpi=200 -o output.png
	imview ./output.png
	# xdg-open ./output.png
	@echo
	rm ./gmon.out ./output.png 
	make clean_Aobj2c

profile_build_Aobj2c: ./src/Aobj2c.c
	gcc ./src/Aobj2c.c $(CFLAGS) -p -ggdb -o ./build/Aobj2c

# valgrind -s --leak-check=full ./Aobj2c
# cloc --exclude-lang=JSON,make .

#############################################################
Astl2c: ./src/Astl2c.c
	@echo [INFO] building Astl2c
	@gcc ./src/Astl2c.c $(CFLAGS) -o ./build/Astl2c
	@echo
	./build/Astl2c
	@echo
	@echo [INFO] removing Astl2c
	@rm ./build/Astl2c

#############################################################
example1: build_example1 run_example1 clean_example1  
	@echo ./build/example1 done

build_example1: ./src/example1.c 
	@echo [INFO] building example1
	@gcc ./src/example1.c $(CFLAGS) -o ./build/example1

run_example1:
	@echo
	./build/example1
	@echo

clean_example1:
	@echo [INFO] removing all build files
	@rm ./build/example1