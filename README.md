# BMPWatermark


## 1 Introduction

Digital signatures are widely being used to sign documents nowadays. This can
cause a problem because anyone can copy a signature from a document to paste
it on a new document, so digital signatures are no longer valid. The purpose
of this project is to watermark the given BMP image. A digital watermark is
a kind of marker covertly embedded in a noise-tolerant signal such as audio,
video or image data. It is typically used to identify ownership of the copyright
of such signal.”Watermarking”is the process of hiding digital information onto
an carrier signal; the hidden information should contain a relationship to the
carrier signal, but not necessarily. As mentioned above, this project works with
BMP images and it operates in such a way that the image can be watermarked
with the given text and the current date, converted intoMorse code, in a
position and color the user wants.

## 2 Usage

The program is called "wm" for ”watermark”. To execute it the command line
should be written in the following way:

$ ./wm sign.bmp -text "Hello" -date -color FFFFFE -pos 10,
-o modsign.bmp

*the values of the text, color, position and the name of the input and output
files are defined by the user.*

### 2.1 How it works?

When executing the program that way it will create a new BMP image called
modsign.bmp where on position 10,20 from the top left of the image, will write
”Hello” followed by current date (the output of thedatelinux command) in
Morse codewhere a dot is a pixel of color FFFFFE (nearly white), and a dash
is a “line” made of 3 pixels. Space between dots and dashes is one background
pixel. Space between letters is 3 pixels, space between 2 words is 5 pixels. If
the resolution is high, pixels will be really small, and the line will be quite
invisible.It can be found only by the people who know it is there. If the line is
too long to fit in the image,it will continue on the next line. If the signature is
watermarked by writing the name of the document and the date in Morse code
in it, and someone makes a digital copy of the signature and uses it on another
document, later it can be proved that the signature is not the right one because
the name of the document and the date will be wrong.


