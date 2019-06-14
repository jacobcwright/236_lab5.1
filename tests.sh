#! /bin/bash

g++ -Wall -Werror -std=c++17 -g *.h *.cpp -o Lab5Test

for i in in[0-9][0-9].txt
do
    out=${i/in/out}
    printf "Comparing $i with $out\n"
    ./Lab5Test $i > check.txt

    if ! diff --strip-trailing-cr  check.txt $out &>/dev/null; 
        then
            >&2 printf "Failure!"
    else 
        printf "Success"
    fi
    printf "\n\n"
done
