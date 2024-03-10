# IdealGasSimulation
simulate ideal gas particles by using openGL
this will simulates the particles based on real physics

## The Simulation
![2024-03-07 20-38-02(1)](https://github.com/ChunHou20c/IdealGasSimulation/assets/93393878/cc937926-2fe8-4beb-a188-39e2a6307e28)

## Dependancies
- make
- glfw3
- glm
- glew

These packages are usually available in most package manager, if you don't want to find the dependancies, you can use nix to run the binary

## Compilation and running of the program
The program can be compiled using make
```
git clone https://github.com/ChunHou20c/IdealGasSimulation.git
make
./target/IdealGasSimulation
```

## Running the program using nix
I had also package the program using nix flake, to run it first clone the repo and then nix run
```
git clone https://github.com/ChunHou20c/IdealGasSimulation.git

cd IdealGasSimulation
nix run
```

## Running as nix flake
The program can be run without cloning the repo
```
nix run github:ChunHou20c/IdealGasSimulation
```
