#!/bin/bash
for i in {1..10000}
do
	./avg "imgs/BOWS2OrigEp3/$i.pgm" >> f.txt
done

