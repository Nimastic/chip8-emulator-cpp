# CHIP-8 Emulator (C++)

Based on [Austin Morlan's CHIP-8 tutorial](https://austinmorlan.com/posts/chip8_emulator/). Working solution lives in `Solution/`.

## Run a ROM

```powershell
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH
cd Solution
.\chip8.exe 10 3 Tetris.ch8
.\chip8.exe 10 1 test_opcode.ch8
```

Args: `<Scale> <Delay ms> <ROM>`

## Sample ROMs

- Games: https://github.com/dmatlack/chip8/tree/master/roms/games
- Tetris: https://github.com/dmatlack/chip8/blob/master/roms/games/Tetris%20%5BFran%20Dachille%2C%201991%5D.ch8
- Opcode test: https://github.com/corax89/chip8-test-rom/blob/master/test_opcode.ch8

---

## Making your own CHIP-8 games

Totally possible. A `.ch8` file is just machine code for the CHIP-8 VM. If your game only uses the opcodes your emulator implements, it will run.

### How people make CHIP-8 games

1. Write CHIP-8 assembly — human-readable instructions like `LD V0, #05`, `DRW V1, V2, 5`, `JP #200`.
2. Assemble that into a binary ROM (the `.ch8`).
3. Load it in an emulator starting at address `0x200`.

Some people also use higher-level tools (Octo, CHIP-8 compilers, visual editors) that eventually emit the same kind of bytecode.

### Do I need to learn assembly?

Mostly yes — for classic CHIP-8, people usually write **CHIP-8 assembly** (or something close, like Octo). It’s a small instruction set (~34 ops), so it’s much easier than x86/ARM. You don’t need full “computer architecture school,” just this tiny dialect.

You generally **cannot** write a normal C++ game and compile it to `.ch8`. C++ is for the emulator; games are CHIP-8 bytecode.

### What you’d need for your own Tetris

- A CHIP-8 assembler (or [Octo](https://github.com/JohnEarnest/Octo), popular for CHIP-8 / SuperChip)
- Knowledge of the instruction set your emulator supports (this one follows Austin Morlan / Cowgod-style CHIP-8)
- Game logic from those ops: draw sprites (`Dxyn`), keypad (`Ex9E` / `Fx0A`), timers, RNG (`Cxkk`), etc.
- Fonts are already in memory at `0x50` if you use `Fx29`

### Compatibility gotchas

Your ROM must match this emulator’s quirks:

- Shift ops (`8xy6` / `8xyE`) — shifts `Vx` only (Cowgod style)
- `Fx55` / `Fx65` — does **not** increment `I`
- Display wrapping / collision behavior
- Speed — CHIP-8 has no fixed clock; delay values matter per game

If you stick to plain CHIP-8 (not SuperChip / XO-CHIP extras), this emulator is enough.

### Practical starting path

1. Write a tiny program: clear screen, draw a digit, wait for a key.
2. Assemble → `.ch8` → run on your emulator.
3. Grow into piece movement, collision, line clear, scoring.

People don’t “export Tetris from Unity into `.ch8`” — they author CHIP-8 code (or use a CHIP-8-oriented tool) and assemble it. Building your own Tetris for this emulator is a normal, well-trodden project.
