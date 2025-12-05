# Particle Swarm Optimization (PSO)

This project provides a C++ implementation of the Particle Swarm Optimization (PSO) algorithm. PSO is a computational method that optimizes a problem by iteratively trying to improve a candidate solution with regard to a given measure of quality.

## Description

The PSO algorithm is inspired by the social behavior of bird flocking or fish schooling. It involves a population of candidate solutions, called particles, which are moved around in the search-space according to simple mathematical formulae over the particle's position and velocity. Each particle's movement is influenced by its local best-known position and is also guided toward the best-known positions in the search space, which are updated as better positions are found by other particles.

This project is designed to be a flexible and extensible implementation of PSO, allowing users to define their own optimization problems and fitness functions.

## Getting Started

### Prerequisites

To build and run this project, you will need:

- A C++ compiler (e.g., g++)
- Make

### Building the Project

To build the project, clone the repository and run the `make` command in the root directory:

```bash
git clone <repository-url>
cd <repository-directory>
make
```

This will compile the source code and create an executable file named `pso` in the root directory.

### Running the Project

To run the PSO algorithm, use the following command:

```bash
./pso <input-file>
```

Replace `<input-file>` with the path to a file containing the problem data. The format of the input file will depend on the specific optimization problem being solved.

## Project Structure

The project is organized as follows:

- `src/`: Contains the C++ source code for the PSO implementation.
- `include/`: Contains the header files for the C++ classes.
- `data/`: Contains sample input files for testing the PSO algorithm.
- `test/`: Contains test cases for the project.
- `Makefile`: The build script for the project.
- `README.md`: This file.
