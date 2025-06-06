# Knapsack Problem Solver

This project is a C++ implementation of a Knapsack Problem Solver. It uses CMake for building the project.


## Prerequisites

- CMake 3.10 or higher
- A C++ compiler (GCC, Clang, etc.)

## Building the Project

1. Clone the repository:
    ```sh
    git clone <repository-url>
    cd <repository-directory>
    ```

2. Create a build directory and navigate into it:
    ```sh
    mkdir build
    cd build
    ```

3. Run CMake to configure the project:
    ```sh
    cmake ..
    ```

4. Build the project:
    ```sh
    make
    ```

## Running the Project

After building the project, you can run the executable:

```sh
./KnapsackProblemSolver <max_iter> <initial_prob> <path>
```
**Where:**
- `<max_iter>`: Maximum number of iterations (integer)
- `<initial_prob>`: Initial probability value (float, e.g., 0.5)
- `<path>`: Path to the input file containing the knapsack problem instance

> **NOTE:** Expected data is of the format provided in [link](http://artemisa.unicauca.edu.co/~johnyortega/instances_01_KP/). Path param should look like `~/large_scale/knapPI_1_500_1000_1` with corresponding optimum file `~/large_scale-optimum/knapPI_1_500_1000_1`

Output of the script is `<problem instance filename>-results.csv` file inside current directory  e.g. `knapPI_1_500_1000_1-results.csv`