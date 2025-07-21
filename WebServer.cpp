/**
 * @file WebServer.cpp
 * @brief Implementation file for the WebServer class
 * @author Your Name
 * @date 2024
 * @version 1.0
 */

#include "WebServer.h"
#include <algorithm>

/**
 * @brief Default constructor
 * 
 * Initializes a web server with default values
 */
WebServer::WebServer() : serverID(0), serverIP("0.0.0.0"), maxCapacity(10), 
                         currentLoad(0), isActive(true), totalRequestsProcessed(0), 
                         totalProcessingTime(0) {
}

/**
 * @brief Parameterized constructor
 * @param id Unique server identifier
 * @param ip Server IP address
 * @param capacity Maximum concurrent requests capacity
 */
WebServer::WebServer(int id, const std::string& ip, int capacity) 
    : serverID(id), serverIP(ip), maxCapacity(capacity), currentLoad(0), 
      isActive(true), totalRequestsProcessed(0), totalProcessingTime(0) {
}

/**
 * @brief Destructor
 */
WebServer::~WebServer() {
    // Clean up any remaining requests
    while (!requestQueue.empty()) {
        requestQueue.pop();
    }
}

/**
 * @brief Get the server ID
 * @return Server identifier
 */
int WebServer::getServerID() const {
    return serverID;
}

/**
 * @brief Get the server IP address
 * @return Server IP as string
 */
std::string WebServer::getServerIP() const {
    return serverIP;
}

/**
 * @brief Get the maximum capacity
 * @return Maximum concurrent requests capacity
 */
int WebServer::getMaxCapacity() const {
    return maxCapacity;
}

/**
 * @brief Get the current load
 * @return Current number of requests being processed
 */
int WebServer::getCurrentLoad() const {
    return currentLoad;
}

/**
 * @brief Get the queue size
 * @return Number of requests in the queue
 */
int WebServer::getQueueSize() const {
    return static_cast<int>(requestQueue.size());
}

/**
 * @brief Check if the server is active
 * @return True if server is active, false otherwise
 */
bool WebServer::getIsActive() const {
    return isActive;
}

/**
 * @brief Get total requests processed
 * @return Total number of requests processed
 */
int WebServer::getTotalRequestsProcessed() const {
    return totalRequestsProcessed;
}

/**
 * @brief Get total processing time
 * @return Total processing time used
 */
int WebServer::getTotalProcessingTime() const {
    return totalProcessingTime;
}

/**
 * @brief Set the server active status
 * @param active New active status
 */
void WebServer::setIsActive(bool active) {
    isActive = active;
}

/**
 * @brief Add a request to the server's queue
 * @param request The request to add
 * @return True if request was added successfully, false if server is at capacity
 */
bool WebServer::addRequest(const Request& request) {
    if (!isActive || currentLoad >= maxCapacity) {
        return false;
    }
    
    requestQueue.push(request);
    currentLoad++;
    return true;
}

/**
 * @brief Process one clock cycle of requests
 * @return Number of requests completed in this cycle
 */
int WebServer::processCycle() {
    if (!isActive || requestQueue.empty()) {
        return 0;
    }
    
    int completedRequests = 0;
    std::queue<Request> tempQueue;
    
    // Process each request in the queue
    while (!requestQueue.empty()) {
        Request currentRequest = requestQueue.front();
        requestQueue.pop();
        
        // Decrease processing time by 1 cycle
        int remainingTime = currentRequest.getProcessingTime() - 1;
        
        if (remainingTime <= 0) {
            // Request completed
            completedRequests++;
            totalRequestsProcessed++;
            totalProcessingTime += currentRequest.getProcessingTime();
            currentLoad--;
        } else {
            // Request still needs more processing time
            currentRequest.setProcessingTime(remainingTime);
            tempQueue.push(currentRequest);
        }
    }
    
    // Restore requests that still need processing
    requestQueue = tempQueue;
    
    return completedRequests;
}

/**
 * @brief Check if server can accept new requests
 * @return True if server has capacity, false otherwise
 */
bool WebServer::canAcceptRequest() const {
    return isActive && currentLoad < maxCapacity;
}

/**
 * @brief Get server utilization percentage
 * @return Utilization as percentage (0-100)
 */
double WebServer::getUtilization() const {
    if (maxCapacity == 0) return 0.0;
    return (static_cast<double>(currentLoad) / maxCapacity) * 100.0;
}

/**
 * @brief Get average processing time per request
 * @return Average processing time, or 0 if no requests processed
 */
double WebServer::getAverageProcessingTime() const {
    if (totalRequestsProcessed == 0) return 0.0;
    return static_cast<double>(totalProcessingTime) / totalRequestsProcessed;
} 