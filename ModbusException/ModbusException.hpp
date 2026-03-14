/**************************************************************************************************************************** 
*                                        Author: Abdelrahman Gamal OKASHA                                                   *
*			                             Created: 9/3/2026                                                                  *
*			                             File: ModbusException.hpp                                                          *
*			                             [ ModbusException Module ]                                                         *
****************************************************************************************************************************/

#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>
#include "../Utils/Utils.hpp"

/**
 * Namespace that contains whole project
 */
namespace MB
{
    /**
     * Thic class represent Modbus exception and is
     * derived form std::exception. It is just a wrapper
     * around standard error codes and some custom codes.
     */
    class ModbusException : public std::exception
    {
        private:
            uint8_t _slaveId;
            bool _validSlave;
            utils::MBErrorCode _errorCode;
            utils::MBFunctionCode _functionCode;

        public:
            ModbusException() = delete;

            /**
             * @brief Constructs Exception from raw data
             * @param inputData is vector of bytes that will be be interpreted
             * @param CRC based on this param method performs CRC calculation and throws
             * */
            explicit ModbusException(const std::vector<uint8_t> &inputData,bool CRC = false) noexcept;

            //! Constructs Exception based on error code, function code and slaveId
            explicit ModbusException(utils::MBErrorCode errorCode, uint8_t slaveId = 0xFF,utils::MBFunctionCode functionCode = utils::Undefined)
                : _slaveId(slaveId), _validSlave(true), _errorCode(errorCode),
                _functionCode(functionCode)
                {

                }

            /*
            * Check if there is Modbus error in raw modbus input
            * checked at ModbusRequest/ModbusResponse
            * */
            static bool exist(const std::vector<uint8_t> &inputData)
            {
                if (inputData.size() < 2) // TODO Figure out better solution to such mistake
                    return false;

                return inputData[1] & 0b10000000;
            }


            /*
            *  Returns attached SlaveID
            *  NOTE: it is worth to check if slaveId is specified with isSlaveValid()
            * */
            [[nodiscard]] uint8_t slaveID() { return _slaveId; }


            //! Checks if SlaveID is specified
            [[nodiscard]] bool isSlaveValid() { return _validSlave; }


            //! Sets SlaveID
            void setSlaveID(uint8_t slaveId)
            {
                _validSlave = true;
                _slaveId    = slaveId;
            }


            //! Returns detected error code
            [[nodiscard]] utils::MBErrorCode getErrorCode() { return _errorCode; }


            //! Returns string representation of object
            [[nodiscard]] std::string toString();


            /**
             * @brief Convert Modbus request object into the vector of bytes,
             * representing modbus frame, ready to be sent over HW interface
             * @throws ModbusException - if modbus data in the object is invalid
             */
            [[nodiscard]] std::vector<uint8_t> toRaw();


            [[nodiscard]] utils::MBFunctionCode functionCode()
            {
                return _functionCode;
            }

            void setFunctionCode(utils::MBFunctionCode functionCode)
            {
                _functionCode = functionCode;
            }
    };
} // namespace MB
