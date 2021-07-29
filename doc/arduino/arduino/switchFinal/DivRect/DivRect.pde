

int numA = 10;
int numB = 6;
int scalar = 50;
numA *= scalar;
numB *= scalar;

int wd = numB;
int xPos = 0;
int yPos = 0;
int itr = 0;

size(500, 500);

while(wd > 0)
{
  itr++;
  if( itr % 2 == 1 )
  {
    while( xPos + wd <= numA )
    {
      rect( xPos, yPos, wd, wd );
      xPos += wd;
      
    }
    wd = numA - xPos;
  }else
  {
    while( yPos + wd <= numB )
    {
      rect( xPos, yPos, wd, wd );
      yPos += wd;
    }
    wd = numB - yPos;
  }
}
