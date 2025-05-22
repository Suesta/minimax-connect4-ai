# Minimax Connect 4 AI

Implementation of a Minimax-based AI agent for the Connect Four game, written in C.

## 🧠 Project Summary

This project features the full development of a decision-making agent for Connect Four. It includes a customizable decision tree with depth selection and a heuristic evaluation function tailored for gameplay strategy.

## ⚙️ Features

- Minimax algorithm with alternating max/min levels
- Custom heuristic scoring based on board state
- Depth selector (easy, medium, hard)
- Modular C implementation with header files
- Terminal-based board visualization

## 📁 Files

- `main.c`: Main execution file  
- `Connect-4.c/h`: Game logic and board management  
- `Minimax.c/h`: Minimax algorithm and tree generation  
- `Practica1 Minimax.*`: Code::Blocks project files

## 🕹️ How to Run

Use any C compiler or an IDE like Code::Blocks:
```bash
gcc -o connect4 main.c Connect-4.c Minimax.c -lm
./connect4
