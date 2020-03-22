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

## 3 Example

It is given the example of the watermarking the sign below. If we run the
program with the following command line:

$ ./wm sign.bmp -text "hello" -color 243E7C -pos 120,75
-o modsign.bmp

```
Figure 1: Original Sign.


```
<img src="https://raw.githubusercontent.com/mirzemehdi/BMPWatermark/master/sign.bmp" alt="originalSign" height="50%" width="40%" >

It is signed with a color #243E7B. Then, it is watermarked the file mod-
sign.bmp with the text ”hello” written in morse code in the position 120,75 from
the top left of the image with the color #243E7C. The result is:

```
Figure 2: Watermarked Sign.
```
The watermark is not recognizable by the human eye. To see where it
changed you can search for the color #243E7C.


## 4 Command line options

Analyzing the command line:

$ ./wm sign.bmp -text "Hello" -date -color FFFFFE -pos 10,20
-o modsign.bmp

*sign.bmp is the name of the file which is being modified.*

### -text

*Takes the value of the text and writes it in theMorse code.*
*It is optional. If there is no text option, then no text is being written.*

### -date

*It writes in Morse code the output of system command date 
after the text (if option -text is present).The -date is optional.
If there is no date option, then no date is being written.
If neither text nor date options are given, then nothing will be 
changed in new BMP file. So the one of these options must be given 
by the user in order to watermark the file.*

### -color

*It gives the color to the watermark of the image. 
It is obligatory to give a color to the watermark. Here it is given the
#FFFFFE color (which is nearly white) to hide the watermark in
the white background of the image.*

### -pos

*It writes theMorse codeat position x,y starting from thetop left of the image.
If -pos is not present it writes from the top left position of the image (0,0).*

### -o modsign.bmp

*Writes the output (-o) in file modsign.bmp. If no -o option is mentioned, 
output on the standard output. The name of the output file must be written by the user.*


## 5 Possible errors

### The list of possible errors of the program:

- Some characters are not supported by theMorse code. Supported characters are letters from A-Z or a-z, numbers from
0-9, ”+” and ”:”. In all other text inputs it will give an error

### message.

- The image file should be given in BMP format. In other case it will give an error message.
- If the position is not given in a range of possible values for x,y 
  an error will appear. The value for thexshould be less than width and value of y 
  should be less thanheight of the BMPimage.

### References

*https://en.wikipedia.org/wiki/Digital_watermarking*

*[http://ascii-table.com/morse-code.php](http://ascii-table.com/morse-code.php)*

*https://en.wikipedia.org/wiki/Endianness*

*https://en.wikipedia.org/wiki/Digital_watermarking*

*[http://ascii-table.com/morse-code.php](http://ascii-table.com/morse-code.php)*




