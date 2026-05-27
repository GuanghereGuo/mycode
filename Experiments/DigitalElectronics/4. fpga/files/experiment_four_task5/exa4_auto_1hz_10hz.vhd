-- 1Hz / 10Hz 自动切换tick发生器
-- loop_end来一次，速度在1Hz和10Hz之间切换一次

library ieee;
use ieee.std_logic_1164.all;

entity exa4_auto_1hz_10hz is
port(
    clk50     : in  std_logic;  -- 50MHz主时钟
    rst       : in  std_logic;  -- 低电平复位
    loop_end  : in  std_logic;  -- 一轮结束信号，接M12计数器的cout
    tick      : out std_logic;  -- 输出给M12计数器的en
    speed_sel : out std_logic   -- 可选输出，0=1Hz，1=10Hz，可以接LED观察
);
end exa4_auto_1hz_10hz;

architecture rtl of exa4_auto_1hz_10hz is

-- 如果开发板时钟是50MHz：
-- 1Hz 需要 50,000,000 个clk周期产生一次tick
-- 10Hz 需要 5,000,000 个clk周期产生一次tick
constant DIV_1HZ  : integer := 50000000;
constant DIV_10HZ : integer := 5000000;

signal cnt    : integer range 0 to DIV_1HZ - 1 := 0;
signal mode   : std_logic := '0';  -- 0表示1Hz，1表示10Hz
signal tick_r : std_logic := '0';

begin

process(clk50, rst)
    variable limit_v : integer;
begin
    if rst = '0' then
        cnt    <= 0;
        mode   <= '0';  -- 复位后先用1Hz
        tick_r <= '0';

    elsif rising_edge(clk50) then
        tick_r <= '0';

        -- 一轮显示结束后，切换下一轮速度
        if loop_end = '1' then
            mode <= not mode;
            cnt  <= 0;

        else
            -- 根据当前模式选择分频系数
            if mode = '0' then
                limit_v := DIV_1HZ - 1;
            else
                limit_v := DIV_10HZ - 1;
            end if;

            -- 到达计数值后，产生一个clk宽度的tick
            if cnt >= limit_v then
                cnt    <= 0;
                tick_r <= '1';
            else
                cnt <= cnt + 1;
            end if;
        end if;
    end if;
end process;

tick <= tick_r;
speed_sel <= mode;

end rtl;