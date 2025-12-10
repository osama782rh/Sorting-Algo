
# Sorting Algorithms Performance Analysis

This project compares the performance of various sorting algorithms in terms of execution time, CPU usage, RAM usage, and context switches. It includes a custom hybrid sorting algorithm named `Esiee Sort`.

## Project Structure

- `main.c`: Main program that generates random strings, runs the sorting algorithms, and collects performance data.
- `sorting_algorithms.c`: Implementation of different sorting algorithms (Bubble Sort, Insertion Sort, Quick Sort, Merge Sort).
- `hybrid_sort.c`: Implementation of the custom hybrid sorting algorithm `Esiee-it Sort`.
- `resource_usage.c`: Functions to measure the performance metrics (execution time, CPU usage, RAM usage, context switches).
- `utils.c`: Utility functions for generating random strings and saving results to a CSV file.
- `analyze_sort_results.py`: Python script to analyze and visualize the performance results from the CSV file.
- `Test_results_X/`: Directory where the results of each test run are saved, with `X` being the test number.

## Requirements

### C Compilation

- GCC (or any other C compiler)
- C Standard Library

### Python Analysis

- Python 3.x
- Pandas
- Matplotlib

You can install the Python dependencies using:

```sh
pip install pandas matplotlib
```

## How to Run

### Step 1: Compile the C Program

```sh
gcc -o main main.c sorting_algorithms.c resource_usage.c hybrid_sort.c utils.c -lm
```

### Step 2: Run the C Program

```sh
./main
```

The program will generate a random string, run the sorting algorithms, collect performance data, and save the results to a CSV file in a new directory named `Test_results_X`.

### Step 3: Analyze the Results

```sh
python3 analyze_sort_results.py
```

The script will find the latest test results, read the CSV file, print the results, and generate visualizations of the performance metrics. The visualizations will be saved as PNG files in the same directory as the CSV file.

## Sorting Algorithms Implemented

- **Bubble Sort**: Simple comparison-based sorting algorithm.
- **Insertion Sort**: Comparison-based sorting algorithm that builds the final sorted array one item at a time.
- **Quick Sort**: Efficient comparison-based sorting algorithm that uses divide-and-conquer.
- **Merge Sort**: Efficient comparison-based sorting algorithm that uses divide-and-conquer and requires additional memory.
- **Esiee-it Sort**: Custom hybrid sorting algorithm combining Quick Sort, Heap Sort, and Insertion Sort.

## Performance Metrics

The following performance metrics are collected for each sorting algorithm:

- **Time Spent (s)**: Total execution time in seconds.
- **User CPU (s)**: Time spent in user mode.
- **Sys CPU (s)**: Time spent in system mode.
- **RAM Usage (KB)**: Peak RAM usage in kilobytes.
- **Involuntary Context Switches (Invol CS)**: Number of context switches caused by the system.
- **Voluntary Context Switches (Vol CS)**: Number of context switches caused by the program.

## Notes

- Ensure that the C program generates the CSV file correctly before running the Python analysis script.
- If any issues arise with missing or incorrect data, verify the implementation and data collection in `resource_usage.c`.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgements

- [Esiee IT](https://www.esiee-it.fr/) for providing the educational resources and environment for this project.
