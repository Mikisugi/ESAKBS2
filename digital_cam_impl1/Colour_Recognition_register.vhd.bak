library ieee;
use ieee.std_logic_1164.ALL;
--use ieee.std_logic_arith.ALL;
--use ieee.std_logic_unsigned.ALL;
use ieee.numeric_std.ALL;

entity Colour_Recognition_register is
  Port (
    activated	: in std_logic;
    clk_i 		: in std_logic;
	 dpixel 		: in std_logic_vector (11 downto 0);
    address_second 	: in std_logic_vector (16 downto 0);
--	 colour		: out std_logic_vector (11 downto 0);
	 pixel		: out std_logic_vector (11 downto 0);
	 
	 -- here we placed all the variables that will be used by the C code
	 -- empty: 				001
	 -- friendly stone:	010
	 -- friendly king:	011
	 -- enemy stone:		100
	 -- enemy king:		101
	 vak_1 		: out std_logic_vector(2 downto 0);
	 vak_2 		: out std_logic_vector(2 downto 0);
	 vak_3 		: out std_logic_vector(2 downto 0);
	 vak_4 		: out std_logic_vector(2 downto 0);
	 vak_5 		: out std_logic_vector(2 downto 0);
	 vak_6 		: out std_logic_vector(2 downto 0);
	 vak_7 		: out std_logic_vector(2 downto 0);
	 vak_8 		: out std_logic_vector(2 downto 0);
	 vak_9 		: out std_logic_vector(2 downto 0);
	 vak_10 		: out std_logic_vector(2 downto 0);
	 vak_11 		: out std_logic_vector(2 downto 0);
	 vak_12 		: out std_logic_vector(2 downto 0);
	 vak_13 		: out std_logic_vector(2 downto 0);
	 vak_14 		: out std_logic_vector(2 downto 0);
	 vak_15 		: out std_logic_vector(2 downto 0);
	 vak_16 		: out std_logic_vector(2 downto 0);
	 vak_17 		: out std_logic_vector(2 downto 0);
	 vak_18 		: out std_logic_vector(2 downto 0);
	 vak_19 		: out std_logic_vector(2 downto 0);
	 vak_20 		: out std_logic_vector(2 downto 0);
	 vak_21 		: out std_logic_vector(2 downto 0);
	 vak_22 		: out std_logic_vector(2 downto 0);
	 vak_23 		: out std_logic_vector(2 downto 0);
	 vak_24 		: out std_logic_vector(2 downto 0);
	 vak_25 		: out std_logic_vector(2 downto 0);
	 vak_26 		: out std_logic_vector(2 downto 0);
	 vak_27 		: out std_logic_vector(2 downto 0);
	 vak_28 		: out std_logic_vector(2 downto 0);
	 vak_29 		: out std_logic_vector(2 downto 0);
	 vak_30 		: out std_logic_vector(2 downto 0);
	 vak_31 		: out std_logic_vector(2 downto 0);
	 vak_32 		: out std_logic_vector(2 downto 0);
	 vak_33 		: out std_logic_vector(2 downto 0);
	 vak_34 		: out std_logic_vector(2 downto 0);
	 vak_35 		: out std_logic_vector(2 downto 0);
	 vak_36 		: out std_logic_vector(2 downto 0);
	 vak_37 		: out std_logic_vector(2 downto 0);
	 vak_38 		: out std_logic_vector(2 downto 0);
	 vak_39 		: out std_logic_vector(2 downto 0);
	 vak_40 		: out std_logic_vector(2 downto 0);
	 vak_41 		: out std_logic_vector(2 downto 0);
	 vak_42 		: out std_logic_vector(2 downto 0);
	 vak_43 		: out std_logic_vector(2 downto 0);
	 vak_44 		: out std_logic_vector(2 downto 0);
	 vak_45 		: out std_logic_vector(2 downto 0);
	 vak_46 		: out std_logic_vector(2 downto 0);
	 vak_47 		: out std_logic_vector(2 downto 0);
	 vak_48 		: out std_logic_vector(2 downto 0);
	 vak_49 		: out std_logic_vector(2 downto 0);
	 vak_50 		: out std_logic_vector(2 downto 0)
  );  
end Colour_Recognition_register;

