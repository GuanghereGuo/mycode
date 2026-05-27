-- M12计数器：0~11循环，用于显示 0661FEEL0938 共12位
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity exa4_3_2 is
port(
    clk  : in  std_logic;
    rst  : in  std_logic;
    en   : in  std_logic;  -- 新增：计数使能，tick=1时才加1
    dout : out std_logic_vector(3 downto 0);
    cout : out std_logic
);
end exa4_3_2;

architecture one of exa4_3_2 is
signal Q1 : unsigned(3 downto 0) := (others => '0');
begin

process(clk, rst)
begin
    if rst = '0' then
        Q1 <= (others => '0');
        cout <= '0';

    elsif rising_edge(clk) then
        cout <= '0';

        if en = '1' then
            -- 计到11后，下一次回到0，同时cout输出1个50MHz时钟周期
            if Q1 = to_unsigned(11, 4) then
                Q1 <= (others => '0');
                cout <= '1';
            else
                Q1 <= Q1 + 1;
            end if;
        end if;
    end if;
end process;

dout <= std_logic_vector(Q1);

end one;