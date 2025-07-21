# Load Balancer Simulation

A C++ simulation of a load balancer system with multiple web servers, featuring dynamic server allocation, request queuing, and IP blocking capabilities.

## Project Overview

This project implements a complete load balancer simulation that demonstrates:
- **Request Management**: Handling web requests with different priorities and processing times
- **Server Management**: Dynamic allocation and deallocation of web servers based on load
- **Load Balancing**: Round-robin distribution of requests across available servers
- **IP Blocking**: Firewall functionality to block malicious IP addresses
- **Real-time Monitoring**: Comprehensive logging and statistics tracking

## Features

### Core Components
- **Request Class**: Manages individual web requests with client IP, type, priority, and processing time
- **WebServer Class**: Represents individual servers with capacity management and request processing
- **RequestQueue Class**: Priority queue for managing pending requests with IP blocking
- **LoadBalancer Class**: Main orchestrator that manages servers and distributes requests

### Key Features
- ✅ Dynamic server allocation/deallocation based on load thresholds
- ✅ Round-robin request distribution algorithm
- ✅ IP address blocking (firewall functionality)
- ✅ Comprehensive logging and statistics
- ✅ Real-time system monitoring
- ✅ Configurable simulation parameters
- ✅ Full Doxygen documentation

## Requirements

- **Compiler**: GCC 7.0+ or compatible C++17 compiler
- **Build Tools**: Make
- **Documentation**: Doxygen (optional, for generating docs)

## Installation

### Prerequisites
```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential g++ make doxygen

# macOS (using Homebrew)
brew install gcc make doxygen

# Windows (using MinGW or Visual Studio)
# Install MinGW-w64 or Visual Studio Community
```

### Building the Project
```bash
# Clone or download the project
cd 412Project3

# Build the project
make

# Or build with debug information
make debug

# Run the simulation
make run
```

## Usage

### Basic Usage
1. Run the executable:
   ```bash
   ./loadbalancer
   ```

2. Enter configuration parameters when prompted:
   - **Number of servers**: 1-50 (default: 5)
   - **Simulation time**: 100-50000 clock cycles (default: 10000)

3. The simulation will:
   - Generate initial requests (servers × 100)
   - Process requests using round-robin distribution
   - Add new requests randomly during simulation
   - Dynamically adjust server count based on load
   - Log statistics to `loadbalancer_log.txt`

### Configuration Options
- **Initial Queue Size**: Automatically set to `servers × 100`
- **Server Capacity**: Each server can handle 10 concurrent requests
- **Load Threshold**: 80% utilization triggers server scaling
- **Request Types**: GET, POST, PUT, DELETE
- **Processing Times**: 5-50 clock cycles per request

### Output Files
- **Console Output**: Real-time simulation status
- **loadbalancer_log.txt**: Detailed cycle-by-cycle statistics
- **docs/html/**: Generated Doxygen documentation (if using `make docs`)

## Project Structure

```
412Project3/
├── main.cpp              # Main driver program
├── Request.h             # Request class header
├── Request.cpp           # Request class implementation
├── WebServer.h           # WebServer class header
├── WebServer.cpp         # WebServer class implementation
├── RequestQueue.h        # RequestQueue class header
├── RequestQueue.cpp      # RequestQueue class implementation
├── LoadBalancer.h        # LoadBalancer class header
├── LoadBalancer.cpp      # LoadBalancer class implementation
├── Makefile              # Build configuration
├── Doxyfile              # Documentation configuration
├── README.md             # This file
└── docs/                 # Generated documentation (after make docs)
```

## Algorithm Details

### Load Balancing Algorithm
The system uses a **Round-Robin** distribution algorithm:
1. Requests are queued in the main request queue
2. Available servers are selected in rotation
3. Each server processes requests in FIFO order
4. System utilization is monitored continuously

### Dynamic Scaling
- **Scale Up**: When average utilization > 80%
- **Scale Down**: When average utilization < 40%
- **Constraints**: Respects min/max server limits

### IP Blocking
- Requests from blocked IPs are automatically rejected
- Supports manual IP blocking/unblocking
- Integrated with the request queue system

## Example Output

```
=== Load Balancer Simulation ===
Enter the number of servers (1-50): 10
Enter the simulation time in clock cycles (100-50000): 10000

Configuration:
- Number of servers: 10
- Simulation time: 10000 cycles
- Initial queue size: 1000 requests

Generating 1000 initial requests...
Queue initialized with 1000 requests

Starting simulation...
Logging to: loadbalancer_log.txt

=== Cycle 1000 Status ===
Active Servers: 10
Queue Size: 245
Total Processed: 755
System Utilization: 67.2%
Queue Utilization: 24.5%

=== Simulation Complete ===
Final Statistics:
- Total requests processed: 1247
- Average processing time: 12.34 cycles
- Final system utilization: 45.8%
- Final queue size: 0
```

## Documentation

Generate comprehensive documentation using Doxygen:
```bash
make docs
```

The documentation will be available in `docs/html/index.html` and includes:
- Complete API documentation
- Class diagrams and relationships
- Function descriptions and parameters
- Usage examples

## Testing

### Sample Test Cases
1. **Low Load**: 2 servers, 1000 cycles
2. **High Load**: 5 servers, 5000 cycles
3. **Overload**: 3 servers, 10000 cycles
4. **IP Blocking**: Test with blocked IP addresses

### Expected Behaviors
- System should scale servers appropriately
- Queue should not overflow under normal conditions
- All requests should eventually be processed
- Statistics should be logged correctly

## Performance Considerations

- **Memory Usage**: Linear with number of servers and queue size
- **Processing Time**: O(n) per cycle where n is number of servers
- **Scalability**: Tested up to 50 servers and 50,000 cycles
- **Optimization**: Uses efficient STL containers and algorithms

## Troubleshooting

### Common Issues
1. **Compilation Errors**: Ensure C++17 support is enabled
2. **Runtime Errors**: Check input validation in main.cpp
3. **Memory Issues**: Large simulations may require more RAM
4. **Documentation**: Install Doxygen for `make docs`

### Debug Mode
```bash
make debug
./loadbalancer
```

## Contributing

This is an academic project. For educational purposes, feel free to:
- Modify algorithms and parameters
- Add new load balancing strategies
- Enhance the IP blocking system
- Improve the user interface

## License

This project is created for educational purposes as part of a university assignment.

## Author

Your Name - CSCE 412 Project 3

## Acknowledgments

- C++ Standard Template Library
- Doxygen documentation system
- Round-robin load balancing algorithm 