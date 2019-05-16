library ieee;
use ieee.std_logic_1164.ALL;
--use ieee.std_logic_arith.ALL;
--use ieee.std_logic_unsigned.ALL;
use ieee.numeric_std.ALL;

entity Colour_Recognition is
  Port (
    clk_i 		: in  std_logic;
	 dpixel 		: in std_logic_vector (11 downto 0);
    address 	: in std_logic_vector (16 downto 0);
	 colour		: out std_logic_vector (11 downto 0)
  );  
end Colour_Recognition;

architecture Recognize of Colour_Recognition is
--
---- array voor het uitrekenen van de gemiddelde kleur
--type colourInt is array (0 to 49, 0 to 2) of integer;										-- (pixelnummer, kleur[red,green,blue])(kleur data als integer)
--signal coloursInt			: colourInt;
--
---- er worden 16 pixels per vakje genomen, de 17de is voor het gemiddelde
--type colourArray is array (0 to 49, 0 to 16) of std_logic_vector(11 downto 0);	-- (vaknummer, pixelnummer)(kleur data)
--signal colours 			: colourArray;

signal pixelCounter		: integer;

signal red					: integer;
signal green				: integer;
signal blue					: integer;
signal temp_red			: integer;
signal temp_green			: integer;
signal temp_blue			: integer;

signal temp_address		: integer;

begin
  process (clk_i)
  begin
    if rising_edge (clk_i) then
		temp_address <= to_integer(signed(address));
	 
--		if (pixelCounter < 16) then
--			temp_red <= to_integer(signed(dpixel(11 downto 8)));
--			temp_green <= to_integer(signed(dpixel(7 downto 4)));
--			temp_blue <= to_integer(signed(dpixel(3 downto 0)));
--			red <= red + temp_red;
--			green <= green + temp_green;
--			blue <= blue + temp_green;
--			pixelCounter <= pixelCounter + 1;
--		elsif (pixelCounter = 16) then
--			red <= red / 16;
--			green <= green / 16;
--			blue <= blue / 16;
--			colour(11 downto 8) <= std_logic_vector(to_unsigned(red, 4));
--			colour(7 downto 4) <= std_logic_vector(to_unsigned(green, 4));
--			colour(3 downto 0) <= std_logic_vector(to_unsigned(blue, 4));
--			pixelCounter <= 0;
--			red <= 0;
--			green <= 0;
--			blue <= 0;
--		else
--			pixelCounter <= 0;
--			red <= 0;
--			green <= 0;
--			blue <= 0;
--			temp_red <= 0;
--			temp_green <= 0;
--			temp_blue <= 0;
--		end if;
		
		if (temp_address > 29999) then
			if (temp_address < 30004) then
				temp_red <= to_integer(signed(dpixel(11 downto 8)));
				temp_green <= to_integer(signed(dpixel(7 downto 4)));
				temp_blue <= to_integer(signed(dpixel(3 downto 0)));
				red <= red + temp_red;
				green <= green + temp_green;
				blue <= blue + temp_green;
				pixelCounter <= pixelCounter + 1;
			end if;
		elsif (temp_address > 30319) then
			if (temp_address < 30324) then
				temp_red <= to_integer(signed(dpixel(11 downto 8)));
				temp_green <= to_integer(signed(dpixel(7 downto 4)));
				temp_blue <= to_integer(signed(dpixel(3 downto 0)));
				red <= red + temp_red;
				green <= green + temp_green;
				blue <= blue + temp_green;
				pixelCounter <= pixelCounter + 1;
			end if;
		elsif (temp_address > 30639) then
			if (temp_address < 30644) then
				temp_red <= to_integer(signed(dpixel(11 downto 8)));
				temp_green <= to_integer(signed(dpixel(7 downto 4)));
				temp_blue <= to_integer(signed(dpixel(3 downto 0)));
				red <= red + temp_red;
				green <= green + temp_green;
				blue <= blue + temp_green;
				pixelCounter <= pixelCounter + 1;
			end if;
		elsif (temp_address > 30959) then
			if (temp_address < 30964) then
				temp_red <= to_integer(signed(dpixel(11 downto 8)));
				temp_green <= to_integer(signed(dpixel(7 downto 4)));
				temp_blue <= to_integer(signed(dpixel(3 downto 0)));
				red <= red + temp_red;
				green <= green + temp_green;
				blue <= blue + temp_green;
				pixelCounter <= pixelCounter + 1;
			end if;
		end if;
		if (pixelCounter = 16) then
			red <= red / 16;
			green <= green / 16;
			blue <= blue / 16;
			colour(11 downto 8) <= std_logic_vector(to_unsigned(red, 4));
			colour(7 downto 4) <= std_logic_vector(to_unsigned(green, 4));
			colour(3 downto 0) <= std_logic_vector(to_unsigned(blue, 4));
			pixelCounter <= 0;
			red <= 0;
			green <= 0;
			blue <= 0;
		end if;
	end if;
	end process;
end Recognize;