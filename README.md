Wie fuehre ich das Programm aus?

1. Terminal oeffnen
2. In den build ordner navigieren
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


Other things TODO
- Benchmarks 
- Video
- Fen String Tests
- Performance-Measurements for Turn Generation



Functions Required:

Main


Connect
- Connect to Server (DONE)
- Start Game (DONE)
- Receive FEN from Server (DONE)
- Send Fen to Server (DONE)


Board
- Fen to Board (DONE)
- Board to Fen (DONE)
- Print Board (DONE)
- Translate Move to Algebraic Notation (DONE)

Moves
- Check if Game is over (DONE)
- Update Board with Move (DONE)
- Get Legal Moves from Board (DONE)

AI
- Rate a Board (DONE)
- AI to choose a Move (MiniMax) (TODO)





Next Steps:

- Negamax
- Iterative Deepening
- Imporve Evaluation Function
- Code Cleanup
- Add Comments
- Move order optimization
- Transposition Table
- Quiescence Search / Null Moves / Aspiration Windows
- Documentation
- Rate moves with a neural network
