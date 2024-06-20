```markdown
# 🐍 snake_p2p

**Snake TCP** is an online game written in C++. Spend your time playing this game and finding bugs and errors! 🙂

## 📦 How to Build

1. **Create a build directory and navigate into it:**
   ```sh
   mkdir build && cd build
   ```

2. **Run CMake to configure the project:**
   ```sh
   cmake ..
   ```

3. **Build the game:**
   ```sh
   cmake --build .
   ```

## 🚀 How to Run a Server

To run the server, execute the following command:
```sh
./game/game
```

## 🎮 How to Play

### Connect to the Game

You need a telnet client to connect to the game. In the terminal, type:
```sh
telnet <IP_ADDRESS> <PORT>
```
Replace `<IP_ADDRESS>` with the IP where the game is running and `<PORT>` with the correct port number.

### Game Settings

- **Field Size:** The default size is 100x40. You can change it in `src/GameInit/GameInit.hpp` and rebuild the game.
- **Food Count:** The default is 15. You can also change it in `src/GameInit/GameInit.hpp` and rebuild the game.
- **Update Interval:** The default is 250,000 microseconds. You can change it in `src/Server/Server.cpp` and rebuild the game.

### Controls

- Use <kbd>W</kbd>, <kbd>A</kbd>, <kbd>S</kbd>, <kbd>D</kbd> keys to move.
- Press <kbd>Enter</kbd> after typing a direction key to send it to the server.

### Symbols

- `*` : Food
- `@` : Your snake's head
- `%` : Other players' snake heads
- `#` : Snake bodies

### Objective

- Eat the food (`*`) to grow your snake.
- You can eat the body (`#`) of other snakes to reduce their size.
- If you collide with another snake's head (`%`), both you and the other player will be removed from the game.

## 🤝 Contribution

Contributions are welcome! Feel free to open issues or submit pull requests.

---

Enjoy playing and feel free to report any issues or bugs! 🎉
```
