/**
 * @file LoadBalancer.cpp
 * @brief Implementation file for the LoadBalancer class
 * @author Your Name
 * @date 2024
 * @version 1.0
 */

#include "LoadBalancer.h"
#include <sstream>
#include <algorithm>
#include <iomanip>

/**
 * @brief Default constructor
 * 
 * Initializes a load balancer with default values
 */
LoadBalancer::LoadBalancer() : nextServerIndex(0), totalRequestsProcessed(0), 
                               totalProcessingTime(0), maxServers(20), minServers(1), 
                               loadThreshold(0.8) {
    // Add one default server
    addServer();
}

/**
 * @brief Parameterized constructor
 * @param initialServers Initial number of servers
 * @param maxServerCount Maximum number of servers allowed
 * @param minServerCount Minimum number of servers to maintain
 * @param threshold Load threshold for scaling (0.0-1.0)
 */
LoadBalancer::LoadBalancer(int initialServers, int maxServerCount, int minServerCount, double threshold)
    : nextServerIndex(0), totalRequestsProcessed(0), totalProcessingTime(0),
      maxServers(maxServerCount), minServers(minServerCount), loadThreshold(threshold) {
    
    // Add initial servers
    for (int i = 0; i < initialServers; ++i) {
        addServer();
    }
}

/**
 * @brief Destructor
 */
LoadBalancer::~LoadBalancer() {
    servers.clear();
}

/**
 * @brief Add a new web server
 * @return True if server was added successfully, false if at maximum capacity
 */
bool LoadBalancer::addServer() {
    if (static_cast<int>(servers.size()) >= maxServers) {
        return false;
    }
    
    int serverID = static_cast<int>(servers.size()) + 1;
    std::string serverIP = "192.168.1." + std::to_string(serverID);
    servers.push_back(std::make_unique<WebServer>(serverID, serverIP, 5));
    
    return true;
}

/**
 * @brief Remove a web server
 * @return True if server was removed successfully, false if at minimum capacity
 */
bool LoadBalancer::removeServer() {
    if (static_cast<int>(servers.size()) <= minServers) {
        return false;
    }
    
    // Remove the last server (simplest approach)
    servers.pop_back();
    return true;
}

/**
 * @brief Add a request to the load balancer
 * @param request The request to add
 * @return True if request was added successfully
 */
bool LoadBalancer::addRequest(const Request& request) {
    return requestQueue.addRequest(request);
}

/**
 * @brief Process one clock cycle of the load balancer
 * @return Number of requests completed in this cycle
 */
int LoadBalancer::processCycle() {
    int totalCompleted = 0;
    
    // Process all servers
    for (auto& server : servers) {
        if (server->getIsActive()) {
            totalCompleted += server->processCycle();
        }
    }
    
    // Distribute requests from queue to available servers
    distributeRequests();
    
    // Check if load balancing is needed
    checkLoadBalancing();
    
    totalRequestsProcessed += totalCompleted;
    return totalCompleted;
}

/**
 * @brief Distribute requests to servers using round-robin algorithm
 */
void LoadBalancer::distributeRequests() {
    if (requestQueue.isEmpty()) {
        return;
    }
    
    int attempts = 0;
    int maxAttempts = servers.size() * 2; // Prevent infinite loops
    
    while (!requestQueue.isEmpty() && attempts < maxAttempts) {
        // Find next available server using round-robin
        int serverIndex = nextServerIndex;
        bool requestAssigned = false;
        
        // Try to find an available server starting from nextServerIndex
        for (size_t i = 0; i < servers.size(); ++i) {
            int currentIndex = (serverIndex + i) % servers.size();
            
            if (servers[currentIndex]->canAcceptRequest()) {
                Request request = requestQueue.getNextRequest();
                if (servers[currentIndex]->addRequest(request)) {
                    nextServerIndex = (currentIndex + 1) % servers.size();
                    requestAssigned = true;
                    break;
                }
            }
        }
        
        if (!requestAssigned) {
            break; // No servers available
        }
        
        attempts++;
    }
}

