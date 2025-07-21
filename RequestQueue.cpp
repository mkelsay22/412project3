/**
 * @file RequestQueue.cpp
 * @brief Implementation file for the RequestQueue class
 * @author Your Name
 * @date 2024
 * @version 1.0
 */

#include "RequestQueue.h"
#include <algorithm>

/**
 * @brief Default constructor
 * 
 * Initializes a request queue with default maximum size
 */
RequestQueue::RequestQueue() : maxSize(1000), totalRequestsAdded(0), totalRequestsRemoved(0) {
}

/**
 * @brief Parameterized constructor
 * @param maxQueueSize Maximum size of the queue
 */
RequestQueue::RequestQueue(int maxQueueSize) : maxSize(maxQueueSize), 
                                              totalRequestsAdded(0), totalRequestsRemoved(0) {
}

/**
 * @brief Destructor
 */
RequestQueue::~RequestQueue() {
    clear();
}

/**
 * @brief Add a request to the queue
 * @param request The request to add
 * @return True if request was added successfully, false if queue is full
 */
bool RequestQueue::addRequest(const Request& request) {
    // Check if IP is blocked
    if (isIPBlocked(request.getClientIP())) {
        return false;
    }
    
    // Check if queue is full
    if (isFull()) {
        return false;
    }
    
    requestQueue.push(request);
    totalRequestsAdded++;
    return true;
}

/**
 * @brief Remove and return the next request from the queue
 * @return The next request, or empty request if queue is empty
 */
Request RequestQueue::getNextRequest() {
    if (isEmpty()) {
        return Request(); // Return empty request
    }
    
    Request nextRequest = requestQueue.front();
    requestQueue.pop();
    totalRequestsRemoved++;
    return nextRequest;
}

/**
 * @brief Check if the queue is empty
 * @return True if queue is empty, false otherwise
 */
bool RequestQueue::isEmpty() const {
    return requestQueue.empty();
}

/**
 * @brief Check if the queue is full
 * @return True if queue is full, false otherwise
 */
bool RequestQueue::isFull() const {
    return getSize() >= maxSize;
}

/**
 * @brief Get the current size of the queue
 * @return Number of requests in the queue
 */
int RequestQueue::getSize() const {
    return static_cast<int>(requestQueue.size());
}

/**
 * @brief Get the maximum size of the queue
 * @return Maximum queue size
 */
int RequestQueue::getMaxSize() const {
    return maxSize;
}

/**
 * @brief Get total requests added
 * @return Total number of requests added to the queue
 */
int RequestQueue::getTotalRequestsAdded() const {
    return totalRequestsAdded;
}

/**
 * @brief Get total requests removed
 * @return Total number of requests removed from the queue
 */
int RequestQueue::getTotalRequestsRemoved() const {
    return totalRequestsRemoved;
}

/**
 * @brief Clear all requests from the queue
 */
void RequestQueue::clear() {
    while (!requestQueue.empty()) {
        requestQueue.pop();
    }
}

/**
 * @brief Check if an IP address is blocked
 * @param ip IP address to check
 * @return True if IP is blocked, false otherwise
 */
bool RequestQueue::isIPBlocked(const std::string& ip) const {
    return std::find(blockedIPs.begin(), blockedIPs.end(), ip) != blockedIPs.end();
}

/**
 * @brief Block an IP address
 * @param ip IP address to block
 */
void RequestQueue::blockIP(const std::string& ip) {
    if (!isIPBlocked(ip)) {
        blockedIPs.push_back(ip);
    }
}

/**
 * @brief Unblock an IP address
 * @param ip IP address to unblock
 */
void RequestQueue::unblockIP(const std::string& ip) {
    auto it = std::find(blockedIPs.begin(), blockedIPs.end(), ip);
    if (it != blockedIPs.end()) {
        blockedIPs.erase(it);
    }
}

/**
 * @brief Get queue utilization percentage
 * @return Utilization as percentage (0-100)
 */
double RequestQueue::getUtilization() const {
    if (maxSize == 0) return 0.0;
    return (static_cast<double>(getSize()) / maxSize) * 100.0;
}

/**
 * @brief Get average wait time for requests in queue
 * @return Average wait time in milliseconds
 */
double RequestQueue::getAverageWaitTime() const {
    if (totalRequestsRemoved == 0) return 0.0;
    
    // This is a simplified calculation - in a real implementation,
    // you would track individual wait times for each request
    return static_cast<double>(totalRequestsRemoved) * 10.0; // Placeholder calculation
} 