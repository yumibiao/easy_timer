::mogrify -font fs.ttf -pointsize 80 -fill black -weight bolder -gravity northeast -annotate +20+20 @"t.txt" scr.jpg 
::convert -blur 80 scr.jpg blur.png

convert src.jpg -resize 1920x1080! src.jpg
convert src.jpg -transparent white -font fs.ttf -fill black -pointsize 50 -size x150 label:@countdowntext.txt -gravity northeast -geometry +200+350 -composite out.jpg
convert out.jpg -transparent white -font fs.ttf -fill black -pointsize 50 -size x45 label:@qu.txt -gravity north -geometry +0+0 -composite out.jpg
