::mogrify -font fs.ttf -pointsize 80 -fill black -weight bolder -gravity northeast -annotate +20+20 @"t.txt" scr.jpg 
::convert -blur 80 scr.jpg blur.png

convert src.jpg -resize 1920x1080! out.jpg
::convert src.jpg -compose atop ( -size 5x5 ) -geometry +5+30 out.jpg
::convert src.jpg -spread 30 -geometry 100x100+0+0 out.jpg
::-region 500x600+20+10
::convert src.jpg -region 500x600+20+10 -gravity northeast -blur 0x5 out.jpg
::convert -fill black -stroke red -font fs.ttf -pointsize 200 -gravity Center -draw 'text 0,0 "123" out.jpg out.jpg
::convert out.jpg -font fs.ttf -fill green -pointsize 50 -size x150 label:@countdowntext.txt -gravity northeast -geometry +200+350 -composite out.jpg
convert out.jpg -background "rgba(255, 255,  240,  0.4)" -font fs.ttf -fill "rgba(0,0,0,0.9)" -pointsize 50 -size x150 label:@countdowntext.txt -gravity northeast -geometry +200+350 -composite out.jpg
convert out.jpg -background "rgba(255, 255,  240,  0.4)" -font fs.ttf -fill "rgba(0,0,0,0.9)" -pointsize 50 -size x45 label:@qu.txt -gravity north -geometry +0+0 -composite out.jpg

::convert src.jpg -transparent white -font fs.ttf -fill black -pointsize 50 -size x150 label:@countdowntext.txt -gravity northeast -geometry +200+350 -composite out.jpg
::convert out.jpg -transparent white -font fs.ttf -fill black -pointsize 50 -size x45 label:@qu.txt -gravity north -geometry +0+0 -composite out.jpg
