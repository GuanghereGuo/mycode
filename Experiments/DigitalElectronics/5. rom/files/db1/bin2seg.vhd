library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity bin2seg is
    Port (
        bin_input : in  STD_LOGIC_VECTOR(3 downto 0);  -- 4位二进制输入
        seg_output : out STD_LOGIC_VECTOR(6 downto 0)  -- 七段数码管输出(abcdefg)
    );
end bin2seg;

architecture Behavioral of bin2seg is
begin
    process(bin_input)
    begin
        case bin_input is
            -- 共阳极数码管段码表（低电平有效）
            when "1010" => seg_output <= "0100100"; -- 2
				when "0000" => seg_output <= "0010010"; -- 5
            when "0001" => seg_output <= "0110000"; -- 3
            when "0010" => seg_output <= "0010000"; -- 9
            when "0011" => seg_output <= "0001110"; -- F
            when "0100" => seg_output <= "1000111"; -- L
            when "0101" => seg_output <= "0000110"; -- E
            when "0110" => seg_output <= "0001100"; -- P
            when "0111" => seg_output <= "0010000"; -- 9
            when "1000" => seg_output <= "0000000"; -- 8
            when "1001" => seg_output <= "1000000"; -- 0
            when others => seg_output <= "1111111"; -- 全灭（保护，正常不出现）
        end case;
    end process;
end Behavioral;

