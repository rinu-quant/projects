Indexed Limit Order Book

A C++ implementation of a simplified limit order book supporting buy orders, sell orders, price-time priority matching, partial executions, and order cancellation.

This project is an extension of my first limit order matching engine. The primary objective was to move beyond "std::priority_queue" and implement a custom indexed binary heap to support efficient arbitrary order cancellation.

Features

- Buy and Sell Orders: Accepts limit orders with a specified price and quantity.
- Price-Time Priority: Prioritizes the highest-priced buy orders and lowest-priced sell orders. Orders at the same price are prioritized by submission ID.
- Order Matching: Automatically matches incoming orders against compatible resting orders.
- Partial Execution: Supports partial fills while maintaining the remaining quantity in the order book.
- Multiple Executions: A single incoming order can match multiple resting orders.
- Order Cancellation: Allows cancellation of active resting orders using their unique order IDs.
- Indexed Binary Heaps: Custom max-heap for buy orders and min-heap for sell orders.
- Direct Order Lookup: Maintains a tracker that maps order IDs to their respective book side and heap index.

Data Structures

1. Buy Book

A custom binary max-heap.

- Higher prices have priority.
- For equal prices, lower order IDs have priority.

2. Sell Book

A custom binary min-heap.

- Lower prices have priority.
- For equal prices, lower order IDs have priority.

3. Order Tracker

A vector-based direct-address tracker stores:

- Order side ("B" for buy, "S" for sell).
- Current index of the order in its respective heap.

Heap swaps update the corresponding tracker indices, allowing an order to be located directly using its ID.

Time Complexity

Let "n" represent the number of resting orders on the relevant side of the book.

Operation| Complexity
Best order lookup| O(1)
Insert order| O(log n)
Cancel order lookup| O(1)
Cancel order removal| O(log n)
Heap repair| O(log n)
Match one resting order| O(log n) when fully removed

Matching an incoming order against "k" resting orders can require O(k log n) time in the worst case, excluding input/output costs.

Technologies

- C++
- STL vectors
- Custom binary heaps
- "enum class"
- "string_view"
- "stringstream"

Input Format

Commands are entered one per line.

Buy order

BUY <price> <quantity>

Sell order

SELL <price> <quantity>

Cancel order

CANCEL <order_id>

Exit

EXIT

"STOP" and "QUIT" are also accepted as exit commands.

Example

BUY 100 50
SELL 105 30
SELL 99 20
CANCEL 1
EXIT

The engine automatically executes compatible orders and reports trade information, including buyer ID, seller ID, execution price, and quantity.

Current Limitations

This is an educational project and not a production-ready exchange engine.

- Supports limit orders only.
- No market orders.
- No order modification.
- Uses a direct-address tracker with memory overhead proportional to the highest assigned order ID.
- No multithreading or concurrent order processing.
- No formal latency benchmarking yet.
- Input validation and additional edge-case testing remain areas for improvement.

Objective

The goal of this project was to understand order-book mechanics, binary heap implementation, indexed data structures, and the trade-offs involved in supporting efficient order cancellation.

This project is part of my ongoing exploration of C++, data structures, systems programming, and low-latency trading systems.
