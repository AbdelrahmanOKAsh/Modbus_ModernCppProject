src = ../APP/Main.cpp ../ModbusClient/ModbusClient.cpp ../ModbusServer/ModbusServer.cpp ../ModbusException/ModbusException.cpp ../CRC/CRC.cpp 
CC  = g++
Flag = -o
Output = APP.exe


$(Output)	:	$(src)
			$(CC) $^ $(Flag) $@ 

run			: 
	@./$(Output)

rebuild		:
	@rm $(Output) && make

clean		:		
	@rm $(Output)