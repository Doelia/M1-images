
# 2)

#formule: Moyenne des 3 couleurs

imIn="$1"

imColorBase="$imIn.ppm"
imGray="$imIn.gray.pgm"

./toGray "imgs/$imColorBase" "imgs/$imGray"
./histo "imgs/$imGray" > imgs/histo_gray.txt
#gnuplot
plot "imgs/histo_gray.txt" with lines

# 3)

#seuil: 90

seuil=$2
imgSeuil="$imIn.seuil.pgm"
./seuil "imgs/$imGray" "imgs/$imgSeuil" $seuil

#4 flou

./floutage "imgs/$imColorBase" "imgs/$imIn.color.flou.ppm"
#./floutage "imgs/$imGray" "imgs/$imIn.gray.flou.pgm"

#5 application

./floutage "imgs/$imColorBase" "imgs/$imgSeuil" "imgs/$imIn.seuil.flou.ppm"
#./floutage_seuil "imgs/$imIn.seuil.flou.ppm" "imgs/$imgSeuil" "imgs/$imIn.seuil.flou.ppm"

