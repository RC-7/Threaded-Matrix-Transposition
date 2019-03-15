#!/bin/ksh
for i in {1..5}
do
	x=$((2**$i))
	export OMP_NUM_THREADS=$x
	echo "value for x is $x"
	/usr/local/bin/g++-8 -lgomp -fopenmp main.cpp -o main
	./main $x 	
done