architecture Recognize_register of Colour_Recognition_register is

  component Colour_Recognition
  port(
	 activated_ii	: in std_logic;
	 clk_ii		: in std_logic;
    dapixel 		: in std_logic_vector(11 downto 0);    
    address		: in std_logic_vector (16 downto 0);
	 limitPixel	: in unsigned(16 downto 0);
    colour 		: out std_logic_vector(11 downto 0);
	 pixel		: out std_logic_vector(11 downto 0)
--	 led			: out std_logic
    );
  end component;
  
  type limitPixelArray is array (0 to 49) of unsigned(16 downto 0);	-- (vaknummer)(adres eerste pixel)
  signal limitPixel_main : limitPixelArray;
  
  type vakInhoudArray is array (0 to 49) of std_logic_vector(2 downto 0);	-- (vaknummer)(adres eerste pixel)
  signal vakInhoud_main : vakInhoudArray;
  
  type pixelArray is array (0 to 49) of std_logic_vector(11 downto 0);	-- (vaknummer)(kleur data)
  signal pixel_main : pixelArray;
  
--  signal colour_1: std_logic_vector(11 downto 0);
  
  type colourArray is array (0 to 49) of std_logic_vector(11 downto 0);	-- (vaknummer)(kleur data)
  signal colour_main : colourArray;
  
  signal activeSend 		: std_logic := '0';
  signal activeInhoud 	: std_logic := '0';
  
  signal limitPixel		: unsigned(16 downto 0);
  
  signal once : std_logic := '0';
  signal count_addr : integer := 0;
  signal pixel_ad : unsigned(16 downto 0) := (others => '0');
  
begin
	
	pixel <= pixel_main(0);

	-- places all the addresses on the right place in the array place
