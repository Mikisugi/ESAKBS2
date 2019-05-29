library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Colour_Recognition is
  Port (
    activated_ii	: in std_logic;
    clk_ii 			: in std_logic;									-- clock
	 dapixel 		: in std_logic_vector (11 downto 0);		-- data of each pixel
    address 		: in std_logic_vector (16 downto 0);		-- address of each pixel
	 limitPixel		: in unsigned(16 downto 0);					-- contains address for average pixels
	 colour			: out std_logic_vector (11 downto 0);		-- average colour
	 pixel			: out std_logic_vector (11 downto 0);		-- actual colour for vga
	 calc				: out std_logic := '0';
	 ledw : out std_logic
  );  
end Colour_Recognition;

architecture Recognize of Colour_Recognition is
signal red					: unsigned(5 downto 0);				-- bevat het totaal aantal rood van een vakje
signal green				: unsigned(5 downto 0);				-- bevat het totaal aantal groen van een vakje
signal blue					: unsigned(5 downto 0);				-- bevat het totaal aantal blauw van een vakje
signal temp_red			: unsigned(3 downto 0);				-- bevat van 1 pixel de kleur rood
signal temp_green			: unsigned(3 downto 0);				-- bevat van 1 pixel de kleur groen
signal temp_blue			: unsigned(3 downto 0);				-- bevat van 1 pixel de kleur blauw
signal temp_address		: unsigned(16 downto 0);			-- bevat de unsigned versie van het address
signal frameCounter		: std_logic_vector(1 downto 0);	-- bevat hoe vaak er een frame is gebruikt per knop indruk. 00: 0 frames, 01: 1 frame, 10: meer dan 1 frame

begin
  process (clk_ii)
  begin
    if rising_edge (clk_ii) then
		pixel <= dapixel;
		temp_address <= unsigned(address);
		
		if (activated_ii = '1') then
			if (temp_address > (limitPixel + 960)) then
				if (temp_address < (limitPixel + 965)) then
					red(5 downto 2) <= unsigned(dapixel(11 downto 8));
					green(5 downto 2) <= unsigned(dapixel(7 downto 4));
					blue(5 downto 2) <= unsigned(dapixel(3 downto 0));
					red <= (red + temp_red);
					green <= (green + temp_green);
					blue <= (blue + temp_green);
					pixel <= "000011110000";
				end if;
			end if;
			if (temp_address > (limitPixel + 640)) then
				if (temp_address < (limitPixel + 645)) then
					temp_red <= unsigned(dapixel(11 downto 8));
					temp_green <= unsigned(dapixel(7 downto 4));
					temp_blue <= unsigned(dapixel(3 downto 0));
					red <= red + temp_red;
					green <= green + temp_green;
					blue <= blue + temp_green;
					pixel <= "000011110000";
				end if;
			end if;
			if (temp_address > (limitPixel + 320)) then
				if (temp_address < (limitPixel + 325)) then
					temp_red <= unsigned(dapixel(11 downto 8));
					temp_green <= unsigned(dapixel(7 downto 4));
					temp_blue <= unsigned(dapixel(3 downto 0));
					red <= red + temp_red;
					green <= green + temp_green;
					blue <= blue + temp_green;
					pixel <= "000011110000";
				end if;
			end if;
			if (temp_address > limitPixel) then
				if (temp_address < (limitPixel + 5)) then
					temp_red <= unsigned(dapixel(11 downto 8));
					temp_green <= unsigned(dapixel(7 downto 4));
					temp_blue <= unsigned(dapixel(3 downto 0));
					red <= red + temp_red;
					green <= green + temp_green;
					blue <= blue + temp_green;
					pixel <= "000011110000";
				end if;
			end if;
			if (temp_address = 76799) then
				if (frameCounter = "01") then
				
					colour(11 downto 8) <= std_logic_vector(red(5 downto 2));
					colour(7 downto 4) <= std_logic_vector(green(5 downto 2));
					colour(3 downto 0) <= std_logic_vector(blue(5 downto 2));
----					if(std_logic_vector(red(5 downto 2)) = "0000" and std_logic_vector(green(5 downto 2)) = "0000" and std_logic_vector(blue(5 downto 2)) = "0000") then
----						colour <= "111111111111";
----					end if;
--					colour <= std_logic_vector(unsigned(dapixel));
					
					red <= "000000";
					green <= "000000";
					blue <= "000000";
					calc <= '1';
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