/**************************************************************************************************************************** 
*                                        Author: Abdelrahman Gamal OKASHA                                                   *
*			                             Created: 9/3/2026                                                                  *
*			                             File: CRC.hpp                                                                      *
*			                             [ CRC Module ]                                                                     *
****************************************************************************************************************************/

#pragma once

#include <cstdint>
//#include <optional>
#include <vector>

//! This namespace contains functions used for CRC calculation
namespace MB::CRC
{
    //! Calculates CRC based on the input buffer - C style
    uint16_t calculateCRC(const uint8_t *buff, std::size_t len);

    uint16_t calculateCRC(const std::vector<uint8_t> &buffer, std::size_t len = 0) 
{
    // If len is 0 or exceeds buffer size, use the whole buffer.
    // If you actually need to support len = 0, use std::numeric_limits<std::size_t>::max()
    std::size_t bufferLength = (len == 0 || len > buffer.size()) ? buffer.size() : len;

    return calculateCRC(buffer.data(), bufferLength);
}

/*
    //! Calculate CRC based on the input vector of bytes
    uint16_t calculateCRC(const std::vector<uint8_t> &buffer,std::optional<std::size_t> len = std::nullopt)
    {
        std::size_t bufferLength = buffer.size();
        if (len.has_value() && bufferLength >= *len)
        {
            bufferLength = *len;
        }

        return calculateCRC(static_cast<const uint8_t *>(&(*buffer.begin())), bufferLength);
    }
*/

}; // namespace MB::CRC
