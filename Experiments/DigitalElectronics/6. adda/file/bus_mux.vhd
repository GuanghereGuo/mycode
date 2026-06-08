LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY bus_mux IS
PORT (
    -- 4 路 8 位输入总线
    bus0  : IN  STD_LOGIC_VECTOR(7 DOWNTO 0);
    bus1  : IN  STD_LOGIC_VECTOR(7 DOWNTO 0);
    bus2  : IN  STD_LOGIC_VECTOR(7 DOWNTO 0);
    bus3  : IN  STD_LOGIC_VECTOR(7 DOWNTO 0);
    
    -- 两个独立分开的选择输入（满足你的要求）
    sel0  : IN  STD_LOGIC;
    sel1  : IN  STD_LOGIC;
    
    -- 8 位输出总线
    dout  : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
);
END bus_mux;

ARCHITECTURE Behavioral OF bus_mux IS
BEGIN
    -- 组合逻辑：根据 sel0、sel1 选择输出总线
    PROCESS(bus0, bus1, bus2, bus3, sel0, sel1)
    BEGIN
        IF sel1 = '0' AND sel0 = '0' THEN
            dout <= bus0;
        ELSIF sel1 = '0' AND sel0 = '1' THEN
            dout <= bus1;
        ELSIF sel1 = '1' AND sel0 = '0' THEN
            dout <= bus2;
        ELSIF sel1 = '1' AND sel0 = '1' THEN
            dout <= bus3;
        ELSE
            dout <= (OTHERS => '0');
        END IF;
    END PROCESS;
END Behavioral;