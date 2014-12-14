Bitmap Vectorization
===================

Bitmap Vectorization is the implementation of an algorithm developed by Johannes Kopf of Microsoft Research and Dani Lischinski of The Hebrew University in C++ using Microsoft Visual Studio and OpenGL. Their algorithm takes in a pixelated bitmap image and returns a smooth-spline approximation. Our version is not as extensive; it takes in a bitmap image and outputs a planarized pixel graph of the image. Both algorithms use three heuristics to determine how crossed squares (that is, two sets of similarly-colored oppositely diagonal crossed connections) should be resolved in order to make the graph planar:

Curves: If one set of diagonally-connected pixels is part of a long curve feature, this heuristic gives them priority to be connected.

Sparse Pixels: If there are fewer of the color of one set of diagonally-connected pixels in the currently-assessed portion of the image, this heuristic assumes that this is the foreground color and gives them priority to be connected.

Islands: If removing the connection between one set of diagonally-connected pixels would create a one-pixel island on either side of the severed connection, this heuristic gives them priority to be connected.