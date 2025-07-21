/**
 * @file WebServer.h
 * @brief Header file for the WebServer class
 * @author Your Name
 * @date 2024
 * @version 1.0
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
#include <queue>
#include <string>

/**
 * @class WebServer
 * @brief Represents a web server that can process requests
 * 
 * This class manages individual web servers, including their processing queue,
 * current load, and status. Each server can handle multiple requests simultaneously
 * up to its capacity limit.
 */
class WebServer {
private:
    int serverID;                    ///< Unique identifier for this server
    std::string serverIP;            ///< IP address of this server
    int maxCapacity;                 ///< Maximum number of concurrent requests
    int currentLoad;                 ///< Current number of requests being processed
    std::queue<Request> requestQueue; ///< Queue of requests waiting to be processed
    bool isActive;                   ///< Whether the server is active/online
    int totalRequestsProcessed;      ///< Total number of requests processed by this server
    int totalProcessingTime;         ///< Total processing time used by this server

public:
    /**
     * @brief Default constructor
     */
    WebServer();

    /**
     * @brief Parameterized constructor
     * @param id Unique server identifier
     * @param ip Server IP address
     * @param capacity Maximum concurrent requests capacity
     */
    WebServer(int id, const std::string& ip, int capacity);

    /**
     * @brief Destructor
     */
    ~WebServer();

    /**
     * @brief Get the server ID
     * @return Server identifier
     */
    int getServerID() const;

    /**
     * @brief Get the server IP address
     * @return Server IP as string
     */
    std::string getServerIP() const;

    /**
     * @brief Get the maximum capacity
     * @return Maximum concurrent requests capacity
     */
    int getMaxCapacity() const;

    /**
     * @brief Get the current load
     * @return Current number of requests being processed
     */
    int getCurrentLoad() const;

    /**
     * @brief Get the queue size
     * @return Number of requests in the queue
     */
    int getQueueSize() const;

    /**
     * @brief Check if the server is active
     * @return True if server is active, false otherwise
     */
    bool getIsActive() const;

    /**
     * @brief Get total requests processed
     * @return Total number of requests processed
     */
    int getTotalRequestsProcessed() const;

    /**
     * @brief Get total processing time
     * @return Total processing time used
     */
    int getTotalProcessingTime() const;

    /**
     * @brief Set the server active status
     * @param active New active status
     */
    void setIsActive(bool active);

    /**
     * @brief Add a request to the server's queue
     * @param request The request to add
     * @return True if request was added successfully, false if server is at capacity
     */
    bool addRequest(const Request& request);

    /**
     * @brief Process one clock cycle of requests
     * @return Number of requests completed in this cycle
     */
    int processCycle();

    /**
     * @brief Check if server can accept new requests
     * @return True if server has capacity, false otherwise
     */
    bool canAcceptRequest() const;

    /**
     * @brief Get server utilization percentage
     * @return Utilization as percentage (0-100)
     */
    double getUtilization() const;

    /**
     * @brief Get average processing time per request
     * @return Average processing time, or 0 if no requests processed
     */
    double getAverageProcessingTime() const;
};

#endif // WEBSERVER_H 