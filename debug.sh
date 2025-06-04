#!/bin/sh

# rm *.o
# rm build/kernel/*.o

# make clean
make incl ARCH="arm/armv7"
make hal
make libs
make ddrivers
make kernel
./rename_obj_to_o.sh
mv ./*.o ./build/kernel/
make ucx
./rename_obj_to_o.sh
make ucx

# mv ./echo.o build/app/echo.o
make echo
./rename_obj_to_o.sh
mv echo.o build/app
rm build/kernel/echo.o
make echo
./rename_obj_to_o.sh