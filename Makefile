cacheSim : cache.cpp main.cpp
	gcc -o cacheSim cache.cpp main.cpp -Wall -Wextra --pedantic -lstdc++
	gcc -o csim cache.cpp main.cpp -Wall -Wextra --pedantic -lstdc++

clean:
	rm -f cacheSim csim


