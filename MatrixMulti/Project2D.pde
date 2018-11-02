//The base for this project was found at: https://youtu.be/p4Iz0XJY-Qk
String filetoload = "coordiante2.txt"; //Change this to the file name you wish to load.

float angle = 0;

PVector[] points;

float[][] projection = {
  {1,0,0},
  {0,1,0},
  {0,0,0}
};


void settings()
{
  size(1000,1000);
}
void setup(){
  String[] filereader = loadStrings("Input\\"+filetoload);
  points = new PVector[(filereader.length/3)];
  int j = 0;
  for(int i = 0; i < points.length; i++){ //<>//
     points[i] = new PVector(float(filereader[j]), float(filereader[j+1]), float(filereader[j+2]));
  j=j+3;
  }
 
}

void draw()
{
  background(0);
  translate(width/2, height/2);
  stroke(255);
  strokeWeight(10);
  noFill();
  
  float[][] rotationZ = {
  {cos(angle),-sin(angle),0},
  {sin(angle),cos(angle),0},
  {0,0,1}
  };
  
  float[][] rotationX = {
  {1,0,0},
  {0,cos(angle),-sin(angle)},
  {0,sin(angle),cos(angle)}
  };
  
  float[][] rotationY = {
  {cos(angle),0, -sin(angle)},
  {0,1,0},
  {sin(angle),0,cos(angle)}
};

  
  for(PVector v: points)
  {
    PVector rotated = matmul(rotationX, v);
    rotated = matmul(rotationZ, rotated);
    rotated = matmul(rotationY, rotated);
    PVector projected2d = matmul(projection, rotated);
    projected2d.mult(2);
    point(projected2d.x, projected2d.y);
    //point(v.x, v.y);
  }
  
  angle += 0.01;
}
