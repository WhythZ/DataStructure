# DataStructure

## License
This repo is licensed under [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)

## About
This repo stores C++ implementations of common data structures and algorithms as listed below, note that the lists and trees are completed without STL

- Linear Lists
    - Sequential
    - Linked
    - Stack
    - Queue

- Tree Structures
    - Multi
        - ~~N-ary~~
        - ~~Search~~
        - ~~B+~~
    - Binary
        - Search
            - ~~AVL~~
            - ~~Red-Black~~
        - Heap

- Sorting Methods
    - $O(n^2)$
        - Selection
        - Insertion
        - Bubble
    - $O(n\ln{n})$
        - Heap
        - Merge
        - Quick
    - $O(n)$
        - ~~Bucket~~
        - ~~Radix~~

Though several of them are not completed because of my lack of leisure, you can also check related notes posted on my own [blog](https://whythz.github.io/) for detailed explanations

## Using

1. Ensure that your VSCode has installed these addons: `C/C++`, `CMake`, `CMake Tools`

2. Use `Ctrl + F5` to use CMake to generate the executable file and run it
    - You can comment the unwanted test cases in `Main.cpp` to hide them
    - The data structures and algorithms' process will be visually printed in console

3. If you want to debug with gdb, follow the steps, else you can ignore this part
    - Firstly change the `"miDebuggerPath"` value in the `launch.json` to your local MinGW `gdb.exe` directory
    - Then use `Ctrl + Shift + D` and click the related button to start debugging with breakpoints