CXX = g++
EXPORT = bin
BINARY = hca2wav

help:
	@echo 'hca2wav'
	@echo 'original author: @Nyagamon'
	@echo 'forked by: @Cryptomelone'
	@echo
	@echo 'Usage: make [TARGET]'
	@echo 'TARGETS:'
	@echo '    compile:	compile hca2wav.'
	@echo '    clean:	clean objects.'
	@echo '    help:	print this message.'

compile: main.cpp src/clHCA.cpp
	@mkdir -p $(EXPORT)
	$(CXX) -o $(EXPORT)/$(BINARY) -O3 main.cpp src/clHCA.cpp

clean:
	$(RM) -r $(EXPORT)
