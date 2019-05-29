library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Switches is
	Port (
		--switches input
		switch	:	in std_logic_vector(6 downto 0);
		
		--data voor de ledjes
		data	: out std_logic_vector(2 downto 0);
		
		-- word gebruikt door de C code:
		-- here we placed all the variables that will be used by the C code
		-- empty: 				001
		-- friendly stone:	010
		-- friendly king:	011
		-- enemy stone:		100
		-- enemy king:		101
		vak1	: in std_logic_vector(2 downto 0);
		vak2	: in std_logic_vector(2 downto 0);
		vak3	: in std_logic_vector(2 downto 0);
		vak4	: in std_logic_vector(2 downto 0);
		vak5	: in std_logic_vector(2 downto 0);
		vak6	: in std_logic_vector(2 downto 0);
		vak7	: in std_logic_vector(2 downto 0);
		vak8	: in std_logic_vector(2 downto 0);
		vak9	: in std_logic_vector(2 downto 0);
		vak10 : in std_logic_vector(2 downto 0);
		vak11 : in std_logic_vector(2 downto 0);
		vak12 : in std_logic_vector(2 downto 0);
		vak13 : in std_logic_vector(2 downto 0);
		vak14 : in std_logic_vector(2 downto 0);
		vak15 : in std_logic_vector(2 downto 0);
		vak16 : in std_logic_vector(2 downto 0);
		vak17 : in std_logic_vector(2 downto 0);
		vak18 : in std_logic_vector(2 downto 0);
		vak19 : in std_logic_vector(2 downto 0);
		vak20 : in std_logic_vector(2 downto 0);
		vak21 : in std_logic_vector(2 downto 0);
		vak22 : in std_logic_vector(2 downto 0);
		vak23 : in std_logic_vector(2 downto 0);
		vak24 : in std_logic_vector(2 downto 0);
		vak25 : in std_logic_vector(2 downto 0);
		vak26 : in std_logic_vector(2 downto 0);
		vak27 : in std_logic_vector(2 downto 0);
		vak28 : in std_logic_vector(2 downto 0);
		vak29 : in std_logic_vector(2 downto 0);
		vak30 : in std_logic_vector(2 downto 0);
		vak31 : in std_logic_vector(2 downto 0);
		vak32 : in std_logic_vector(2 downto 0);
		vak33 : in std_logic_vector(2 downto 0);
		vak34 : in std_logic_vector(2 downto 0);
		vak35 : in std_logic_vector(2 downto 0);
		vak36 : in std_logic_vector(2 downto 0);
		vak37 : in std_logic_vector(2 downto 0);
		vak38 : in std_logic_vector(2 downto 0);
		vak39 : in std_logic_vector(2 downto 0);
		vak40 : in std_logic_vector(2 downto 0);
		vak41 : in std_logic_vector(2 downto 0);
		vak42 : in std_logic_vector(2 downto 0);
		vak43 : in std_logic_vector(2 downto 0);
		vak44 : in std_logic_vector(2 downto 0);
		vak45 : in std_logic_vector(2 downto 0);
		vak46 : in std_logic_vector(2 downto 0);
		vak47 : in std_logic_vector(2 downto 0);
		vak48 : in std_logic_vector(2 downto 0);
		vak49 : in std_logic_vector(2 downto 0);
		vak50 : in std_logic_vector(2 downto 0)
	);  
end Switches;

architecture turn of Switches is
begin

	-- switches(6 downto 0) eerste 3 zijn voor horizontaal, de overige 4 zijn voor verticaal (links naar rechts, boven naar beneden)
	data <=		vak1 when switch(6 downto 0) = "0000000" else
					vak2 when switch(6 downto 0) = "0010000" else
					vak3 when switch(6 downto 0) = "0100000" else
					vak4 when switch(6 downto 0) = "0110000" else
					vak5 when switch(6 downto 0) = "1000000" else
					vak6 when switch(6 downto 0) = "0000001" else
					vak7 when switch(6 downto 0) = "0010001" else
					vak8 when switch(6 downto 0) = "0100001" else
					vak9 when switch(6 downto 0) = "0110001" else
					vak10 when switch(6 downto 0) = "1000001" else
					vak11 when switch(6 downto 0) = "0000010" else
					vak12 when switch(6 downto 0) = "0010010" else
					vak13 when switch(6 downto 0) = "0100010" else
					vak14 when switch(6 downto 0) = "0110010" else
					vak15 when switch(6 downto 0) = "1000010" else
					vak16 when switch(6 downto 0) = "0000011" else
					vak17 when switch(6 downto 0) = "0010011" else
					vak18 when switch(6 downto 0) = "0100011" else
					vak19 when switch(6 downto 0) = "0110011" else
					vak20 when switch(6 downto 0) = "1000011" else
					vak21 when switch(6 downto 0) = "0000100" else
					vak22 when switch(6 downto 0) = "0010100" else
					vak23 when switch(6 downto 0) = "0100100" else
					vak24 when switch(6 downto 0) = "0110100" else
					vak25 when switch(6 downto 0) = "1000100" else
					vak26 when switch(6 downto 0) = "0000101" else
					vak27 when switch(6 downto 0) = "0010101" else
					vak28 when switch(6 downto 0) = "0100101" else
					vak29 when switch(6 downto 0) = "0110101" else
					vak30 when switch(6 downto 0) = "1000101" else
					vak31 when switch(6 downto 0) = "0000110" else
					vak32 when switch(6 downto 0) = "0010110" else
					vak33 when switch(6 downto 0) = "0100110" else
					vak34 when switch(6 downto 0) = "0110110" else
					vak35 when switch(6 downto 0) = "1000110" else
					vak36 when switch(6 downto 0) = "0000111" else
					vak37 when switch(6 downto 0) = "0010111" else
					vak38 when switch(6 downto 0) = "0100111" else
					vak39 when switch(6 downto 0) = "0110111" else
					vak40 when switch(6 downto 0) = "1000111" else
					vak41 when switch(6 downto 0) = "0001000" else
					vak42 when switch(6 downto 0) = "0011000" else
					vak43 when switch(6 downto 0) = "0101000" else
					vak44 when switch(6 downto 0) = "0111000" else
					vak45 when switch(6 downto 0) = "1001000" else
					vak46 when switch(6 downto 0) = "0001001" else
					vak47 when switch(6 downto 0) = "0011001" else
					vak48 when switch(6 downto 0) = "0101001" else
					vak49 when switch(6 downto 0) = "0111001" else
					vak50 when switch(6 downto 0) = "1001001" else
					"111";
end turn;
