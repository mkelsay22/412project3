/**
 * @file main.cpp
 * @brief Main driver program for the Load Balancer Simulation
 * @author Your Name
 * @date 2024
 * @version 1.0
 * 
 * This program simulates a load balancer system with multiple web servers.
 * It allows users to configure the number of servers, simulation time,
 * and generates a full queue of requests. The system dynamically allocates
 * and deallocates servers based on load conditions.
 */

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
#include <iomanip>
#include "LoadBalancer.h"
#include "Request.h"

/**
 * @brief Generate a random IP address
 * @return Random IP address as string
 */
std::string generateRandomIP() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 254);
    
    return std::to_string(dis(gen)) + "." + 
           std::to_string(dis(gen)) + "." + 
           std::to_string(dis(gen)) + "." + 
           std::to_string(dis(gen));
}

/**
 * @brief Generate a random request type
 * @return Random request type as string
 */
std::string generateRandomRequestType() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 3);
    
    std::vector<std::string> types = {"GET", "POST", "PUT", "DELETE"};
    return types[dis(gen)];
}

/**
 * @brief Generate a random request
 * @param requestID Unique identifier for the request
 * @return Generated Request object
 */
Request generateRandomRequest(int requestID) {
    std::string clientIP = generateRandomIP();
    std::string requestType = generateRandomRequestType();
    
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> priorityDis(1, 10);
    static std::uniform_int_distribution<> timeDis(5, 50);
    
    int priority = priorityDis(gen);
    int processingTime = timeDis(gen);
    
    return Request(clientIP, requestType, priority, processingTime, requestID);
}

/**
 * @brief Initialize the load balancer with a full queue
 * @param loadBalancer Reference to the load balancer
 * @param queueSize Number of requests to generate
 */
void initializeQueue(LoadBalancer& loadBalancer, int queueSize) {
    std::cout << "Generating " << queueSize << " initial requests..." << std::endl;
    
    for (int i = 1; i <= queueSize; ++i) {
        Request request = generateRandomRequest(i);
        if (!loadBalancer.addRequest(request)) {
            std::cout << "Warning: Could not add request " << i << " - queue may be full" << std::endl;
            break;
        }
    }
    
    std::cout << "Queue initialized with " << loadBalancer.getQueueSize() << " requests" << std::endl;
}

/**
 * @brief Add new requests at random intervals
 * @param loadBalancer Reference to the load balancer
 * @param cycle Current cycle number
 * @param maxCycles Maximum number of cycles
 */
void addRandomRequests(LoadBalancer& loadBalancer, int cycle, int maxCycles) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 100);
    
    // 5% chance to add a new request each cycle
    if (dis(gen) <= 5 && cycle < maxCycles * 0.8) { // Stop adding requests near the end
        static int nextRequestID = 1001; // Start after initial requests
        Request newRequest = generateRandomRequest(nextRequestID++);
        
        if (loadBalancer.addRequest(newRequest)) {
            std::cout << "  [Cycle " << cycle << "] New request added from " 
                      << newRequest.getClientIP() << std::endl;
        }
    }
}

/**
 * @brief Log simulation statistics to file
 * @param filename Output filename
 * @param loadBalancer Reference to the load balancer
 * @param cycle Current cycle number
 */
void logStatistics(const std::string& filename, const LoadBalancer& loadBalancer, int cycle) {
    std::ofstream logFile(filename, std::ios::app);
    if (logFile.is_open()) {
        logFile << "Cycle " << std::setw(5) << cycle << " | "
                << "Servers: " << std::setw(2) << loadBalancer.getActiveServerCount() << " | "
                << "Queue: " << std::setw(4) << loadBalancer.getQueueSize() << " | "
                << "Processed: " << std::setw(6) << loadBalancer.getTotalRequestsProcessed() << " | "
                << "System Util: " << std::setw(5) << std::fixed << std::setprecision(1) 
                << loadBalancer.getSystemUtilization() << "% | "
                << "Queue Util: " << std::setw(5) << std::fixed << std::setprecision(1) 
                << loadBalancer.getQueueUtilization() << "%" << std::endl;
        logFile.close();
    }
}

/**
 * @brief Display current system status
 * @param loadBalancer Reference to the load balancer
 * @param cycle Current cycle number
 */
