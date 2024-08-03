How to use:

1. Open terminal
2.Navigate to Build Directory
3. cmake ..
4. make -j
5. ./jumpsturdy







University Project

1. Connect to Server  
1a. Start Game
2. Get FEN from Server 

3. Convert FEN to Board
3a. Check if game is over


4. Get legal moves from Board
5. Choose a move from legal moves 
6. Send move to Server 
7. Repeat from 2 until game is over
8. Close connection



Functions Required:

Main

Connect
- Connect to Server
- Start Game
- Receive FEN from Server 
- Send Fen to Server


Board
- Fen to Board 
- Board to Fen 
- Print Board
- Translate Move to Algebraic Notation 

Moves
- Check if Game is over 
- Update Board with Move
- Undo Move
- Get Legal Moves from Board 

AI
- Rate a Board
- AI to choose a Move