--	process (clk_i)
--	begin
--		if rising_edge (clk_i) then
--			if (once = '0') then
--			pixel_ad <= to_unsigned(752, 17);
--			count_addr <= 0;
--				for jj in 0 to 9 loop
--					for ii in 0 to 4 loop
--						limitPixel_main(count_addr) <= pixel_ad;
--						pixel_ad <= pixel_ad + to_unsigned(32, 17);
--						count_addr <= count_addr + 1;
--					end loop;
--					if (jj = 0 or jj = 2 or jj = 4 or jj = 6 or jj = 8) then
--						pixel_ad <= pixel_ad + to_unsigned(4944, 17);
--					elsif (jj = 1 or jj = 3 or jj = 5 or jj = 7 or jj = 9) then
--						pixel_ad <= pixel_ad + to_unsigned(4976, 17);
--					end if;
--				end loop;
--			once <= '1';
--			end if;
--		end if;
--	end process;
	
	limitPixel_main(0) <= to_unsigned(752, 17);
	limitPixel_main(1) <= to_unsigned(784, 17);
	limitPixel_main(2) <= to_unsigned(816, 17);
	limitPixel_main(3) <= to_unsigned(848, 17);
	limitPixel_main(4) <= to_unsigned(880, 17);
	limitPixel_main(5) <= to_unsigned(5856, 17);
	limitPixel_main(6) <= to_unsigned(5888, 17);
	limitPixel_main(7) <= to_unsigned(5920, 17);
	limitPixel_main(8) <= to_unsigned(5952, 17);
	limitPixel_main(9) <= to_unsigned(5984, 17);
	limitPixel_main(10) <= to_unsigned(10992, 17);
	limitPixel_main(11) <= to_unsigned(11024, 17);
	limitPixel_main(12) <= to_unsigned(11056, 17);
	limitPixel_main(13) <= to_unsigned(11088, 17);
	limitPixel_main(14) <= to_unsigned(11120, 17);
	limitPixel_main(15) <= to_unsigned(16096, 17);
	limitPixel_main(16) <= to_unsigned(16128, 17);
	limitPixel_main(17) <= to_unsigned(16160, 17);
	limitPixel_main(18) <= to_unsigned(16192, 17);
	limitPixel_main(19) <= to_unsigned(16224, 17);
	limitPixel_main(20) <= to_unsigned(21232, 17);
	limitPixel_main(21) <= to_unsigned(21264, 17);
	limitPixel_main(22) <= to_unsigned(21296, 17);
	limitPixel_main(23) <= to_unsigned(21328, 17);
	limitPixel_main(24) <= to_unsigned(21360, 17);
	limitPixel_main(25) <= to_unsigned(26336, 17);
	limitPixel_main(26) <= to_unsigned(26368, 17);
	limitPixel_main(27) <= to_unsigned(26400, 17);
	limitPixel_main(28) <= to_unsigned(26432, 17);
	limitPixel_main(29) <= to_unsigned(26464, 17);
	limitPixel_main(30) <= to_unsigned(31472, 17);
	limitPixel_main(31) <= to_unsigned(31504, 17);
	limitPixel_main(32) <= to_unsigned(31536, 17);
	limitPixel_main(33) <= to_unsigned(31568, 17);
	limitPixel_main(34) <= to_unsigned(31600, 17);
	limitPixel_main(35) <= to_unsigned(36576, 17);
	limitPixel_main(36) <= to_unsigned(36608, 17);
	limitPixel_main(37) <= to_unsigned(36640, 17);
	limitPixel_main(38) <= to_unsigned(36672, 17);
	limitPixel_main(39) <= to_unsigned(36704, 17);
	limitPixel_main(40) <= to_unsigned(41712, 17);
	limitPixel_main(41) <= to_unsigned(41744, 17);
	limitPixel_main(42) <= to_unsigned(41776, 17);
	limitPixel_main(43) <= to_unsigned(41808, 17);
	limitPixel_main(44) <= to_unsigned(41840, 17);
	limitPixel_main(45) <= to_unsigned(46816, 17);
	limitPixel_main(46) <= to_unsigned(46848, 17);
	limitPixel_main(47) <= to_unsigned(46880, 17);
	limitPixel_main(48) <= to_unsigned(46912, 17);
	limitPixel_main(49) <= to_unsigned(46944, 17);

	process (clk_i)
	begin
		if rising_edge (clk_i) then
			if (activeInhoud = '1') then
				for l in 0 to 49 loop
					if (colour_main(l) = "000000000000") then		-- empty
						vakInhoud_main(l) <= "000";
					elsif (colour_main(l) = "111100000000") then	-- friendly
						vakInhoud_main(l) <= "000";
					elsif (colour_main(l) = "110011000000") then	-- friendly king
						vakInhoud_main(l) <= "000";
					elsif (colour_main(l) = "000011110000") then	-- enemy
						vakInhoud_main(l) <= "000";
					elsif (colour_main(l) = "000100010000") then	-- enemy king
						vakInhoud_main(l) <= "000";
					else
						vakInhoud_main(l) <= "111";
					end if;
				end loop;
				activeSend <= '1';
				activeInhoud <= '0';
			end if;
		end if;
	end process;
	
	process (clk_i)
	begin
		if rising_edge (clk_i) then
			if (activeSend = '1') then
				vak_1 <= vakInhoud_main(0);
				vak_2 <= vakInhoud_main(1);
				vak_3 <= vakInhoud_main(2);
				vak_4 <= vakInhoud_main(3);
				vak_5 <= vakInhoud_main(4);
				vak_6 <= vakInhoud_main(5);
				vak_7 <= vakInhoud_main(6);
				vak_8 <= vakInhoud_main(7);
				vak_9 <= vakInhoud_main(8);
				vak_10 <= vakInhoud_main(9);
				vak_11 <= vakInhoud_main(10);
				vak_12 <= vakInhoud_main(11);
				vak_13 <= vakInhoud_main(12);
				vak_14 <= vakInhoud_main(13);
				vak_15 <= vakInhoud_main(14);
				vak_16 <= vakInhoud_main(15);
				vak_17 <= vakInhoud_main(16);
				vak_18 <= vakInhoud_main(17);
				vak_19 <= vakInhoud_main(18);
				vak_20 <= vakInhoud_main(19);
				vak_21 <= vakInhoud_main(20);
				vak_22 <= vakInhoud_main(21);
				vak_23 <= vakInhoud_main(22);
				vak_24 <= vakInhoud_main(23);
				vak_25 <= vakInhoud_main(24);
				vak_26 <= vakInhoud_main(25);
				vak_27 <= vakInhoud_main(26);
				vak_28 <= vakInhoud_main(27);
				vak_29 <= vakInhoud_main(28);
				vak_30 <= vakInhoud_main(29);
				vak_31 <= vakInhoud_main(30);
				vak_32 <= vakInhoud_main(31);
				vak_33 <= vakInhoud_main(32);
				vak_34 <= vakInhoud_main(33);
				vak_35 <= vakInhoud_main(34);
				vak_36 <= vakInhoud_main(35);
				vak_37 <= vakInhoud_main(36);
				vak_38 <= vakInhoud_main(37);
				vak_39 <= vakInhoud_main(38);
				vak_40 <= vakInhoud_main(39);
				vak_41 <= vakInhoud_main(40);
				vak_42 <= vakInhoud_main(41);
				vak_43 <= vakInhoud_main(42);
				vak_44 <= vakInhoud_main(43);
				vak_45 <= vakInhoud_main(44);
				vak_46 <= vakInhoud_main(45);
				vak_47 <= vakInhoud_main(46);
				vak_48 <= vakInhoud_main(47);
				vak_49 <= vakInhoud_main(48);
				vak_50 <= vakInhoud_main(49);
			end if;
		end if;
	end process;
	
