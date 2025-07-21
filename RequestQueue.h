/**
 * @file RequestQueue.h
 * @brief Header file for the RequestQueue class
 * @author Your Name
 * @date 2024
 * @version 1.0
 */

#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include "Request.h"
#include <queue>
#include <vector>
#include <string>

/**
 * @class RequestQueue
 * @brief Manages a queue of web requests with priority handling
 * 
 * This class implements a priority queue for web requests, allowing
 * for efficient request management and distribution to web servers.
 * Requests can be added, removed, and prioritized based on various criteria.
 */
class RequestQueue {
private:
    std::queue<Request> requestQueue; ///< Main queue of requests
    int maxSize;                      ///< Maximum size of the queue
    int totalRequestsAdded;           ///< Total number of requests added
    int totalRequestsRemoved;         ///< Total number of requests removed
    std::vector<std::string> blockedIPs; ///< List of blocked IP addresses

public:
    /**
     * @brief Default constructor
     */
    RequestQueue();

    /**
     * @brief Parameterized constructor
     * @param maxQueueSize Maximum size of the queue
     */
    RequestQueue(int maxQueueSize);

    /**
     * @brief Destructor
     */
    ~RequestQueue();

    /**
     * @brief Add a request to the queue
     * @param request The request to add
     * @return True if request was added successfully, false if queue is full
     */
    bool addRequest(const Request& request);

    /**
     * @brief Remove and return the next request from the queue
     * @return The next request, or empty request if queue is empty
     */
    Request getNextRequest();

    /**
     * @brief Check if the queue is empty
     * @return True if queue is empty, false otherwise
     */
    bool isEmpty() const;

    /**
     * @brief Check if the queue is full
     * @return True if queue is full, false otherwise
     */
    bool isFull() const;

    /**
     * @brief Get the current size of the queue
     * @return Number of requests in the queue
     */
    int getSize() const;

    /**
     * @brief Get the maximum size of the queue
     * @return Maximum queue size
     */
    int getMaxSize() const;

    /**
     * @brief Get total requests added
     * @return Total number of requests added to the queue
     */
    int getTotalRequestsAdded() const;

    /**
     * @brief Get total requests removed
     * @return Total number of requests removed from the queue
     */
    int getTotalRequestsRemoved() const;

    /**
     * @brief Clear all requests from the queue
     */
    void clear();

    /**
     * @brief Check if an IP address is blocked
     * @param ip IP address to check
     * @return True if IP is blocked, false otherwise
     */
    bool isIPBlocked(const std::string& ip) const;

    /**
     * @brief Block an IP address
     * @param ip IP address to block
     */
    void blockIP(const std::string& ip);

    /**
     * @brief Unblock an IP address
     * @param ip IP address to unblock
     */
    void unblockIP(const std::string& ip);

    /**
     * @brief Get queue utilization percentage
     * @return Utilization as percentage (0-100)
     */
    double getUtilization() const;

    /**
     * @brief Get average wait time for requests in queue
     * @return Average wait time in milliseconds
     */
    double getAverageWaitTime() const;
};

#endif // REQUESTQUEUE_H 