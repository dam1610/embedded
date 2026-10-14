# Exercise 01 — control an 8-bit status register

**Goal:** implement set, clear, toggle and read operations while preserving every other bit. Allow about 20–30 minutes. No board or external libraries required.

## Start
Open `main.c` and complete its four TODO functions. The starter compiles, but its placeholders intentionally do not produce the expected output.

From this directory, on macOS (clang) or Linux (GCC):
```sh
cc -std=c11 -Wall -Wextra -Werror -pedantic main.c -o bit_demo
./bit_demo
./bit_demo > actual-output.txt
diff -u expected-output.txt actual-output.txt
```
An empty diff means the demo matches. Remove generated files with:
```sh
rm -f bit_demo actual-output.txt
```

## Requirements and hints
- Use `uint8_t` for the simulated 8-bit register.
- Bit positions range from 0 to 7, counted from the right.
- Build a mask with `1u << bit`, **after** checking the position.
- Set uses OR (`|`); clear uses AND (`&`) with a complemented mask (`~`); toggle uses XOR (`^`); read tests AND against zero.
- Invalid positions (8 or larger) leave the value unchanged; read returns false. Check before shifting to avoid undefined behavior.
- Cast the updated result to `uint8_t`. Integer promotions mean intermediate operations are wider than eight bits.

## Expected output
After completing the TODOs:
```text
Initial: 00000000 (0x00)
LED on: 00000001 (0x01)
Motor on: 00000101 (0x05)
Alarm toggled: 10000101 (0x85)
LED off: 10000100 (0x84)
Motor bit: 1
LED bit: 0
```

## Check your understanding
Try bit 0 and bit 7, setting an already-set bit, clearing an already-clear bit, and toggling the same bit twice. Try invalid positions 8 and 32: they must not change the register, and read must return false. Explain why OR turns on a selected bit without changing its neighbours.

## Short extension — undo with a stack
Add a four-entry `uint8_t history[4]` stack with a count:
1. Push the current status before each successful update.
2. If full, report "History full" and reject the update.
3. Pop to undo the most recent update; if empty, report "History empty" and leave status unchanged.
4. After the demo's four updates, undo twice. Expect `10000101 (0x85)`, then `00000101 (0x05)`.

Push stores a snapshot; pop restores it (last in, first out). This models undoing embedded configuration changes. Real peripheral registers may have special write rules, and shared register updates may need synchronization; this exercise only uses local RAM.
