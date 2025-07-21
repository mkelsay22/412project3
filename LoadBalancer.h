/**
 * @file LoadBalancer.h
 * @brief Header file for the LoadBalancer class
 * @author Your Name
 * @date 2024
 * @version 1.0
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "WebServer.h"
#include "RequestQueue.h"
#include <vector>
#include <string>
#include <memory>

/**
 * @class LoadBalancer
 * @brief Manages web servers and distributes requests among them
 * 
 * This class implements a load balancer that manages multiple web servers
 * and distributes incoming requests among them using various load balancing
 * algorithms. It also handles dynamic server allocation and deallocation
 * based on load conditions.
 */
class LoadBalancer {
private:
    std::vector<std::unique_ptr<WebServer>> servers; ///< Vector of web servers
    RequestQueue requestQueue;                        ///< Queue of pending requests
    int nextServerIndex;                              ///< Index for round-robin distribution
    int totalRequestsProcessed;                       ///< Total requests processed by all servers
    int totalProcessingTime;                          ///< Total processing time across all servers
    int maxServers;                                   ///< Maximum number of servers allowed
    int minServers;                                   ///< Minimum number of servers to maintain
    double loadThreshold;                             ///< Load threshold for adding/removing servers

public:
    /**
     * @brief Default constructor
     */
    LoadBalancer();

    /**
     * @brief Parameterized constructor
     * @param initialServers Initial number of servers
     * @param maxServerCount Maximum number of servers allowed
     * @param minServerCount Minimum number of servers to maintain
     * @param threshold Load threshold for scaling (0.0-1.0)
     */
    LoadBalancer(int initialServers, int maxServerCount, int minServerCount, double threshold);

    /**
     * @brief Destructor
     */
    ~LoadBalancer();

    /**
     * @brief Add a new web server
     * @return True if server was added successfully, false if at maximum capacity
     */
    bool addServer();

    /**
     * @brief Remove a web server
     * @return True if server was removed successfully, false if at minimum capacity
     */
    bool removeServer();

    /**
     * @brief Add a request to the load balancer
     * @param request The request to add
     * @return True if request was added successfully
     */
    bool addRequest(const Request& request);

    /**
     * @brief Process one clock cycle of the load balancer
     * @return Number of requests completed in this cycle
     */
    int processCycle();

    /**
     * @brief Distribute requests to servers using round-robin algorithm
     */
    void distributeRequests();

    /**
     * @brief Check if load balancing is needed and adjust server count
     */
    void checkLoadBalancing();

    /**
     * @brief Get the number of active servers
     * @return Number of currently active servers
     */
    int getActiveServerCount() const;

    /**
     * @brief Get the total number of requests processed
     * @return Total requests processed by all servers
     */
    int getTotalRequestsProcessed() const;

    /**
     * @brief Get the average processing time across all servers
     * @return Average processing time per request
     */
    double getAverageProcessingTime() const;

    /**
     * @brief Get the overall system utilization
     * @return System utilization as percentage (0-100)
     */
    double getSystemUtilization() const;

    /**
     * @brief Get queue utilization
     * @return Queue utilization as percentage (0-100)
     */
    double getQueueUtilization() const;

    /**
     * @brief Get server statistics
     * @return Vector of server statistics strings
     */
    std::vector<std::string> getServerStats() const;

    /**
     * @brief Block an IP address across all components
     * @param ip IP address to block
     */
    void blockIP(const std::string& ip);

    /**
     * @brief Unblock an IP address across all components
     * @param ip IP address to unblock
     */
    void unblockIP(const std::string& ip);

    /**
     * @brief Get the current queue size
     * @return Number of requests in the queue
     */
    int getQueueSize() const;

    /**
     * @brief Check if the system is overloaded
     * @return True if system is overloaded, false otherwise
     */
    bool isOverloaded() const;
};

#endif // LOADBALANCER_H 