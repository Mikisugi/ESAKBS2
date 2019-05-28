library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
--use ieee.numeric_std.all;

entity Address_Generator is
	Port (   
		CLK25,enable : in  std_logic;  -- horloge de 25 MHz et signal d'activation respectivement
		vsync        : in  std_logic;
		address      : out std_logic_vector (16 downto 0) -- adresse genere
	);  
end Address_Generator;

architecture Behavioral of Address_Generator is

	signal val: std_logic_vector(address'range):= (others => '0'); -- signal intermidiaire
  
begin

	address <= val; -- adresse genere

	process(CLK25)
		begin
			if rising_edge(CLK25) then

			if (enable='1') then           -- si enable = 0 on arrete la generation d'adresses
				if (val < 320*240) then      -- si l'espace memoire est balay completement        
					val <= val + 1 ;
				end if;
			end if;
        
			if vsync = '0' then 
				val <= (others => '0');
			end if;
        
		end if;  
	end process;
end Behavioral;
