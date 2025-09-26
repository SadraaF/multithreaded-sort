# Multithreaded Sort in C

This project is a C implementation of a parallel sorting algorithm. It was developed for an Operating Systems course assignment at AUT to demonstrate the principles of multithreading and the "divide and conquer" strategy.

The program sorts an array by splitting it into two halves, sorting each half concurrently in a separate thread, and then merging the sorted halves in a final thread.

## Key Concepts Demonstrated

-   **Multithreading:** Creating and managing multiple threads of execution using the `pthread` library.
-   **Parallel Programming:** Executing tasks (sorting subarrays) concurrently to improve performance.
-   **Synchronization:** Using `pthread_join` to ensure the main thread waits for worker threads to complete their tasks before proceeding.
-   **Divide and Conquer:** Breaking a large problem into smaller, independent sub-problems that can be solved in parallel.

## Technologies Used

-   **Language:** C
-   **Compiler:** GCC
-   **Core Libraries:** `pthread.h`

## How to Compile and Run

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/SadraaF/multithreaded-sort.git
    cd multithreaded-sort
    ```

2.  **Compile the code:**
    The `-lpthread` flag is required to link the POSIX threads library.
    ```bash
    gcc main.c -o sort -lpthread
    ```

3.  **Run the program:**
    ```bash
    ./sort
    ```

## Code Explanation

The program's logic is as follows:
1.  The `main` function initializes an integer array.
2.  It creates two worker threads. Each thread is assigned half of the array and sorts it using the **Insertion Sort** algorithm.
3.  The `main` thread calls `pthread_join` to wait for both sorting threads to finish.
4.  A third thread is then created to merge the two now-sorted halves into a final, fully sorted array.
5.  After the merge thread completes, the program prints the sorted array to the console.
