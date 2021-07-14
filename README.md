# The Travelling Salesman Problem
> This project is slightly different from the original The Travelling Salesman Problem due some given constraints in the description.

## Team

[Luciana Serrão](https://github.com/LucianaSerrao), [Gustavo Eraldo](https://github.com/gustavoeraldo), [Kenji Sato](https://github.com/KenjiSato97)


## Introduction


## How to run

Compile the code:
```bash
g++ main.cpp vnd.cpp -o main 
```

And then execute it:

```bash
# ./executable file_name
./main cup1.txt
```

You can try any input instance once it follows the [pattern](./instances/descricao.txt).


## To Do list

- [x] Develop heuristic building;

- [X] VND
    - [X] Swap
    - [X] 2-opt
    - [X] Re-insertion

- [ ] ILS (metaheuristic)