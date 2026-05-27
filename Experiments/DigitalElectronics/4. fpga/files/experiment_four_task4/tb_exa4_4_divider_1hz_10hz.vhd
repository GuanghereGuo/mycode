library ieee;
use ieee.std_logic_1164.all;

entity tb_exa4_4_divider_1hz_10hz is
end tb_exa4_4_divider_1hz_10hz;

architecture sim of tb_exa4_4_divider_1hz_10hz is
    signal clk50    : std_logic := '0';
    signal clk_1hz  : std_logic;
    signal clk_10hz : std_logic;
begin
    dut: entity work.exa4_4_divider_1hz_10hz
        generic map(
            HALF_PERIOD_1HZ  => 4,
            HALF_PERIOD_10HZ => 2
        )
        port map(
            clk50    => clk50,
            clk_1hz  => clk_1hz,
            clk_10hz => clk_10hz
        );

    clk50 <= not clk50 after 5 ns;

    process
    begin
        wait for 1 ns;
        assert clk_1hz = '0' report "1Hz output should start low" severity error;
        assert clk_10hz = '0' report "10Hz output should start low" severity error;

        wait until rising_edge(clk50);
        wait until rising_edge(clk50);
        wait until rising_edge(clk50);
        wait for 1 ns;
        assert clk_10hz = '1' report "10Hz test divider did not toggle after 2 cycles" severity error;
        assert clk_1hz = '0' report "1Hz test divider toggled too early" severity error;

        wait until rising_edge(clk50);
        wait until rising_edge(clk50);
        wait for 1 ns;
        assert clk_10hz = '0' report "10Hz test divider did not toggle back" severity error;
        assert clk_1hz = '1' report "1Hz test divider did not toggle after 4 cycles" severity error;
        wait;
    end process;
end sim;
