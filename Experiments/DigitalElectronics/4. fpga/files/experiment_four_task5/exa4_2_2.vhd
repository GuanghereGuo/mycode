-- 七段码译码器：显示 0661FEEL0938
library ieee;
use ieee.std_logic_1164.all;

entity exa4_2_2 is
port(
    BCD_IN : in  std_logic_vector(3 downto 0);
    SG_OUT : out std_logic_vector(6 downto 0)
);
end exa4_2_2;

architecture one of exa4_2_2 is
begin
process(BCD_IN)
begin
    case BCD_IN is
        when "0000" => SG_OUT <= "1000000"; -- 0
        when "0001" => SG_OUT <= "0000010"; -- 6
        when "0010" => SG_OUT <= "0000010"; -- 6
        when "0011" => SG_OUT <= "1111001"; -- 1
        when "0100" => SG_OUT <= "0001110"; -- F
        when "0101" => SG_OUT <= "0000110"; -- E
        when "0110" => SG_OUT <= "0000110"; -- E
        when "0111" => SG_OUT <= "1000111"; -- L
        when "1000" => SG_OUT <= "1000000"; -- 0
        when "1001" => SG_OUT <= "0010000"; -- 9
        when "1010" => SG_OUT <= "0110000"; -- 3
        when "1011" => SG_OUT <= "0000000"; -- 8
        when others => SG_OUT <= "1111111"; -- 灭灯
    end case;
end process;
end one;