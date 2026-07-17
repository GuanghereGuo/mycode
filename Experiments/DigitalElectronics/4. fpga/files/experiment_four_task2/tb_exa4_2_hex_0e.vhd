library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity tb_exa4_2_hex_0e is
end tb_exa4_2_hex_0e;

architecture sim of tb_exa4_2_hex_0e is
    type seg_table_t is array (0 to 15) of std_logic_vector(6 downto 0);
    constant expected : seg_table_t := (
        0  => "1000000",
        1  => "1111001",
        2  => "0100100",
        3  => "0110000",
        4  => "0011001",
        5  => "0010010",
        6  => "0000010",
        7  => "1111000",
        8  => "0000000",
        9  => "0010000",
        10 => "0001000",
        11 => "0000011",
        12 => "1000110",
        13 => "0100001",
        14 => "0000110",
        15 => "1111111"
    );
    signal data_in : std_logic_vector(3 downto 0) := (others => '0');
    signal seg_out : std_logic_vector(6 downto 0);
begin
    dut: entity work.exa4_2_hex_0e
        port map(data_in => data_in, seg_out => seg_out);

    process
    begin
        for i in 0 to 15 loop
            data_in <= std_logic_vector(to_unsigned(i, 4));
            wait for 10 ns;
            assert seg_out = expected(i) report "decoder output mismatch" severity error;
        end loop;
        wait;
    end process;
end sim;