--				vak_1 <= vakInhoud_main(0) when activeSend = '1';
--				vak_2 <= vakInhoud_main(1) when activeSend = '1';
--				vak_3 <= vakInhoud_main(2) when activeSend = '1';
--				vak_4 <= vakInhoud_main(3) when activeSend = '1';
--				vak_5 <= vakInhoud_main(4) when activeSend = '1';
--				vak_6 <= vakInhoud_main(5) when activeSend = '1';
--				vak_7 <= vakInhoud_main(6) when activeSend = '1';
--				vak_8 <= vakInhoud_main(7) when activeSend = '1';
--				vak_9 <= vakInhoud_main(8) when activeSend = '1';
--				vak_10 <= vakInhoud_main(9) when activeSend = '1';
--				vak_11 <= vakInhoud_main(10) when activeSend = '1';
--				vak_12 <= vakInhoud_main(11) when activeSend = '1';
--				vak_13 <= vakInhoud_main(12) when activeSend = '1';
--				vak_14 <= vakInhoud_main(13) when activeSend = '1';
--				vak_15 <= vakInhoud_main(14) when activeSend = '1';
--				vak_16 <= vakInhoud_main(15) when activeSend = '1';
--				vak_17 <= vakInhoud_main(16) when activeSend = '1';
--				vak_18 <= vakInhoud_main(17) when activeSend = '1';
--				vak_19 <= vakInhoud_main(18) when activeSend = '1';
--				vak_20 <= vakInhoud_main(19) when activeSend = '1';
--				vak_21 <= vakInhoud_main(20) when activeSend = '1';
--				vak_22 <= vakInhoud_main(21) when activeSend = '1';
--				vak_23 <= vakInhoud_main(22) when activeSend = '1';
--				vak_24 <= vakInhoud_main(23) when activeSend = '1';
--				vak_25 <= vakInhoud_main(24) when activeSend = '1';
--				vak_26 <= vakInhoud_main(25) when activeSend = '1';
--				vak_27 <= vakInhoud_main(26) when activeSend = '1';
--				vak_28 <= vakInhoud_main(27) when activeSend = '1';
--				vak_29 <= vakInhoud_main(28) when activeSend = '1';
--				vak_30 <= vakInhoud_main(29) when activeSend = '1';
--				vak_31 <= vakInhoud_main(30) when activeSend = '1';
--				vak_32 <= vakInhoud_main(31) when activeSend = '1';
--				vak_33 <= vakInhoud_main(32) when activeSend = '1';
--				vak_34 <= vakInhoud_main(33) when activeSend = '1';
--				vak_35 <= vakInhoud_main(34) when activeSend = '1';
--				vak_36 <= vakInhoud_main(35) when activeSend = '1';
--				vak_37 <= vakInhoud_main(36) when activeSend = '1';
--				vak_38 <= vakInhoud_main(37) when activeSend = '1';
--				vak_39 <= vakInhoud_main(38) when activeSend = '1';
--				vak_40 <= vakInhoud_main(39) when activeSend = '1';
--				vak_41 <= vakInhoud_main(40) when activeSend = '1';
--				vak_42 <= vakInhoud_main(41) when activeSend = '1';
--				vak_43 <= vakInhoud_main(42) when activeSend = '1';
--				vak_44 <= vakInhoud_main(43) when activeSend = '1';
--				vak_45 <= vakInhoud_main(44) when activeSend = '1';
--				vak_46 <= vakInhoud_main(45) when activeSend = '1';
--				vak_47 <= vakInhoud_main(46) when activeSend = '1';
--				vak_48 <= vakInhoud_main(47) when activeSend = '1';
--				vak_49 <= vakInhoud_main(48) when activeSend = '1';
--				vak_50 <= vakInhoud_main(49) when activeSend = '1';
	
  gen: for i in 0 to 49 generate
	  Inst_Colour_Recognition: Colour_Recognition port map (
			activated_ii => activated,
			clk_ii => clk_i,
			dapixel => dpixel,
			address => address_second,
			limitPixel => limitPixel_main(i),
			colour => colour_main(i),
			pixel => pixel_main(i)
--			led => ledR
	  );
  end generate;
  
end Recognize_register;