FdF
=====

You can watch the project preview on my [Instagram](https://www.instagram.com/p/Bl_LoxZAw2B/).
Don't worry to like and subscribe.

![Picture](https://github.com/olehsamoilenko/screenshots/blob/master/FdF/julia.png)

This project is about creating a simplified graphic “wireframe” (“**fils de fer**” in french,
hence the name of the project) representation of a relief landscape linking various points
(x, y, z) via segments. The coordinates of this landscape are stored in a file passed as
a parameter to your program. Examples you can find in the folder ```maps```.
Use my maps or create your own.
Each number corresponds to a point in space:
* The horizontal position corresponds to its axis
* The vertical position corresponds to its ordinate
* The value corresponds to its altitude

Interesting features:
-----
* Rotating
* Moving
* Zooming
* Relief changing
* Gradient lines
* Intro window

Run the project:
-----
```
git clone --recursive https://github.com/olehsamoilenko/FdF.git
cd FdF
make
./fdf maps/example.fdf
```
:green_apple: Works only on **Mac OS**

![Picture](https://github.com/olehsamoilenko/screenshots/blob/master/FdF/t1.png)
