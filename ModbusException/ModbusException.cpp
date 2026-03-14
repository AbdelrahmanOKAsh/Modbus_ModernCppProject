/**************************************************************************************************************************** 
*                                        Author: Abdelrahman Gamal OKASHA                                                   *
*			                             Created: 9/3/2026                                                                  *
*			                             File: ModbusException.cpp                                                          *
*			                             [ ModbusException Module ]                                                         *
****************************************************************************************************************************/


#include "ModbusException.hpp"
#include "../Utils/Utils.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>

using namespace MB;

// Construct Modbus exception from raw data
ModbusException::ModbusException (const std::vector<uint8_t> &inputData,bool checkCRC) 
{
    const std::size_t PACKET_SIZE_WITHOUT_CRC = 3;
    const std::size_t PACKET_SIZE_WITH_CRC    = 5;

    if (inputData.size() !=((checkCRC) ? PACKET_SIZE_WITH_CRC : PACKET_SIZE_WITHOUT_CRC))
    {
        _slaveId      = 0xFF;
        _functionCode = utils::Undefined;
        _validSlave   = false;
        _errorCode    = utils::InvalidByteOrder;
        return;
    }

    _slaveId      = inputData[0];
    _functionCode = static_cast<utils::MBFunctionCode>(0b01111111 & inputData[1]);
    _validSlave   = true;
    _errorCode    = static_cast<utils::MBErrorCode>(inputData[2]);

    if (checkCRC)
    {
        const auto actualCrc = *reinterpret_cast<const uint16_t *>(&inputData[3]);
        const uint16_t calculatedCRC = MB::CRC::calculateCRC(inputData, PACKET_SIZE_WITHOUT_CRC);

        if (actualCrc != calculatedCRC) {
            _errorCode = utils::ErrorCodeCRCError;
        }
    }
}

// Returns string representation of exception
std::string ModbusException::toString()
{
    std::string res;
    res += "Error on slave ";
    if (_validSlave)
        res += std::to_string(_slaveId);
    
    else
        res += "Unknown";

    res += " - ";
    res += utils::mbErrorCodeToStr(_errorCode);

    if (_functionCode != MB::utils::Undefined)
    {
        res += " ( on function: ";
        res += utils::mbFunctionToStr(_functionCode);
        res += " )";
    }
    return res;
}

std::vector<uint8_t> ModbusException::toRaw()
{
    std::vector<uint8_t> result(3);

    result[0] = _slaveId;
    result[1] = static_cast<uint8_t>(_errorCode | 0b10000000);
    result[2] = static_cast<uint8_t>(_functionCode);

    return result;
}
