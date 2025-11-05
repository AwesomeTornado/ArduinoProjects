/*
 * rover requirements:
 *  can map the space around it
 *  has dynamic memory for mapping?
 *  is consistent
 *
 *when we take the time ping returneedd we need to convert it into distance
 *
 * 
 * we can measure positions ans store them as an XY cooradanate pair for a location that contains a solid object. the hard part now is finding them.
 * the locations of the obsticals will be stored in two bytes, one for x and one for y. the scale and method for the cooradnates will be as follows
 *  the origin is wherever the rover starts.
 *  when we find an obsticle we store the location.
 *    the grid the cooradanates are on has 5cm in between grid lines
 *  
 * 
 * -32,768 to 32,767
 */
 short* obstacles;
 short* orientationMap;

int GetDistance(){
  
}

void updateMap(short distance, short rotation, short xLocation, short yLocation){
  
 short yDistance = sin(rotation)*distance;
 short xDistance = cos(rotation)*distance;
 yDistance = yDistance + yLocation;
 xDistance = xDistance + xLocation;
 obstacles = (short*) realloc(obstacles, (sizeof(obstacles)/2 + 1) * sizeof(short));
 
}

void StarPathfind(){
  
}

void compareLocations(short* xLocation, short* yLocation){

int mainMapSize = sizeof(obstacles);
int otherMapSize = sizeof(orientationMap);

for(int i = ; i > 0; i = i - 1){
  for(int x = otherMapSize; x > 0; x = x - 1){
    
  }
}
  
}


void setup() {
 obstacles = new short[1];
 orientationMap = new short[1];
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:

}
