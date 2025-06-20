# DataStructure

## License
This repo is licensed under [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)

## About
This repo stores C++ implementations of common data structures and algorithms as listed below, note that the lists and trees are completed without STL

- Linear Lists
    - Sequential (Completed)
    - Linked (Completed)
    - Stack (Completed)
    - Queue (Completed)

- Tree Structures
    - Multi
        - Basic (Completed)
    - Binary
        - Basic (Completed)
        - Heap (Completed)
        - Search
            - Basic (Completed)
            - ~~AVL~~
            - ~~Red-Black~~
    - N-ary
        - ~~Basic~~
        - ~~Search~~
        - ~~B+~~

- Sorting Methods
    - $O(n^2)$
        - Selection (Completed)
        - Insertion (Completed)
        - Bubble (Completed)
    - $O(n\ln{n})$
        - Heap (Completed)
        - Merge (Completed)
        - Quick (Completed)
    - $O(n)$
        - ~~Bucket~~
        - ~~Radix~~

- Graph
    - Structures
        - Disjoint Set Union (Completed)
        - ~~Adjacency-Matrix~~
        - ~~Adjacency-List~~
    - Algorithms
        - MST
            - ~~Prim-List~~
            - ~~Prim-Heap~~
            - ~~Kruskal~~
        - Search
            - ~~BFS/DFS~~ 
            - ~~Dijkstra~~
            - ~~A*~~

Though several of them are not completed because of my lack of leisure, you can also check related notes posted on my own [blog](https://whythz.github.io/) for detailed explanations

## Deployment
- Ensure that your VSCode has installed these addons: `C/C++`, `CMake`, `CMake Tools`, then clone this repo and open it in VSCode

```
git clone https://github.com/WhythZ/DataStructure.git
```

- Use `Ctrl + Shift + P` and then find `CMake: Configure`, choose your local compiler such as gcc from MinGW, then create `build` folder in root directory, `cd build` enter it in terminal, use instructions below to generate Makefiles

```
cmake -G"MinGW Makefiles" ..
```

- Then use following command to compile all the codes for the first time or after whenever you edit the codes

```
cmake --build .
```

- After that you can use `Ctrl + F5` to run the executable file to print the running process of the test cases visually in console, by the way if you want to debug the codes with gdb
    - Change the `"miDebuggerPath"` value in the `launch.json` to your local MinGW `gdb.exe` directory
    - Then use `Ctrl + Shift + D` and click the related button to start debugging with debug tools like breakpoints