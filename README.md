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

## Using

Ensure that your VSCode has installed these addons: `C/C++`, `CMake`, `CMake Tools`, then clone this repo and open it in VSCode
```
git clone https://github.com/WhythZ/DataStructure.git
```

Use `Ctrl + Shift + P` and then find `CMake: Configure`, choose your local compiler such as gcc from MinGW, read [here](https://whythz.github.io/posts/VSCode%E4%B8%AD%E7%9A%84CMake%E7%BC%96%E8%AF%91%E4%B8%8E%E8%B0%83%E8%AF%95%E7%9A%84%E5%9F%BA%E6%9C%AC%E9%85%8D%E7%BD%AE/) for details of this and following steps

Then you will find a `build` folder generated in root directory, cd into it in terminal, use instructions below to compile for the first time
```
cd build
cmake ..
mingw32-make.exe
```

After finished all before, you can use `Ctrl + F5` to run the executable file `Main.exe`
- The data structures and algorithms' running process will be visually printed in console
- You can comment the unwanted test cases in `Main.cpp` to hide them or edit the codes, after that you should run `mingw32-make.exe` again to re-compile the codes into new `Main.exe`

If you want to debug the codes with gdb
- Change the `"miDebuggerPath"` value in the `launch.json` to your local MinGW `gdb.exe` directory
- Then use `Ctrl + Shift + D` and click the related button to start debugging with breakpoints