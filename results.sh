for i in 1 2
do
	export OPEN_MP_THREADS=4
	/usr/local/bin/g++-8 -lgomp -fopenmp main.cpp -8 -o main
	./main 	
done

