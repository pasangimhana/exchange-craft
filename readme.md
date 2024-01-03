```
 _____          _                                   ____            __ _     ____    ___  
| ____|_  _____| |__   __ _ _ __   __ _  ___       / ___|_ __ __ _ / _| |_  |___ \  / _ \ 
|  _| \ \/ / __| '_ \ / _` | '_ \ / _` |/ _ \_____| |   | '__/ _` | |_| __|   __) || | | |
| |___ >  < (__| | | | (_| | | | | (_| |  __/_____| |___| | | (_| |  _| |_   / __/ | |_| |
|_____/_/\_\___|_| |_|\__,_|_| |_|\__, |\___|      \____|_|  \__,_|_|  \__| |_____(_)___/ 
                                  |___/                                                                                                              
```
## Simple ATS (Automated Trading System) Implementation - Version 2.0

This C++ program, now in its Version 2.0, continues to implement a basic Automated Trading System (ATS) for handling buy and sell orders in the financial domain. The latest version brings structural improvements for better code organization.

## Features
- **Order Structure**: Defines an `Order` structure with attributes such as price, amount, timestamp, product, and order type (buy, sell, or sold).
- **CSV Processor**: Parses a CSV file containing order data and populates order entries using the `CSVProcessor` class.
- **Order Sorting**: Implements sorting for buy and sell orders based on price and timestamp.
- **Order Matching**: Matches buy and sell orders with similar prices using a simple matching algorithm.
- **Filled Book**: Maintains a filled book with details of matched orders.
- **Cleanup**: Removes orders with zero amounts from buy, sell, and filled order books.
- **Reordering**: Sorts the order books after matching orders to maintain a consistent order.

## How to Use
1. **CSV Input**: Create a CSV file with order data in the format: `timestamp, product, order_type, price, amount`.
2. **Program Execution**: Modify the `main` function in the provided C++ code to specify the CSV file path (`exchangeCore.parseCSV("your_data.csv");`).
3. **Run the Program**: Compile and run the C++ program to see the order book sizes and the filled order book.

## Execution Time
The program measures the execution time using the `chrono` library and prints the elapsed time after processing orders.

## Example
An example CSV file (`data.csv`) is included for testing the ATS.

## Dependencies
The program relies on standard C++ libraries and does not require additional dependencies.

## License
This ATS implementation is provided under an open-source license. Feel free to modify and use it for educational or practical purposes.

---

*Note: Version 2.0 introduces structural enhancements, making the code more organized and maintainable.*
