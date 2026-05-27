library ieee;
use ieee.std_logic_1164.all;

entity exa4_4_divider_1hz_10hz is
generic(
    HALF_PERIOD_1HZ  : positive := 25000000;
    HALF_PERIOD_10HZ : positive := 2500000
);
port(
    clk50    : in  std_logic;
    clk_1hz  : out std_logic;
    clk_10hz : out std_logic
);
end exa4_4_divider_1hz_10hz;

architecture rtl of exa4_4_divider_1hz_10hz is
    signal cnt_1hz  : integer range 0 to HALF_PERIOD_1HZ - 1 := 0;
    signal cnt_10hz : integer range 0 to HALF_PERIOD_10HZ - 1 := 0;
    signal out_1hz  : std_logic := '0';
    signal out_10hz : std_logic := '0';
begin
    process(clk50)
    begin
        if rising_edge(clk50) then
            if cnt_1hz = HALF_PERIOD_1HZ - 1 then
                cnt_1hz <= 0;
                out_1hz <= not out_1hz;
            else
                cnt_1hz <= cnt_1hz + 1;
            end if;

            if cnt_10hz = HALF_PERIOD_10HZ - 1 then
                cnt_10hz <= 0;
                out_10hz <= not out_10hz;
            else
                cnt_10hz <= cnt_10hz + 1;
            end if;
        end if;
    end process;

    clk_1hz <= out_1hz;
    clk_10hz <= out_10hz;
end rtl;
