





all: a.out

a.out: 
	g++ -o a.out main.cpp -lraylib -lbox2d

clean:
	rm -f a.out 

