CXX    = c++
LIBS   = -lfcgi -lfcgi++
PORT   = 8000


all: main.cpp
	$(CXX) $(LIBS) -o app $^

.PHONY: dev
dev: all
	spawn-fcgi -p $(PORT) -n -- app

.PHONY: clean
clean:
	rm -rf app
