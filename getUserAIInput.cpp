/*
 * @brief AI that will be the second player in a game mode with another user or computer (1P or 0P)
 * 
 * @param [inout] board - 2D array of board values
 * @param [in] ydim - number of rows
 * @param [in] xdim - number of columns
 * @param [out] y - pointer to an integer that should be set with the chosen row 
 * @param [out] x - pointer to an integer that should be set with the chosen column
 * @param [in] currentPlayer - 0 = red, 1 = yellow
 * @return true If there is an error (i.e. no possible place to play exists)
 * @return false If a location was succesfully chosen.
 */

bool getUserAIInput(
  BoardValue** board, 
  int ydim, int xdim, 
  int *y, int *x,
  int currentPlayer)
{
  
  bool chosen = false;
  int otherPlayer;
  if(currentPlayer == 0){
    otherPlayer = 1;
  }
  else{
    otherPlayer = 0;
  }

  //if either player is about to win, place the piece there
  for(int i = 0; i < ydim; i++){
    for(int j = 0; j < xdim; j++){
      if(hasWon(board, ydim, xdim, i, j, otherPlayer) || hasWon(board, ydim, xdim, i, j, currentPlayer)){
        chosen = true;
        *x = j;
        *y = findYValue(board, ydim, *x);
        board[*y][*x] = playerToValue[currentPlayer];
        break;
      }
    }
    if(chosen){
      break;
    }
  }

  //if nothing has been chosen, place in the next open spot
  if(!chosen){
    for(int i = 0; i < ydim; i++){
      for(int j = 0; j < xdim; j++){
        if(board[i][j] == BLANK){
          *x = j;
          *y = findYValue(board, ydim, *x);
          board[*y][*x] = playerToValue[currentPlayer];
          chosen = true;
          break;
        }
      }
      if(chosen == true){
        break;
      }
    }
  }

  return false;

}
