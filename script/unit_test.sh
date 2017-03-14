#!/bin/bash

YEL="\033[33m"
GREEN="\033[32m"
RES="\033[0m"
INT_MAX="2147483647"
INT_MIN="-2147483648"

lm_test() { 
	echo -e "\n$YEL"$1"$RES";
	echo -e $2 | ./lem-in; 
}

display_title() {
echo -e "\n=============================="
echo -e "== $GREEN""  Lem_in parsing tests$RES   =="
echo -e "==============================\n"
}

correction_tests() {
echo -e "$GREEN""42 CORRECTION TESTS$RES"

lm_test  \
	"Test 00: no rooms" \
	"10" 
lm_test  \
	"Test 01: no ants" \
	"room1 1 1"
lm_test  \
	"Test 02a: no ##end / no ##start" \
	"10\nroom1 1 1\nroom2 2 2\nroom3 3 3\nroom1-room2"
lm_test  \
	"Test 02b: no ##start" \
	"10\nroom1 1 1\nroom2 2 2\n##end\nroom3 3 3\nroom1-room2"
lm_test  \
	"Test 02c: no ##end" \
	"10\nroom1 1 1\nroom2 2 2\n##start\nroom3 3 3\nroom1-room2"
lm_test  \
	"Test 03: no valid path" \
	"10\n##end\nroom1 1 1\nroom2 2 2\n##start\nroom3 3 3\nroom3-room2"
lm_test  \
	"Test 04: valid colony with comments" \
	"10\n##this is a comment\n##end\nroom1 1 1\nroom2 2 2\n##start\nroom3 3 3\n#this is another comment\nroom3-room2\nroom2-room1"
lm_test  \
	"Test 05: valid colony with other commands" \
	"10\n##command1\n##end\nroom1 1 1\nroom2 2 2\n##start\nroom3 3 3\n##command2\nroom3-room2\nroom2-room1"
lm_test  \
	"Test 06: valid input display output format" \
	"10\n##end\nroom1 1 1\nroom2 2 2\n##start\nroom3 3 3\n#what a great output !\nroom3-room2\nroom2-room1"
lm_test  \
	"Test 07: Demonstrating shortest path" \
	"1\n##start\nr0 1 1\nr1 1 1\nr2 1 1\nr3 1 1\n##end\nr4 1 1\nr5 1 1\nr6 1 1\nr7 1 1\nr0-r1\nr0-r5\nr1-r2\nr1-r7\nr2-r3\nr3-r4\nr4-r7\nr7-r6\nr6-r5"
lm_test  \
	"Test 08: Multiple ants" \
	"10\n##start\nr0 1 1\nr1 1 1\nr2 1 1\nr3 1 1\n##end\nr4 1 1\nr5 1 1\nr6 1 1\nr7 1 1\nr0-r1\nr0-r5\nr1-r2\nr1-r7\nr2-r3\nr3-r4\nr4-r7\nr7-r6\nr6-r5"
}

ants_parsing() {
echo -e "$GREEN""ANTS PARSING$RES"

lm_test  \
	"Test 00: 0 ants" \
	"0" 
lm_test  \
	"Test 01: -10 ants" \
	"-10"
lm_test  \
	"Test 02: INT_MAX ants" \
	"$INT_MAX"
}

rooms_parsing() {
echo -e "$GREEN""\nROOMS PARSING$RES"

lm_test  \
	"Test 00: 10 ants, no room" \
	"10"
lm_test  \
	"Test 01: 0 room" \
	"10\n2-3"
lm_test  \
	"Test 02: 0 room, 3 comments" \
	"10\n#comment\n##comment\n###comment\n3-4"
lm_test  \
	"Test 03: invalid room format 1 (L)$" \
	"10\n#comment\n##start\nroom1 2 3\nLroom2 9 1\n3-4"
lm_test  \
	"Test 04: invalid room format 2 (name x y z)" \
	"10\n#comment\n##start\nroom1 2 3 4\nLroom2 9 1\n3-4" 
lm_test  \
	"Test 05: invalid room format 3 (name x)" \
	"10\n#comment\n##start\nroom1 4\nLroom2 9 1\n3-4"
lm_test  \
	"Test 06: invalid room format 4 (wrong x y)" \
	"10\n#comment\n##start\nroom1 4 3\nLroom2 a b\n3-4"
lm_test  \
	"Test 07: invalid room format 5 (name only)" \
	"10\n#comment\n##start\nroom1\nLroom2 a b\n3-4"
lm_test  \
	"Test 08: ##start && ##end attributed to the same room" \
	"10\n#comment\n##end\n##start\nroom1 4 3\nroom2 4 99\n3-4"
lm_test  \
	"Test 09: valid room format" \
	"10\n#comment\n##start\nroom1 4 3\nroom2 4 99\n3-4"
# INT MAX coordinates
}

edges_parsing() {
echo -e "$GREEN""\nEDGES PARSING$RES"

lm_test  \
	"Test 00: no edges" \
	"10\n#comment\n##start\nroom1 4 3\n##end\nroom2 4 99"
lm_test  \
	"Test 01: normal edges" \
	"10\n#comment\n##start\nr1 4 3\nr3 0 9\n##end\nr2 4 99\nr1-r2\nr2-r3\nr3-r1"
lm_test  \
	"Test 02: double dash - -" \
	"10\n#comment\n##start\nr1 4 3\nr3 0 9\n##end\nr2 4 99\nr1-r2\nr2-r3-\nr3-r1"
lm_test  \
	"Test 03: triple dash - - -" \
	"10\n#comment\n##start\nr1 4 3\nr3 0 9\n##end\nr2 4 99\nr1-r2\nr2-r3--\nr3-r1"
lm_test  \
	"Test 04: circular edge roomA-roomA" \
	"10\n#comment\n##start\nr1 4 3\nr3 0 9\n##end\nr2 4 99\nr1-r1\nr2-r3\nr3-r1"
lm_test  \
	"Test 05: non-existing room in edge" \
	"10\n#comment\n##start\nr1 4 3\nr3 0 9\n##end\nr2 4 99\nr2-r3\nr2-r9\nr3-r1"
lm_test  \
	"Test 06: triple rooms" \
	"10\n#comment\n##start\nr1 4 3\nr3 0 9\n##end\nr2 4 99\nr1-r2\nr2-r3-r1\nr3-r1"
# tirets "-" "- -" "--"
}

main() {
	display_title
	correction_tests
	ants_parsing
	rooms_parsing
	edges_parsing
}

main $@

