#include <TVout.h>
#include <fontALL.h>

#define MAX 3
// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];
// board's dimension
int d = 3;
int tile;
int resolve[]={3,4,1,2,5,8,7,6,4,1,2,5,8,7,6,4,1,2,4,1,2,3,5,4,
7,6,1,2,3,7,4,8,6,4,8,5,7,8,5,6,4,5,6,7,8,6,5,4,7,8};
int resolver = 50;

// position of the empty place 
int empty_i ;
int empty_j ;
// creation of a TVout object
TVout TV;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

void setup()
{
    Serial.begin(9600);
    TV.begin(PAL, 120, 96);
    TV.select_font(font8x8ext);
    // greet player
    greet();
    
    empty_i = d - 1; // we initialize the position of blank case as bottom right corner of the board
    empty_j = d - 1;

    // initialize the board
    init(); 
}

void loop()
{        
        int iterator = 0;
        // clear the screen
        clear();

        // draw the current state of the board
        draw();
        // check for win
        if (won())
        {
            clear();
            TV.println("ftw!\n");
            TV.delay(5000);
            init();
        }

        // prompt for move
        TV.print("Tile to move: ");
        while(true)
        {
          if (Serial.available() > 0)
          {
            int ch = Serial.read();
            if ( ch != 'R' || ch != 'r' ) && ( )
            {
              tile = int(ch)-48;
              TV.print(tile);
              TV.delay(1000);
              break;
            }
            else if( ch == 'R' || ch == 'r' )
            {
              
            } 
          }
        }

        // move if possible, else report illegality
        if (!move(tile))
        {
            TV.print("\nIllegal move.\n");
            TV.delay(2000);
        }

        // sleep for animation's sake
        TV.delay(500);
}        

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    TV.clear_screen();
}

/**
 * Greets player.
 */
void greet(void)
{
    TV.println(30,40,"THIS IS\n");
    TV.println(40,50,"CS50\n");
    TV.delay(4000);
    clear();
    TV.println("GAME OF \nFIFTEEN\n");
    TV.println("In my Arduino\nUNO");
    TV.delay(4000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    // some initialization
    int val = d * d;         // dimantion of the board
    int control = (val % 2); // ferification of the number of case 
    
    for (int i = 0; i < d; i++) 
    {
        for (int j = 0; j < d; j++)
        {
            if (!control)     //if number of case is paires we swap 1 and 2 tilles
            {
                if (i == d-1 && j == d - 3)
                {
                    board[i][j] = 1 ;
                }
                else if (i == d-1 && j == d - 2)
                {
                    board[i][j] = 2 ;
                }
                else if (i == d-1 && j == d - 1)
                {
                    board[i][j] = d * d;
                }
                else
                {
                    board[i][j] = -- val;
                }
            }else  // else we initializad the board normally
            {
                if (i == d-1 && j == d - 1)
                {
                    board[i][j] = d * d; // d * d is the value of the empty space                    
                }
                else
                {
                    board[i][j] = -- val;
                }
            }
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    printf("\n");
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == d * d)
            {
                TV.print("_"); // a special charecter for the empty space
                TV.print(" ");
            }
            else
            {
                TV.print(board[i][j]);
                TV.print(" ");
            }
        }
        TV.print("\n\n");
    }
    
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // TODO
    for (int i = 0; i < d; i++ )
    {
        for ( int j = 0; j < d; j++ )
        {
            if (board[i][j] == tile)
            {
                if (j == empty_j && ((i == empty_i + 1) || (i == empty_i - 1)))
                {
                    board[i][j] = d * d;                // we put the special char in the title position
                    board[empty_i][empty_j] = tile;     // we put the tile in the position of empty place
                    
                    // the new index of the empty place
                    empty_i = i;
                    empty_j = j;
                    
                    return true;                
                }
                else if (i == empty_i && ((j == empty_j + 1) || (j == empty_j- 1)))
                {
                    board[i][j] = d * d;
                    board[empty_i][empty_j] = tile;
                    empty_i = i;
                    empty_j = j;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // we search in the board if one of the tiles are in a wrong place return false
    int val = 0; 
    
    for (int i = 0; i < d; i ++)
    {
        for (int j = 0; j < d; j ++)
        {
            val = ++ val;
            if (!(board[i][j] == val))
            {
                return false;
            }  
        }
    }
    return true;
}
