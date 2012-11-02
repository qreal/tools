Hello world!

We have made new architecture. Actually we have just changed some names and added few classes :)
So now we have a class for each stage.
First of all lets talk about basics. We call fragment(arc) without selfintersection - component.
United components are figures or edges. Set of figures connected by edges - diagram.

There are 7 stages in our plans:
1. Recognize image and take contour.
2. Divide contour into components.
3. Unite components into figures and edges.
4-5. Recognize figures and edges. Study system.
6. Output.
7. Create database.

Existing prototype provide these stages by these classes.
1. bitmap
2. component
3. formSegmentator
4-5. abstractRecognizer and recognizers folder. (for now it hasn't any study system)
6. output (captain obvious)
7. simpleFormInitializer.

So if you are trying to write code for "1. Recognize image and take contour.", you have to do it in bitmap.
Existing algorithm can't fit our needs, so don't fear to delete some written code(but do it only in your class).

This is our conception:
digramRecognizer is the main class. It will call other classes and receive their results.
For example, it will take image, send it to bitmap class, that will recognize this image and return a grid.
Then diagramRecognizer will send grid with contour to component class, that will divide this cintour into components.
So it will return pathVector with all components of contour and so on.
Please check the whole conception in the Conception.jpg

At the end we will have 7 independent classes and each of them can work on their own.

Best wishes,

Alexey Kor, George Kraychik
