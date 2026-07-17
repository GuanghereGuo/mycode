--5M分频器
LIBRARY IEEE; 
USE IEEE.STD_LOGIC_1164.ALL; 
ENTITY exa4_4_2 IS 
PORT(clk:IN STD_LOGIC; 
clk_out:OUT STD_LOGIC); 
END exa4_4_2; 
ARCHITECTURE fwm OF exa4_4_2 IS 
CONSTANT m : INTEGER:= 2500000; 
SIGNAL tmp :STD_LOGIC; 
BEGIN   
PROCESS(clk, tmp) 
VARIABLE cout : INTEGER:=0; 
BEGIN 
IF clk'EVENT AND clk='1' THEN 
cout:=cout+1; --计数器+1 
IF cout<=m THEN tmp<='0'; --计数小于等于 2500000，输出 0 
ELSIF cout<m*2 THEN tmp<='1'; --计数小于 5000000，输出 1 
ELSE cout:=0; 
END IF; 
END IF; 
END PROCESS; 
clk_out<=tmp; 
END fwm;