library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity exa4_3_counter_0e is
port(
    clk  : in  std_logic;
    rst  : in  std_logic;
    DOUT : out std_logic_vector(3 downto 0);
    COUT : out std_logic
);
end exa4_3_counter_0e;

architecture rtl of exa4_3_counter_0e is
    signal count_q : unsigned(3 downto 0) := (others => '0');
    signal cout_q  : std_logic := '0';
begin
    process(clk, rst)
    begin
        if rst = '0' then
            count_q <= (others => '0');
            cout_q <= '0';
        elsif rising_edge(clk) then
            if count_q = to_unsigned(14, 4) then
                count_q <= (others => '0');
                cout_q <= '1';
            else
                count_q <= count_q + 1;
                cout_q <= '0';
            end if;
        end if;
    end process;

    DOUT <= std_logic_vector(count_q);
    COUT <= cout_q;
end rtl;
