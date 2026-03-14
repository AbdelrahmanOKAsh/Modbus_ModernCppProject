/**************************************************************************************************************************** 
*                                        Author: Abdelrahman Gamal OKASHA                                                   *
*			                             Created: 9/3/2026                                                                  *
*			                             File: ModbusClient.hpp                                                             *
*			                             [ ModbusClient Module ]                                                            *
****************************************************************************************************************************/

#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "../Utils/ModbusCell.hpp"
#include "../Utils/Utils.hpp"
#include "ModbusClient.hpp"

/**
 * Namespace that contains whole project
 */
namespace MB
{
    /**
     * This class represent Modbus response, it allows
     * user to manipulate and display it in various ways.
     */
    class ModbusRequest
    {
        private:
            uint8_t _slaveID;
            utils::MBFunctionCode _functionCode;

            uint16_t _address;
            uint16_t _registersNumber;

            std::vector<ModbusCell> _values;

        public:
            
            ModbusRequest() = delete;

            /**
             * @brief
             * Constructs Request from raw data
             * @param inputData - Is vector of bytes that will be be interpreted,
            *whereas based on CRC parameter method performs CRC calculation and throws
            *exception if it is invalid
            * @throws ModbusException
            **/
            ModbusRequest(const std::vector<uint8_t> &inputData,bool CRC = false);

            /*
            * @description Constructs Request from raw data
            * @params inputData is a vector of bytes that will be interpreted
            * @throws ModbusException
            **/
            static ModbusRequest fromRaw(const std::vector<uint8_t> &inputData)
            {
                return ModbusRequest(inputData);
            }

            /*
            * @description Constructs Request from raw data and checks it's CRC
            * @params inputData is a vector of bytes that will be interpreted
            * @throws ModbusException
            * @note This methods performs CRC check that may throw ModbusException on
            * invalid CRC
            **/
            ModbusRequest fromRawCRC(const std::vector<uint8_t> &inputData)
            {
                return ModbusRequest(inputData, true);
            }

            

            /**
             * Copy constructor for the response.
             */
            ModbusRequest(const ModbusRequest &);

            /**
             * Equal operator for the response.
             */
            ModbusRequest &operator=(const ModbusRequest &);

            //! Returns string representation of object
            [[nodiscard]] std::string toString();

            //! Returns raw bytes representation of object, ready for modbus communication
            [[nodiscard]] std::vector<uint8_t> toRaw();

            //! Returns function type based on Modbus function code
            [[nodiscard]] utils::MBFunctionType functionType()
            {
                return utils::functionType(_functionCode);
            }
            
            //! Returns register type based on Modbus function code
            [[nodiscard]] utils::MBFunctionRegisters functionRegisters()
            {
                return utils::functionRegister(_functionCode);
            }

            [[nodiscard]] uint8_t slaveID() const { return _slaveID; }
            [[nodiscard]] utils::MBFunctionCode functionCode() const { return _functionCode; }
            [[nodiscard]] uint16_t registerAddress() const { return _address; }
            [[nodiscard]] uint16_t numberOfRegisters() const { return _registersNumber; }
            [[nodiscard]] const std::vector<ModbusCell> &registerValues() const { return _values; }

            void setSlaveId(uint8_t slaveId) { _slaveID = slaveId; }

            void setFunctionCode(utils::MBFunctionCode functionCode) {_functionCode = functionCode; }

            void setAddress(uint16_t address) { _address = address; }

            void setRegistersNumber(uint16_t registersNumber)
            {
                _registersNumber = registersNumber;
                _values.resize(registersNumber);
            }
            
            void setValues(const std::vector<ModbusCell> &values) { _values = values; }
    };
} // namespace MB
