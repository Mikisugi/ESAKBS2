library ieee;
use ieee.std_logic_1164.all;
--use ieee.std_logic_arith.all;
--use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity RGB is
	Port ( 
		Din   : in  std_logic_vector (11 downto 0);  -- niveau de gris du pixels sur 8 bits
		Nblank : in  std_logic;                      -- signal indique les zone d'affichage, hors la zone d'affichage
																	-- les trois couleurs prendre 0
		R,G,B   : out  std_logic_vector (7 downto 0) -- les trois couleurs sur 10 bits
	);      
end RGB;

architecture Behavioral of RGB is

begin

	R <= Din(11 downto 8) & Din(11 downto 8) when Nblank='1' else "00000000";
	G <= Din(7 downto 4)  & Din(7 downto 4)  when Nblank='1' else "00000000";
	B <= Din(3 downto 0)  & Din(3 downto 0)  when Nblank='1' else "00000000";

end Behavioral;
