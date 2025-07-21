/**
 * @file Request.cpp
 * @brief Implementation file for the Request class
 * @author Your Name
 * @date 2024
 * @version 1.0
 */

#include "Request.h"
#include <chrono>

/**
 * @brief Default constructor
 * 
 * Initializes a request with default values
 */
Request::Request() : clientIP("0.0.0.0"), requestType("GET"), priority(5), 
                     processingTime(10), arrivalTime(std::chrono::steady_clock::now()), requestID(0) {
}

/**
 * @brief Parameterized constructor
 * @param ip Client IP address
 * @param type Type of request
 * @param prio Priority level (1-10)
 * @param procTime Processing time in clock cycles
 * @param id Unique request identifier
 */
Request::Request(const std::string& ip, const std::string& type, int prio, int procTime, int id)
    : clientIP(ip), requestType(type), priority(prio), processingTime(procTime), 
      arrivalTime(std::chrono::steady_clock::now()), requestID(id) {
}

/**
 * @brief Get the client IP address
 * @return Client IP as string
 */
std::string Request::getClientIP() const {
    return clientIP;
}

/**
 * @brief Get the request type
 * @return Request type as string
 */
std::string Request::getRequestType() const {
    return requestType;
}

/**
 * @brief Get the priority level
 * @return Priority level (1-10)
 */
int Request::getPriority() const {
    return priority;
}

/**
 * @brief Get the processing time
 * @return Processing time in clock cycles
 */
int Request::getProcessingTime() const {
    return processingTime;
}

/**
 * @brief Get the arrival time
 * @return Arrival time as time_point
 */
std::chrono::steady_clock::time_point Request::getArrivalTime() const {
    return arrivalTime;
}

/**
 * @brief Get the request ID
 * @return Unique request identifier
 */
int Request::getRequestID() const {
    return requestID;
}

/**
 * @brief Set the processing time
 * @param time New processing time in clock cycles
 */
void Request::setProcessingTime(int time) {
    processingTime = time;
}

/**
 * @brief Get the time spent waiting in queue
 * @return Wait time in milliseconds
 */
int Request::getWaitTime() const {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - arrivalTime);
    return static_cast<int>(duration.count());
} 