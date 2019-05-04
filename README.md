# Tetrix for Gumstix

We recreated Tetris from scratch using the Gumstix board with an lcd screen and hardware buttons. We were able to implement the major features of tetris such as hard drop, soft drop, next block and basic gameplay movement and logic as well as additional features such as color customization. It is a fully functional recreation of a classic game. We developed the game logic from our understanding of the game and did not use any external sources. 

## Getting Started

### Prerequisites

- LCD Screen
- Gumstix Board
- Proper Compiler
- 8 buttons

### Buttons

Make sure that the 8 buttons are connected appropriately. Here are the default values used

```c
//Assigning GPIO buttons 
#define GPIO_BUTTON_0 113	//hard drop
#define GPIO_BUTTON_1 101	//translate left
#define GPIO_BUTTON_2 9		//soft drop
#define GPIO_BUTTON_3 28	//translate right
#define GPIO_BUTTON_4 16	//rotate left
#define GPIO_BUTTON_5 29	//color cycle 
#define GPIO_BUTTON_6 30	//rotate right
#define GPIO_BUTTON_7 31	//reset
```

### Installing/Compiling

Navigate to the kernel folder and compile

```
cd kernel
make
```

Navigate to the game folder and compile

```
cd ../game
make
```

Now connect the gumstix board and get it runnning and transfer these two files over

```
kernel/tetrix.ko
game/game
```

Setup the lcd screen and then install the kernel module

```
mknod /dev/tetrix c 61 0
insmod tetrix.ko
```

## Running the game

Now you can run the game

```
./game -qws
```


