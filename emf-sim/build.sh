#/bin/sh
set -x
g++ -o sim-tx -march=native -mtune=native -O3 -I /usr/include/eigen3/ sim-tx.cc
g++ -o sim-tx-multithreaded -march=native -mtune=native -O3 -I /usr/include/eigen3/ sim-tx-multithreaded.cc -lpthread
g++ -o sim-rx -march=native -mtune=native -O3 -I /usr/include/eigen3/ sim-rx.cc
