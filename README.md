# Simple benchmark and test environment for C++ code

This project represnets a simple plug-and-play environment that can be used to benchmark and test C++ code.

## Preparing the environment

To prepare the environment, you should do the following:
1. Download the code from the github and position yourself into the downloaded folder:
```
git clone https://github.com/mladja777/benchmarkandtest.git
cd benchmarkandtest
```
2. Run google benchmark setup:
> [!NOTE]
> Not needed if you already have google benchmark installed.
```
chmod +x setup_benchmark.py
./setup_benchmark.py
```

## Writing Tests and Benchmarks

In order to write test or benchmark, it is enough to create `.hpp` file in `src/` folder and write desired code in it. Created file will automatically be included in the build procedure. For a reference, you can observe few sample files provided in `src/` folder.

## Building and Running

In order to build and run tests and benchmarks you should start `run.py` script:
```
chmod +x run.py
./run.py
```

If you want to clean build directory before a new build-and-run procedure:
```
./run.py --clean
```

If you want to run only tests or benchmarks:
```
./run.py test
./run.py benchmark
```