/**
 * @brief Check if load balancing is needed and adjust server count
 */
void LoadBalancer::checkLoadBalancing() {
    if (servers.empty()) {
        return;
    }
    
    double avgUtilization = getSystemUtilization() / 100.0; // Convert to 0-1 scale
    int queueSize = getQueueSize();
    
    // Add server if utilization is high OR queue is building up
    if ((avgUtilization > loadThreshold || queueSize > 10) && static_cast<int>(servers.size()) < maxServers) {
        addServer();
    }
    
    // Only remove servers if utilization is extremely low and we have excess capacity
    if (avgUtilization < (loadThreshold * 0.05) && queueSize == 0 && static_cast<int>(servers.size()) > minServers + 3) {
        removeServer();
    }
}

/**
 * @brief Get the number of active servers
 * @return Number of currently active servers
 */
int LoadBalancer::getActiveServerCount() const {
    int activeCount = 0;
    for (const auto& server : servers) {
        if (server->getIsActive()) {
            activeCount++;
        }
    }
    return activeCount;
}

/**
 * @brief Get the total number of requests processed
 * @return Total requests processed by all servers
 */
int LoadBalancer::getTotalRequestsProcessed() const {
    return totalRequestsProcessed;
}

/**
 * @brief Get the average processing time across all servers
 * @return Average processing time per request
 */
double LoadBalancer::getAverageProcessingTime() const {
    if (totalRequestsProcessed == 0) return 0.0;
    return static_cast<double>(totalProcessingTime) / totalRequestsProcessed;
}

/**
 * @brief Get the overall system utilization
 * @return System utilization as percentage (0-100)
 */
double LoadBalancer::getSystemUtilization() const {
    if (servers.empty()) return 0.0;
    
    double totalUtilization = 0.0;
    int activeServers = 0;
    
    for (const auto& server : servers) {
        if (server->getIsActive()) {
            totalUtilization += server->getUtilization();
            activeServers++;
        }
    }
    
    // Return average utilization across all active servers
    return activeServers > 0 ? totalUtilization / activeServers : 0.0;
}

/**
 * @brief Get queue utilization
 * @return Queue utilization as percentage (0-100)
 */
double LoadBalancer::getQueueUtilization() const {
    return requestQueue.getUtilization();
}

/**
 * @brief Get server statistics
 * @return Vector of server statistics strings
 */
std::vector<std::string> LoadBalancer::getServerStats() const {
    std::vector<std::string> stats;
    
    for (const auto& server : servers) {
        std::stringstream ss;
        ss << "Server " << server->getServerID() 
           << " (" << server->getServerIP() << "): "
           << "Load: " << server->getCurrentLoad() << "/" << server->getMaxCapacity()
           << " (" << std::fixed << std::setprecision(1) << server->getUtilization() << "%)"
           << " | Processed: " << server->getTotalRequestsProcessed()
           << " | Active: " << (server->getIsActive() ? "Yes" : "No");
        stats.push_back(ss.str());
    }
    
    return stats;
}

/**
 * @brief Block an IP address across all components
 * @param ip IP address to block
 */
void LoadBalancer::blockIP(const std::string& ip) {
    requestQueue.blockIP(ip);
}

/**
 * @brief Unblock an IP address across all components
 * @param ip IP address to unblock
 */
void LoadBalancer::unblockIP(const std::string& ip) {
    requestQueue.unblockIP(ip);
}

/**
 * @brief Get the current queue size
 * @return Number of requests in the queue
 */
int LoadBalancer::getQueueSize() const {
    return requestQueue.getSize();
}

/**
 * @brief Check if the system is overloaded
 * @return True if system is overloaded, false otherwise
 */
bool LoadBalancer::isOverloaded() const {
    return getSystemUtilization() > 90.0 || getQueueUtilization() > 80.0;
} 