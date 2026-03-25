## Hex Dump
Basic implementation of xxd without flags. 
Build:
```shell
make hex-dump
```

Test:
```shell
./hex-dump sample.c
./hex-dump test.txt
```

Example output:
```shell
696e 7420 6d61 696e 2829 0a7b 0a20 2020 | int main().{.    |
2072 6574 7572 6e20 303b 0a7d           |  return 0;.}     |
```