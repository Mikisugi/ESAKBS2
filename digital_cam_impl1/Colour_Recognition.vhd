library ieee;
use ieee.std_logic_1164.ALL;
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
  );  
end Colour_Recognition;

architecture Recognize of Colour_Recognition is

signal pixelCounter		: integer;

signal red					: unsigned(7 downto 0);
signal green				: unsigned(7 downto 0);
signal blue					: unsigned(7 downto 0);
signal temp_red			: unsigned(3 downto 0);
signal temp_green			: unsigned(3 downto 0);
signal temp_blue			: unsigned(3 downto 0);

signal temp_address		: unsigned(16 downto 0);
signal frameCounter			: std_logic_vector(1 downto 0);

begin
  process (clk_ii)
  begin
    if rising_edge (clk_ii) then
		pixel <= dapixel;
		temp_address <= unsigned(address);
		
		if (activated_ii = '1') then
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
				if (frameCounter = "01") then
					colour(11 downto 8) <= std_logic_vector(red(7 downto 4));
					colour(7 downto 4) <= std_logic_vector(green(7 downto 4));
					colour(3 downto 0) <= std_logic_vector(blue(7 downto 4));
					colour <= std_logic_vector(unsigned(dapixel));
					pixelCounter <= 0;
					red <= "00000000";
					green <= "00000000";
					blue <= "00000000";
					frameCounter <= "10";
				elsif (frameCounter ="00") then
					frameCounter <= "01";
				end if;
			end if;
			temp_red <= "0000";
			temp_green <= "0000";
			temp_blue <= "0000";
		else
			frameCounter <= "00";
			pixel <= dapixel;
		end if;
	end if;
	end process;
end Recognize;