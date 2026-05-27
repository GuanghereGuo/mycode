library ieee;
use ieee.std_logic_1164.all;

entity exa4_1_xor is
port(
    A : in  std_logic;
    B : in  std_logic;
    C : out std_logic
);
end exa4_1_xor;

architecture rtl of exa4_1_xor is
begin
    C <= A xor B;
end rtl;
