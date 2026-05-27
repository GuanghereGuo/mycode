library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity tb_exa4_3_counter_0e is
end tb_exa4_3_counter_0e;

architecture sim of tb_exa4_3_counter_0e is
    signal clk  : std_logic := '0';
    signal rst  : std_logic := '0';
    signal DOUT : std_logic_vector(3 downto 0);
    signal COUT : std_logic;
begin
    dut: entity work.exa4_3_counter_0e
        port map(clk => clk, rst => rst, DOUT => DOUT, COUT => COUT);

    clk <= not clk after 5 ns;

    process
    begin
        wait for 12 ns;
        assert DOUT = "0000" report "reset did not clear counter" severity error;
        rst <= '1';

        for i in 1 to 14 loop
            wait until rising_edge(clk);
            wait for 1 ns;
            assert DOUT = std_logic_vector(to_unsigned(i, 4)) report "counter sequence mismatch" severity error;
            assert COUT = '0' report "cout asserted before E rollover" severity error;
        end loop;

        wait until rising_edge(clk);
        wait for 1 ns;
        assert DOUT = "0000" report "counter did not wrap after E" severity error;
        assert COUT = '1' report "cout not asserted on E rollover" severity error;

        wait until rising_edge(clk);
        wait for 1 ns;
        assert DOUT = "0001" report "counter did not continue after rollover" severity error;
        assert COUT = '0' report "cout stayed asserted after rollover" severity error;
        wait;
    end process;
end sim;
