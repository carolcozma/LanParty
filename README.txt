For the first requirement, I created a list for teams where each element in the list contains a list of players. I iterated through the file, filled the list of teams and players, and then displayed the resulting list.

For the second requirement, I searched for the top n teams with the highest score and eliminated the teams with the lowest score (total number of teams minus n teams). I removed the teams one by one, searching for the team with the lowest score in each iteration until reaching n remaining teams.

For the third requirement, I created a function called "tournament" that takes the "team_queue" queue with matches. Inside a "while" loop until the number of teams equals 1, I used the "matches" function to select the teams and the "select_winner" function to choose the winner of each match. I also created two separate stacks for losers and winners. When the number of teams reaches 8, I copied the contents of the current match queue into a list.

For the fourth requirement, I created the "createBST" function that builds a binary search tree using the list created in requirement 3. I traversed the tree in order to display the teams in ascending order.

For the fifth requirement, I created the "createAVL" function that should create a balanced AVL tree.
