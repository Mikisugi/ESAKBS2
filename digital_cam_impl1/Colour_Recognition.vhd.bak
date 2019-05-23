library ieee;
use ieee.std_logic_1164.ALL;
--use ieee.std_logic_arith.ALL;
--use ieee.std_logic_unsigned.ALL;
use ieee.numeric_std.ALL;

entity Colour_Recognition is
  Port (
    activated_ii	: in std_logic;
    clk_ii 		: in std_logic;									-- clock
	 dapixel 	: in std_logic_vector (11 downto 0);		-- data of each pixel
    address 	: in std_logic_vector (16 downto 0);		-- address of each pixel
	 limitPixel	: in unsigned(16 downto 0);					-- contains address for average pixels
	 colour		: out std_logic_vector (11 downto 0);		-- average colour
	 pixel		: out std_logic_vector (11 downto 0)		-- actual colour for vga
--	 led			: out std_logic
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

signal red					: unsigned(7 downto 0);
signal green				: unsigned(7 downto 0);
signal blue					: unsigned(7 downto 0);
signal temp_red			: unsigned(3 downto 0);
signal temp_green			: unsigned(3 downto 0);
signal temp_blue			: unsigned(3 downto 0);

signal temp_address		: unsigned(16 downto 0);

begin
  process (clk_ii)
  begin
    if rising_edge (clk_ii) then
		pixel <= dapixel;
		temp_address <= unsigned(address);
		
		if (activated_ii = '1') then
--			if (temp_address > 30959) then
--				if (temp_address < 30964) then
			if (temp_address > (limitPixel + 960)) then
				if (temp_address < (limitPixel + 965)) then
					temp_red <= unsigned(dapixel(11 downto 8));
					temp_green <= unsigned(dapixel(7 downto 4));
					temp_blue <= unsigned(dapixel(3 downto 0));
					red <= red + temp_red;
					green <= green + temp_green;
					blue <= blue + temp_green;
					pixelCounter <= pixelCounter + 1;
					pixel <= "000011110000";
				end if;
--			elsif (temp_address > 30639) then
--				if (temp_address < 30644) then
			elsif (temp_address > (limitPixel + 640)) then
				if (temp_address < (limitPixel + 645)) then
					temp_red <= unsigned(dapixel(11 downto 8));
					temp_green <= unsigned(dapixel(7 downto 4));
					temp_blue <= unsigned(dapixel(3 downto 0));
					red <= red + temp_red;
					green <= green + temp_green;
					blue <= blue + temp_green;
					pixelCounter <= pixelCounter + 1;
					pixel <= "000011110000";
				end if;
--			elsif (temp_address > 30319) then
--				if (temp_address < 30324) then
			elsif (temp_address > (limitPixel + 320)) then
				if (temp_address < (limitPixel + 325)) then
					temp_red <= unsigned(dapixel(11 downto 8));
					temp_green <= unsigned(dapixel(7 downto 4));
					temp_blue <= unsigned(dapixel(3 downto 0));
					red <= red + temp_red;
					green <= green + temp_green;
					blue <= blue + temp_green;
					pixelCounter <= pixelCounter + 1;
					pixel <= "000011110000";
				end if;
--			elsif (temp_address > 29999) then
--				if (temp_address < 30004) then
			elsif (temp_address > limitPixel) then
				if (temp_address < (limitPixel + 5)) then
					temp_red <= unsigned(dapixel(11 downto 8));
					temp_green <= unsigned(dapixel(7 downto 4));
					temp_blue <= unsigned(dapixel(3 downto 0));
					red <= red + temp_red;
					green <= green + temp_green;
					blue <= blue + temp_green;
					pixelCounter <= pixelCounter + 1;
					pixel <= "000011110000";
				end if;
			else
				pixel <= dapixel;
			end if;
			if (temp_address = 76799) then
				colour(11 downto 8) <= std_logic_vector(red(7 downto 4));
				colour(7 downto 4) <= std_logic_vector(green(7 downto 4));
				colour(3 downto 0) <= std_logic_vector(blue(7 downto 4));
				colour <= std_logic_vector(unsigned(dapixel));
				pixelCounter <= 0;
				red <= "00000000";
				green <= "00000000";
				blue <= "00000000";
--				led <= '1';
			end if;
			temp_red <= "0000";
			temp_green <= "0000";
			temp_blue <= "0000";
		else
--			led <= '0';
			pixel <= dapixel;
		end if;
	end if;
	end process;
end Recognize;