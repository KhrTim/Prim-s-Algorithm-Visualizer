# Prim's Algorithm Visualizer
Prim's Algorithm Visualizer built with C++ and SFML


### Demo
![Demo](./assets/2.gif "Demo")

### How to compile
1. You need to have SFML installed. In case you don't have it, follow this guide: [SFML installation](https://www.sfml-dev.org/download/sfml/2.5.1/)
2. Clone this repository
3. Navigate to the root of this repo
4. run `make`. In case of any errors inspect the `Makefile` and configure it for your local environment
5. run executable from `/bin/`

### How to use
![Controls demo](./assets/1.gif "Controls demo")

interaction with the program is carried out using keyboard and mouse:
- Press `A` to create vertex at mouse current position
- Press `X` to remove vertex/edge at mouse current position
- Click and drag `Mouse Right Button` to create edge between 2 vertices
- Click and drag `Mouse Left Button` to move a vertex
- Click and drag `Mouse Middle Button` to move the canvas around
- Press `Space` to start Prim's algorithm animation
