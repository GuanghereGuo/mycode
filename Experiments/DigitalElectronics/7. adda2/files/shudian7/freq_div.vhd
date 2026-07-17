LIBRARY IEEE;
USE IEEE. STD_LOGIC_1164.ALL;
USE IEEE. STD_LOGIC_ARITH. ALL;
USE IEEE. STD_LOGIC_UNSIGNED. ALL;
ENTITY freq_div IS

PORT (
clk: IN STD_LOGIC; 
clk_div_2: OUT STD_LOGIC; 
clk_div_4: OUT STD_LOGIC;
clk_div_8: OUT STD_LOGIC); 
END freq_div;
ARCHITECTURE clk_div_behavior OF freq_div IS 
SIGNAL counter: STD_LOGIC_VECTOR (2 DOWNTO 0); 
BEGIN
PROCESS(clk) 
BEGIN
IF(clk'EVENT AND clk='1')THEN 
IF(counter="111")THEN counter<="000"; 
ELSE counter<=counter+1; 
END IF;
END IF; 
END PROCESS;
clk_div_2<=NOT counter(0); 
clk_div_4<=NOT counter(1);
clk_div_8<=NOT counter(2); 
END clk_div_behavior;