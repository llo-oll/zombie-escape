# A Rubbish Zombie Roguelike
Make it to the staircase while you still have your brains. 
Climb to the top of the tower to win.

## To complile
To compile the game without including the development tests, remove the reference to  
./tests in the top level CMakeLists.txt and run cmake.

To include the development tests, the Google Tests library needs to be put in "./tests/gtest"

## Controls
### vim bindings (nethack like)
* j - S 
* k - N
* h - W
* l - E
* y - NW
* u - NE
* b - SW
* n - SE 
* space- skip a go
### wasd bindings
* w - N
* e - NE
* d - E
* c - SE
* s or x - S
* z - SW
* a - W
* q - NW
* space- skip a go
