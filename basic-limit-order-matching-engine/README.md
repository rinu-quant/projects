Basic Limit Order Matching Engine

A C++ implementation of a basic limit-order matching engine that matches buy and sell orders using price-time priority.

This is the first project in my trading-systems repository and serves as a foundation for progressively more advanced order-book and low-latency systems.

Features

- Buy and sell limit orders
- Price-time priority
- Separate buy and sell order books
- Automatic order matching
- Partial order execution
- Resting orders
- Order IDs for tracking
- Custom comparators for buy and sell priority queues
- Execution at the resting order's price

Order Priority

Buy Side

Buy orders are prioritized by:

1. Highest price
2. Earliest order ID when prices are equal

Sell Side

Sell orders are prioritized by:

1. Lowest price
2. Earliest order ID when prices are equal

This is implemented using custom comparators with "std::priority_queue".

Matching Logic

A new buy order can execute against the best resting sell order when:

buy price >= sell price

A new sell order can execute against the best resting buy order when:

sell price <= buy price

When an order is partially filled, the remaining quantity is returned to the appropriate order book.

When no matching order exists, the incoming order becomes a resting order.

Example

Suppose the sell book contains:

SELL 100 × 10

A new order arrives:

BUY 105 × 6

Since:

105 >= 100

the orders match.

The trade executes at the resting sell price:

100 × 6

The remaining sell quantity is:

100 × 4

The incoming buy order is completely filled.

Implementation

Language

- C++

Main STL Components

- "std::priority_queue"
- "std::vector"
- "std::string"
- "std::min"

Data Structure

Each order is represented as:

struct Order
{
    int64_t price;
    int id;
    int quantity;
};

Two priority queues maintain the order books:

Buy Book  → highest price, then earliest ID
Sell Book → lowest price, then earliest ID

Current Scope

This implementation intentionally focuses on the fundamental matching logic.

It does not yet implement:

- Order cancellation
- Order modification
- Market orders
- Multiple order types
- Persistent order IDs
- Market-data output
- Threading
- Lock-free structures
- Latency benchmarking
- Production-grade networking

These are potential areas for future implementations.

Goal

The purpose of this project is to build a progressively more sophisticated understanding of trading-system architecture, data structures, and performance.

Future versions will explore more efficient order-book representations, benchmarking, memory behavior, and low-latency design.
