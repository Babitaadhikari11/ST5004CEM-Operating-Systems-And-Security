Copy everything below and paste it into your README.md file:

# ST5003CEM Advanced Algorithms Coursework
This repository contains the implementation and evaluation of advanced data structures and algorithms completed for the **ST5003CEM Advanced Algorithms** coursework.
The project covers efficient data structures, graph algorithms, algorithmic strategies, heuristic optimisation and concurrent programming.
---
## Student Information
- **Student Name:** Babita Kumari Adhikari
- **Student ID:** 240712
- **Module:** ST5003CEM – Advanced Algorithms
- **Institution:** Softwarica College of IT and E-Commerce
- **University:** Coventry University
---
## Project Tasks
### Task 1 – Efficient Data Structures
Four data structures were implemented using city records:
- Binary Search Tree
- AVL Tree
- Min-Heap
- Hash Table
Insertion, search and deletion operations were tested using datasets containing:
- 100 city records
- 1,000 city records
- 10,000 city records
The results were compared using runtime and complexity analysis.
---
### Task 2 – Graph Algorithms and Pathfinding
A weighted city graph was created to implement and evaluate:
- Dijkstra’s shortest-path algorithm
- Prim’s Minimum Spanning Tree algorithm
- Bellman–Ford algorithm
The algorithms were compared using correctness, runtime, graph density and theoretical complexity.
Dijkstra was used for non-negative shortest paths. Prim connected all cities using minimum total distance. Bellman–Ford was tested with negative edges and negative cycles.
---
### Task 3 – Algorithmic Strategies
Three different algorithmic approaches were implemented:
- Dynamic Programming for Weighted Job Scheduling
- Greedy algorithm for Minimum Platforms
- Backtracking for Hamiltonian Path
Dynamic Programming selected non-overlapping jobs with maximum profit. The Greedy method calculated the minimum number of railway platforms. Backtracking searched for a path that visited every graph vertex exactly once.
---
### Task 4 – NP-Hard Problem and Heuristics
Multi-Dimensional Bin Packing was used to allocate applications to servers.
Each application required:
- CPU
- RAM
- Bandwidth
Two methods were compared:
- First Fit Decreasing
- Local Search
First Fit Decreasing quickly produced a valid server arrangement. Local Search attempted to improve it by relocating or swapping applications between servers.
---
### Task 5 – Concurrent Programming
Sequential and concurrent sorting were compared using city population data.
The concurrent version:
1. Divides the population data into chunks.
2. Uses a mutex for safe task allocation.
3. Assigns each chunk to a worker thread.
4. Sorts the chunks independently.
5. Merges them into one final sorted list.
The experiment compared runtime, speedup and efficiency using 1, 2, 4 and 8 threads.
---
## Technologies Used
- Python 3
- Python threading library
- Python heapq library
- CSV datasets
- Matplotlib
- time.perf_counter()
- Visual Studio Code
- Git
- GitHub
---
## Project Structure
```text
ST5003CEM_Advanced_Algorithms/
│
├── task1_data_structures/
│   ├── __init__.py
│   ├── city.py
│   ├── data_loader.py
│   ├── bst.py
│   ├── avl.py
│   ├── min_heap.py
│   ├── hash_table.py
│   └── benchmark.py
│
├── task2_graph_algorithms/
│   ├── __init__.py
│   ├── weighted_graph.py
│   ├── dijkstra.py
│   ├── prim.py
│   └── bellman_ford.py
│
├── task3_algorithmic_strategies/
│   ├── __init__.py
│   ├── weighted_job_scheduling.py
│   ├── minimum_platforms.py
│   └── hamiltonian_path.py
│
├── task4_np_hard/
│   ├── __init__.py
│   ├── models.py
│   ├── task4_data.py
│   ├── greedy_ffd.py
│   └── local_search.py
│
├── task5_concurrent_programming/
│   ├── __init__.py
│   └── concurrent_sorting.py
│
├── data/
├── results/
├── requirements.txt
└── README.md
```
The exact file names may vary slightly depending on the final project structure.
---
## Installation
Open Terminal and move to the project folder:
```bash
cd /Users/babitaadhikari/ST5003CEM_Advanced_Algorithms
```
Create a virtual environment:
```bash
python3 -m venv .venv
```
Activate the virtual environment:
```bash
source .venv/bin/activate
```
Install the required libraries:
```bash
pip install matplotlib
```
Alternatively, when a `requirements.txt` file is available, run:
```bash
pip install -r requirements.txt
```
---
## Running the Programs
Run all commands from the main project folder.
### Run Task 1
```bash
python -m task1_data_structures.benchmark
```
### Run Task 2
```bash
python -m task2_graph_algorithms.dijkstra
python -m task2_graph_algorithms.prim
python -m task2_graph_algorithms.bellman_ford
```
### Run Task 3
```bash
python -m task3_algorithmic_strategies.weighted_job_scheduling
python -m task3_algorithmic_strategies.minimum_platforms
python -m task3_algorithmic_strategies.hamiltonian_path
```
### Run Task 4
```bash
python -m task4_np_hard.task4_data
```
### Run Task 5
```bash
python -m task5_concurrent_programming.concurrent_sorting
```
Running the files as modules from the project root helps prevent import errors such as:
```text
ModuleNotFoundError: No module named 'task4_np_hard'
```
---
## Main Results
The experiments showed that no single algorithm was best for every operation.
- Hash Table provided the fastest average lookup.
- AVL Tree maintained balanced and predictable performance.
- Binary Search Tree was simple and performed well in the experiments.
- Min-Heap was suitable for retrieving minimum values.
- Dijkstra efficiently found shortest paths with non-negative weights.
- Prim created a Minimum Spanning Tree connecting all cities.
- Bellman–Ford supported negative edges and detected negative cycles.
- Dynamic Programming produced the maximum job profit.
- Greedy Minimum Platforms was faster than the exact method.
- Backtracking found a Hamiltonian Path but had limited scalability.
- First Fit Decreasing was much faster than Local Search.
- Sequential sorting was faster than threaded sorting for the tested CPU-bound workload.
---
## Limitations
The project used simplified datasets and generated graph connections. Geographic distance was used instead of actual road distance or travel time.
The concurrent sorting experiment was also affected by Python thread overhead and the Global Interpreter Lock.
---
## Future Improvements
Possible future improvements include:
- Testing with larger datasets
- Using real road and transport networks
- Comparing Dijkstra with A*
- Testing stronger optimisation techniques
- Improving Local Search strategies
- Using multiprocessing for CPU-bound sorting
- Creating an interactive results dashboard
---
## Author
**Babita Kumari Adhikari**  
Student ID: **240712**  
Module: **ST5003CEM – Advanced Algorithms**
