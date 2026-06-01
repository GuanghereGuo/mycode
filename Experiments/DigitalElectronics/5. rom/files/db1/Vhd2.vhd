LIBRARY IEEE; 
USE IEEE.STD_LOGIC_1164.ALL; 
ENTITY Vhd2 IS 
PORT(clk:IN STD_LOGIC; 
clk_out:OUT STD_LOGIC); 
END Vhd2; 
ARCHITECTURE fwm OF Vhd2 IS 
CONSTANT m : INTEGER:= 25000000; 
SIGNAL tmp :STD_LOGIC; 
BEGIN --50M 分频到 1Hz 时=25000000。  
PROCESS(clk, tmp) 
VARIABLE cout : INTEGER:=0; 
BEGIN 
IF clk'EVENT AND clk='1' THEN 
cout:=cout+1; --计数器+1 
IF cout<=m THEN tmp<='0'; --计数小于等于 25000000，输出 0 
ELSIF cout<m*2 THEN tmp<='1'; --计数小于 50000000，输出 1 
ELSE cout:=0; 
END IF; 
END IF; 
END PROCESS; 
clk_out<=tmp; 
END fwm; 