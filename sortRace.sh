# start shell file
./generate 1000000 100000 999999
time sort numbers.txt > sysSort.out
time ./mySort numbers.txt mySort.out
./verifySort mySort.out # this function shows how many numbers in the file and if they are sorted.