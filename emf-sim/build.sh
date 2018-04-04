#/bin/sh
set -x
g++ -o sim-rx -march=native -mtune=native -O3 -I /usr/include/eigen3/ sim-rx.cc
g++ -o sim-rx-multithreaded -march=native -mtune=native -O3 -I /usr/include/eigen3/ sim-rx-multithreaded.cc -lpthread
g++ -o sim-tx -march=native -mtune=native -O3 -I /usr/include/eigen3/ sim-tx.cc
