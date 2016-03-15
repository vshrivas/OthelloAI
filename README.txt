Describe how and what each group member contributed for the past two weeks. 
If you are solo, these points will be part of the next section.

We both worked equally on each part of the code, writing the pseudocode and the
 actual code, and debugging. When writing the pseudocode, we came up with a strategy
 for our heuristic function and minmax algorithm and then implemented our design. We
 worked together for essentially the entire project, so we did not divide the project up 
into specific parts. 


Document the improvements that your group made to your AI to make it 
tournament-worthy. Explain why you think your strategy(s) will work. Feel free to 
discuss any ideas were tried but didn't work out.

Initially, we had implemented our minmax algorithm iteratively, so we changed our 
minmax algorithm to make it recursive, which allowed us to add more ply (initially, we 
were only using 1 ply). This made our player smarter, allowing it to beat Constant Time
 Player, because now it’s not looking for the best move in the short term, but for the 
best move in the long run instead. This strategy should work because we are anticipating 
future moves our opponent can make and taking our opponent’s intelligence into 
account before making our moves. We wanted to make our minmax algorithm faster by 
implementing a better design with a lower time complexity. We also wanted to improve 
our heuristic function to have weights for each position on the board, instead of just 
the corners and positions near the corners, to encourage moves which put our player 
in a more strategic position.
