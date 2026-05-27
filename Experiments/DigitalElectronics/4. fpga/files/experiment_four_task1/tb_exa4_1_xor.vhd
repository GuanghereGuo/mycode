library ieee;
use ieee.std_logic_1164.all;

entity tb_exa4_1_xor is
end tb_exa4_1_xor;

architecture sim of tb_exa4_1_xor is
    signal A : std_logic := '0';
    signal B : std_logic := '0';
    signal C : std_logic;
begin
    dut: entity work.exa4_1_xor
        port map(A => A, B => B, C => C);

    process
    begin
        A <= '0'; B <= '0'; wait for 10 ns; assert C = '0' report "00 failed" severity error;
        A <= '0'; B <= '1'; wait for 10 ns; assert C = '1' report "01 failed" severity error;
        A <= '1'; B <= '0'; wait for 10 ns; assert C = '1' report "10 failed" severity error;
        A <= '1'; B <= '1'; wait for 10 ns; assert C = '0' report "11 failed" severity error;
        wait;
    end process;
end sim;
