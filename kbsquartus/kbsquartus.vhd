-- Implements a simple Nios II system for the DE-series board

library ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

entity kbsquartus IS --name of top level entity
	
	port (
		CLOCK_50 : in std_logic;
		KEY : in std_logic_vector (0 DOWNTO 0);
		SW : in std_logic_vector (7 DOWNTO 0);
		LEDR : out std_logic_vector (7 DOWNTO 0)
	);

	end kbsquartus;

ARCHITECTURE kbsquartusArch OF kbsquartus IS

	
    component unsaved is
        port (
            clk_clk         : in  std_logic                    := 'X';             -- clk
            switches_export : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
            leds_export     : out std_logic_vector(7 downto 0)                     -- export
        );
    end component unsaved;
	 
BEGIN

	u0 : component unsaved
        port map (
            clk_clk         => CLOCK_50,         --      clk.clk
            switches_export => SW, -- switches.export
            leds_export     => LEDR      --     leds.export
        );

END kbsquartusArch;