#include <iostream>

using namespace std;

const int FIELD_SIZE=3;
const int MOVES_LEFT=3;
const int X_MOVES=3;
const int O_MOVES=2;
const int MOVES[X_MOVES*O_MOVES*MOVES]={1, 2, 3, 1, 3, 2, 2, 1, 3, 2, 3, 1,
                                        3, 1, 2, 3, 2, 1};
const char NOT_FINISHED='#';
const char DRAW='D';
const char OUTHS_WIN='O';
const char CROSSES_WIN='X';

char check_field(char *field,int moves_left)
{
  int i;
  for(i=0;i<FIELD_SIZE;i++)
  {
    if ((*(field + i * FIELD_SIZE) == *(field + i * FIELD_SIZE + 1)) && (*(field + i *
      FIELD_SIZE) == *(field + i * FIELD_SIZE + 2)))
        return *(field + i * FIELD_SIZE);
    if ((*(field + i) == *(field + FIELD_SIZE + i)) && (*(field + i) == *(field + 2 *
      FIELD_SIZE + i)))
        return *(field + i);
  }
  if ((*(field) == *(field + FIELD_SIZE + 1)) && (*(field) == *(field + 2 * FIELD_SIZE + 2)))
      return *(field);
  if ((*(field + 2) == *(field + FIELD_SIZE + 1)) && (*(field + 2) == *(field + 2 *
    FIELD_SIZE)))
      return *(field + 2);
  if (moves_left)
    return NOT_FINISHED;
  return DRAW;
}

int main()
{
  char *field,c,moves_count=0,finish,finish2;
  char moves_x[MOVES_LEFT],moves_y[MOVES_LEFT];
  field=new char[FIELD_SIZE*FIELD_SIZE];
  for(int i=0;i<FIELD_SIZE;i++)
  {
    for(int j=0;j<FIELD_SIZE;j++)
    {
      cin.get(c);
        field[i*FIELD_SIZE+j]
    }
    scanf("%3s\n", c);
    for (j = 0; j < FIELD_SIZE; j++)
    {
      *(field + i * FIELD_SIZE + j) = *(c + j);
      if (*(c + j) == '#')
      {
        *(moves_x + moves_count) = j;
        *(moves_y + moves_count++) = i;
      }
    }
  }
  finish = check_field(field, 3);
  if (finish == OUTHS_WIN)
  {
    printf("Ouths win\n");
    return 0;
  }
  if (finish == CROSSES_WIN)
  {
    printf("Crosses win\n");
    return 0;
  }
  finish = OUTHS_WIN;
  for (i = 0; i < POSSIBLE_X_MOVES; i++)
  {
    *(field + (*(moves_y + *(POSSIBLE_MOVES + i * POSSIBLE_O_MOVES * MOVES_LEFT) - 1)) *
      FIELD_SIZE + *(moves_x + *(POSSIBLE_MOVES + i * POSSIBLE_O_MOVES * MOVES_LEFT) - 1)) =
      'X';
    if (check_field(field, 2) == CROSSES_WIN)
    {
      printf("Crosses win\n");
      return 0;
    }
    finish2 = CROSSES_WIN;
    for (j = 0; j < POSSIBLE_O_MOVES; j++)
    {
      *(field + (*(moves_y + *(POSSIBLE_MOVES + (i * POSSIBLE_O_MOVES + j) * MOVES_LEFT + 1) -
        1)) * FIELD_SIZE + *(moves_x + *(POSSIBLE_MOVES + (i * POSSIBLE_O_MOVES + j) *
        MOVES_LEFT + 1) - 1)) = 'O';
      if (check_field(field, 1) == OUTHS_WIN)
      {
        finish2 = OUTHS_WIN;
        *(field + (*(moves_y + *(POSSIBLE_MOVES + (i * POSSIBLE_O_MOVES + j) * MOVES_LEFT + 1) -
          1)) * FIELD_SIZE + *(moves_x + *(POSSIBLE_MOVES + (i * POSSIBLE_O_MOVES + j) *
          MOVES_LEFT + 1) - 1)) = '#';
        break;
      }
      *(field + (*(moves_y + *(POSSIBLE_MOVES + (i * POSSIBLE_O_MOVES + j) * MOVES_LEFT + 2) -
        1)) * FIELD_SIZE + *(moves_x + *(POSSIBLE_MOVES + (i * POSSIBLE_O_MOVES + j) *
        MOVES_LEFT + 2) - 1)) = 'X';
      if (check_field(field, 0) == DRAW)
        finish2 = DRAW;
      *(field + (*(moves_y + *(POSSIBLE_MOVES + (i * POSSIBLE_O_MOVES + j) * MOVES_LEFT + 2) -
        1)) * FIELD_SIZE + *(moves_x + *(POSSIBLE_MOVES + (i * POSSIBLE_O_MOVES + j) *
        MOVES_LEFT + 2) - 1)) = '#';
      *(field + (*(moves_y + *(POSSIBLE_MOVES + (i * POSSIBLE_O_MOVES + j) * MOVES_LEFT + 1) -
        1)) * FIELD_SIZE + *(moves_x + *(POSSIBLE_MOVES + (i * POSSIBLE_O_MOVES + j) *
        MOVES_LEFT + 1) - 1)) = '#';
    }
    if (finish2 == DRAW)
      finish = DRAW;
    if (finish2 == CROSSES_WIN)
    {
      finish = CROSSES_WIN;
      break;
    }
    *(field + (*(moves_y + *(POSSIBLE_MOVES + i * POSSIBLE_O_MOVES * MOVES_LEFT) - 1)) *
      FIELD_SIZE + *(moves_x + *(POSSIBLE_MOVES + i * POSSIBLE_O_MOVES * MOVES_LEFT) - 1)) =
      '#';
  }
  if (finish == OUTHS_WIN)
    printf("Ouths win\n");
  if (finish == CROSSES_WIN)
    printf("Crosses win\n");
  if (finish == DRAW)
    printf("Draw\n");
}