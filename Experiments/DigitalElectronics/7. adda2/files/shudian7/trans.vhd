library ieee;
use ieee.std_logic_1164.all;
ENTITY trans IS
port (Data_IN:in std_logic_vector (7 downto 0);
dis_out1:out std_logic_vector (6 downto 0);
dis_out2:out std_logic_vector (6 downto 0));
end trans;
ARCHITECTURE fwn OF trans IS BEGIN
PROCESS (Data_IN) BEGIN
CASE Data_IN IS
	WHEN"11111111"	=>dis_out1<="1000000";dis_out2<="0000000";--高电位80
	WHEN"00000000"	=>dis_out1<="0010000";dis_out2<="0110000";--低电位39
	WHEN"01111111"	=>dis_out1<="1000000";dis_out2<="0000110";--0电位E0
	WHEN"10000000"	=>dis_out1<="1000000";dis_out2<="0000110";--0电位E0
	WHEN"01111110"	=>dis_out1<="1000000";dis_out2<="0000110";--0电位E0
	WHEN others		=>dis_out1<="0111110";dis_out2<="0111110";--None
END CASE;
END PROCESS;
END fwn; 