# OCR



## Project

![Logo](https://raw.githubusercontent.com/NoneOfAllOfTheAbove/OCR/master/docs/logo_small.png)  

OCR stands for Optical Character Recognition software. As part of a student project, our objective is to make a program capable of extracting text from images. It must be written in the C language, rely on a neural network and be used through a GUI. To learn more, please take a look at [the book of specifications](https://github.com/NoneOfAllOfTheAbove/OCR/tree/master/docs/book-of-specifications.pdf).

## Usage

Dependencies: `SDL2`, `SDL2_image` and `GTK+ 3`.  

1. Clone this repository with `git clone git@github.com:NoneOfAllOfTheAbove/OCR.git`.
2. Compile the project by running the command `make` in the project folder.
3. Execute the program with `./OCR [path to image]`.

## Features

Currently implemented:
- Preprocess image (efficient binarization)
- Detect paragraphs, lines, words and characters
- A pretrained neural network to recognize characters
- Simple GUI to load an image and export its extracted text
  
Features we are working on:
- Advanced preprocessing (noise canceling, contrast enhancement, deskew)
- Advanced segmentation (understand page layout, export as HTML)
- Add a second hidden layer for the neural network
- Postprocessing step (spell check)

## Contributing

Refer to [CONTRIBUTING.md](https://github.com/NoneOfAllOfTheAbove/OCR/blob/master/CONTRIBUTING.md).