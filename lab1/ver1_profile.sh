gcc ver1.c -g -pg -o ver1.out -Ofast
let times=10
for((i=0; i<times; ++i))
do
    ./ver1.out 100 100 5000 > /dev/null
done

gprof ./ver1.out 100 100 5000> ver1.profile.txt

gprof -A ver1.out > ver1.source.txt