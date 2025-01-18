# Lecture 2 - Digital Colors
This lecture is about RGB, HSI, HSV, thresholding, bayer patterns & more.

## Excercise 1 - Threshold `letter.png` (it's on Moodle) to find the red stamp using ImageJ:

### Try `Image > Adjust > Threshold...`
This is the image we are working with:\
![Letter](https://github.com/nikobk/aau-image-processing/tree/main/lecture2/dat/letter.png?raw=true)

Trying to edit the thresholding for the RGB image is not allowed since it only
works with grayscale images. Therefor I convert it to grayscale with ImageJ by
using:\
`Image > Type > 8bit`

This makes ImageJ represent the image with 8bits, meaning a value between 0 - 255,
and thus grayscale.

![Grayscaled Letter](https://github.com/nikobk/aau-image-processing/tree/main/lecture2/ext/letter-gray.png?raw=true)

Adjusting the threshold on the red channel does not work ecause it is an RGB image there are green and blue channels representing the post stamp and everything else meaning the colors are too similar. We can get a better seperation using HSV/HSI/HSL/HSB.

### Try `Image > Adjust > Color Threshold...` (note the color space used)

Using the HSB color space:\
H: 185 - 255
S: 37 - 255
B: 164 - 255

We get the following:

![HSB Color Space](https://github.com/nikobk/aau-image-processing/tree/main/lecture2/ext/color_thres_hsb.png?raw=true)

### Try splitting the RGB channels and comparing them (`Image > Color > Split Channels`)

We get three images that look like this:

[red] [green] [blue]

As seen by the stamp area with the white stamp we can tell that there is a high intensity on the red channel there (remember intensity represented in greyscale, at this point a value up near 255!)

Blue and green are almost even so there is not  a lot of information there.

### Try converting to HSB and compare the channels (`Image > Color > HSB Stack, Image > Stacks > Stack to images`)

Using `Image > Type > HSB Stack` I get the following image. I am pretty sure it is supposed to be a different hsb stack image that required a plugin to work, but this is what I got:

![HSB Image Stack](https://github.com/nikobk/aau-image-processing/tree/main/lecture2/ext/hsb_stack.png?raw=true)

All channels should show high values at the red mark making it easy to use for thresholding. Not sure about this excercise..

### Explain why a simple thresholding of the red RGB channel does not work. Is green or blue better? Why?`
As mentioned in the first part of this excercise the mark is represented by 3 color channels and can therefor not just be thresholded with only the red one. This is why HSV thresholding generally works better than RGB thresholding (its more robust). Green is also a better choice because it seperates the two features, however using a mix of green and blue is better to get more details with the thresholding.

## Explain how color is represented in HTML.
In HTML colors can be specified in an array of ways that includes `rgb`, `hsv` and generally all of the methods we also use in image-processing.

One of the more common methods however is hexadecimal where you specify a color like red as:
`#ff0000` or `0xFF0000`.

This is based on the RGB model where `FF` is the red channel, `00` is the green channel and `00` is the blue channel.

Red hex: `#ff0000`
Green hex: `#00ff00`
Blue hex: `#0000ff`

Hexadecimal represents numeric values with characters where
`a = 10`
`b = 11`
`c = 12`
`...`
`f = 15`

And ofcourse `0 = 0`
So when you convert a hex value to decimal you multiply the number by 16 and add the last number. When `f = 15` you get the following equation:

`15 * 16 + 15 = 255`
as such `#ff = 255`.

## The image to the right has been captured by a Bayer pattern sensor. Use demosaicing (the algorithm in the book) to convert the image into an RGB image.

This is the bayer pattern given for this excercise:
![Bayer Pattern](https://github.com/nikobk/aau-image-processing/tree/main/lecture2/ext/bayer_pattern.png?raw=true)

See `demosaicing.py`

My code is based on the book's instructions wheere you use information from surrounding pixels rather than using an average (which is an alternative).

Note that there is always double as many green pixels as opposed because human eyes are more sensitive to green light (thus we need to catch and display more green color).

To build a picture in HSI we want to make eaach layer (H, S and I - Hue, Saturation & Intensity). Computer screens only display BGR or RGB so it makes no sense to try and display an image as HSI since you will only see a RGB representation of a HSI color space.

## Make a Python program which performs the demosaicing you did manually in the previous exercise
(Same as the above, making it in hand is just following equation (3.2) from the book)

## Make a Python program which loads and converts a picture to HSI
See `converter.py`
![BRG -> HSV convertion](https://github.com/nikobk/aau-image-processing/tree/main/lecture2/ext/converter.png?raw=true)