LIBRARY IEEE;    
USE IEEE.STD_LOGIC_1164.ALL;  
USE IEEE.STD_LOGIC_UNSIGNED.ALL;  
ENTITY time2 IS  
    PORT ( clk,RST  : IN STD_LOGIC;                    
           DOUT : OUT STD_LOGIC_VECTOR (4 DOWNTO 0);  -- 五位计数  
           COUT : OUT STD_LOGIC);                         -- 进位位  
END time2;  



ARCHITECTURE fwm OF time2 IS  
    SIGNAL Q1 : STD_LOGIC_VECTOR (4 DOWNTO 0);   
BEGIN 
	PROCESS(clk,RST) 
	BEGIN 
		IF RST = '0' THEN 
			Q1<=(OTHERS => '0'); COUT<= '0'; 
		ELSIF  clk'EVENT AND clk='1' THEN 
			Q1<=Q1+1; 
			COUT<= '0'; 
			IF Q1 >= "01010" THEN 
				Q1<=(OTHERS => '0'); COUT<= '1'; 
			END IF; 
		END IF; 
	END PROCESS; 
	DOUT<=Q1 ; 
END fwm; 