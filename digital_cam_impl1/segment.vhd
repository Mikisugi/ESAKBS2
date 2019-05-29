library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;

entity segment is
  Port (
    avg_colour : in std_logic_vector(11 downto 0);
    hex1 : out std_logic_vector(6 downto 0);
    hex2 : out std_logic_vector(6 downto 0);
    hex3 : out std_logic_vector(6 downto 0);
    hex4 : out std_logic_vector(6 downto 0);
    hex5 : out std_logic_vector(6 downto 0);
    hex6 : out std_logic_vector(6 downto 0)
  );  
end segment;

architecture segmentout of segment is
begin
	hex1 <=		"1000000" when avg_colour(3 downto 0) = "0000" else
					"1111001" when avg_colour(3 downto 0) = "0001" else
					"0100100" when avg_colour(3 downto 0) = "0010" else
					"0110000" when avg_colour(3 downto 0) = "0011" else
					"0011001" when avg_colour(3 downto 0) = "0100" else
					"0010010" when avg_colour(3 downto 0) = "0101" else
					"0000011" when avg_colour(3 downto 0) = "0110" else
					"1111000" when avg_colour(3 downto 0) = "0111" else
					"0000000" when avg_colour(3 downto 0) = "1000" else
					"0011000" when avg_colour(3 downto 0) = "1001" else
					"1000000" when avg_colour(3 downto 0) = "1010" else
					"1111001" when avg_colour(3 downto 0) = "1011" else
					"0100100" when avg_colour(3 downto 0) = "1100" else
					"0110000" when avg_colour(3 downto 0) = "1101" else
					"0011001" when avg_colour(3 downto 0) = "1110" else
					"0010010" when avg_colour(3 downto 0) = "1111" else
					"0000110";
					
	hex2 <=		"1111001" when avg_colour(3 downto 0) = "1010" else
					"1111001" when avg_colour(3 downto 0) = "1011" else
					"1111001" when avg_colour(3 downto 0) = "1100" else
					"1111001" when avg_colour(3 downto 0) = "1101" else
					"1111001" when avg_colour(3 downto 0) = "1110" else
					"1111001" when avg_colour(3 downto 0) = "1111" else
					"1000000";
					
	hex3 <=		"1000000" when avg_colour(7 downto 4) = "0000" else
					"1111001" when avg_colour(7 downto 4) = "0001" else
					"0100100" when avg_colour(7 downto 4) = "0010" else
					"0110000" when avg_colour(7 downto 4) = "0011" else
					"0011001" when avg_colour(7 downto 4) = "0100" else
					"0010010" when avg_colour(7 downto 4) = "0101" else
					"0000011" when avg_colour(7 downto 4) = "0110" else
					"1111000" when avg_colour(7 downto 4) = "0111" else
					"0000000" when avg_colour(7 downto 4) = "1000" else
					"0011000" when avg_colour(7 downto 4) = "1001" else
					"1000000" when avg_colour(7 downto 4) = "1010" else
					"1111001" when avg_colour(7 downto 4) = "1011" else
					"0100100" when avg_colour(7 downto 4) = "1100" else
					"0110000" when avg_colour(7 downto 4) = "1101" else
					"0011001" when avg_colour(7 downto 4) = "1110" else
					"0010010" when avg_colour(7 downto 4) = "1111" else
					"0000110";
					
	hex4 <=		"1111001" when avg_colour(7 downto 4) = "1010" else
					"1111001" when avg_colour(7 downto 4) = "1011" else
					"1111001" when avg_colour(7 downto 4) = "1100" else
					"1111001" when avg_colour(7 downto 4) = "1101" else
					"1111001" when avg_colour(7 downto 4) = "1110" else
					"1111001" when avg_colour(7 downto 4) = "1111" else
					"1000000";
					
	hex5 <=		"1000000" when avg_colour(11 downto 8) = "0000" else
					"1111001" when avg_colour(11 downto 8) = "0001" else
					"0100100" when avg_colour(11 downto 8) = "0010" else
					"0110000" when avg_colour(11 downto 8) = "0011" else
					"0011001" when avg_colour(11 downto 8) = "0100" else
					"0010010" when avg_colour(11 downto 8) = "0101" else
					"0000011" when avg_colour(11 downto 8) = "0110" else
					"1111000" when avg_colour(11 downto 8) = "0111" else
					"0000000" when avg_colour(11 downto 8) = "1000" else
					"0011000" when avg_colour(11 downto 8) = "1001" else
					"1000000" when avg_colour(11 downto 8) = "1010" else
					"1111001" when avg_colour(11 downto 8) = "1011" else
					"0100100" when avg_colour(11 downto 8) = "1100" else
					"0110000" when avg_colour(11 downto 8) = "1101" else
					"0011001" when avg_colour(11 downto 8) = "1110" else
					"0010010" when avg_colour(11 downto 8) = "1111" else
					"0000110";
					
	hex6 <=		"1111001" when avg_colour(11 downto 8) = "1010" else
					"1111001" when avg_colour(11 downto 8) = "1011" else
					"1111001" when avg_colour(11 downto 8) = "1100" else
					"1111001" when avg_colour(11 downto 8) = "1101" else
					"1111001" when avg_colour(11 downto 8) = "1110" else
					"1111001" when avg_colour(11 downto 8) = "1111" else
					"1000000";
end segmentout;