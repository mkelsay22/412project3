/**
 * @file Request.h
 * @brief Header file for the Request class
 * @author Your Name
 * @date 2024
 * @version 1.0
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <chrono>

/**
 * @class Request
 * @brief Represents a web request with various properties
 * 
 * This class encapsulates all the information needed for a web request,
 * including client IP, request type, priority, and timing information.
 */
class Request {
private:
    std::string clientIP;           ///< IP address of the client making the request
    std::string requestType;        ///< Type of request (GET, POST, etc.)
    int priority;                   ///< Priority level of the request (1-10)
    int processingTime;             ///< Estimated processing time in clock cycles
    std::chrono::steady_clock::time_point arrivalTime; ///< When the request arrived
    int requestID;                  ///< Unique identifier for the request

public:
    /**
     * @brief Default constructor
     */
    Request();

    /**
     * @brief Parameterized constructor
     * @param ip Client IP address
     * @param type Type of request
     * @param prio Priority level (1-10)
     * @param procTime Processing time in clock cycles
     * @param id Unique request identifier
     */
    Request(const std::string& ip, const std::string& type, int prio, int procTime, int id);

    /**
     * @brief Get the client IP address
     * @return Client IP as string
     */
    std::string getClientIP() const;

    /**
     * @brief Get the request type
     * @return Request type as string
     */
    std::string getRequestType() const;

    /**
     * @brief Get the priority level
     * @return Priority level (1-10)
     */
    int getPriority() const;

    /**
     * @brief Get the processing time
     * @return Processing time in clock cycles
     */
    int getProcessingTime() const;

    /**
     * @brief Get the arrival time
     * @return Arrival time as time_point
     */
    std::chrono::steady_clock::time_point getArrivalTime() const;

    /**
     * @brief Get the request ID
     * @return Unique request identifier
     */
    int getRequestID() const;

    /**
     * @brief Set the processing time
     * @param time New processing time in clock cycles
     */
    void setProcessingTime(int time);

    /**
     * @brief Get the time spent waiting in queue
     * @return Wait time in milliseconds
     */
    int getWaitTime() const;
};

#endif // REQUEST_H 