void displayStatus(const LoadBalancer& loadBalancer, int cycle) {
    std::cout << "\n=== Cycle " << cycle << " Status ===" << std::endl;
    std::cout << "Active Servers: " << loadBalancer.getActiveServerCount() << std::endl;
    std::cout << "Queue Size: " << loadBalancer.getQueueSize() << std::endl;
    std::cout << "Total Processed: " << loadBalancer.getTotalRequestsProcessed() << std::endl;
    std::cout << "System Utilization: " << std::fixed << std::setprecision(1) 
              << loadBalancer.getSystemUtilization() << "%" << std::endl;
    std::cout << "Queue Utilization: " << std::fixed << std::setprecision(1) 
              << loadBalancer.getQueueUtilization() << "%" << std::endl;
    
    if (loadBalancer.isOverloaded()) {
        std::cout << "*** SYSTEM OVERLOADED ***" << std::endl;
    }
}

/**
 * @brief Main function
 * @return Exit status
 */
int main() {
    std::cout << "=== Load Balancer Simulation ===" << std::endl;
    std::cout << "This program simulates a load balancer with multiple web servers." << std::endl;
    
    // Get user input
    int numServers, simulationTime;
    
    std::cout << "\nEnter the number of servers (1-50): ";
    std::cin >> numServers;
    
    if (numServers < 1 || numServers > 50) {
        std::cout << "Invalid number of servers. Using default value of 5." << std::endl;
        numServers = 5;
    }
    
    std::cout << "Enter the simulation time in clock cycles (100-50000): ";
    std::cin >> simulationTime;
    
    if (simulationTime < 100 || simulationTime > 50000) {
        std::cout << "Invalid simulation time. Using default value of 10000." << std::endl;
        simulationTime = 10000;
    }
    
    // Calculate queue size (servers * 100 as specified)
    int queueSize = numServers * 100;
    
    std::cout << "\nConfiguration:" << std::endl;
    std::cout << "- Number of servers: " << numServers << std::endl;
    std::cout << "- Simulation time: " << simulationTime << " cycles" << std::endl;
    std::cout << "- Initial queue size: " << queueSize << " requests" << std::endl;
    
    // Create load balancer
    LoadBalancer loadBalancer(numServers, numServers * 2, 1, 0.8);
    
    // Initialize queue with requests
    initializeQueue(loadBalancer, queueSize);
    
    // Set up logging
    std::string logFilename = "loadbalancer_log.txt";
    std::ofstream logFile(logFilename);
    if (logFile.is_open()) {
        logFile << "Load Balancer Simulation Log" << std::endl;
        logFile << "Servers: " << numServers << ", Cycles: " << simulationTime << std::endl;
        logFile << "Cycle    | Servers | Queue | Processed | System Util | Queue Util" << std::endl;
        logFile << "---------|---------|-------|-----------|-------------|-----------" << std::endl;
        logFile.close();
    }
    
    std::cout << "\nStarting simulation..." << std::endl;
    std::cout << "Logging to: " << logFilename << std::endl;
    
    // Main simulation loop
    for (int cycle = 1; cycle <= simulationTime; ++cycle) {
        // Add random new requests
        addRandomRequests(loadBalancer, cycle, simulationTime);
        
        // Process one cycle
        int completed = loadBalancer.processCycle();
        
        // Log statistics every 100 cycles or at the end
        if (cycle % 100 == 0 || cycle == simulationTime) {
            logStatistics(logFilename, loadBalancer, cycle);
            
            // Display status every 1000 cycles
            if (cycle % 1000 == 0 || cycle == simulationTime) {
                displayStatus(loadBalancer, cycle);
            }
        }
        
        // Small delay to make simulation visible (optional)
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    // Final statistics
    std::cout << "\n=== Simulation Complete ===" << std::endl;
    std::cout << "Final Statistics:" << std::endl;
    std::cout << "- Total requests processed: " << loadBalancer.getTotalRequestsProcessed() << std::endl;
    std::cout << "- Average processing time: " << std::fixed << std::setprecision(2) 
              << loadBalancer.getAverageProcessingTime() << " cycles" << std::endl;
    std::cout << "- Final system utilization: " << std::fixed << std::setprecision(1) 
              << loadBalancer.getSystemUtilization() << "%" << std::endl;
    std::cout << "- Final queue size: " << loadBalancer.getQueueSize() << std::endl;
    
    // Display server statistics
    std::cout << "\nServer Statistics:" << std::endl;
    auto serverStats = loadBalancer.getServerStats();
    for (const auto& stat : serverStats) {
        std::cout << "  " << stat << std::endl;
    }
    
    std::cout << "\nLog file saved as: " << logFilename << std::endl;
    std::cout << "Press Enter to exit...";
    std::cin.ignore();
    std::cin.get();
    
    return 0;
} 