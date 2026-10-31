C++ Systems & Trading Projects

A collection of C++ projects focused on systems programming, trading systems, data structures, performance, and low-latency software engineering.

The projects in this repository are built progressively, starting with fundamental implementations and moving toward more performance-oriented and low-latency systems.

Projects

1. Basic Limit Order Matching Engine

A foundational C++ implementation of a limit-order matching engine using price-time priority and "std::priority_queue".

Focus:

- Buy and sell order books
- Price-time priority
- Order matching
- Partial fills
- Resting orders
- Custom comparators

"View Project" (./basic-limit-order-matching-engine/)

2. Indexed Limit Order Book (V2)

A C++ limit order book implementation using custom indexed binary heaps and a direct-address tracker to support efficient order cancellation.

Focus:

- Custom min-heap and max-heap
- Price-time priority
- Order ID tracking
- Arbitrary order cancellation
- Heap index maintenance
- Partial fills
- Efficient order removal

"View Project" (./indexed-limit-order-book/)


Roadmap

Future projects and iterations may explore:

- More advanced order-book data structures
- Order cancellation and modification
- Market orders
- Trade and market-data generation
- Matching-engine architecture
- Performance benchmarking
- Memory and cache behavior
- C++ concurrency
- Lock-free data structures
- Low-latency system design
- Networking and market-data systems

Projects will be added as they are implemented rather than being treated as completed items in advance.

Technologies

- C++
- Linux
- Git
- CMake
- GDB
- Performance and benchmarking tools

Philosophy

The goal is to understand the underlying systems rather than simply produce working code.

Each project is intended to progress through:

Correctness
    ↓
Measurement
    ↓
Profiling
    ↓
Optimization
    ↓
Low-latency design

Performance claims will be supported by measurements and benchmarks rather than assumptions.

Related Repository

My DSA implementations and algorithm practice are maintained separately in:

cpp-dsa-portfolio

This repository is focused on larger engineering and systems projects rather than standalone DSA problem solving.
